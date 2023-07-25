void Mode1() {
  //IR 값 확인 
  check_ir(); 

  if ((IR1 > ir1_th) && (line_index == 0)) {
    line_index = 1;
  }
  if (( IR4 > ir4_th) && (line_index == 0)) {
    line_index = 3;
  }
  switch (line_index) {
    case 0:
      linetrace();
      break;
    case 1:
      move_l();
      break;
    case 2:
      turn_left();
      break;
    case 3:
      move_r();
      break;
    case 4:
      turn_right();
      break;
    default:
      line_index = 0;

  }
  if (turn_flag >= 7) { // 7번의 좌회전 및 우회전 진행한 후 Mission 3로 이동
    mode_index = 1;
    turn_flag=0;
  }
  //  check data
  //  Serial.print("m1 :");
  //  Serial.print(tx_data[2]);
  //  Serial.print("m2 :");
  //  Serial.println(tx_data[3]);

}
void linetrace() {
  //직진
  if ( (IR2 < ir2_th && IR3 < ir3_th)) {
    m1_ref_speed = 20;
    m2_ref_speed = 20;
    //오른쪽으로 치우쳐짐 > 왼쪽으로
  } else if ((IR2 > ir2_th && IR3 < ir3_th)) {
    m1_ref_speed = 5;
    m2_ref_speed = 40;
  } else if ((IR2 < ir2_th && IR3 > ir3_th)) {
    m1_ref_speed = 40;
    m2_ref_speed = 5;
  }
  sendmotor(m1_ref_speed, m2_ref_speed);
}

void move_l() { // 왼쪽 교차로 인식 후 다시 하얀색을 인식할 때까지 직진
  if (IR1 < ir1_th && IR2 < ir2_th) { 
    delay(500);
    m1_ref_speed = 0;
    m2_ref_speed = 0;
    sendmotor(m1_ref_speed, m2_ref_speed);
    line_index = 2;
    return;
  }
  m1_ref_speed = 15;
  m2_ref_speed = 15;
  sendmotor(m1_ref_speed, m2_ref_speed);
}
void turn_left() { // 좌회전
  if (IR1 > ir1_th) left_flag = true;
  if ((IR2 > ir2_th) && (left_flag == true)) left_flag2 = true;
  if ((IR3 > ir3_th) && (left_flag2 == true)) {
    m1_ref_speed = 0;
    m2_ref_speed = 0;
    sendmotor(m1_ref_speed, m2_ref_speed);
    line_index = 0;
    left_flag = 0;
    left_flag2 = 0;
    turn_flag ++;
    return;
  }
  // IR3이 검은색을 인식할 때까지 회전 
  m1_ref_speed = -15;
  m2_ref_speed = 15;
  sendmotor(m1_ref_speed, m2_ref_speed);
}

void move_r() { // 오른쪽 교차로 인식 후 다시 하얀색을 인식할 때까지 직진
  if (IR3 < ir3_th && IR4 < ir4_th) {
    delay(500);
    m1_ref_speed = 0;
    m2_ref_speed = 0;
    sendmotor(m1_ref_speed, m2_ref_speed);
    line_index = 4;
    return;
  }
  m1_ref_speed = 15;
  m2_ref_speed = 15;
  sendmotor(m1_ref_speed, m2_ref_speed);
}
void turn_right() { // 우회전 
  if (IR4 > ir4_th) right_flag = true;
  if ((IR3 > ir3_th) && (right_flag == true)) right_flag2 = true;
  if ((IR2 > ir2_th) && (right_flag2 == true)) {
    m1_ref_speed = 0;
    m2_ref_speed = 0;
    sendmotor(m1_ref_speed, m2_ref_speed);
    line_index = 0;
    right_flag = 0;
    right_flag2 = 0;
    turn_flag ++;
    return;
  }
  // IR2이 검은색을 인식할 때까지 회전 
  m1_ref_speed = 15;
  m2_ref_speed = -15;
  sendmotor(m1_ref_speed, m2_ref_speed);
}
