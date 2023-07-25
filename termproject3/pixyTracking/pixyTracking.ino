#define SerialA Serial2
#define SerialB Serial3
#include <Pixy2SPI_SS.h>
#include <PIDLoop.h>

Pixy2SPI_SS pixy;
PIDLoop panLoop(350, 0, 228, true);
PIDLoop tiltLoop(500, 0, 228, true);



byte tx_dataA[7];
byte checksumA = 0;

byte tx_dataB[7];
byte checksumB = 0;

int tilt = tiltLoop.m_command;
int pan = panLoop.m_command;

int ma1 = 0;
int ma2 = 0;
int mb1 = 0;
int mb2 = 0;

int x = pixy.ccc.blocks[0]. m_x;
int y = pixy.ccc.blocks[0].m_y;
int width = pixy.ccc.blocks[0].m_width;
int height = pixy.ccc.blocks[0].m_height;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Starting...\n");

  // We need to initialize the pixy object
  pixy.init();
  // Use color connected components program for the pan tilt to track
  pixy.changeProg("color_connected_components");

  SerialA.begin(115200);
  SerialB.begin(115200);
  tx_dataA[0] = 0xFF; //Header 1
  tx_dataA[1] = 0xFF; //Header
  tx_dataB[0] = 0xFF; //Header 1
  tx_dataB[1] = 0xFF; //Header


}


void loop() {
  // put your main code here, to run repeatedly:
  //
  pixy_tracking();
  pixy_check();

  sendmotorA(ma1, ma2);
  sendmotorB(mb1, mb2);

//      sendmotorA(53,53);
//      sendmotorB(53,53);




  //
  //  Serial.print(ma1);
  //  Serial.print("    ");
  //  Serial.print(ma2);
  //  Serial.print("    ");
  //  Serial.print(mb1);
  //  Serial.print("    ");
  //  Serial.print(mb2);
  //  Serial.print("    ");
  //  Serial.print(panLoop.m_command);
  //  Serial.print("    ");
  //  Serial.println(pixy.ccc.blocks[0].m_width);


}
//==============]=============================================
void pixy_check() {
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks) {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (int i = 0; i < pixy.ccc.numBlocks; i++) {
      Serial.print("block");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
    }
  }
}

void speed_setting() {
  // 중앙값 pan tilt 500 500
  // 가만히 있어야 하는 width 250


  //////전진
  //  sendmotorA(30, 30);
  //  sendmotorB(30, 30);

  //////후진
  //  sendmotorA(-30, -30);
  //  sendmotorB(-30, -30);

  //////좌
  //  sendmotorA(-30, -30);
  //  sendmotorB(30, 30);

  //////우
  //  sendmotorA(30, 30);
  //  sendmotorB(-30, -30);

  //////우전진대각
  //  sendmotorA(30, 30);
  //  sendmotorB(0, 0);

  //////좌전진대각
  //  sendmotorA(0, 0);
  //  sendmotorB(30, 30);

  //////우후진대각
  //  sendmotorA(0, 0);
  //  sendmotorB(-30, -30);

  //////좌후진대각
  //  sendmotorA(-30, -30);
  //  sendmotorB(0, 0);

  //////제자리 회전(우)
  //  sendmotorA(30,-30);
  //  sendmOtorB(-30,30);

  //////제자리 회전(좌)
  //   sendmotorA(-30,30);
  //   sendmotorB(30,-30);


}


