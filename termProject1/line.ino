void detect_line() {
  int8_t i;
  int8_t x0, x1, y0, y1;
  // 모든 라인 피쳐 받아오기
  // pixy.line.getAllFeautures(uint8_t features[optional], bool wait[optional])
  // optional features - LINE_VECTOR, LINE_INTERSECTION, LINE_BARCODE
  // example) pixy.line.getAllFeatures(LINE_VECTOR);
  right_slope = 0;
  left_slope = 0;
  pixy.line.getAllFeatures();
  if (pixy.line.numVectors < 2) {
    for (i = 0; i < pixy.line.numVectors; i++) {
      x0 = pixy.line.vectors[i].m_x0;
      x1 = pixy.line.vectors[i].m_x1;
      y0 = pixy.line.vectors[i].m_y0;
      y1 = pixy.line.vectors[i].m_y1;
      //벡터가 왼쪽에 위치할 때,
      if (x0 <= 78 / 2 && x1 <= 78 / 2) {
        //이미 벡터를 잡은 상태라면 벡터인식 안함
        //if (left_flag || right_flag) return;
        //벡터가 -로 잡혔을 때
        if (y1 > y0) {
          int8_t x = x0;
          int8_t y = y0;
          x0 = x1;
          y0 = y1;
          x1 = x;
          y1 = y;
        }
        //기울기 구하기
        if (x1 - x0 != 0)  slope = (float)(y0 - y1) / (x1 - x0);
        else               slope = 100;
        left_x0 = x0;
        left_x1 = x1;
        left_y0 = y0;
        left_y1 = y1;
        left_slope = slope;
        left_flag = 1;
        pre_millis = millis();
        //벡터가 오른쪽에 위치할 때
      } else if (x0 > 78 / 2 && x1 > 78 / 2) {
        //이미 벡터를 잡은 상태라면 벡터인식 안함
        //if (left_flag || right_flag) return;
        //벡터가 -로 잡혔을 때
        if (y1 > y0) {
          int8_t x = x0;
          int8_t y = y0;
          x0 = x1;
          y0 = y1;
          x1 = x;
          y1 = y;
        }
        if (x1 - x0 != 0)  slope = (float)(y0 - y1) / (x1 - x0);
        else               slope = 100;

        right_x0 = x0;
        right_x1 = x1;
        right_y0 = y0;
        right_y1 = y1;
        right_slope = slope;
        right_flag = 1;
        pre_millis = millis();
      }
    }
  }

  /* 바코드 인식 함수 0 >> slow 1>> go
    pixy.line.barcodes->m_code - 바코드가 인식되면 그 값 (0 - 15)을 읽어 int8_t 형태로 반환 */
  if (millis() - bar_millis > bar_delay && barcode_flag) barcode_count = 2;
  int numbar =  pixy.line.numBarcodes;
  if (numbar == 0) return;
  if (barcode_count == 1 || barcode_count == 3) return;
  if (pixy.line.barcodes->m_code == 0) {
    if (barcode_count == 2) {
      barcode_flag = 0;
      short_delay = 950;
      long_delay = 1300;
      barcode_count = 3;
      return;
    }
    barcode_index = 0;
    barcode_flag = 1;
    barcode_count = 1;
    short_delay = 1500;
    long_delay = 1700;
    bar_millis = millis();





  } else if (pixy.line.barcodes->m_code == 1 ) {

    if (barcode_count == 2) {
      barcode_flag = 0;
      short_delay = 950;
      long_delay = 1100;
      barcode_count = 3;
      return;
    }
    barcode_index = 1;
    barcode_flag = 1;
    barcode_count = 1;
    short_delay = 730;
    long_delay = 900;
    bar_millis = millis();

  }
}
