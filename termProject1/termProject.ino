
#define TRIG_f 2
#define ECHO_f 3
#define TRIG_l 4
#define ECHO_l 5
#define TRIG_r 6
#define ECHO_r 7
#define TRIG_ll 8
#define ECHO_ll 9
#define TRIG_rr 10
#define ECHO_rr 11

#include <TimerFive.h>
#include<Wire.h>
#include <Adafruit_TCS34725.h>
#include <Pixy2SPI_SS.h>
Pixy2SPI_SS pixy;

#define delay_time 400
#define bar_delay 5000

//bluetooth
char u2_rcv_data;
int bt_index = 0;
bool bt_flag = 0;

//line을 받아서 계산할 변수
double slope;
int8_t left_x0, left_x1, left_y0, left_y1 = -1;
double left_slope, right_slope, left_angle, right_angle = 0;
int8_t right_x0, right_x1, right_y0, right_y1 = -1;

//line flag
bool barcode_flag = 0;
bool left_flag = 0;
bool right_flag = 0;

//rgb flag
bool rgb_flag = 0;
bool t5_flag = 0;
uint16_t clear, red, green, blue;

bool mode1_flag = 1;
int mode_index = 0;             //선을 감지하고 움직이는 메인 함수에 쓰이는 index
int linetrace_index = 0;
int barcode_index = -1;
int barcode_count = 0;
int mode2_index = 0;            //rgb  감지했을 때 사용하는 index
int long_delay = 850;
int short_delay = 950;          //delay를 주기 위한 수치
unsigned long pre_millis = 0;   //움직일 떄 사용하는 millis
unsigned long bar_millis = 0;   //바코드에 사용하는 millis
unsigned long rgb_millis = 0;

//speed to motor
int m1_ref_speed = 0;
int m2_ref_speed = 0;

//for motor UART
byte tx_data[7];
byte checksum = 0;

// Serial Receiver Parameter
bool rcv_status = 0;
bool rcv_ready = 0;
byte rcv_data = 0;
byte rcv_checksum = 0;
byte rx_buffer[7];
byte rx_data[7];
int rcv_count = 0;
int rcv_index = 0;
bool rcv_stauts = 0;

// Motor Degree Parameter
int m1_angle = 0;
int m2_angle = 0;
bool m1_sign = 0;
bool m2_sign = 0;



// Odometry Parameter
float L = 17;
float Wheel_R = 3.2;
float theta_1 = 0.0;
float theta_2 = 0.0 ;
float S_R = 0.0;
float S = 0.0;
float S_L = 0.0;
float S_R1 = 0.0;
float S_L1 = 0.0;
float S_R2 = 0.0;
float S_L2 = 0.0;
float theta = 0.0;
float x1 = 0.0;
float y1 = 0.0;
float dtheta = 0.0;
float deltaS = 0.0;
float deltaSR = 0.0;
float deltaSL = 0.0;
float current_theta = 0.0;
int mod = 0;
int save_R = 0;
int save_L = 0;

float current_x = 0.0;
float current_y = 0.0;

//turn 함수
int turnRight_count = 0;
int turnLeft_count = 0;
float pre_theta = 0;
float reference_theta = 0;
bool turn_l_flag = 0;
bool turn_r_flag = 0;

//초음파
double distance1 = 0, distance2 = 0, distance3 = 0, distance4 = 0, distance5 = 0;
bool front_ultra_flag = 0;
bool right_ultra_flag = 0;
bool left_ultra_flag = 0;
bool side_right_ultra_flag = 0;
bool side_left_ultra_flag = 0;
double distance = 0;
double duration = 0;


bool mode3_flag = 0;
bool mode2_t5_flag = 0;
bool balance_flag = 0;               //보정을 하기위한 flag
unsigned long odometry_millis = 0;
int  t5_index = 0;
int mode3_index = 0;                 //rgb끝나고 오도메트리 전까지 사용할 index
bool mode4_flag = 0;                 //오도메트리를 시작할  flag
int mode4_index = 0;

int turn_left_count = 0;
int turn_right_count = 0;
bool pre_right_flag = 0;
bool pre_left_flag = 0;
bool move_priority = 0;
bool x_finish = 0;
bool y_finish = 0;
int y_first_count = 0;
int x_first_count = 0;


