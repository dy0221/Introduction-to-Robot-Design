#ifndef AIROARM_H
#define AIROARM_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <AIROBOTICS.h>

// PIN DEFINE
#define stp 9
#define dir 8
#define SW_U 7
#define SW_B 6

// ID
#define SHOULDER_ID 1
#define ELBOW_ID 2

// DYNAMIC ARM LIMIT PARAMETERS
#define SHOULDER_MAX 3000
#define SHOULDER_MIN 1000
#define SHOULDER_SPD 1200
#define SHOULDER_ACC 50

#define ELBOW_MAX 3000
#define ELBOW_MIN 1000
#define ELBOW_SPD 1200
#define ELBOW_ACC 50

// #define LINK_EE_OFFSET  0

// JOINT OFFSET
#define SHOULDER_OFFSET 0
#define ELBOW_OFFSET 0

struct Planar
{
  float m1_deg;
  float m2_deg;
};

struct Decart
{
  double x;
  double y;
};

class AiroArm : public AiRobotics
{
public:
  AiroArm();
  AiroArm *arm;
  void _init();
  void movep(double x, double y);
  void movepElbowDown(double x, double y);
  void movep(double x, double y, double z);

  void movel(float goal_x, float goal_y);
  void movel(float goal_x, float goal_y, float z);

  void movez(float z);

  Planar offset;

  int z_pulseNum;
  int z_index;

  bool Error_M1[2];
  bool Error_M2[2];

private:
  // static int m1_offset;
  // static int m2_offset;

  int i_ref;

  float T;
  float V;
  float A;

  float dist_ref;

  Decart d;
  Decart _i;
  Decart d_tmp;

  Planar deg_org;
  Planar dist;
  Planar dm;

  Planar current;
  Planar p_tmp;
};

#endif