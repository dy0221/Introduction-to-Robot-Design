// 《 상보필터를 적용한 Roll과 Pitch, Yaw의 각도 구하기 실습  》
/* 아래 코드관련 실습에 대한 설명과 회로도 및 자료는 https://rasino.tistory.com/ 에 있습니다    */

#include<Wire.h>
#include<Servo.h>

Servo s1, s2, s3, s4;
const int MPU_ADDR = 0x68;    // I2C통신을 위한 MPU6050의 주소
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;   // 가속도(Acceleration)와 자이로(Gyro)
double angleAcX, angleAcY, angleAcZ;
double angleGyX, angleGyY, angleGyZ;
double angleFiX, angleFiY, angleFiZ;
int16_t initAcX, initAcY, initAcZ, initTmp, initGyX, initGyY, initGyZ;
double initangleFiX, initangleFiY, initangleFiZ;
const double RADIAN_TO_DEGREE = 180 / 3.14159;
const double DEG_PER_SEC = 32767 / 250;    // 1초에 회전하는 각도
const double ALPHA = 1 / (1 + 0.04);
// GyX, GyY, GyZ 값의 범위 : -32768 ~ +32767 (16비트 정수범위)


unsigned long now = 0;   // 현재 시간 저장용 변수
unsigned long past = 0;  // 이전 시간 저장용 변수
double dt = 0;           // 한 사이클 동안 걸린 시간 변수

double averAcX, averAcY, averAcZ;
double averGyX, averGyY, averGyZ;
//pid
//P0.5 I0.007 D0.005    W0.4E0.07R0.01
//P0.2 I0.007 D0.005    W0.4E0.07R0.01
float db = 0.5;
float KpX = 0.25;                                                                           //Gain setting for the P-controller ()
float KiX = 0.0002;                                                                        //Gain setting for the I-controller ()
float KdX = 0.0001;

float KpY = 0.27;                                                                           //Gain setting for the P-controller ()
float KiY = 0.0002;                                                                        //Gain setting for the I-controller ()
float KdY = 0.0001;

float P_x, I_x, D_x;                                                                    //PID substitudes x-axis
float P_y, I_y, D_y;                                                                    //PID substitudes y-axis
float s_y, e_y, e_sum_y, e_old_y, y;

float x_ang         = 0;
float x_ref_ang     = 0;
float x_err_ang     = 0;
float x_err_ang_k_1 = 0;
float x_derr_ang    = 0;
float x_err_sum     = 0;

float y_ang         = 0;
float y_ref_ang     = 0;
float y_err_ang     = 0;
float y_err_ang_k_1 = 0;
float y_derr_ang    = 0;
float y_err_sum     = 0;

float ctrX_up = 0;
float ctrX_ui = 0;
float ctrX_ud = 0;
int ctrX_u = 0;

float ctrY_up = 0;
float ctrY_ui = 0;
float ctrY_ud = 0;
int ctrY_u = 0;

int output1, output2, output3, output4;                                                 //PID-Outputs for all 4 Servos
int output1_b, output2_b, output3_b, output4_b;                                         //MAP corrected outputs due to non-linear behavior of the system

int w1, w2, w3, w4;
//motor
float i_lim = 50;

const int pin_s1 = 6;                                                                         //Arduino PWM Pin for Servo1(S1)
const int pin_s2 = 7;                                                                         //Arduino PWM Pin for Servo2(S2)
const int pin_s3 = 8;                                                                         //Arduino PWM Pin for Servo3(S3)
const int pin_s4 = 9;
//1500 >> 90도 1000>> 45도 2000>> 135도
const int s1_max = 1350;                                                                      //Max. angle for S1
const int s2_max = 1450;                                                                      //Max. angle for S2
const int s3_max = 1450;                                                                      //Max. angle for S3
const int s4_max = 1450;                                                                      //Max. angle for S4

const int s1_mid = 970;                                                                      //Norm. angle for S1
const int s2_mid = 1010;                                                                      //Norm. angle for S2
const int s3_mid = 1020;                                                                      //Norm. angle for S3
const int s4_mid = 1050;                                                                     //Norm. angle for S4

