void RGB_MODE() {
  TCS.getRawData(&red, &green, &blue, &clear);
  // 색상 감지 센서에서 받아온 데이터 값을 사용 가능하게끔 수치 변경
  int r = map(red, 0, 21504, 0, 1025);    // 빨간색 데이터 값
  int g = map(green, 0, 21504, 0, 1025);  // 초록색 데이터 값
  int b = map(blue, 0, 21504, 0, 1025);   // 파란색 데이터 값
  if (r > 150 && g<90) {
    mode2_index = 1;
    rgb_flag = 1;
    mode1_flag = 0;
    t5_flag = false;
  }
  //초록색감지하면 바로 오도메트리 조정
  else if ( g > 150 ) {
    Timer5.stop();
    Timer5.detachInterrupt(); //detach interrupt
    mode2_index = 4;
    rgb_flag = 1;
    mode1_flag = 0;
    t5_flag = false;
  }
  else mode2_index = 0;

    Serial.print("   R: ");
    Serial.print(r);        // 시리얼 모니터에 빨간색 값 출력
    Serial.print("   G: ");
    Serial.print(g);        // 시리얼 모니터에 초록색 값 출력
    Serial.print("   B: ");
    Serial.println(b);      // 시리얼 모니터에 파란색 값 출력
}