// TCS34725 라이브러리 사용을 위한 객체 생성
Adafruit_TCS34725 TCS = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_16X);
void setup() {
  Serial.begin(115200);
  Serial1.begin(250000);//motor
  Serial.print("Starting...\n");
  Serial3.begin(9600);
  pinMode(12, OUTPUT);
  digitalWrite(12, 1);
  tx_data[0] = 0xFF; //Header 1
  tx_data[1] = 0xFF; //Header
  // we need to initialize the pixy object
  pixy.init();
  // Change to line tracking program
  pixy.changeProg("line");
  pixy.setLamp(1, 255);
  //Timer5 setup (rgb)
  Timer5.initialize(250000);       //50000 = 50msec
  Timer5.attachInterrupt(T5ISR);  //T5ISR


  pinMode(TRIG_f, OUTPUT);
  pinMode(ECHO_f, INPUT);
  pinMode(TRIG_l, OUTPUT);
  pinMode(ECHO_l, INPUT);
  pinMode(TRIG_r, OUTPUT);
  pinMode(ECHO_r, INPUT);
  pinMode(TRIG_rr, OUTPUT);
  pinMode(ECHO_rr, INPUT);
  pinMode(TRIG_ll, OUTPUT);
  pinMode(ECHO_ll, INPUT);
}

