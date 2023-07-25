/*
  movep(double x, double y),movep(double x, double y, double z) (mm)
  movel(double x, double y),movel(double x, double y, double z) (mm)
  movez(float z) (cm)
  movepp 원래 movep함수
  moveppp sigularity 피하려고 만든 함수
*/
#include <AIROARM.h>
#include <Wire.h>

AiroArm    arm;

// NOTE, THIS PROGRAM REQUIRES FIRMWARE VERSION 3.0.11 OR GREATER
#include <stdio.h>
#include <Pixy2SPI_SS.h>
// TCS34725 라이브러리 사용을 위한 객체 생성

Pixy2SPI_SS pixy;
//====================================================================================================
/*
   (0,0)  (2,2)
   (1,1)  (3,3)
*/
//물체 집기 전 초기 위치
#define initX0 148.62
#define initX1 147.92
#define initX2 -146.86
#define initX3 -143.74

#define initY0 87.36
#define initY1 77.19
#define initY2 97.81
#define initY3 75.97

//그 이외의 변수
#define pickHeight 31
#define putdownHeight 0
#define button 12
#define led 33
#define redled 45
#define greenled 44
#define blueled 46
//배열 크기=========================================================================================
#define aimRows    2
#define aimColumns 6

#define objectRows   2
#define objectColumns 2
//FK를 계산할 변수==================================================================================
#define link1L 150.21
#define link2L 30
double mx, my;
//버튼 변수=========================================================================================
bool buttonState = true;
//컬러 저장 변수=====================================================================================
char aimArray[aimRows][aimColumns] = {
  {'n', 'n', 'n', 'n', 'n', 'n'},
  {'n', 'n', 'n', 'n', 'n', 'n'}
};
char objectArray[objectRows][objectColumns] = {
  {'n', 'n'},
  {'n', 'n'}
};
//움직여야할 위치를 저장할 변수========================================================================
//rgb 확인
double aimXlocation[6] = {93.28, aimXlocation[0] - 40, aimXlocation[1] - 40, aimXlocation[2] - 40, aimXlocation[3] - 40, aimXlocation[4] - 40};
double aimYlocation[2] = {221.12, aimYlocation[0] - 50};

double objecXlocation[4] = {143.71 , 158.03, -148.20, -158.32};
double objecYlocation[4] = {135.52,  68.88, 128.86,   60.92} ;//y
//pick object
double objecRedXlocation[4]   = {177.63, 189.69, -187.86, -187.34};
double objecRedYlocation[4]   = {148.46, 50.85 , 124.36, 26.91};
double objecYelloXlocation[4] = {195.05, 191.22, -184.91, -184.15};
double objecYelloYlocation[4] = {143.66, 45.71, 136.87, 32.60};
double objecGreenXlocation[4] = {174.17, 191.11, -184.91, -191.84};
double objecGreenYlocation[4] = {145.05, 48.49, 137.92, 36.24};
double objecBlueXlocation[4]  = {173.95, 181.73, -177.18, -178.17};
double objecBlueYlocation[4]  = {137.28, 48.28,  131.75, 42.67};
//mv aim
double aimInitXlocation[6] = {78.86, 40.92, 11.53, -31.49, -66.38, -101.54};  //12.68
double aimInitYlocation[2] = {159.63, 159.63};  //171.95
//                                0      1      2       3       4        5          6       7      8         9      10       11
double aimRedXlocation[12] = {96.42,  55.65,   15.49,  -21.19, -61.56, - 97.19,  99.16,  60.43,  23.75,  -19.65,  -59.53, -98.22};
double aimRedYlocation[12] = {215.33, 212.76, 212.57, 212.19, 213.67, 208.24,      177.95, 172.74, 173.39, 171.90, 177.06, 170.06};

double aimYelloXlocation[12] = {93.84, 54.04,  17.60,  -19.19, -59.19, -97.86, 97.79,  58.7,  19.0,    -18.68,  -59.74, -94.07};
double aimYelloYlocation[12] = {214.28, 211.58, 212.19, 211.19, 211.04, 209.95, 173.30, 170.22, 170.17, 174.78, 172.27, 169.67};

double aimGreenXlocation[12] = {93.84, 50.55,  17.60,  -21.19, -59.19, -97.86, 94.79,  55.7,  17.0,  -21.68,  -61.74, -98.72};
double aimGreenYlocation[12] = {214.28, 213.28, 212.19, 212.19, 209.04, 209.95, 173.30, 170.22, 170.17, 173.78, 172.27, 169.51};
//                              0        1      2          3       4       5     6        7      8         9        10
double aimBlueXlocation[12] = {83.04,  49.04, 9.81 ,   -29.58, -65.77, -99.94,  82.45,  45.02,  8.37, -27.59, -67.36, -103.57};
double aimBlueYlocation[12] = {205.49, 205.39, 203.08, 201.87, 199.64 , 196.00, 169.36, 166.94, 170.24, 166.04, 160.17, 158.42} ;

//움직여야할 목표 좌표와 색을 저장하는 변수=================================================================================
char aimInfo[1] = {'n'};
int aimInfo2[2] = { -1, -1};
int redInfo[2] = { -1, -1};
int yelloInfo[2] = { -1, -1 };
int greenInfo[2] = { -1, -1 };
int blueInfo[2] = { -1, -1 };
//반복문을 카운트할 변수=================================================================================================
int forCount  = 0;
int myRow    = 0;
int myColumn = 0;


void setup() {
  Serial.begin(115200);
  Serial1.begin(1000000);

  Serial.print("Starting...\n");
  pixy.init();
  //  pixy.setLamp(1,1);
  //   Getting the RGB pixel values requires the 'video' program
  pixy.changeProg("video");
  arm.pSerial = &Serial1;

  pinMode(button, INPUT_PULLUP);
  pinMode(A0 , OUTPUT);
  digitalWrite(A0, 0);
  // torque off
  arm.EnableTorque(SHOULDER_ID, 0);
  arm.EnableTorque(ELBOW_ID, 0);
  //adjust ininital defalut angle to motor1,2 (2048)
  arm.offset.m1_deg = 1;
  arm.offset.m2_deg = -1;

  //led
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
}

void loop() {
  if (buttonState) {
    chkBtn();
    chkRGB();
    chk_rgb1();
    printAim();
    chkInfoDgree(1);
    chkInfoLocation(1);
    Serial.println("");
    //    delay(1000);
  } else if (buttonState == false) {
    //main code
    pixy.ccc.getBlocks();
    arm._init();
    //check=========================
    checkAim();
    arm.movez(pickHeight);
    chkInfoDgree(500);
    checkObject();
    arm.movep(1, 1000);
    //move == == == == == == == == == == == == ==
    findObject();
    while (1) {
      findAim();
      printAim();
      bool result = pickBolt();
      if (result) continue;
      bool result2 = mvBolt();
      if (result2) continue;
      putdownBolt();
      aimArray[myRow][myColumn] = 'n';
      printAim();
      arm.movez(pickHeight);
      arm.movep(1, 1000);
      bool chkd = chkDone();
      if (chkd) break;
    }
    finish();
  }
}
