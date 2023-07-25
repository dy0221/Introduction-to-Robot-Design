#include <AIROBOTICS.h>

AiRobotics::AiRobotics()
{
  link1 = LINK_UPPER_L;
  EE_offset = 33;
  link2 = LINK_LOWER_L + EE_offset;

  cosine2 = 0;
  sine2 = 0;
}

// 입력 deg를 0~4069의 펄스로 계산하여 반환
double AiRobotics::deg2pul(double deg)
{
  double m_deg = 2048 + deg * 4096 / 360;
  return m_deg;
}

// 입력 펄스를 0~360도의 각도로 계산하여 반환
double AiRobotics::pul2deg(float pulse)
{
  double deg = (pulse - 2048) * 360 / 4096;
  return deg;
}

// foward kinematics
void AiRobotics::FK(double deg1, double deg2)
{

  EF[0] = link1 * sin(radians(deg1)) + link2 * sin(radians(deg1) + radians(deg2));
  EF[1] = link1 * cos(radians(deg1)) + link2 * cos(radians(deg1) + radians(deg2));
}

// inverse kinematics
void AiRobotics::IK(double x, double y)
{
  cosine2 = (pow(x, 2) + pow(y, 2) - pow(link1, 2) - pow(link2, 2)) / (2 * link1 * link2);
  if (cosine2 > 1)
    cosine2 = 1;
  else if (cosine2 < -1)
    cosine2 = -1;
  sine2 = sqrt(1 - (pow(cosine2, 2)));
  // ElbowDown theta2
  theta2[0] = degrees(atan2(sine2, cosine2));
  // ElbowUp theta2
  theta2[1] = degrees(atan2(-sine2, cosine2));

  theta1[0] = degrees(atan2(x, y) - atan2((link2 * sin(radians(theta2[0]))), (link1 + link2 * cos(radians(theta2[0])))));
  theta1[1] = degrees(atan2(x, y) - atan2((link2 * sin(radians(theta2[1]))), (link1 + link2 * cos(radians(theta2[1])))));

  limitChecker();
}

void AiRobotics::IKElbowDown(double x, double y)
{
  cosine2 = (pow(x, 2) + pow(y, 2) - pow(link1, 2) - pow(link2, 2)) / (2 * link1 * link2);
  if (cosine2 > 1)
    cosine2 = 1;
  else if (cosine2 < -1)
    cosine2 = -1;
  sine2 = sqrt(1 - (pow(cosine2, 2)));
  // ElbowDown theta2
  theta2[0] = degrees(atan2(sine2, cosine2));
  // ElbowUp theta2
  theta2[1] = degrees(atan2(-sine2, cosine2));

  theta1[0] = degrees(atan2(x, y) - atan2((link2 * sin(radians(theta2[0]))), (link1 + link2 * cos(radians(theta2[0])))));
  theta1[1] = degrees(atan2(x, y) - atan2((link2 * sin(radians(theta2[1]))), (link1 + link2 * cos(radians(theta2[1])))));

  limitCheckerElbowDown();
}
// 각도 오류chk
void AiRobotics::limitChecker()
{
  // pose1 = (ReadPos(1)-2048)*360/4096;
  // pose2 = (ReadPos(2)-2048)*360/4096;
  pose1 = tmp_deg[0];
  pose2 = tmp_deg[1];

  // 각 세타 값과 현재 위치를 빼준 값 (실제로 움직여야하는 각도) 의 합 계산 (theta2 값 우선)
  for (int i = 0; i < 2; i++)
  {

    // 각도 초과 검출
    if (abs(theta1[i]) > 120)
      Error_M1[i] = true;
    else
      Error_M1[i] = false;
    if (abs(theta2[i]) > 120)
      Error_M2[i] = true;
    else
      Error_M2[i] = false;

    m1_dst[i] = theta1[i] - pose1;
    m2_dst[i] = theta2[i] - pose2;
    dst_sum[i] = abs(m2_dst[i]) + abs(m1_dst[i]);
  }

  // dst_sum 이 작으면 움직여야 하는 각도가 적다는 뜻이므로 더 적은 pose로 최종 각도 선정 (theta2 값 우선, 에러 존재 유무 파악)

  if (dst_sum[0] <= dst_sum[1])
  {
    m_deg[0] = (Error_M1[0] == false) ? theta1[0] : theta1[1];
    m_deg[1] = (Error_M2[0] == false) ? theta2[0] : theta2[1];
  }
  else
  {
    m_deg[0] = (Error_M1[1] == false) ? theta1[1] : theta1[0];
    m_deg[1] = (Error_M2[1] == false) ? theta2[1] : theta2[0];
  }

  // final result error find
  if (abs(m_deg[0]) > 120)
  {
    Serial.println("ERROR : Theta 1 Exceeded");
    while (1)
      ;
    m_deg[0] = 0;
  }
  if (abs(m_deg[1]) > 120)
  {
    Serial.println("ERROR : Theta 2 Exceeded");
    while (1)
      ;
    m_deg[1] = 0;
  }

  tmp_deg[0] = m_deg[0];
  tmp_deg[1] = m_deg[1];
}

// 각도 오류chk
void AiRobotics::limitCheckerElbowDown()
{
  // pose1 = (ReadPos(1)-2048)*360/4096;
  // pose2 = (ReadPos(2)-2048)*360/4096;
  pose1 = tmp_deg[0];
  pose2 = tmp_deg[1];

  // 각 세타 값과 현재 위치를 빼준 값 (실제로 움직여야하는 각도) 의 합 계산 (theta2 값 우선)
  for (int i = 0; i < 2; i++)
  {

    // 각도 초과 검출
    if (abs(theta1[i]) > 120)
      Error_M1[i] = true;
    else
      Error_M1[i] = false;
    if (abs(theta2[i]) > 125)
      Error_M2[i] = true;
    else
      Error_M2[i] = false;

    m1_dst[i] = theta1[i] - pose1;
    m2_dst[i] = theta2[i] - pose2;
    dst_sum[i] = abs(m2_dst[i]) + abs(m1_dst[i]);
  }

  // dst_sum 이 작으면 움직여야 하는 각도가 적다는 뜻이므로 더 적은 pose로 최종 각도 선정 (theta2 값 우선, 에러 존재 유무 파악)

  if (dst_sum[0] >= dst_sum[1])
  {
    m_deg[0] = (Error_M1[0] == false) ? theta1[0] : theta1[1];
    m_deg[1] = (Error_M2[0] == false) ? theta2[0] : theta2[1];
  }
  else
  {
    m_deg[0] = (Error_M1[1] == false) ? theta1[1] : theta1[0];
    m_deg[1] = (Error_M2[1] == false) ? theta2[1] : theta2[0];
  }

  // final result error find
  if (abs(m_deg[0]) > 120)
  {
    Serial.println("ERROR : Theta 1 Exceeded");
    while (1)
      ;
    m_deg[0] = 0;
  }
  if (abs(m_deg[1]) > 120)
  {
    Serial.println("ERROR : Theta 2 Exceeded");
    while (1)
      ;
    m_deg[1] = 0;
  }

  tmp_deg[0] = m_deg[0];
  tmp_deg[1] = m_deg[1];
}