//const int s1_mid = 1000;
//const int s2_mid = 1000;
//const int s3_mid = 1000;
//const int s4_mid = 1000;

const int s1_min = 400;                                                                      //Min. angle for S1
const int s2_min = 500;                                                                      //Min. angle for S2
const int s3_min = 500;                                                                      //Min. angle for S3
const int s4_min = 500;
//timer
int loopo = 0;
char sec;
unsigned long preMillis = 0;
double angleTmpX = 0;
double angleTmpY = 0;
double angleTmpZ = 0;
bool chkX = 0;
bool chkY = 0;
void setup() {
  //초기 오차
  initangleFiX = 0;
  initangleFiY = 0;
  initAcX = 1500;
  initAcY = -900;
  initAcZ = 600;
  initGyX = 600;
  initGyY = -200;
  initGyZ = -200;
  //  initAcX = 0;
  //  initAcY = 0;
  //  initGyX = 0;
  //  initGyY = 0;
  //  initGyZ = 0;
  initSensor();
  Serial.begin(115200);
  caliSensor();   //  초기 센서 캘리브레이션 함수 호출

  s1.attach(pin_s1);                                                                    //Attach S1
  s2.attach(pin_s2);                                                                    //Attach S2
  s3.attach(pin_s3);                                                                    //Attach S3
  s4.attach(pin_s4);                                                                    //Attach S4
  //중간값 설정
  s1.writeMicroseconds(s1_mid);                                                         //Go to the Norm. position after init
  s2.writeMicroseconds(s2_mid);
  s3.writeMicroseconds(s3_mid);
  s4.writeMicroseconds(s4_mid);
  //  s1.writeMicroseconds(s1_max);                                                         //Go to the Norm. position after init
  //  s2.writeMicroseconds(s2_max);
  //  s3.writeMicroseconds(s3_max);
  //  s4.writeMicroseconds(s4_max);
  delay(5000);
  w1 =  s1_mid;                                                                          //Save positions to w1,w2,w3,w4 variables
  w2 = s2_mid;
  w3 = s3_mid;
  w4 = s4_mid;
  Serial.println("start");

  past = millis(); // past에 현재 시간 저장

}

void loop() {
  getData();
  getDT();

  angleAcX = atan(AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2)));
  angleAcX *= RADIAN_TO_DEGREE;
  angleAcY = atan(-AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2)));
  angleAcY *= RADIAN_TO_DEGREE;
  // 가속도 센서로는 Z축 회전각 계산 불가함.

  // 가속도 현재 값에서 초기평균값을 빼서 센서값에 대한 보정
  angleGyX += ((GyX - averGyX) / DEG_PER_SEC) * dt;  //각속도로 변환
  angleGyY += ((GyY - averGyY) / DEG_PER_SEC) * dt;
  angleGyZ += ((GyZ - averGyZ) / DEG_PER_SEC) * dt;

  // 상보필터 처리를 위한 임시각도 저장
  angleTmpX = angleFiX + angleGyX * dt;
  angleTmpY = angleFiY + angleGyY * dt;
  angleTmpZ = angleFiZ + angleGyZ * dt;

  // (상보필터 값 처리) 임시 각도에 0.96가속도 센서로 얻어진 각도 0.04의 비중을 두어 현재 각도를 구함.
  angleFiX = ALPHA * angleTmpX + (1.0 - ALPHA) * angleAcX;
  angleFiY = ALPHA * angleTmpY + (1.0 - ALPHA) * angleAcY;
