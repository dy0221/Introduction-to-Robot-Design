//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//check rgb
void checkAim() {
  arm.movepElbowDown(103.77, 161.17);
  unsigned long preMillis = millis();
  while (millis() - preMillis < 2000) {
    chk_rgb1();
    printAim();
  }
  printAim();
  arm.movepElbowDown(-37.99 , 176.37);
  preMillis = millis();
  while (millis() - preMillis < 2000) {
    chk_rgb2();
    printAim();
  }
  arm.movep(-103.57, 158.42);
  preMillis = millis();
  while (millis() - preMillis < 2000) {
    chk_rgb3();
    printAim();
  }
  return;
}
/*
   (0,0)  (1,0)
   (0,1)  (1,1)
*/
void checkObject() {
  forCount = 0;
  for (int currentRow = 0; currentRow < objectRows; currentRow ++) {
    for (int currentColumn = 0; currentColumn < objectColumns; currentColumn ++) {
      if (forCount == 0) move2chkObject(currentColumn, currentColumn);
      else               move2chkObject(currentColumn + 2, currentColumn + 2);
      delay(1000);
      char objectRGB = chkRGB();
      objectArray[currentRow][currentColumn] = objectRGB;

    }
    forCount = 1;
  }
  forCount = 0;
  return;
}

/*
   (0,0)  (1,0)  >> (0,0)  (1,2)
   (0,1)  (1,1)  >> (0,1)  (1,3)
*/
void move2chkObject(unsigned int row, unsigned int column ) {
  double x = objecXlocation[row];
  double y = objecYlocation[column];
  arm.movep(x, y);
  return;
}

//rgb 체크
char chkRGB() {
  int i; // grab blocks!
  pixy.ccc.getBlocks(); // If there are detect blocks, print them!
  rgbLedOff();
  if ((pixy.ccc.blocks[i].m_signature) == 1)
  {
    Serial.println('b');
    analogWrite(blueled, 170);
    return 'b';
  }
  else if ((pixy.ccc.blocks[i].m_signature) == 2)
  {
    Serial.println('r');
    analogWrite(redled, 100);
    return 'r';
  }
  else if ((pixy.ccc.blocks[i].m_signature) == 3)
  {
    Serial.println('y');
    analogWrite(redled, 100);
    analogWrite(blueled, 170);
    return 'y';
  }
  else if ((pixy.ccc.blocks[i].m_signature) == 4)
  {
    Serial.println('g');
    analogWrite(greenled, 100);
    return 'g';
  }
  else {
    Serial.println('n');
    analogWrite(greenled, 100);
    analogWrite(blueled, 170);
    return 'n';
  }
}
