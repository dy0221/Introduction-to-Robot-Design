//AIRO DC Motor Driver V1.0

//*pin layout
//------------------------------------------------------------
//           |   dir1    dir2    ENCA    ENCB    PWM    STBY
//------------------------------------------------------------
//  Motor1   |   PB12    PB13    PB06    PB07    PB0    PA8
//  Motor2   |   PB14    PB15    PB08    PB09    PB1    PA8
//------------------------------------------------------------




//모터 1
#define ENC1_CHA  PB6
#define ENC1_CHB  PB7
#define M1_PWM    PB0
#define M1_DIR1   PB12
#define M1_DIR2   PB13

//모터 2
#define ENC2_CHA  PB8
#define ENC2_CHB  PB9
#define M2_PWM    PB1
#define M2_DIR1   PB14
#define M2_DIR2   PB15

#define STBY      PA8


//모터 1 PID Gain
float Kp1 = 0.7;
float Ki1 = 0.5;
float Kd1 = 0.1;

//모터 1 PID Gain
float Kp2 = 0.7;
float Ki2 = 0.5;
float Kd2 = 0.1;

int e1cnt = 0;
int e1cnt_k = 0, e1cnt_k_1 = 0, d_e1cnt = 0;

int e2cnt = 0;
int e2cnt_k = 0, e2cnt_k_1 = 0, d_e2cnt = 0;

float m1speed = 0;
float m1_ref_spd = 0;
float m1_err_spd = 0;
float m1_err_spd_k_1 = 0;
float m1_derr_spd = 0;
float m1_err_sum = 0;
float ctrl_up = 0;
float ctrl_ui = 0;
float ctrl_ud = 0;

float m2speed = 0;
float m2_ref_spd = 0;
float m2_err_spd = 0;
float m2_err_spd_k_1 = 0;
float m2_derr_spd = 0;
float m2_err_sum = 0;
float ctrl2_up = 0;
float ctrl2_ui = 0;
float ctrl2_ud = 0;

int ctrl_u = 0;
int ipwm_u = 0;

int ctrl2_u = 0;
int ipwm2_u = 0;

bool t2_flag = 0;
//urat
bool rcv_status = 0;
bool rcv_ready = 0;
byte rcv_data = 0;
byte rcv_checksum = 0;
byte rx_buffer[7];
byte rx_data[4];
int rcv_count = 0;
int rcv_index = 0;
bool rcv_flag = 0;
char sec = NULL;

void setup() {
  pinMode(ENC1_CHA, INPUT_PULLUP);
  pinMode(ENC1_CHB, INPUT_PULLUP);

  pinMode(M1_DIR1, OUTPUT);
  pinMode(M1_DIR2, OUTPUT);
  pinMode(M1_PWM, OUTPUT);

  pinMode(ENC2_CHA, INPUT_PULLUP);
  pinMode(ENC2_CHB, INPUT_PULLUP);

  pinMode(M2_DIR1, OUTPUT);
  pinMode(M2_DIR2, OUTPUT);
  pinMode(M2_PWM, OUTPUT);

  pinMode(STBY, OUTPUT);


  attachInterrupt(digitalPinToInterrupt(ENC1_CHA), Enc1chA_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC1_CHB), Enc1chB_ISR, CHANGE);

  attachInterrupt(digitalPinToInterrupt(ENC2_CHA), Enc2chA_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC2_CHB), Enc2chB_ISR, CHANGE);


  Serial.begin(115200);
  Serial3.begin(115200);
  Timer2.setChannel1Mode(TIMER_OUTPUTCOMPARE);
  // 1000us(1ms) 에 한번씩 타이머 발생하게 설정
  Timer2.setPeriod(50000);  //50,000 us = 50ms
  Timer2.attachCompare1Interrupt(t2_ISR);

}