void loop() {
  if (rcv_stauts) {
    rcv_stauts = 0;
    memcpy((char*)&m1_angle, (char*)rx_data, 2);
    memcpy((char*)&m2_angle, (char*)&rx_data[2], 2);

    if (rx_data[4] == 0x00)  m1_sign = true;  // CW
    else                    m1_sign = false;  // CCW
    if (rx_data[5] == 0x00)  m2_sign = true;  // CW
    else                    m2_sign = false;  // CCW

    if (m1_sign) m1_angle = m1_angle * (-1);
    if (m2_sign) m2_angle = m2_angle * (-1);
    odometry();
  }
  //bluetooth
  if (Serial3.available() && bt_flag == 0) {
    u2_rcv_data = Serial3.read();
    if (u2_rcv_data == '1')       bt_index = 1;
    else if (u2_rcv_data == '2')      bt_index = 2;
    else if (u2_rcv_data == '3')     bt_index = 3;
    else if (u2_rcv_data == '4') bt_flag = 1;


  }

  //----start--------------------------------------------------------------------------------------------
  if (bt_flag) {
    if (mode3_flag) {
      //----parking1------------------------------------------------------------------------------------------------
      if (bt_index == 1) {
        switch (mode3_index) {
          //살짝 앞으로 오기
          case 0:
            sendmotor(30, 30);
            if (x1 > 22) {
              mode3_index = 2;
            }
            break;
          //수평 직진
          case 1:
            sendmotor(30, 30);
            if (y1 > 85) {
              mode3_index = 3;
            }
            break;
          //살짝 앞으로 가고 오른쪽으로 90도 돌기
          case 2:
            if (turn_r_flag) {
              turn_r_flag = 0;
              mode3_index = 1;
            }else turn_R(85, 10);
            break;
          //수평 직진후 왼쪽 90도 회전
          case 3:
          if (turn_l_flag) {
              turn_l_flag = 0;
              mode3_flag = 0;
              mode4_flag = 1;
              //Timer5 setup (shedulling)
              Timer5.initialize(20000);       //50000 = 50msec
              Timer5.attachInterrupt(T5_MODE2_ISR);  //ISR
              Timer5.start();
              //돌았던 횟수 혹시 모르니 초기화
              turn_left_count = 0;
              turn_right_count = 0;
            }else turn_L(87, 10);
            
          default:
            break;
        }
        //-----parking 2, 3----------------------------------------------------------------------------------------
      } else if (bt_index == 2 || bt_index == 3) {
        switch (mode3_index) {
          //수직 전진
          case 0:
            sendmotor(30, 30);
            if (x1 > 110) {   // x축 100cm 전진 후 case 1
              mode3_index = 1;
            }
            break;
          //수직 전진후 오른쪽으로 돌기
          case 1:
            turn_R(85, 10); // 오른쪽 90도 회전 후 오도메트리 알고리즘 ㄱㄱ
            if (turn_r_flag) {
              turn_r_flag = 0;
              mode3_flag = 0;
              mode4_flag = 1;
              current_theta = 90;
              Timer5.initialize(20000);       //50000 = 50msec
              Timer5.attachInterrupt(T5_MODE2_ISR);  //ISR
              Timer5.start();
              turn_left_count = 0;
              turn_right_count = 0;
            }
            break;
          default:
            break;
        }
      }
    }
    //--오도메트리 알고리즘------------------------------------------------------------------------------------
    if (mode4_flag) {
      //----parking 1----------------------------------------------------------------------------------------
      if (bt_index == 1) {
        switch (mode4_index) {
          //초음파 && 직진 알고리즘
          case 0:
            scheduling1();
            break;
          //왼쪽 턴
          case 1:
            turn_L(86, 10);
            if (turn_l_flag) {
              turn_left_count++;
              mode4_index = 0;
              turn_l_flag = 0;
              //우선순위 주기
              move_priority = 1;
              odometry_millis = millis();
            }
            break;
          //오른쪽 턴
          case 2:
            turn_R(86, 10);
            if (turn_r_flag) {
              turn_right_count++;
              mode4_index = 0;
              turn_r_flag = 0;
              odometry_millis = millis();
            }
            break;
          //0도로 보정하기
          case 3:
            if (current_theta > -4 + 0.5) sendmotor(-10, 10);
            else if (current_theta < -4 - 0.5) sendmotor(10, -10);
            else {
              mode4_index = 0;
              balance_flag = 0;
            }
            break;
          //y시작전 -90보정
          case 4:
            if (current_theta < -90 - 0.5) sendmotor(10, -10);
            else if (current_theta > -90 + 0.5) sendmotor(-10, 10);
            else {
              mode4_index = 0;
              y_first_count = 2;
            }
            break;
          case 5:
            if (current_theta < -88 - 0.5) sendmotor(10, -10);
            else if (current_theta > -88 + 0.5) sendmotor(-10, 10);
            else  {
              mode4_index = 0;
              balance_flag = 0;
            }
            break;
        }
        //--------parking2-------------------------------------------------------------------------------------
      } else if (bt_index == 2) {
        switch (mode4_index) {
          //초음파 && 직진 알고리즘
          case 0:
            scheduling2();
            break;
          //왼쪽 턴
          case 1:
            turn_L(90, 10);
            if (turn_l_flag) {
              turn_left_count++;
              mode4_index = 0;
              turn_l_flag = 0;
              odometry_millis = millis();
            }
            break;
          //오른쪽 턴
          case 2:
            turn_R(88, 10);
            if (turn_r_flag) {
              turn_right_count++;
              mode4_index = 0;
              turn_r_flag = 0;
              move_priority = 1;
              odometry_millis = millis();
            }
            break;
          //90도로 보정하기
          case 3:
            if (current_theta > 89 + 0.5) sendmotor(-10, 10);
            else if (current_theta < 89 - 0.5) sendmotor(10, -10);
            else {
              sendmotor(0, 0);
              mode4_index = 0;
              balance_flag = 0;
            }
            break;
          //x시작전 0도로 맞추기
          case 4:
            if (current_theta < 4 - 0.5) sendmotor(10, -10);
            else if (current_theta > 4 + 0.5) sendmotor(-10, 10);
            else {
              sendmotor(0, 0);
              mode4_index = 0;
              x_first_count = 2;
            }
            break;
          //0도 맞추기
          case 5:
            if (current_theta < 2 - 0.5) sendmotor(10, -10);
            else if (current_theta > 2 + 0.5) sendmotor(-10, 10);
            else  {
              sendmotor(0, 0);
              mode4_index = 0;
              balance_flag = 0;
            }

            break;
        }
        //-------parking3-------------------------------------------------------------------------------------
      } else if (bt_index == 3) {
        switch (mode4_index) {
          //초음파 && 직진 알고리즘
          case 0:
            scheduling3();
            break;
          //왼쪽 턴
          case 1:
            turn_L(88, 10);
            if (turn_l_flag) {
              turn_left_count++;
              mode4_index = 0;
              turn_l_flag = 0;
              odometry_millis = millis();
            }
            break;
          //오른쪽 턴
          case 2:
            turn_R(88, 10);
            if (turn_r_flag) {
              turn_right_count++;
              mode4_index = 0;
              turn_r_flag = 0;
              move_priority = 1;
              odometry_millis = millis();
            }
            break;
          //90도로 보정하기
          case 3:
            if (current_theta > 88 + 1) sendmotor(-10, 10);
            else if (current_theta < 88 - 1) sendmotor(10, -10);
            else {
              sendmotor(0, 0);
              mode4_index = 0;
              balance_flag = 0;
            }
            break;
          //x 시작전 180도로 보정
          case 4:
            if (current_theta < 180 - 1) sendmotor(10, -10);
            else if (current_theta > 180 + 1) sendmotor(-10, 10);
            else {
              sendmotor(0, 0);
              mode4_index = 0;
              x_first_count = 2;
            }
            break;
          //180도 보정
          case 5:
            if (current_theta < 180 - 1) sendmotor(10, -10);
            else if (current_theta > 180 + 1) sendmotor(-10, 10);
            else {
              sendmotor(0, 0);
              mode4_index = 0;
              balance_flag = 0;
            }
            break;
        }
      }
    }
    //--rgb_check---------------------------------------------------------------------------------------------
    if (t5_flag) {
      t5_flag = false;
      RGB_MODE();
    }

    if (rgb_flag) {
      //빨간색 감지
      if (mode2_index == 1) {
        sendmotor(0, 0);
        RGB_MODE();
       
      }
      else if (mode2_index == 3) {
        rgb_flag = 0;
        sendmotor(0, 0);
        mode2_index = 0;
        mode3_flag = true;
        x1 = 0;
        y1 = 0;
        //초록색 감지 오도메트리 조정
      } else if (mode2_index == 4) {
        if (current_theta <= -2.5 && current_theta >= - 3.5) {
          current_theta = 0;
          sendmotor(0, 0);
          mode2_index = 3;
        }
        else if (current_theta <  -3) sendmotor(10, -10);
        else                            sendmotor(-10, 10);
      }

    }

    //----linetracing----------------------------------------------------------------------------------------
    if (mode1_flag) {
      switch (mode_index) {
        case 0:
          detect_line();
          mode_index = 1;
          break;
        case 1:
          select_mode();
          break;
        case 2:
          move_line();
          break;
        default:
          mode_index = 0;
      }
    }
  }
}



