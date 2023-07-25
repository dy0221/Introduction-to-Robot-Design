
//4칸씩 나누어서 rgb 체크
void chk_rgb1() {


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

  for (int i = 0; i < pixy.ccc.numBlocks; i++) {

    // [0][0]
    if (pixy.ccc.blocks[i].m_x <186  &&pixy.ccc.blocks[i].m_x > 114&& pixy.ccc.blocks[i].m_y < 97  && pixy.ccc.blocks[i].m_y > 29) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[0][0] = 'b';
          break;
        case 2 :
          aimArray[0][0] = 'r';
          break;
        case 3 :
          aimArray[0][0] = 'y';
          break;
        case 4 :
          aimArray[0][0] = 'g';
          break;
        default:
          aimArray[0][0] = 'n';
          break;
      }
    }

    // [0][1]
    if (pixy.ccc.blocks[i].m_x < 276 && pixy.ccc.blocks[i].m_x > 205 && pixy.ccc.blocks[i].m_y < 65&& pixy.ccc.blocks[i].m_y > 2) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[0][1] = 'b';
          break;
        case 2 :
          aimArray[0][1] = 'r';
          break;
        case 3 :
          aimArray[0][1] = 'y';
          break;
        case 4 :
          aimArray[0][1] = 'g';
          break;
        default:
          aimArray[0][1] = 'n';
          break;
      }
    }
    // [1][0]
    if (pixy.ccc.blocks[i].m_x < 215 && pixy.ccc.blocks[i].m_x > 145&& pixy.ccc.blocks[i].m_y > 120 && pixy.ccc.blocks[i].m_y < 190) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[1][0] = 'b';
          break;
        case 2 :
          aimArray[1][0] = 'r';
          break;
        case 3 :
          aimArray[1][0] = 'y';
          break;
        case 4 :
          aimArray[1][0] = 'g';
          break;
        default:
          aimArray[1][0] = 'n';
          break;
      }
    }
    // [1][1]
    if (pixy.ccc.blocks[i].m_x < 295 && pixy.ccc.blocks[i].m_x > 240 && pixy.ccc.blocks[i].m_y > 95 && pixy.ccc.blocks[i].m_y < 165 ) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[1][1] = 'b';
          break;
        case 2 :
          aimArray[1][1] = 'r';
          break;
        case 3 :
          aimArray[1][1] = 'y';
          break;
        case 4 :
          aimArray[1][1] = 'g';
          break;
        default:
          aimArray[1][1] = 'n';
          break;
      }
    }
  }
}


void chk_rgb2() {


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

  for (int i = 0 ; i < pixy.ccc.numBlocks; i++) {
    // [0][2]
    if (pixy.ccc.blocks[i].m_x < 159 && pixy.ccc.blocks[i].m_x > 84 && pixy.ccc.blocks[i].m_y > 2 && pixy.ccc.blocks[i].m_y < 68 ) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[0][2] = 'b';
          break;
        case 2 :
          aimArray[0][2] = 'r';
          break;
        case 3 :
          aimArray[0][2] = 'y';
          break;
        case 4 :
          aimArray[0][2] = 'g';
          break;
        default:
          aimArray[0][2] = 'n';
          break;
      }
    }

    // [0][3]
    if (pixy.ccc.blocks[i].m_x < 227 && pixy.ccc.blocks[i].m_x > 160 && pixy.ccc.blocks[i].m_y > 70 && pixy.ccc.blocks[i].m_y < 134 ) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[0][3] = 'b';
          break;
        case 2 :
          aimArray[0][3] = 'r';
          break;
        case 3 :
          aimArray[0][3] = 'y';
          break;
        case 4 :
          aimArray[0][3] = 'g';
          break;
        default:
          aimArray[0][3] = 'n';
          break;
      }
    }
    // [1][2]
    if (pixy.ccc.blocks[i].m_x < 80 && pixy.ccc.blocks[i].m_x > 5 && pixy.ccc.blocks[i].m_y > 70 && pixy.ccc.blocks[i].m_y < 145 ) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[1][2] = 'b';
          break;
        case 2 :
          aimArray[1][2] = 'r';
          break;
        case 3 :
          aimArray[1][2] = 'y';
          break;
        case 4 :
          aimArray[1][2] = 'g';
          break;
        default:
          aimArray[1][2] = 'n';
          break;
      }
    }
    // [1][3]
    if (pixy.ccc.blocks[i].m_x < 155 && pixy.ccc.blocks[i].m_x > 85 && pixy.ccc.blocks[i].m_y > 143 && pixy.ccc.blocks[i].m_y < 200 ) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[1][3] = 'b';
          break;
        case 2 :
          aimArray[1][3] = 'r';
          break;
        case 3 :
          aimArray[1][3] = 'y';
          break;
        case 4 :
          aimArray[1][3] = 'g';
          break;
        default:
          aimArray[1][1] = 'n';
          break;
      }
    }
  }
}


void chk_rgb3() {


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

  for (int i = 0; i < pixy.ccc.numBlocks; i++) {
    
    // [0][4]
    if (pixy.ccc.blocks[i].m_x < 135 && pixy.ccc.blocks[i].m_x > 75 && pixy.ccc.blocks[i].m_y > 5 && pixy.ccc.blocks[i].m_y < 70 ) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[0][4] = 'b';
          break;
        case 2 :
          aimArray[0][4] = 'r';
          break;
        case 3 :
          aimArray[0][4] = 'y';
          break;
        case 4 :
          aimArray[0][4] = 'g';
          break;
        default:
          aimArray[0][4] = 'n';
          break;
      }
    }

    // [0][5]
    if (pixy.ccc.blocks[i].m_x < 238 && pixy.ccc.blocks[i].m_x > 165 && pixy.ccc.blocks[i].m_y > 35 && pixy.ccc.blocks[i].m_y < 108 ) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[0][5] = 'b';
          break;
        case 2 :
          aimArray[0][5] = 'r';
          break;
        case 3 :
          aimArray[0][5] = 'y';
          break;
        case 4 :
          aimArray[0][5] = 'g';
          break;
        default:
          aimArray[0][5] = 'n';
          break;
      }
    }
    // [1][4]
    if (pixy.ccc.blocks[i].m_x < 108 && pixy.ccc.blocks[i].m_x > 43 && pixy.ccc.blocks[i].m_y > 96 && pixy.ccc.blocks[i].m_y < 160 ) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[1][4] = 'b';
          break;
        case 2 :
          aimArray[1][4] = 'r';
          break;
        case 3 :
          aimArray[1][4] = 'y';
          break;
        case 4 :
          aimArray[1][4] = 'g';
          break;
        default:
          aimArray[1][4] = 'n';
          break;
      }
    }
    // [1][5]
    if (pixy.ccc.blocks[i].m_x < 206 && pixy.ccc.blocks[i].m_x > 136 && pixy.ccc.blocks[i].m_y > 132 && pixy.ccc.blocks[i].m_y < 200 ) {
      switch (pixy.ccc.blocks[i].m_signature) {
        case 1 :
          aimArray[1][5] = 'b';
          break;
        case 2 :
          aimArray[1][5] = 'r';
          break;
        case 3 :
          aimArray[1][5] = 'y';
          break;
        case 4 :
          aimArray[1][5] = 'g';
          break;
        default:
          aimArray[1][5] = 'n';
          break;
      }
    }
  }
}