void pixy_tracking() {

  static int i = 0;
  int j;
  char buf[64];
  int32_t panOffset, tiltOffset;

  // get active blocks from Pixy
  pixy.ccc.getBlocks();

  if (pixy.ccc.numBlocks)
  {
    i++;

    if (i % 60 == 0)
      Serial.println(i);

    // calculate pan and tilt "errors" with respect to first object (blocks[0]),
    // which is the biggest object (they are sorted by size).
    panOffset = (int32_t)pixy.frameWidth / 2 - (int32_t)pixy.ccc.blocks[0].m_x;
    tiltOffset = (int32_t)pixy.ccc.blocks[0].m_y - (int32_t)pixy.frameHeight / 2;

    // update loops
    panLoop.update(panOffset);
    tiltLoop.update(tiltOffset);

    // set pan and tilt servos
    pixy.setServos(panLoop.m_command, tiltLoop.m_command);

#if 0 // for debugging
    sprintf(buf, "%ld %ld %ld %ld", rotateLoop.m_command, translateLoop.m_command, left, right);
    Serial.println(buf);
#endif

  }
  else // no object detected, go into reset state
  {

    pixy.setServos(panLoop.m_command, 200);
  }

  if (pixy.ccc.numBlocks) {
    int spd = pixy.ccc.blocks[0].m_width;
    delay(3);
    spd = map(spd, 80 , 650, 50, -50);

    if ( tiltLoop.m_command > 800 || tiltLoop.m_command < 200)
    {
      spd = spd * 0.7;
    }
    Serial.print(pixy.ccc.blocks[0].m_width);
    Serial.print("      ");
    Serial.println(spd);
    //


    if (250 < panLoop.m_command && panLoop.m_command < 750) {
      ma1 = spd;
      ma2 = spd;
      mb1 = spd;
      mb2 = spd;

    }

    //물체가 왼쪽에 있을 때
    else if (panLoop.m_command > 750 && panLoop.m_command < 850) {
      if (pixy.ccc.blocks[0].m_width < 55) {
        ma1 = -spd;
        ma2 = -spd;
        mb1 = 50;
        mb2 = 50;
        //        if (ma1 > 0) ma1 = 0;
        //        if (ma2 > 0) ma2 = 0;
      }
      else if (pixy.ccc.blocks[0].m_width > 55 ) {
        ma1 = -50;
        ma2 = -50;
        mb1 = spd;
        mb2 = spd;
        //        if (mb1 < 0) mb1 = 0;
        //        if (mb2 < 0) mb2 = 0;
      }
    }

    //물체가 pixy 오른쪽에 있을 때
    else if (panLoop.m_command < 250 && panLoop.m_command > 150) {
      if (pixy.ccc.blocks[0].m_width < 55) {
        ma1 = 50;
        ma2 = 50;
        mb1 = -spd;
        mb2 = -spd;

        //        if (mb1 > 0) mb1 = 0;
        //        if (mb2 > 0) mb2 = 0;


      }
      else if (pixy.ccc.blocks[0].m_width > 55) {
        ma1 = spd;
        ma2 = spd;
        mb1 = -50;
        mb2 = -50;

        //        if (ma1 < 0) ma1 = 0;
        //        if (ma2 < 0) ma2 = 0;
      }

    }


    // 물체 정 중앙에 있을 때
    //pixy 너무 돌아갔을 때 시계방향 회전
    else if (panLoop.m_command < 150 ) {
      ma1 = 50;
      ma2 = -50;
      mb1 = -50;
      mb2 = 50;
    }

    // pixy 너무 돌아갔을 때 반시계방향 회전
    else if ( panLoop.m_command > 850) {
      ma1 = -50;
      ma2 = 50;
      mb1 = 50;
      mb2 = -50;
    }

  }
  // pixy가 아무것도 인식하지 못했을 때
  else if (panLoop.m_command <= 500)
  {
    ma1 = 40;
    ma2 = -40;
    mb1 = -40;
    mb2 = 40;
  }

  else if (panLoop.m_command > 500)
  {
    ma1 = -40;
    ma2 = 40;
    mb1 = 40;
    mb2 = -40;
  }
}



void sendmotorA(int m1, int m2) {
  if (m1 < 0) {
    tx_dataA[2] = 0x00;
    m1 *= -1;
  }
  else tx_dataA[2] = 0x01;

  if (m1 > 255) m1 = 255;
  tx_dataA[3] = m1;

  if (m2 < 0) {
    tx_dataA[4] = 0x00;
    m2 *= -1;
  }
  else tx_dataA[4] = 0x01;

  if (m2 > 255) m2 = 255;
  tx_dataA[5] = m2;


  checksumA = 0;
  for (int i = 2; i < 6; i++) checksumA ^= tx_dataA[i];
  checksumA += 1;
  tx_dataA[6] = checksumA;
  SerialA.write(tx_dataA, 7);
}


void sendmotorB(int m1, int m2) {
  if (m1 < 0) {
    tx_dataB[2] = 0x00;
    m1 *= -1;
  }
  else tx_dataB[2] = 0x01;

  if (m1 > 255) m1 = 255;
  tx_dataB[3] = m1;

  if (m2 < 0) {
    tx_dataB[4] = 0x00;
    m2 *= -1;
  }
  else tx_dataB[4] = 0x01;

  if (m2 > 255) m2 = 255;
  tx_dataB[5] = m2;


  checksumB = 0;
  for (int i = 2; i < 6; i++) checksumB ^= tx_dataB[i];
  checksumB += 1;
  tx_dataB[6] = checksumB;
  SerialB.write(tx_dataB, 7);
}
