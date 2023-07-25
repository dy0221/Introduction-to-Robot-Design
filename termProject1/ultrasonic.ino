void check_ultrasonic() {
  //front
  if (distance1 <  10 && distance1 > 1) front_ultra_flag = 1;
  else                                  front_ultra_flag = 0;
  //right
  if (distance2 < 25 && distance2 > 1)  right_ultra_flag = 1;
  else                                  right_ultra_flag = 0;
  //left
  if (distance3 < 25 && distance3 > 1)  left_ultra_flag = 1;
  else                                  left_ultra_flag = 0;
  //side_right
  if (distance4 < 12 && distance4 > 1)  side_right_ultra_flag = 1;
  else                                   side_right_ultra_flag = 0;
  //side_left
  if (distance5 < 12 && distance5 > 1)  side_left_ultra_flag = 1;
  else                                  side_left_ultra_flag = 0;
}
