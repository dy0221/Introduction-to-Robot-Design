void select_mode() {
  //왼쪽만 감지
  if (left_flag) {
    if (left_slope > 0) linetrace_index = 1;
    else                linetrace_index = 2;
    //오른쪽만 감지
  } else if (right_flag) {
    if (right_slope < 0) linetrace_index = 3;
    else                 linetrace_index = 4;
    //감지 못했을 때
  } else {
    //직진
    linetrace_index = 0;
  }

  mode_index = 2;
}