//  angleFiX = angleFiX - initangleFiX;
//  angleFiY = angleFiY - initangleFiY;
  //    printData();
  //  printRawData();
  //  chkG();
  
  //x양수 y양수
    if (AcX > 2000 && AcY > 2000 ) {
      x_ref_ang = -20;
      y_ref_ang = 20;
      
      //x양수 y0
    } else if (AcX > 2000 && (AcY <= 2000 && AcY >= -2000) ) {
      x_ref_ang = 0;
      y_ref_ang = 20;
      //x0 y양수
    } else if ((AcX <= 2000 && AcX >= -2000) && AcY > 2000 ) {
      x_ref_ang = -20;
      y_ref_ang = 0;
      
      //x양수 y음수
    } else if (AcX > 2000 && AcY < -2000 ) {
      x_ref_ang = 20;
      y_ref_ang = 20;
      
      //x음수 y양수
    } else if (AcX < -2000 && AcY > 2000) {
      x_ref_ang = -20;
      y_ref_ang = -20;
      //x음수 y음수
    } else if (AcX < -2000 && AcY < -2000 ) {
      x_ref_ang = 20;
      y_ref_ang = -20;
      //x0 y음수
    } else if ((AcX >= -2000 && AcX <= 2000) && AcY < -2000 ) {
      x_ref_ang = 20;
      y_ref_ang = 0;
      //x음수 y0
    } else if (AcX < -2000 && (AcY >= -2000 && AcY <= 2000) ) {
      x_ref_ang = 0;
      y_ref_ang = -20;
      //x0 y0
    } else {
      x_ref_ang = 0;
      y_ref_ang = 0;
    }

    if ( (AcX < -700 && AcX > -2000)||(AcX> 700 && AcX <2000)) x_ref_ang = -1 * angleAcX;
    if ( (AcY < -700 && AcY > -2000)||(AcY> 700 && AcY <2000)) y_ref_ang = -1 * angleAcY;
  //pid
  x_ang = angleFiX;
  y_ang = angleFiY;
  //Error
  x_err_ang     = x_ref_ang - x_ang;
  x_derr_ang    = (x_err_ang - x_err_ang_k_1) / dt;
  x_err_sum     = x_err_sum + (x_err_ang * dt);
  x_err_ang_k_1 = x_err_ang;

  //PID-Controller
  ctrX_up = KpX * x_err_ang;
  ctrX_ui = KiX * x_err_sum;
  ctrX_ud = KdX * x_derr_ang;
  ctrX_u = (int)(ctrX_up + ctrX_ud + ctrX_ui);

  //Error
  y_err_ang     = y_ref_ang - y_ang;
  y_derr_ang    = (y_err_ang - y_err_ang_k_1) / dt;
  y_err_sum     = y_err_sum + (y_err_ang * dt);
  y_err_ang_k_1 = y_err_ang;

  //PID-Controller
  ctrY_up = KpY * y_err_ang;
  ctrY_ui = KiY * y_err_sum;
  ctrY_ud = KdY * y_derr_ang;

  ctrY_u = (int)(ctrY_up + ctrY_ud + ctrY_ui);

  output1 = (int)(w1 + ctrX_u );                                                                    //Adding the controller correction part to the output
  output2 = (int)(w2 - ctrY_u) ;
  output3 = (int)(w3 - ctrX_u );
  output4 = (int)(w4 + ctrY_u);

  // check limit
  if (output2 > s2_max) {                                                             //Make sure that the servos are only operating within the defined ranges
    output2 = s2_max;
  }
  if (output2 < s2_min) {
    output2 = s2_min;
  }
  if (output4 > s4_max) {
    output4 = s4_max;
  }
  if (output4 < s4_min) {
    output4 = s4_min;
  }
  if (output1 > s1_max) {
    output1 = s1_max;
  }
  if (output1 < s1_min) {
    output1 = s1_min;
  }
  if (output3 > s3_max) {
    output3 = s3_max;
  }
  if (output3 < s3_min) {
    output3 = s3_min;
  }

  if (output1 != output1_b) {                                                         //Servos starts to shaking if you spam the output with the same information the whole time. This section avoids to spam the servos.
    s1.writeMicroseconds(int(output1));
    w1 = int(output1);
  }

  if (output2 != output2_b) {
    s2.writeMicroseconds(int(output2));
    w2 = int(output2);
  }

  if (output3 != output3_b) {
    s3.writeMicroseconds(int(output3));
    w3 = int(output3);
  }

  if (output4 != output4_b) {
    s4.writeMicroseconds(int(output4));
    w4 = int(output4);
  }

  output1_b = output1;                                                                  //Save the old values to caompare them in the next loop
  output2_b = output2;
  output3_b = output3;
  output4_b = output4;
    Serial.print("x_ref");
    Serial.print(x_ref_ang);
    Serial.print(",");
    Serial.print("x");
    Serial.print(x_ang);
    Serial.print(",");
    Serial.print("y_ref");
    Serial.print(y_ref_ang);
    Serial.print(",");
    Serial.print("y");
    Serial.println(y_ang);
}
void initSensor() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);   // I2C 통신용 어드레스(주소)
  Wire.write(0x6B);    // MPU6050과 통신을 시작하기 위해서는 0x6B번지에
  Wire.write(0);
  Wire.endTransmission(true);
}
void printRawData() {
  //  Serial.print("AcX:");
  //  Serial.print(AcX);
  //  Serial.print("\t          AcY:");
  Serial.print(AcY);
  //  Serial.print("\t          AcZ:");
  //  Serial.print(AcZ);
  //  Serial.print("\t          GyX:");
  //  Serial.print(GyX);
  //  Serial.print("\t          GyY:");
  //  Serial.print(GyY);
  //  Serial.print("\t          GyZ:");
  //  Serial.print(GyZ);
  Serial.println();
  //  delay(300);
}
void printData() {
  //      Serial.print("AngleAcX:");
  //  Serial.print(angleAcX);
  //  Serial.print(",");
  Serial.print("\t FilteredX:");
  Serial.print(angleFiX);
  //      Serial.print("\t AngleAcY:");
  //      Serial.print(angleAcY);
  Serial.print("\t FilteredY:");
  Serial.println(angleFiY);
  //    Serial.print("\t AngleGyZ:");
  //    Serial.print(angleGyZ);
  //    Serial.print("\t FilteredZ:");
  //    Serial.print(angleFiZ);
  //
  //      Serial.print("     Angle Gyro X:");
  //      Serial.print(angleGyX);
  //      Serial.print("\t\t Angle Gyro y:");
  //      Serial.println(angleGyY);
  //    Serial.print("\t\t Angle Gyro Z:");
  //    Serial.println(angleGyZ);

  //  Serial.print("angleTmpX:");
  //  Serial.print(angleTmpX);
  //  Serial.print("\t angleTmpY:");
  //  Serial.print(angleTmpY);
  //  Serial.print("\t angleTmpZ:");
  //  Serial.println(angleTmpZ);
  delay(20);
}
void getData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);   // AcX 레지스터 위치(주소)를 지칭합니다
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);  // AcX 주소 이후의 14byte의 데이터를 요청
  AcX = Wire.read() << 8 | Wire.read(); //두 개의 나뉘어진 바이트를 하나로 이어 붙여서 각 변수에 저장
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
  AcX = AcX - initAcX;
  AcY = AcY - initAcY;
  AcZ = AcZ - initAcZ;
  GyX = GyX - initGyX;
  GyY = GyY - initGyY;
  GyZ = GyZ - initGyZ;
}