void loop() {
  //PID 제어
  
  if (t2_flag) {
    t2_flag = 0;
    m1speed = d_e1cnt * 10 / 11; // *500/11/50
    //Error
    m1_err_spd = m1_ref_spd - m1speed;
    m1_derr_spd = m1_err_spd - m1_err_spd_k_1;
    m1_err_sum = m1_err_sum + m1_err_spd;
    m1_err_spd_k_1 = m1_err_spd;
    //PID-Controller
    ctrl_up = Kp1 * m1_err_spd;
    ctrl_ui = Ki1 * m1_err_sum;
    ctrl_ud = Kd1 * m1_derr_spd;
    ctrl_u = (int)(ctrl_up + ctrl_ud + ctrl_ui);

    m2speed = d_e2cnt * 10 / 11; // *500/11/50
    //Error
    m2_err_spd = m2_ref_spd - m2speed;
    m2_derr_spd = m2_err_spd - m2_err_spd_k_1;
    m2_err_sum = m2_err_sum + m2_err_spd;
    m2_err_spd_k_1 = m2_err_spd;
    //PID-Controller
    ctrl2_up = Kp2 * m2_err_spd;
    ctrl2_ui = Ki2 * m2_err_sum;
    ctrl2_ud = Kd2 * m2_derr_spd;
    ctrl2_u = (int)(ctrl2_up + ctrl2_ud + ctrl2_ui);

    if (ctrl_u >= 0) {
      digitalWrite(M1_DIR1, LOW);
      digitalWrite(M1_DIR2, HIGH); //ccw
      digitalWrite(STBY, HIGH);

      if (ctrl_u > 255)
        ipwm_u = 255;
      else
        ipwm_u = (int)ctrl_u;
    }
    else {
      digitalWrite(M1_DIR1, HIGH);
      digitalWrite(M1_DIR2, LOW); //cw
      digitalWrite(STBY, HIGH);

      if (ctrl_u < -255)
        ipwm_u = 255;
      else
        ipwm_u = (int)ctrl_u * (-1);
    }



    if (ctrl2_u >= 0) {
      digitalWrite(M2_DIR1, HIGH);
      digitalWrite(M2_DIR2, LOW); //ccw
      digitalWrite(STBY, HIGH);

      if (ctrl2_u > 255)
        ipwm2_u = 255;
      else
        ipwm2_u = (int)ctrl2_u;
    }
    else {
      digitalWrite(M2_DIR1, LOW);
      digitalWrite(M2_DIR2, HIGH); //cw
      digitalWrite(STBY, HIGH);

      if (ctrl2_u < -255)
        ipwm2_u = 255;
      else
        ipwm2_u = (int)ctrl2_u * (-1);
    }
    analogWrite(M1_PWM, ipwm_u);
    analogWrite(M2_PWM, ipwm2_u);
    //    Serial.print(m1_ref_spd);
    //    Serial.print(",");
    //    Serial.print(m1speed);
    //    Serial.print(",");
    //    Serial.print(m2_ref_spd);
    //    Serial.print(",");
    //    Serial.println(m2speed);
  }

  // Arduino Mega 보드에서 전송받은 모터값을 m1_ref_spd, m2_ref_spd에 저장
  if (Serial3.available()) rcv_data_f();
  if (rcv_status) {
    rcv_status = 0;
    if (rx_data[0] == 0x01) m1_ref_spd = rx_data[1]; // Mega 보드에서 모터값을 양수로 지정했을 때 
    else                    m1_ref_spd = -rx_data[1]; // Mega 보드에서 모터값을 음수로 지정했을 때 

    if (rx_data[2] == 0x00) m2_ref_spd = -rx_data[3]; // Mega 보드에서 모터값을 양수로 지정했을 때
    else                    m2_ref_spd = rx_data[3]; // Mega 보드에서 모터값을 음수로 지정했을 때 
  }
}

void rcv_data_f() {
  rcv_data = Serial3.read();
  switch (rcv_count) {
    
    case 0: //Header 
      if ((rcv_ready == 0) && (rcv_data == 0xFF)) {
        rcv_count = 1;
      }
      else
        rcv_count = 0;
      break;
      
    case 1: //Header 
      if ((rcv_ready == 0) && (rcv_data == 0xFF)) {
        rcv_count = 2;
        rcv_ready = 1;
      }
      else
        rcv_count = 0;
      break;
      
    case 2: // 데이터값 받기
      rx_buffer[rcv_index] = rcv_data;
      rcv_index++;
      if (rcv_index > 4) {
        rcv_checksum = 0;
        for (int i = 0; i < 4; i++) {
          rcv_checksum ^= rx_buffer[i];
        }
        rcv_checksum += 1;
        if (rcv_checksum == rx_buffer[rcv_index - 1]) {
          rcv_status = 1;
          memcpy((char*)rx_data, (char*)rx_buffer, 4);
        }
        rcv_count = 0;
        rcv_index = 0;
        rcv_ready = 0;
      }
      break;
      
    default:
      rcv_count = 0;
      rcv_index = 0;
      rcv_ready = 0;
      break;
  }
}
void t2_ISR() {
  t2_flag = 1;
  e1cnt_k = e1cnt;
  d_e1cnt = e1cnt_k - e1cnt_k_1; //delta_error
  e1cnt_k_1 = e1cnt_k;

  e2cnt_k = e2cnt;
  d_e2cnt = e2cnt_k - e2cnt_k_1; //delta_error
  e2cnt_k_1 = e2cnt_k;
}

//모터 1 cw, ccw 제어
void Enc1chA_ISR() {
  if (digitalRead(ENC1_CHA) == HIGH) {
    if (digitalRead(ENC1_CHB) == LOW) e1cnt--;
    else                             e1cnt++;
  }
  else {
    if (digitalRead(ENC1_CHB) == HIGH)  e1cnt--;
    else                               e1cnt++;
  }
}

void Enc1chB_ISR() {
  if (digitalRead(ENC1_CHB) == HIGH) {
    if (digitalRead(ENC1_CHA) == HIGH) e1cnt--;
    else                              e1cnt++;
  }
  else {
    if (digitalRead(ENC1_CHA) == LOW)
      e1cnt--;
    else
      e1cnt++;
  }
}

//모터 2 cw, ccw 제어
void Enc2chA_ISR() {
  if (digitalRead(ENC2_CHA) == HIGH) {
    if (digitalRead(ENC2_CHB) == LOW) e2cnt++;
    else                             e2cnt--;
  }
  else {
    if (digitalRead(ENC2_CHB) == HIGH)  e2cnt++;
    else                               e2cnt--;
  }
}

void Enc2chB_ISR() {
  if (digitalRead(ENC2_CHB) == HIGH) {
    if (digitalRead(ENC2_CHA) == HIGH) e2cnt++;
    else                              e2cnt--;
  }
  else {
    if (digitalRead(ENC2_CHA) == LOW)  e2cnt++;
    else                              e2cnt--;
  }
}
