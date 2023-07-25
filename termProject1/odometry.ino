void odometry() {

  theta_1 = m1_angle * PI / 180;
  theta_2 = m2_angle * PI / 180;

  S_R = Wheel_R * theta_1;
  S_L = Wheel_R * theta_2;

  S_R1 = S_R;
  S_L1 = S_L;

  deltaSR = S_R1 - S_R2;
  deltaSL = S_L1 - S_L2;

  S_R2 = S_R1;
  S_L2 = S_L1;

  deltaS = (deltaSR + deltaSL) / 2;

  S = (S_R + S_L) / 2;
  dtheta = (deltaSR - deltaSL) / L;

  //  current_theta = (S_R - S_L) / L * 180 / PI;
  current_theta += dtheta * 180 / PI;

  x1 = x1 + deltaS * cos(theta + dtheta / 2 );
  y1 = y1 + deltaS * sin(theta + dtheta / 2 );
//
  theta += dtheta;

}