void sendmotor(int m1, int m2) {
  if (m1 < 0) {
    tx_data[2] = 0x00;
    m1 *= -1;
  }
  else tx_data[2] = 0x01;

  if (m1 > 255) m1 = 255;
  tx_data[3] = m1;

  if (m2 < 0) {
    tx_data[4] = 0x00;
    m2 *= -1;
  }
  else tx_data[4] = 0x01;

  if (m2 > 255) m2 = 255;
  tx_data[5] = m2;


  checksum = 0;
  for (int i = 2; i < 6; i++) checksum ^= tx_data[i];
  checksum += 1;
  tx_data[6] = checksum;
  Serial1.write(tx_data, 7);
}
// Encoder Data Serial Receive
void serialEvent1() {
  rcv_data = Serial1.read();
  switch (rcv_count) {
    case 0:
      if ((rcv_ready == 0) && (rcv_data == 0xFF)) {
        rcv_count = 1;
      }
      else
        rcv_count = 0;
      break;
    case 1:
      if ((rcv_ready == 0) && (rcv_data == 0xFF)) {
        rcv_count = 2;
        rcv_ready = 1;
      }
      else
        rcv_count = 0;
      break;
    case 2:
      rx_buffer[rcv_index] = rcv_data;
      rcv_index++;
      if (rcv_index > 6) {
        rcv_checksum = 0;
        for (int i = 0; i < 6; i++) {
          rcv_checksum ^= rx_buffer[i];
        }
        rcv_checksum += 1;
        if (rcv_checksum == rx_buffer[rcv_index - 1]) {
          rcv_status = 1;
          memcpy((char*)rx_data, (char*)rx_buffer, 7);
        }
        rcv_count = 0;
        rcv_index = 0;
        rcv_ready = 0;
        rcv_stauts = 1;
      }
      break;
    default:
      rcv_count = 0;
      rcv_index = 0;
      rcv_ready = 0;
      rcv_stauts = 0;
      break;
  }
}

void T5ISR() {
  t5_flag = true;
}
void T5_MODE2_ISR() {
  mode2_t5_flag = true;
}
double getDistance(int Trig, int Echo) {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duration = pulseIn(Echo, HIGH, 5000);
  distance = (double)340 * duration / 20000;
  return distance;
}
