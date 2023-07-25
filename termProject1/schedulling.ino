void scheduling1() {
  if (mode2_t5_flag) {
    mode2_t5_flag = false;
    t5_index++;
    switch (t5_index) {
      //초음파 최대 30 cm
      //front
      case 0 :
        distance1 = getDistance(TRIG_f, ECHO_f);
        Serial.print("  sensor1: ");
        Serial.print(distance1);
        break;
      //right
      case 1 :
        distance2 = getDistance(TRIG_l, ECHO_l);
        Serial.print("  sensor2: ");
        Serial.print(distance2);
        break;
      //left
      case 2 :
        distance3 = getDistance(TRIG_r, ECHO_r);
        Serial.print("  sensor3: ");
        Serial.print(distance3);
        break;
      //side_right
      case 3:
        distance4 = getDistance(TRIG_ll, ECHO_ll);
        Serial.print("  sensor4: ");
        Serial.print(side_right_ultra_flag);
        break;
      //side_left
      case 5:
        distance5 = getDistance(TRIG_rr, ECHO_rr);
        Serial.print("  sensor5: ");
        Serial.println(side_left_ultra_flag);
        break;

      case 6 :
        check_ultrasonic();
        break;
      case 7 :
        t5_index = -1;
        move_odometry1();
        Serial.print(mode4_index);
        Serial.print(x_finish);
        Serial.print(y_finish);
        Serial.print("x ");
        Serial.print(x1);
        Serial.print("y ");
        Serial.print(y1);
        Serial.print(" ");
        Serial.println(current_theta);
      default :
        break;
    }
  }
}
//==================================================================================================
void scheduling2() {
  if (mode2_t5_flag) {
    mode2_t5_flag = false;
    t5_index++;
    switch (t5_index) {
      //초음파 최대 30 cm
      //front
      case 0 :
        distance1 = getDistance(TRIG_f, ECHO_f);
        Serial.print("  sensor1: ");
        Serial.print(distance1);
        break;
      //right
      case 1 :
        distance2 = getDistance(TRIG_l, ECHO_l);
        Serial.print("  sensor2: ");
        Serial.print(distance2);
        break;
      //left
      case 2 :
        distance3 = getDistance(TRIG_r, ECHO_r);
        Serial.print("  sensor3: ");
        Serial.print(distance3);
        break;
      //side_right
      case 3:
        distance4 = getDistance(TRIG_ll, ECHO_ll);
        Serial.print("  sensor4: ");
        Serial.print(side_right_ultra_flag);
        break;
      //side_left
      case 5:
        distance5 = getDistance(TRIG_rr, ECHO_rr);
        Serial.print("  sensor5: ");
        Serial.print(side_left_ultra_flag);
        break;

      case 6 :
        check_ultrasonic();
        break;
      case 7 :
        t5_index = -1;
        move_odometry2();

        //      case 8:
        //        t5_index = -1;
        //        //        Serial.print(x1);
        //        //        Serial.print(" ");
        //        //        Serial.print(y1);
        //        //        Serial.print(" ");
        //        //        Serial.println(current_theta);
        //        Serial.print(theta * 180 / PI);
        Serial.print(mode4_index);
        Serial.print(x_finish);
        Serial.print(y_finish);
        Serial.print("x ");
        Serial.print(x1);
        Serial.print("y ");
        Serial.print(y1);
        Serial.print(" ");
        Serial.println(current_theta);
      default :
        break;
    }
  }
}
//=======================================================================================
void scheduling3() {
  if (mode2_t5_flag) {
    mode2_t5_flag = false;
    t5_index++;
    switch (t5_index) {
      //초음파 최대 30 cm
      //front
      case 0 :
        distance1 = getDistance(TRIG_f, ECHO_f);
        //        Serial.print("  sensor1: ");
        //        Serial.print(distance1);
        break;
      //right
      case 1 :
        distance2 = getDistance(TRIG_l, ECHO_l);
        //        Serial.print("  sensor2: ");
        //        Serial.print(distance2);
        break;
      //left
      case 2 :
        distance3 = getDistance(TRIG_r, ECHO_r);
        //        Serial.print("  sensor3: ");
        //        Serial.print(distance3);
        break;
      //side_right
      case 3:
        distance4 = getDistance(TRIG_ll, ECHO_ll);
        //        Serial.print("  sensor4: ");
        //        Serial.print(side_right_ultra_flag);
        break;
      //side_left
      case 5:
        distance5 = getDistance(TRIG_rr, ECHO_rr);
        //        Serial.print("  sensor5: ");
        //        Serial.println(side_left_ultra_flag);
        break;

      case 6 :
        check_ultrasonic();
        break;
      case 7 :
        t5_index = -1;
        move_odometry3();

      //      case 8:
      //        t5_index = -1;
      //        //        Serial.print(x1);
      //        //        Serial.print(" ");
      //        //        Serial.print(y1);
      //        //        Serial.print(" ");
      //        //        Serial.println(current_theta);
      //        Serial.print(theta * 180 / PI);
      //        Serial.print(" ");
      //        Serial.println(move_priority);
      default :
        break;
    }
  }
}
