//기본 함수
void chkInfoDgree(unsigned int delayTime) {
  Serial.print("Joint 1 angle : ");
  //use to pulse or degree
  //  Serial.print(arm.ReadPos(SHOULDER_ID));
  Serial.print(arm.pul2deg(arm.ReadPos(SHOULDER_ID)));
  Serial.print(",\t");
  Serial.print("Joint 2 angle : ");
  //  Serial.print(arm.ReadPos(ELBOW_ID));
  Serial.print(arm.pul2deg(arm.ReadPos(ELBOW_ID)));
  Serial.print(",\t");
  Serial.print("current z pulse : ");
  Serial.print(arm.z_index);
  delay(delayTime);
}
//forward kinematic로 계산 한 EF길이
void chkInfoLocation(unsigned int delayTime) {
  int init_deg1 = arm.pul2deg(arm.ReadPos(1) - arm.offset.m1_deg);
  int init_deg2 = arm.pul2deg(arm.ReadPos(2) - arm.offset.m2_deg);
  //    Serial.print("init deg1 : ");
  //    Serial.print(init_deg1);
  //    Serial.print("\t");
  //    Serial.print("init deg2 : ");
  //    Serial.print(init_deg2);
  //    Serial.print("\t");

  // 현재 EE의 위치 구하기, EF[0], EF[1]이 x,y값.
  arm.FK(init_deg1, init_deg2);
  Serial.print(" x : ");
  Serial.print(arm.EF[0]);
  Serial.print("\t");
  Serial.print("y : ");
  Serial.print(arm.EF[1]);
  delay(delayTime);
}
//EK로부터 5cm뒤로  movel하기위해 만든함수
void chkInfoArm1(unsigned int delayTime) {
  int init_deg1 = arm.pul2deg(arm.ReadPos(1) - arm.offset.m1_deg);
  int init_deg2 = arm.pul2deg(arm.ReadPos(2) - arm.offset.m2_deg);
  mx = link1L * sin(radians(init_deg1)) + link2L * sin(radians(init_deg1) + radians(init_deg2));
  my = link1L * cos(radians(init_deg1)) + link2L * cos(radians(init_deg1) + radians(init_deg2));
  Serial.print(" mx : ");
  Serial.print(mx);
  Serial.print("\t");
  Serial.print("my : ");
  Serial.println(my);
  delay(delayTime);
}
//버튼 확인
void chkBtn() {
  if (digitalRead(button)) {
    //채터링 현상을 막기위한 약간의 딜레이
    delayMicroseconds(50);
  }
  else {
    delayMicroseconds(50);
    buttonState = false;
  }
}
//버튼 초기화
void btnReset() {
  buttonState = true;
}
//완료 함수
void finish() {
  arm.movep(1, 1000);
  arm.movep(-160.95, 31.53);
  
  while(1){
  analogWrite(redled, 100);
  delay(500);
  analogWrite(greenled, 170);
  delay(500);
  analogWrite(redled, 0);
  delay(500);
  analogWrite(blueled, 170);
  delay(500);
  analogWrite(greenled, 0);
  delay(500);
  analogWrite(redled, 100);
  delay(500);
  analogWrite(greenled, 100);
  }



  return;
}

void rgbLedOff() {
  analogWrite(redled, 0);
  analogWrite(greenled, 0);
  analogWrite(blueled, 0);
}

void printAim() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      Serial.print(aimArray[i][j]);
      Serial.print("   ");
    }
  }
  Serial.print(" obect : ");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Serial.print(objectArray[i][j]);
      Serial.print("   ");
    }
  }
  Serial.println("");
}
//배열애 색이 없으면 >> 완료
bool chkDone() {
  for (int forRow = 0; forRow < aimRows; forRow ++) {
    for (int forColumn = 0; forColumn < aimColumns; forColumn ++) {
      if (aimArray[forRow][forColumn] == 'r')   return false;
      else if (aimArray[forRow][forColumn] == 'y')   return false;
      else if (aimArray[forRow][forColumn] == 'g')   return false;
      else if (aimArray[forRow][forColumn] == 'b')   return false;
    }
  }
  return true;
}
