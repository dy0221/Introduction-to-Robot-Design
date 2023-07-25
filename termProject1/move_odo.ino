void move_odometry1() {
  //장애물 감지 x가 입구말고 아래 벽 까지
  if (x1 > 175 && x1 < 177) x_finish = 1;
  if (y1 > 20 && y1 < 25) y_finish = 1;
   //정지
  if (left_ultra_flag && right_ultra_flag ) {
    delay(800);
    sendmotor(0, 0);
    mode4_flag = 0;
    delay(1111111);
  }
  if (x_finish == 0) {
    //앞에 인식하면 왼쪽으로 90도 회전 우선순위 1번 >> 회전후 움직이는 동안은 직진의 우선순위 증가
    if (front_ultra_flag) {
      mode4_index = 1;
      return;
    }
    //왼쪽으로 돈 상태에서 오른쪽이 감지 되면 감지된값 저장 우선순위 2번
    if (right_ultra_flag  && turn_left_count > 0) pre_right_flag = right_ultra_flag;
    //왼쪽으로 돈 상태에서 오른쪽이 감지가 안되면 약간의 딜레이를 위하여 밀리스
    if (pre_right_flag != right_ultra_flag && turn_left_count > 0) {
      pre_right_flag = right_ultra_flag;  // 0,0
      odometry_millis = millis();
    }
    //장애물을 완전이 벗어나면 오른쪽 회전
    if (right_ultra_flag == 0 && millis() - odometry_millis > 1000 && turn_left_count > 0) {
      mode4_index = 2;
      turn_left_count --;
      if (turn_left_count <= 0) move_priority = 0;
      return;
    }
    //장애물을 지나는 동안은 직진만 하기 우선순위3
    if (move_priority) {
      sendmotor(30, 30);
      return;
    }

    //아무것도 아닌상태
    //가장자리가 검출 되었을때  우선순위 4

    if (side_right_ultra_flag && (side_left_ultra_flag == 0)) {
      sendmotor(-30, 0);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if ((side_right_ultra_flag == 0 ) && side_left_ultra_flag) {
      sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if (side_right_ultra_flag && side_left_ultra_flag) {
      //오른쪽이 더 가까울때,
      if (distance4 < distance5) sendmotor(-30, 0);
      //왼쪽이 더 가까울때,
      else                       sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    }
    //0도 보정
    if ((front_ultra_flag == 0) && (side_left_ultra_flag == 0) && (side_right_ultra_flag == 0) && (right_ultra_flag == 0) && (left_ultra_flag == 0) && balance_flag && (millis() - odometry_millis > 850)) {
      mode4_index = 3;
      return;
    }
    //아무것도 아닐때 직진 우선순위 5
    sendmotor(30, 30);
    return;
  }
  if (y_first_count == 0 && x_finish) {
    mode4_index = 4;
    return;
  }
  if (y_finish == 0) {
    //앞에 인식하면 왼쪽으로 90도 회전 우선순위 1번
    if (front_ultra_flag) {
      mode4_index = 1;
      return;
    }
    //왼쪽으로 돈 상태에서 오른쪽이 감지 되면 감지된값 저장 우선순위 2번
    if (right_ultra_flag  && turn_left_count > 0) pre_right_flag = right_ultra_flag;
    //왼쪽으로 돈 상태에서 오른쪽이 감지가 안되면 약간의 딜레이를 위하여 밀리스
    if (pre_right_flag != right_ultra_flag && turn_left_count > 0) {
      pre_right_flag = right_ultra_flag;
      odometry_millis = millis();
    }
    //장애물을 완전이 벗어나면 오른쪽 회전
    if (right_ultra_flag == 0 && millis() - odometry_millis > 1000 && turn_left_count > 0) {
      mode4_index = 2;
      turn_left_count --;
      if (turn_left_count <= 0) move_priority = 0;
      return;
    }
    //장애물을 지나는 동안은 직진만 하기 우선순위3
    if (move_priority) {
      sendmotor(30, 30);
      return;
    }

    //아무것도 아닌상태
    //가장자리가 검출 되었을때  우선순위 4

    if (side_right_ultra_flag && (side_left_ultra_flag == 0)) {
      sendmotor(-30, 0);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if ((side_right_ultra_flag == 0 ) && side_left_ultra_flag) {
      sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if (side_right_ultra_flag && side_left_ultra_flag) {
      //오른쪽이 더 가까울때,
      if (distance4 < distance5) sendmotor(-30, 0);
      //왼쪽이 더 가까울때,
      else                       sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    }
    //-90도 보정
    if ((front_ultra_flag == 0) && (side_left_ultra_flag == 0) && (side_right_ultra_flag == 0) && (right_ultra_flag == 0) && (left_ultra_flag == 0) && balance_flag && (millis() - odometry_millis > 850)) {
      mode4_index = 5;
      return;
    }
    //아무것도 아닐때 직진 우선순위 5
    sendmotor(30, 30);
    return;
  }
  //x값이 틀어졌을 경우
  if (x_finish && y_finish) {
    if (x1 < 165) {
      x_finish = 0;
      mode4_index = 3;
      y_first_count = 0;
      return;
    }
  }
  if (x_finish && y_finish) {
    //parking
    if (left_ultra_flag && right_ultra_flag ) {
      delay(800);
      sendmotor(0, 0);
      mode4_flag = 0;
      delay(1111111);
    }
    sendmotor(13, 15);
    if (side_right_ultra_flag && side_left_ultra_flag == 0) {
      sendmotor(-30, 0);
      return;
    } else if (side_right_ultra_flag == 0 && side_left_ultra_flag) {
      sendmotor(0, -30);
      return;
    } else if (side_right_ultra_flag && side_left_ultra_flag) {
      //오른쪽이 더 가까울때,
      if (distance4 < distance5) sendmotor(-30, 0);
      //왼쪽이 더 가까울때,
      else                       sendmotor(0, -30);
      return;
    }
  }
}

//----------------------------------------------------------------------------------------------------
void move_odometry2() {

  if (x1 > 90) x_finish = 1;
  else if ( x1 < 90) x_finish = 0;

  if (y1 > 129 && y1 < 132) y_finish = 1;
   //정지
  if (left_ultra_flag && right_ultra_flag ) {
    delay(800);
    sendmotor(0, 0);
    mode4_flag = 0;
    return;
  }
  if (y_finish == 0) {
    // 앞에 인식하면 오른쪽으로 회전
    if (front_ultra_flag) {
      mode4_index = 2;
      return;
    }
    // 오른쪽으로 돈 상태에서 왼쪽이 감지 되면 감지된 값 저장 우선순위 2번
    if (left_ultra_flag  && turn_right_count > 0) pre_left_flag = left_ultra_flag;
    //왼쪽으로 돈 상태에서 오른쪽이 감지가 안되면 약간의 딜레이를 위하여 밀리스
    if (pre_left_flag != left_ultra_flag && turn_right_count > 0) {
      pre_left_flag = left_ultra_flag;
      odometry_millis = millis();
    }
    //장애물을 완전히 벗어나면 왼쪽 회전
    if (left_ultra_flag == 0 && millis() - odometry_millis > 1000 && turn_right_count > 0) {
      mode4_index = 1;
      turn_right_count --;
      if (turn_right_count <= 0) move_priority = 0;
      return;
    }
    //장애물을 지나는 동안은 직진만 하기 우선순위3
    if (move_priority) {
      sendmotor(30, 30);
      return;
    }

    //아무것도 아닌상태
    //가장자리가 검출 되었을때  우선순위 4

    if (side_right_ultra_flag && (side_left_ultra_flag == 0)) {
      sendmotor(-30, 0);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if ((side_right_ultra_flag == 0 ) && side_left_ultra_flag) {
      sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if (side_right_ultra_flag && side_left_ultra_flag) {
      //오른쪽이 더 가까울때,
      if (distance4 < distance5) sendmotor(-30, 0);
      //왼쪽이 더 가까울때,
      else                       sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    }

    //90도 보정
    if ((front_ultra_flag == 0) && (side_left_ultra_flag == 0) && (side_right_ultra_flag == 0) && (right_ultra_flag == 0) && (left_ultra_flag == 0) && balance_flag && (millis() - odometry_millis > 850)) {
      mode4_index = 3;
      return;
    }
    //아무것도 아닐때 직진 우선순위 5
    sendmotor(30, 30);
    return;
  }

  if (x_first_count == 0 && y_finish) {
    mode4_index = 4;
    return;
  }

  if (x_finish == 0) {
    // 앞에 인식하면 오른쪽으로 회전
    if (front_ultra_flag) {
      mode4_index = 2;
      return;
    }
    // 오른쪽으로 돈 상태에서 왼쪽이 감지 되면 감지된 값 저장 우선순위 2번
    if (left_ultra_flag  && turn_right_count > 0) pre_left_flag = left_ultra_flag;
    //왼쪽으로 돈 상태에서 오른쪽이 감지가 안되면 약간의 딜레이를 위하여 밀리스
    if (pre_left_flag != left_ultra_flag && turn_right_count > 0) {
      pre_left_flag = left_ultra_flag;
      odometry_millis = millis();
    }
    //장애물을 완전히 벗어나면 왼쪽 회전
    if (left_ultra_flag == 0 && millis() - odometry_millis > 1000 && turn_right_count > 0) {
      mode4_index = 1;
      turn_right_count --;
      if (turn_right_count <= 0) move_priority = 0;
      return;
    }
    //장애물을 지나는 동안은 직진만 하기 우선순위3
    if (move_priority) {
      sendmotor(30, 30);
      return;
    }

    //아무것도 아닌상태
    //가장자리가 검출 되었을때  우선순위 4

    if (side_right_ultra_flag && (side_left_ultra_flag == 0)) {
      sendmotor(-30, 0);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if ((side_right_ultra_flag == 0 ) && side_left_ultra_flag) {
      sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if (side_right_ultra_flag && side_left_ultra_flag) {
      //오른쪽이 더 가까울때,
      if (distance4 < distance5) sendmotor(-30, 0);
      //왼쪽이 더 가까울때,
      else                       sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    }

    //0도 보정
    if ((front_ultra_flag == 0) && (side_left_ultra_flag == 0) && (side_right_ultra_flag == 0) && (right_ultra_flag == 0) && (left_ultra_flag == 0) && balance_flag && (millis() - odometry_millis > 850)) {
      mode4_index = 3;
      return;
    }
    //아무것도 아닐때 직진 우선순위 5
    sendmotor(30, 30);
    return;
  }
  if (x_finish && y_finish) {
    //parking
    sendmotor(17, 15);
    if (side_right_ultra_flag && side_left_ultra_flag == 0) {
      sendmotor(-30, 0);
      return;
    } else if (side_right_ultra_flag == 0 && side_left_ultra_flag) {
      sendmotor(0, -30);
      return;
    } else if (side_right_ultra_flag && side_left_ultra_flag) {
      //오른쪽이 더 가까울때,
      if (distance4 < distance5) sendmotor(-30, 0);
      //왼쪽이 더 가까울때,
      else                       sendmotor(0, -30);
      return;
    }
  }
}
//====================================================================================================
void move_odometry3() {

  if (x1 > 20 && x1 < 40) x_finish = 1;
  else if ( y_finish && x1 > 20) x_finish = 0;

  if (y1 > 135 && y1 < 145) y_finish = 1;
  //정지
  if (left_ultra_flag && right_ultra_flag ) {
    delay(1000);
    sendmotor(0, 0);
    mode4_flag = 0;
    delay(111111);
  }
  if (y_finish == 0) {
    // 앞에 인식하면 오른쪽으로 회전
    if (front_ultra_flag) {
      mode4_index = 2;
      return;
    }
    // 오른쪽으로 돈 상태에서 왼쪽이 감지 되면 감지된 값 저장 우선순위 2번
    if (left_ultra_flag  && turn_right_count > 0) pre_left_flag = left_ultra_flag;
    //왼쪽으로 돈 상태에서 오른쪽이 감지가 안되면 약간의 딜레이를 위하여 밀리스
    if (pre_left_flag != left_ultra_flag && turn_right_count > 0) {
      pre_left_flag = left_ultra_flag;
      odometry_millis = millis();
      return;
    }
    //장애물을 완전히 벗어나면 왼쪽 회전
    if (left_ultra_flag == 0 && millis() - odometry_millis > 1000 && turn_right_count > 0) {
      mode4_index = 1;
      turn_right_count --;
      if (turn_right_count <= 0) move_priority = 0;
      return;
    }
    //장애물을 지나는 동안은 직진만 하기 우선순위3
    if (move_priority) {
      sendmotor(30, 30);
      return;
    }

    //아무것도 아닌상태
    //가장자리가 검출 되었을때  우선순위 4

    if (side_right_ultra_flag && (side_left_ultra_flag == 0)) {
      sendmotor(-30, 0);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if ((side_right_ultra_flag == 0 ) && side_left_ultra_flag) {
      sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if (side_right_ultra_flag && side_left_ultra_flag) {
      //오른쪽이 더 가까울때,
      if (distance4 < distance5) sendmotor(-30, 0);
      //왼쪽이 더 가까울때,
      else                       sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    }

    //90도 보정
    if ((front_ultra_flag == 0) && (side_left_ultra_flag == 0) && (side_right_ultra_flag == 0) && (right_ultra_flag == 0) && (left_ultra_flag == 0) && balance_flag && (millis() - odometry_millis > 850)) {
      mode4_index = 3;
      return;
    }
    //아무것도 아닐때 직진 우선순위 5
    sendmotor(30, 30);
    return;
  }
  //180도 보정
  if (x_first_count == 0 && y_finish) {
    mode4_index = 4;
    return;
  }

  if (x_finish == 0) {
    // 앞에 인식하면 오른쪽으로 회전
    if (front_ultra_flag) {
      mode4_index = 2;
      return;
    }
    // 오른쪽으로 돈 상태에서 왼쪽이 감지 되면 감지된 값 저장 우선순위 2번
    if (left_ultra_flag  && turn_right_count > 0) pre_left_flag = left_ultra_flag;
    //왼쪽으로 돈 상태에서 오른쪽이 감지가 안되면 약간의 딜레이를 위하여 밀리스
    if (pre_left_flag != left_ultra_flag && turn_right_count > 0) {
      pre_left_flag = left_ultra_flag;
      odometry_millis = millis();
    }
    //장애물을 완전히 벗어나면 왼쪽 회전
    if (left_ultra_flag == 0 && millis() - odometry_millis > 1000 && turn_right_count > 0) {
      mode4_index = 1;
      turn_right_count --;
      if (turn_right_count <= 0) move_priority = 0;
      return;
    }
    //장애물을 지나는 동안은 직진만 하기 우선순위3
    if (move_priority) {
      sendmotor(30, 30);
      return;
    }

    //아무것도 아닌상태
    //가장자리가 검출 되었을때  우선순위 4

    if (side_right_ultra_flag && (side_left_ultra_flag == 0)) {
      sendmotor(-30, 0);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if ((side_right_ultra_flag == 0 ) && side_left_ultra_flag) {
      sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    } else if (side_right_ultra_flag && side_left_ultra_flag) {
      //오른쪽이 더 가까울때,
      if (distance4 < distance5) sendmotor(-30, 0);
      //왼쪽이 더 가까울때,
      else                       sendmotor(0, -30);
      odometry_millis = millis();
      balance_flag = 1;
      return;
    }

    //180도로 보정
    if ((front_ultra_flag == 0) && (side_left_ultra_flag == 0) && (side_right_ultra_flag == 0) && (right_ultra_flag == 0) && (left_ultra_flag == 0) && balance_flag && (millis() - odometry_millis > 850)) {
      mode4_index = 5;
      return;
    }
    //아무것도 아닐때 직진 우선순위 5
    sendmotor(30, 30);
    return;
  }
  if (x_finish && y_finish) {
    if (y1 < 135) {
      y_finish = 0;
      //90도 보정
      mode4_index = 3;
      x_first_count = 0;

    }
  }
  if (x_finish && y_finish) {
    if (left_ultra_flag && right_ultra_flag ) {
      delay(1000);
      sendmotor(0, 0);
      mode4_flag = 0;
      delay(111111);
    }
    //parking
    sendmotor(15, 15);
    if (side_right_ultra_flag && side_left_ultra_flag == 0) {
      sendmotor(-30, 0);
      return;
    } else if (side_right_ultra_flag == 0 && side_left_ultra_flag) {
      sendmotor(0, -30);
      return;
    } else if (side_right_ultra_flag && side_left_ultra_flag) {
      //오른쪽이 더 가까울때,
      if (distance4 < distance5) sendmotor(-30, 0);
      //왼쪽이 더 가까울때,
      else                       sendmotor(0, -30);
      return;
    }
  }
}
