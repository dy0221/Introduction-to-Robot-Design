#ifndef AIROBOTICS_H
#define AIROBOTICS_H

#include <SCServo.h>
// using namespace std;

// LINK LENGTH PARAMETERS
#define LINK_UPPER_L 150.21
#define LINK_LOWER_L 110.7

class AiRobotics : public SMS_STS
{

public:
  AiRobotics();
  ~AiRobotics(){};

  double deg2pul(double deg);
  double pul2deg(float pulse);
  void FK(double deg1, double deg2);
  void IKElbowDown(double deg1, double deg2);
  void IK(double x, double y);

  float EF[2];
  float link1;
  float link2;
  float EE_offset;
  float m_deg[2];

private:
  void limitChecker();
  void limitCheckerElbowDown();

  float m1_dst[2];
  float m2_dst[2];

  double theta1[2];
  double theta2[2];

  double cosine2;
  double sine2;

  bool Error_M1[2];
  bool Error_M2[2];
  double dst_sum[2];
  double tmp_deg[2];

  double pose1;
  double pose2;
};

#endif