// loop 한 사이클동안 걸리는 시간을 알기위한 함수
void getDT() {
  now = millis();
  dt = (now - past) / 1000.0;
  past = now;
}
void chkG() {
  if ((int)angleFiX < x_ref_ang + db && (int)angleFiX > x_ref_ang - db) {
    chkX = 1;
  } else {
    chkX = 0;
  }
  //
  if ((int)angleFiY < y_ref_ang + db && (int)angleFiY > y_ref_ang - db) {
    chkY = 1;
  } else {
    chkY = 0;
  }
}
// 센서의 초기값을 10회 정도 평균값으로 구하여 저장하는 함수
void caliSensor() {
  double sumAcX = 0 , sumAcY = 0, sumAcZ = 0;
  double sumGyX = 0 , sumGyY = 0, sumGyZ = 0;
  getData();
  for (int i = 0; i < 10; i++) {
    getData();
    sumAcX += AcX;  sumAcY += AcY;  sumAcZ += AcZ;
    sumGyX += GyX;  sumGyY += GyY;  sumGyZ += GyZ;
    delay(50);
  }
  averAcX = sumAcX / 10;  averAcY = sumAcY / 10;  averAcZ = sumAcY / 10;
  averGyX = sumGyX / 10;  averGyY = sumGyY / 10;  averGyZ = sumGyZ / 10;
}
