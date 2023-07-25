void Mode2() { // 중간 도착지점 3에 도달하면 정지 후 대기
  check_ir();
  linetrace();
  if (IR1 > ir1_th &&IR4 > ir4_th) { // 3도착지점 인식
    m1_ref_speed = 0;
    m2_ref_speed = 0;
    sendmotor(m1_ref_speed, m2_ref_speed);
    mode_index = 2;
  }
}
