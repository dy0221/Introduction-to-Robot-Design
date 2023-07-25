void Mode3() { // 조이스틱 값 불러온 후 map을 통해 모터값 범위로 받아온 뒤 bluepill에 모터값 전송
  if (Serial3.available()) readJoyStick();
  if (rcv_status) {
    rcv_status = 0;
    int y = map(joy_y, 0, 1023, -50, 50);
    int x = map(joy_x, 0, 1023, -15, 15);
    sendmotor(y + x, y - x);
  }
}
void readJoyStick() { // packet 통신 및 조이스틱 값 저장
  rcv_data = Serial3.read();
  switch (rcv_count) {
    
    case 0: //Header1 
      if ((rcv_ready == 0) && (rcv_data == 0xFF)) {
        rcv_count = 1;
      }
      else
        rcv_count = 0;
      break;
      
    case 1: //Header 2
      if ((rcv_ready == 0) && (rcv_data == 0xFF)) {
        rcv_count = 2;
        rcv_ready = 1;
      }
      else
        rcv_count = 0;
      break;
      
    case 2: // 조이스틱 데이터값 및 Check sum
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
          memcpy((char*)rx_data, (char*)rx_buffer, 5);
          memcpy((char*)&joy_x, (char*)rx_data, 2);
          memcpy((char*)&joy_y, (char*)&rx_data[2], 2);
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
