///////////////////////////////////////////////////////////////////////////////
//pick bolt
bool pickBolt() {
  bool chkError = 0;
  if (aimInfo[0] == 'r') {
    chkError = pickRed();
  } else if (aimInfo[0] == 'y') {
    chkError = pickYello();
  } else if (aimInfo[0] == 'g') {
    chkError = pickGreen();
  } else if (aimInfo[0] == 'b') {
    chkError = pickBlue();
  } else {
    Serial.println("rgb check error");
    return true;
  }
  if (chkError) return true;
  return false;
}
//mv bolt to aim
bool mvBolt() {
  bool chkError = 0;
  if (aimInfo[0] == 'r') {
    chkError = mvRed();
  } else if (aimInfo[0] == 'y') {
    chkError = mvYello();
  } else if (aimInfo[0] == 'g') {
    chkError = mvGreen();
  } else if (aimInfo[0] == 'b') {
    chkError = mvBlue();
  }
  if (chkError) return true;

  return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool pickRed() {
  if (redInfo[0] == -1 || redInfo[1] == -1) {
    Serial.println("red objcet check error");
    return true;
  }
  float    z = 0;
  delay(500);
  if (redInfo[0] == 0 && redInfo[1] == 0) {
    double x = objecRedXlocation[0];
    double y = objecRedYlocation[0];
    arm.movepElbowDown(initX0, initY0);
    arm.movez(z);
    delay(500);
    arm.movep(163.72, 101.98);
    arm.movel(x, y);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(124.81, 183.10);
    arm.movep(118.61, 100.11);
    arm.movep(55.94, 130.26);
    arm.movel(-56.50, 134.57);
    arm.movep(-144.38, 108.18);
    arm.movep(-151.09, 180.38);
    arm.movepElbowDown(-140.70, 130.18);
    return false;
  } else if (redInfo[0] == 0 && redInfo[1] == 1) {
    double x = objecRedXlocation[1];
    double y = objecRedYlocation[1];
    arm.movep(119.69, 142.47);
    arm.movep(initX1, initY1);
    arm.movez(z);
    delay(500);
    arm.movel(x, y);
    delay(500);
    arm.movep(184.44, 47.61);
    delay(500);
    arm.movep(188.61, 40.37);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(115.79, 89.48);
    arm.movep(124.81, 183.10);
    arm.movepElbowDown(118.61, 100.11);
    arm.movep(55.94, 130.26);
    arm.movel(-56.50, 134.57);
    arm.movel(-140.70, 130.18);
    return false;
  } else if (redInfo[0] == 1 && redInfo[1] == 0) {
    double x = objecRedXlocation[2];
    double y = objecRedYlocation[2];
    arm.movepElbowDown(initX2, initY2);
    arm.movez(z);
    delay(500);
    arm.movep(-165.63, 96.49);
    arm.movep(-176.52, 87.07);
    arm.movep(-181.53, 116.64);
    arm.movep(-185.63, 133.41);
    arm.movep(-189.27, 140.46);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    return false;
  } else if (redInfo[0] == 1 && redInfo[1] == 1) {
    double x = objecRedXlocation[3];
    double y = objecRedYlocation[3];
    arm.movep(initX3, initY3);
    arm.movez(z);
    delay(500);
    arm.movel(x, y);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(-117.34, 87.45);
    arm.movel(-133.74, 164.63);
    delay(500);
  }
  return false;
}
bool pickYello() {
  if (yelloInfo[0] == -1 || yelloInfo[1] == -1) {
    Serial.println("yello objcet check error");
    return true;
  }
  int    z = 4;
  chkInfoDgree(500);
  if (yelloInfo[0] == 0 && yelloInfo[1] == 0) {
    double x = objecYelloXlocation[0];
    double y = objecYelloYlocation[0];
    arm.movepElbowDown(initX0, initY0);
    arm.movez(z);
    delay(500);
    arm.movep(163.72, 101.98);
    arm.movel(x, y);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(124.81, 183.10);
    arm.movep(118.61, 100.11);
    arm.movep(55.94, 130.26);
    arm.movel(-56.50, 134.57);
    arm.movep(-144.38, 108.18);
    arm.movep(-151.09, 180.38);
    arm.movepElbowDown(-140.70, 130.18);
    return false;
  } else if (yelloInfo[0] == 0 && yelloInfo[1] == 1) {
    double x = objecYelloXlocation[1];
    double y = objecYelloYlocation[1];
    arm.movep(119.69, 142.47);
    arm.movep(initX1, initY1);
    arm.movez(z);
    delay(500);
    arm.movel(x, y);
    delay(500);
    arm.movep(184.44, 47.61);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(115.79, 89.48);
    arm.movep(124.81, 183.10);
    arm.movepElbowDown(118.61, 100.11);
    arm.movep(55.94, 130.26);
    arm.movel(-56.50, 134.57);
    arm.movel(-140.70, 130.18);
    return false;
  } else if (yelloInfo[0] == 1 && yelloInfo[1] == 0) {
    double x = objecYelloXlocation[2];
    double y = objecYelloYlocation[2];
    arm.movepElbowDown(initX2, initY2);
    arm.movez(z);
    delay(500);
    arm.movep(-165.63, 96.49);
    arm.movep(-170.25, 95.55);
    arm.movep(-181.53, 92.43);
    arm.movep(-179.18, 115.25);
    arm.movep(-183.72, 126.61);
    arm.movep(-182.70, 142.17);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    return false;
  } else if (yelloInfo[0] == 1 && yelloInfo[1] == 1) {
    double x = objecYelloXlocation[3];
    double y = objecYelloYlocation[3];
    arm.movep(initX3, initY3);
    arm.movez(z);
    delay(500);
    arm.movel(x, y);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(-117.34, 87.45);
    arm.movel(-133.74, 164.63);
    delay(500);
    return false;
  }
  return false;
}
bool pickGreen() {
  if (greenInfo[0] == -1 || greenInfo[1] == -1) {
    Serial.println("green objcet check error");
    return true;
  }
  int    z = 10;
  chkInfoDgree(500);
  if (greenInfo[0] == 0 && greenInfo[1] == 0) {
    double x = objecGreenXlocation[0];
    double y = objecGreenYlocation[0];
    arm.movepElbowDown(initX0, initY0);
    arm.movez(z);
    delay(500);
    arm.movep(163.72, 101.98);
    arm.movel(x, y);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(124.81, 183.10);
    arm.movep(118.61, 100.11);
    arm.movep(55.94, 130.26);
    arm.movel(-56.50, 134.57);
    arm.movep(-144.38, 108.18);
    arm.movep(-151.09, 180.38);
    arm.movepElbowDown(-140.70, 130.18);
    return false;
  } else if (greenInfo[0] == 0 && greenInfo[1] == 1) {
    double x = objecGreenXlocation[1];
    double y = objecGreenYlocation[1];
    arm.movep(119.69, 142.47);
    arm.movep(initX1, initY1);
    arm.movez(z);
    delay(500);
    arm.movel(x, y);
    delay(500);
    arm.movep(184.44, 47.61);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(115.79, 89.48);
    arm.movep(124.81, 183.10);
    arm.movepElbowDown(118.61, 100.11);
    arm.movep(55.94, 130.26);
    arm.movel(-56.50, 134.57);
    arm.movel(-140.70, 130.18);
    return false;
  } else if (greenInfo[0] == 1 && greenInfo[1] == 0) {
    double x = objecGreenXlocation[2];
    double y = objecGreenYlocation[2];
    arm.movepElbowDown(initX2, initY2);
    arm.movez(z);
    delay(500);
    arm.movep(-165.63, 96.49);
    arm.movep(-176.52, 87.07);
    arm.movep(-181.53, 116.64);
    arm.movep(-185.63, 133.41);
    arm.movep(-189.27, 140.46);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    return false;
  } else if (greenInfo[0] == 1 && greenInfo[1] == 1) {
    double x = objecGreenXlocation[3];
    double y = objecGreenYlocation[3];
    arm.movep(initX3, initY3);
    arm.movez(z);
    delay(500);
    arm.movel(x, y);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(-117.34, 87.45);
    arm.movel(-133.74, 164.63);
    delay(500);
    return false;
  }
  return false;
}
bool pickBlue() {
  if (blueInfo[0] == -1 || blueInfo[1] == -1) {
    Serial.println("blue objcet check error");
    return true;
  }
  float    z = 14.5;
  chkInfoDgree(500);
  if (blueInfo[0] == 0 && blueInfo[1] == 0) {
    double x = objecBlueXlocation[0];
    double y = objecBlueYlocation[0];
    arm.movepElbowDown(initX0, initY0);
    arm.movez(z);
    delay(500);
    arm.movep(162.37, 88.60);
    arm.movel(x, y);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(124.81, 183.10);
    arm.movep(118.61, 100.11);
    arm.movep(55.94, 130.26);
    arm.movel(-56.50, 134.57);
    arm.movep(-144.38, 108.18);
    arm.movep(-151.09, 180.38);
    arm.movepElbowDown(-140.70, 130.18);
    return false;
  } else if (blueInfo[0] == 0 && blueInfo[1] == 1) {
    double x = objecBlueXlocation[1];
    double y = objecBlueYlocation[1];
    arm.movep(119.69, 142.47);
    arm.movep(initX1, initY1);
    arm.movez(z);
    delay(500);
    arm.movel(x, y);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(115.79, 89.48);
    arm.movep(124.81, 183.10);
    arm.movepElbowDown(118.61, 100.11);
    arm.movep(55.94, 130.26);
    arm.movel(-56.50, 134.57);
    arm.movel(-140.70, 130.18);
    return false;
  } else if (blueInfo[0] == 1 && blueInfo[1] == 0) {
    double x = objecBlueXlocation[2];
    double y = objecBlueYlocation[2];
    arm.movepElbowDown(initX2, initY2);
    arm.movez(z);
    delay(500);
    arm.movep(-177.93, 90.84);
    arm.movep(-175.40, 104.37);
    arm.movep(-181.53, 116.64);
    arm.movep(-182.43, 122.97);
    delay(500);
    arm.movep(-185.66, 127.62);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    return false;
  } else if (blueInfo[0] == 1 && blueInfo[1] == 1) {
    double x = objecBlueXlocation[3];
    double y = objecBlueYlocation[3];
    arm.movep(initX3, initY3);
    arm.movez(z);
    delay(500);
    arm.movel(x, y);
    delay(500);
    arm.movez(pickHeight);
    delay(500);
    arm.movep(-117.34, 87.45);
    arm.movel(-133.74, 164.63);
    delay(500);
    return false;
  }
  return false;
}
//////////////////////////////////////////////////////////////////////////
bool mvRed() {
  if (aimInfo[0] == 'n') {
    Serial.println("aim red location error");
    return true;
  }
  int column = 0;
  if (aimInfo2[0] == 1) {
    column = aimInfo2[1] + 6;
  } else {
    column = aimInfo2[1];
  }
  if (aimInfo2[1] == 0) {
    if ( redInfo[0] == 1 && redInfo[1] == 0 ||  redInfo[0] == 0 && redInfo[1] == 0)   arm.movep(-128.99, 187.18);
    else                     arm.movepElbowDown(-128.99, 187.18);
  } else {
    if (redInfo[0] == 1 && redInfo[1] == 0 ||  redInfo[0] == 0 && redInfo[1] == 0)       arm.movep(-132.39, 143.49);
    else                        arm.movepElbowDown(-132.39, 143.49);

  }
  double x  = aimRedXlocation[column];
  double y  = aimRedYlocation[column];
  if (aimInfo2[0] == 0) arm.movep(x, y);
  else arm.movel(x, y);
  delay(500);
  return false;
}
bool mvYello() {
  if (aimInfo[0] == 'n' ) {
    Serial.println("aim yello location error");
    return true;
  }

  int column = 0;
  if (aimInfo2[0] == 1) {
    column = aimInfo2[1] + 6;
  } else {
    column = aimInfo2[1];
  }

  if (aimInfo2[1] == 0) {
    if ( yelloInfo[0] == 1 && yelloInfo[1] == 0 ||  yelloInfo[0] == 0 && yelloInfo[1] == 0)   arm.movep(-128.99, 187.18);
    else                     arm.movepElbowDown(-128.99, 187.18);
  } else {
    if (yelloInfo[0] == 1 && yelloInfo[1] == 0 ||  yelloInfo[0] == 0 && yelloInfo[1] == 0)       arm.movep(-132.39, 143.49);
    else                        arm.movepElbowDown(-132.39, 143.49);

  }
  double x  = aimYelloXlocation[column];
  double y  = aimYelloYlocation[column];
  if (aimInfo2[0] == 0) arm.movep(x, y);
  else arm.movel(x, y);
  delay(500);
  return false;
}
bool mvGreen() {
  if (aimInfo[0] == 'n') {
    Serial.println("aim green location error");
    return true;
  }
  int column = 0;
  if (aimInfo2[0] == 1) {
    column = aimInfo2[1] + 6;
  } else {
    column = aimInfo2[1];
  }

  if (aimInfo2[1] == 0) {
    if ( greenInfo[0] == 1 && greenInfo[1] == 0 ||  greenInfo[0] == 0 && greenInfo[1] == 0)   arm.movep(-128.99, 187.18);
    else                     arm.movepElbowDown(-128.99, 187.18);
  } else {
    if (greenInfo[0] == 1 && greenInfo[1] == 0 ||  greenInfo[0] == 0 && greenInfo[1] == 0)       arm.movep(-132.39, 143.49);
    else                        arm.movepElbowDown(-132.39, 143.49);

  }
  double x  = aimGreenXlocation[column];
  double y  = aimGreenYlocation[column];
  if (aimInfo2[0] == 0) arm.movep(x, y);
  else arm.movel(x, y);
  delay(500);
  return false;
}
bool mvBlue() {
  if (aimInfo[0] == 'n') {
    Serial.println("aim blue location error");
    return true;
  }
  int column = 0;
  if (aimInfo2[0] == 1) {
    column = aimInfo2[1] + 6;
  } else {
    column = aimInfo2[1];
  }
  if (aimInfo[1] == 0) {
    if ( blueInfo[0] == 1 && blueInfo[1] == 0 ||  blueInfo[0] == 0 && blueInfo[1] == 0)   arm.movep(-128.99, 187.18);
    else                     arm.movepElbowDown(-128.99, 187.18);
  } else {
    if (blueInfo[0] == 1 && blueInfo[1] == 0 ||  blueInfo[0] == 0 && blueInfo[1] == 0)       arm.movep(-132.39, 143.49);
    else                        arm.movepElbowDown(-132.39, 143.49);

  }


  double x  = aimBlueXlocation[column];
  double y  = aimBlueYlocation[column];
  if (aimInfo[0] == 1 && aimInfo[1] >= 3) {
    arm.movep(x, y);
    return;
  }
  arm.movel(x, y);
  delay(500);
  return false;
}

//======================================================================================================================================================
void putdownBolt() {
  if (aimInfo[0] == 'r') {
    arm.movez(6.5);
    delay(500);
    mvBackRed();
  } else if (aimInfo[0] == 'y') {
    arm.movez(6.5);
    delay(500);
    mvBackYello();
  } else if (aimInfo[0] == 'g') {
    arm.movez(7);
    delay(500);
    mvBackGreen();
  } else if (aimInfo[0] == 'b') {
    arm.movez(1);
    delay(500);
    mvBackBlue();
  }
  return;
}
//====================================================================================================================================================
//mv back (볼트가 이미 옆에 있으면 치므로)
void mvBackRed() {
  if (aimInfo2[0] == 0) {
    if (aimInfo2[1] == 0)    {
      arm.movez(putdownHeight);
      arm.movepp(84.65, 207.24);
      arm.movep(50.65, 191.71);
    } else if (aimInfo2[1] == 1) {
      arm.movepp(35.15, 204.21);
      arm.movez(putdownHeight);
      arm.movel(42.15,211.21);
      delay(700);
      arm.movepp(-0.58, 189.27);
      return;
    } else if (aimInfo2[1] == 2) {
      arm.movepp(4.02, 209.18);
      arm.movez(putdownHeight);
      arm.movel(10.02, 215.18);
      arm.movep(4.02, 209.18);
      delay(700);
      arm.movepp(-20.71, 178.11);
      return ;
    } else if (aimInfo2[1] == 3 ) {
      arm.movepp(-33.12, 202.30);
      arm.movez(putdownHeight);
      arm.movel(-22.12, 212.30);
      delay(700);
      arm.movepp(-67.17, 164.36);
      return ;
    } else if (aimInfo2[1] == 4 ) {
      arm.movepp(-72.09, 192.07);
      arm.movez(putdownHeight);
      arm.movel(-62.09, 202.07);
      delay(700);
      arm.movepp(-105.56, 139.72);
      return ;
    } else if (aimInfo2[1] == 5 ) {
      arm.movepp(-110.35, 190.29);
      arm.movez(putdownHeight);
      arm.movel(-102.35, 196.29);
      delay(700);
      arm.movepp(-112.84, 150.41);
      return ;
    }

  } else {
    if (aimInfo2[1] == 0) {
      arm.movepp(77.56, 160.56);
      arm.movez(putdownHeight);
      arm.movepp(93.16, 171.95);
      arm.movepp(50.59, 169.04);

      arm.movepp(8.23, 156.57);

      return;
    } else if (aimInfo2[1] == 1) {
      arm.movepp(42.60, 168.45);
      arm.movez(putdownHeight);
      arm.movepp(-17.66, 146.79);
      return;
    } else if (aimInfo2[1] == 2) {
      arm.movepp(1.97, 165.42);
      arm.movez(putdownHeight);
      arm.movepp(5.97, 171.42);
      arm.movepp(-40.45, 146.88);
      return;
    }  else if (aimInfo2[1] == 3) {
      arm.movepp(-37.63, 160.79);
      arm.movez(putdownHeight);
      arm.movepp(-32.63, 171.79);
      arm.movel(-56.58, 138.64);
      return;
    }  else if (aimInfo2[1] == 4) {
      arm.movepp(-72.91, 157.72);
      arm.movez(putdownHeight);
      arm.movepp(-90.25, 131.75);
      return;
    }  else if (aimInfo2[1] == 5) {
      arm.movepp(-115.13, 156.23);
      arm.movez(putdownHeight);
      arm.movepp(-120.25, 126.20);
      return;
    }
  }
  return;
}
void mvBackYello() {
  if ( aimInfo2[0] == 0) {
    if (aimInfo2[1] == 0) {
      arm.movez(putdownHeight);
      arm.movepp(84.65, 207.24);
      arm.movepp(53.65, 194.71);
    } else if (aimInfo2[1] == 1) {
      arm.movepp(30.09, 200.52);
      arm.movez(putdownHeight);
      arm.movel(-0.58, 189.27);
      return;
    } else if (aimInfo2[1] == 2) {
      arm.movepp(4.02, 209.18);
      arm.movez(putdownHeight);
      arm.movepp(-20.71, 178.11);
      return ;
    } else if (aimInfo2[1] == 3 ) {
      arm.movepp(-33.12, 202.30);
      arm.movez(putdownHeight);
      arm.movepp(-28.12, 209.30);
      delay(700);
      arm.movepp(-62.17, 169.36);
      return ;
    } else if (aimInfo2[1] == 4 ) {
      arm.movepp(-67.28, 192.70);
      arm.movez(putdownHeight);
      arm.movel(-60.28, 197.70);
      delay(700);
      arm.movel(-86.49, 165.56);
      return ;
    } else if (aimInfo2[1] == 5 ) {
      arm.movepp(-112.35, 192.29);
      arm.movez(putdownHeight);
      arm.movepp(-112.84, 150.41);
      return ;
    }

  } else {
    if (aimInfo2[1] == 0) {
      arm.movepp(80.17, 162.72);
      arm.movez(putdownHeight);
      arm.movepp(42.72, 151.92);
      return;
    } else if (aimInfo2[1] == 1) {
      arm.movepp(42.15, 168.96);
      arm.movez(putdownHeight);
      arm.movepp(6.47, 153.70);
      return;
    } else if (aimInfo2[1] == 2) {
      arm.movepp(3.25, 162.55);
      arm.movepp(8.25, 167.55);
      arm.movez(putdownHeight);
      arm.movepp(-40.45, 146.88);
      return;
    }  else if (aimInfo2[1] == 3) {
      arm.movepp(-37.27, 164.07);
      arm.movez(putdownHeight);
      arm.movepp(-31.27, 170.07);
      delay(700);
      arm.movepp(-60.15, 143.19);
      return;
    }  else if (aimInfo2[1] == 4) {
      arm.movepp(-72.91, 157.72);
      arm.movez(putdownHeight);
      arm.movepp(-65.91, 164.72);
      delay(700);
      arm.movepp(-90.25, 131.75);
      return;
    }  else if (aimInfo2[1] == 5) {

      arm.movepp(-115.13, 156.23);
      arm.movez(putdownHeight);
      arm.movepp(-109.13, 150.23);
      delay(700);
      arm.movepp(-120.25, 126.20);
      return;
    }
  }

  return;
}


void mvBackGreen() {
  int row = 0;
  int column = 0;
  if (aimInfo[0] == '1') {
    row = aimInfo[0];
    column = (int)aimInfo[1] + 6;
  } else {
    row = (int)aimInfo[1];
    column = row;
  }
  int init_deg1 = arm.pul2deg(arm.ReadPos(1) - arm.offset.m1_deg);
  int init_deg2 = arm.pul2deg(arm.ReadPos(2) - arm.offset.m2_deg);
  mx = link1L * sin(radians(init_deg1)) + link2L * sin(radians(init_deg1) + radians(init_deg2));
  my = link1L * cos(radians(init_deg1)) + link2L * cos(radians(init_deg1) + radians(init_deg2));
  double x  = mx;
  double y  = my;
  if ( aimInfo2[0] == 0) {
    if (aimInfo2[1] == 0) {
      arm.movez(putdownHeight);
      arm.movepp(84.65, 207.24);
      arm.movepp(53.65, 194.71);
    } else if (aimInfo2[1] == 1) {
      arm.movepp(30.09, 200.52);
      arm.movez(putdownHeight);
      arm.movel(-0.58, 189.27);
      return;
    } else if (aimInfo2[1] == 2) {
      arm.movepp(4.02, 209.18);
      arm.movez(putdownHeight);
      arm.movepp(-20.71, 178.11);
      return ;
    } else if (aimInfo2[1] == 3 ) {
      arm.movepp(-33.12, 202.30);
      arm.movez(putdownHeight);
      arm.movepp(-62.17, 169.36);
      return ;
    } else if (aimInfo2[1] == 4 ) {
      arm.movepp(-68.22, 202.80);
      arm.movez(putdownHeight);
      arm.movepp(-94.77, 155.04);
      return ;
    } else if (aimInfo2[1] == 5 ) {
      arm.movepp(-109.62, 194.33);
      arm.movez(putdownHeight);
      arm.movepp(-124.15, 128.10);
      return ;
    }

  } else {
    if (aimInfo2[1] == 0) {
      arm.movepp(80.17, 162.72);
      arm.movez(putdownHeight);
      arm.movepp(47.72, 156.92);
      return;
    } else if (aimInfo2[1] == 1) {
      arm.movepp(42.15, 168.96);
      arm.movez(putdownHeight);
      arm.movepp(6.47, 153.70);
      return;
    } else if (aimInfo2[1] == 2) {
      arm.movepp(3.25, 162.55);
      arm.movez(putdownHeight);
      arm.movepp(-40.45, 146.88);
      return;
    }  else if (aimInfo2[1] == 3) {
      arm.movepp(-37.27, 164.07);
      arm.movez(putdownHeight);
      arm.movepp(-60.15, 143.19);
      return;
    }  else if (aimInfo2[1] == 4) {
      arm.movepp(-72.91, 157.72);
      arm.movez(putdownHeight);
      arm.movepp(-90.25, 131.75);
      return;
    }  else if (aimInfo2[1] == 5) {
      arm.movepp(-106.31, 156.59);
      arm.movez(putdownHeight);
      arm.movepp(-126.82, 92.18);
      return;
    }
  }

  return;
}
//파란색은 이미 앞에 있으므로 안나누어도 됨. >> 그리퍼 로부터 일정거리 떨어진 위치의 역기구학 계산해서 movel
void mvBackBlue() {
  arm.movez(0);
  int init_deg1 = arm.pul2deg(arm.ReadPos(1) - arm.offset.m1_deg);
  int init_deg2 = arm.pul2deg(arm.ReadPos(2) - arm.offset.m2_deg);
  mx = link1L * sin(radians(init_deg1)) + link2L * sin(radians(init_deg1) + radians(init_deg2));
  my = link1L * cos(radians(init_deg1)) + link2L * cos(radians(init_deg1) + radians(init_deg2));
  double x  = mx;
  double y  = my;
  if (aimInfo2[0] == 1) {
    if (aimInfo2[1] == 0) {
      mx = link1L * sin(radians(1)) + link2L * sin(radians(1) + radians(init_deg2));
      double x  = mx;
      arm.moveppp(x, y);
      return;
    }
    arm.movel(x, y);
  } else {
    arm.movepp(x, y);
  }
  return;
}
