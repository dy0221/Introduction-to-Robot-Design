//IR 센서 핀 번호 선언
#define ir1 A10
#define ir2 A2
#define ir3 A3
#define ir4 A4

//IR 센서 범위 값 지정
#define ir1_th 300
#define ir2_th 150
#define ir3_th 400
#define ir4_th 400

//풀업 스위치 선언
#define pull_up 9

//joystick
int joy_x = 0;
int joy_y = 0;
int map_x = 0;
int map_y = 0;

//for joystick UART
bool rcv_status = 0;
bool rcv_ready = 0;
byte rcv_data = 0;
byte rcv_checksum = 0;
byte rx_buffer[5];
byte rx_data[5];
int rcv_count = 0;
int rcv_index = 0;

//for motor UART
byte tx_data[7];
byte checksum = 0;

//ir a0,a1,a2
int IR1 = 0;
int IR2 = 0;
int IR3 = 0;
int IR4 = 0;

//speed to motor
int m1_ref_speed = 0;
int m2_ref_speed = 0;

//motor_index
int mode_index = 0;

//linetrace_index
int line_index = 0;

//flag
bool left_flag = 0;
bool left_flag2 = 0;
bool right_flag = 0;
bool right_flag2 = 0;
int turn_flag = 0;


void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);//motor
  Serial3.begin(115200);//joystick
  tx_data[0] = 0xFF; //Packet 전송 Header 1
  tx_data[1] = 0xFF; //Packet 전송 Header 2
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(pull_up, INPUT);
}

void loop() {

  if (digitalRead(pull_up)&&pull_flag ==0) { //택트 스위치 누르지 않았을 때
    check_ir();
    m1_ref_speed = 0;
    m2_ref_speed = 0;
    sendmotor(m1_ref_speed, m2_ref_speed);
  } else { // 택트 스위치 눌렀을 때 
    pull_flag = 1;
  }
  if (pull_flag) {
    switch (mode_index) {
      case 0:
        Mode1();
        break;
      case 1:
        Mode2();
        break;
      case 2:
        Mode3();
        break;
      default:
        mode_index = 0;
        break;
    }
  }
}



void check_ir() { // IR 센서값 확인 및 출력 함수
  IR1 = analogRead(ir1);
  IR2 = analogRead(ir2);
  IR3 = analogRead(ir3);
  IR4 = analogRead(ir4);
//  Serial.print(IR1);
//  Serial.print(" ");
//  Serial.print(IR2);
//  Serial.print(" ");
//  Serial.print(IR3);
//  Serial.print(" ");
//  Serial.println(IR4);
}


void sendmotor(int m1, int m2) { // 모터 값 bluepill로 전달
  if (m1 < 0) {
    tx_data[2] = 0x00; // 모터값 음수일 때 0x00 전송
    m1 *= -1; //모터값 양수로 전송
  }
  
  else tx_data[2] = 0x01; // 모터값 양수일 때 0x01 전송

  if (m1 > 255) m1 = 255;
  tx_data[3] = m1; // 모터값 전송

  if (m2 < 0) {
    tx_data[4] = 0x00; // 모터값 음수일 때 0x00 전송
    m2 *= -1; //모터값 양수로 전송
  }
  else tx_data[4] = 0x01; // 모터값 양수일 때 0x01 전송

  if (m2 > 255) m2 = 255;
  tx_data[5] = m2; // 모터값 전송


  checksum = 0;
  for (int i = 2; i < 6; i++) checksum ^= tx_data[i]; // Multiple byte 송수신 Packet 전송 방식
  checksum += 1;
  tx_data[6] = checksum; // check sum 값 전송
  Serial1.write(tx_data, 7);
}
