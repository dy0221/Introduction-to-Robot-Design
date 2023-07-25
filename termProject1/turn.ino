
//다 돌면 flag로 확인
void turn_R(float input_theta, int input_speed)
{
  if (turnRight_count == 0) {
    reference_theta = current_theta;
    turnRight_count = 1;
    pre_theta = current_theta;
  }
  if (current_theta < reference_theta + input_theta - 0.5) sendmotor(input_speed, -input_speed);
  else if (current_theta > reference_theta + input_theta + 0.5) sendmotor(-input_speed, input_speed);
  else {
    turnRight_count = 0;
    reference_theta = 0;
    turn_r_flag = 1;
  }

}

void turn_L(float input_theta, int input_speed)
{
  if (turnLeft_count == 0) {
    reference_theta = current_theta;
    turnLeft_count = 1;
    pre_theta = current_theta;
  }

  if (current_theta > reference_theta - input_theta + 0.5) sendmotor(-input_speed, input_speed);
  else if (current_theta < reference_theta - input_theta - 0.5) sendmotor(input_speed, -input_speed);
  else {
    turnLeft_count = 0;
    reference_theta = 0;
    turn_l_flag = 1;
  }
}
