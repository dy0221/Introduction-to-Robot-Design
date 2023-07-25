void move_line() {
  switch (linetrace_index) {
    //직진
    case 0:
      m1_ref_speed = 35;
      m2_ref_speed = 35;
      mode_index = 0;
      break;
    //오른쪽으로 회전 left_flag
    case 1:
      m1_ref_speed = 0;
      m2_ref_speed = -35;
      if (left_slope > 1) {
        if (millis() - pre_millis > short_delay) {
          left_flag = 0;
          mode_index = 0;
        }
      } else {
        if (millis() - pre_millis > long_delay) {
          left_flag = 0;
          mode_index = 0;
        }
      }
      break;
    //왼쪽으로 회전 left_flag
    case 2:
      m1_ref_speed = 35;
      m2_ref_speed = 35;
      if (millis() - pre_millis > 200) {
        left_flag = 0;
        mode_index = 0;
      }
      break;
    case 3:
      m1_ref_speed = -35;
      m2_ref_speed = 0;
      if (right_slope < -1) {
        if (millis() - pre_millis > short_delay) {
          right_flag = 0;
          mode_index = 0;
        }
      } else {
        if (millis() - pre_millis > long_delay) {
          right_flag = 0;
          mode_index = 0;
        }
      }
      break;
    case 4:
      m1_ref_speed = 35;
      m2_ref_speed = 35;
      if (millis() - pre_millis > 200) {
        right_flag = 0;
        mode_index = 0;
      }
      break;
    default:
      mode_index = 0;
  }

  if (barcode_flag) {
    if (barcode_index == 0) {
      m1_ref_speed = m1_ref_speed * 5/7;
      m2_ref_speed = m2_ref_speed * 5/7;
    } else {
      m1_ref_speed = m1_ref_speed * 10 / 7;
      m2_ref_speed = m2_ref_speed * 10/ 7;
    }
  }
  sendmotor(m1_ref_speed, m2_ref_speed);
}
