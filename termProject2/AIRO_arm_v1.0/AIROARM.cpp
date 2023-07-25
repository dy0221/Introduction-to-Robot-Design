#include "AIROARM.h"
#include <Stream.h>

AiroArm::AiroArm()
{
  // 초기화
  z_pulseNum = 0;
  z_index = 0;

  T = 0.0;
  // z is 2400mm
  V = 2400;
  A = 50;

  d.x = 0;
  d.y = 0;

  i_ref = 0;
  _i.x = 0;
  _i.y = 0;

  d_tmp.x = 0;
  d_tmp.y = 0;

  p_tmp.m1_deg = 0.0;
  p_tmp.m2_deg = 0.0;

  End = 0;
  // step motor
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  // switch
  pinMode(SW_U, INPUT);
  pinMode(SW_B, INPUT);

  offset.m1_deg = 0;
  offset.m2_deg = 0;
}

void AiroArm::_init()
{

  Serial.println("Airo Arm header V 0.1");
  Serial.println("initializing..");
  WritePosEx(SHOULDER_ID, 2048 + offset.m1_deg, 1000, 50);
  WritePosEx(ELBOW_ID, 2048 + offset.m2_deg, 1000, 50);
  delay(3000);

  digitalWrite(dir, LOW);
  delay(1000);
  while (!digitalRead(SW_U))
  {
    digitalWrite(stp, HIGH);
    delayMicroseconds(600);
    digitalWrite(stp, LOW);
    delayMicroseconds(600);
  }
  digitalWrite(dir, HIGH);
  delay(1000);
  while (!digitalRead(SW_B))
  {
    digitalWrite(stp, HIGH);
    delayMicroseconds(600);
    digitalWrite(stp, LOW);
    delayMicroseconds(600);
    z_pulseNum = z_pulseNum + 1;
  }

  Serial.print("pulse num = ");
  Serial.println(z_pulseNum);

  digitalWrite(dir, LOW);
  delay(1000);

  while (z_index < 70 && !digitalRead(SW_U))
  {
    digitalWrite(stp, HIGH);
    delayMicroseconds(600);
    digitalWrite(stp, LOW);
    delayMicroseconds(600);
    z_index = z_index + 1;
  }

  Serial.print("current z : ");
  Serial.println(z_index);

  // dSerial->write("calibration done! \n");
  Serial.print("link1 length : ");
  Serial.println(link1);
  Serial.print("link2 length : ");
  Serial.println(link2);
  Serial.println("calibration done! ready to move");
  delay(3000);
}

void AiroArm::movep(double x, double y)
{
  // 이동 전 위치 값 읽어오기
  int init_deg1 = pul2deg(ReadPos(1) - offset.m1_deg);
  int init_deg2 = pul2deg(ReadPos(2) - offset.m2_deg);
  if (init_deg1 == -1 || init_deg2 == -1)
  {
    while (1)
      Serial.println("motor status failed");
  }
  else
  {
    Serial.println(init_deg1);
    Serial.println(init_deg2);
  }

  // 현재 EE의 위치 구하기, EF[0], EF[1]이 x,y값.
  FK(init_deg1, init_deg2);
  Serial.print("x : ");
  Serial.print(EF[0]);
  Serial.print(" ");
  Serial.print("y : ");
  Serial.println(EF[1]);
  if (EF[0] * x < 0)
  {
    movep(0, 1000);
    delay(500);
  }
  IK(x, y);
  // degree 1, 2
  double deg1 = m_deg[0];
  double deg2 = m_deg[1];

  current.m1_deg = ReadPos(1);
  current.m2_deg = ReadPos(2);

  dist.m1_deg = deg2pul(deg1) - current.m1_deg;
  dist.m2_deg = deg2pul(deg2) - current.m2_deg;

  dist_ref = (abs(dist.m1_deg) >= abs(dist.m2_deg)) ? abs(dist.m1_deg) : abs(dist.m2_deg);

  dm.m1_deg = dist.m1_deg / dist_ref;
  dm.m2_deg = dist.m2_deg / dist_ref;

  float _dm = (abs(dm.m1_deg) >= abs(dm.m2_deg)) ? abs(dm.m1_deg) : abs(dm.m2_deg);

  T = (_dm / V) * 1000 + (V / (A * 100)) * 1000;

  for (int i = 0; i < dist_ref; i++)
  {
    WritePosEx(1, current.m1_deg + dm.m1_deg * i, V, A);
    WritePosEx(2, current.m2_deg + dm.m2_deg * i, V, A);

    delay(T / 200);
  }
  // Final Move to Accuracy Point
  WritePosEx(1, deg2pul(deg1), V, A);
  WritePosEx(2, deg2pul(deg2), V, A);
  delay(1000);

  FK(deg1, deg2);
  Serial.print("x : ");
  Serial.print(EF[0]);
  Serial.print(" ");
  Serial.print("y : ");
  Serial.println(EF[1]);
}

void AiroArm::movepElbowDown(double x, double y)
{
  IKElbowDown(x, y);
  // degree 1, 2
  double deg1 = m_deg[0];
  double deg2 = m_deg[1];

  current.m1_deg = ReadPos(1);
  current.m2_deg = ReadPos(2);

  dist.m1_deg = deg2pul(deg1) - current.m1_deg;
  dist.m2_deg = deg2pul(deg2) - current.m2_deg;

  dist_ref = (abs(dist.m1_deg) >= abs(dist.m2_deg)) ? abs(dist.m1_deg) : abs(dist.m2_deg);

  dm.m1_deg = dist.m1_deg / dist_ref;
  dm.m2_deg = dist.m2_deg / dist_ref;

  float _dm = (abs(dm.m1_deg) >= abs(dm.m2_deg)) ? abs(dm.m1_deg) : abs(dm.m2_deg);

  T = (_dm / V) * 1000 + (V / (A * 100)) * 1000;

  for (int i = 0; i < dist_ref; i++)
  {
    WritePosEx(1, current.m1_deg + dm.m1_deg * i, V, A);
    WritePosEx(2, current.m2_deg + dm.m2_deg * i, V, A);

    delay(T / 200);
  }
  // Final Move to Accuracy Point
  WritePosEx(1, deg2pul(deg1), V, A);
  WritePosEx(2, deg2pul(deg2), V, A);
  delay(1000);

  FK(deg1, deg2);
  Serial.print("x : ");
  Serial.print(EF[0]);
  Serial.print(" ");
  Serial.print("y : ");
  Serial.println(EF[1]);
}

void AiroArm::movep(double x, double y, double z)
{
  movez(z);
  movep(x, y);
}

void AiroArm::movel(float goal_x, float goal_y)
{
  // 이동 전 위치 값 읽어오기
  int init_deg1 = pul2deg(ReadPos(1) - offset.m1_deg);
  int init_deg2 = pul2deg(ReadPos(2) - offset.m2_deg);
  if (init_deg1 == -1 || init_deg2 == -1)
  {
    while (1)
      Serial.println("motor status failed");
  }
  else
  {
    Serial.println(init_deg1);
    Serial.println(init_deg2);
  }

  // 현재 EE의 위치 구하기, EF[0], EF[1]이 x,y값.
  FK(init_deg1, init_deg2);
  Serial.print("x : ");
  Serial.print(EF[0]);
  Serial.print(" ");
  Serial.print("y : ");
  Serial.println(EF[1]);
  // 목표 좌표값과 현재값의 차 구하기
  d.x = goal_x - EF[0];
  d.y = goal_y - EF[1];

  // x 와 y 중 절대값이 더 큰 값을 iteration 개수로 선정
  i_ref = (abs(d.x) >= abs(d.y)) ? abs(d.x) : abs(d.y);

  // 각 iteration마다 증감시켜줄 값
  _i.x = d.x / i_ref;
  _i.y = d.y / i_ref;

  Serial.println(_i.x);
  Serial.println(_i.y);

  // 현재 x, y값으로 초기값 지정
  d_tmp.x = EF[0];
  d_tmp.y = EF[1];

  for (int i = 0; i < i_ref; i++)
  {
    // d_tmp.x, d_tmp.y로 inv kin 실행, m_deg[0], m_deg[1]으로 출력
    IK(d_tmp.x, d_tmp.y);

    WritePosEx(1, deg2pul(m_deg[0]) + offset.m1_deg, V, A);
    WritePosEx(2, deg2pul(m_deg[1]) + offset.m2_deg, V, A);
    //    T = ((abs())/V)*1000+(V/(A*100))*1000;
    delay(5);
    p_tmp.m1_deg = m_deg[0];
    p_tmp.m2_deg = m_deg[1];
    // iteration마다 i.x, i.y 누적
    d_tmp.x = d_tmp.x + _i.x;
    d_tmp.y = d_tmp.y + _i.y;
  }
  p_tmp.m1_deg = pul2deg(ReadPos(1) + offset.m1_deg);
  p_tmp.m2_deg = pul2deg(ReadPos(2) + offset.m2_deg);
  FK(p_tmp.m1_deg, p_tmp.m2_deg);
  Serial.print("x : ");
  Serial.print(EF[0]);
  Serial.print(" ");
  Serial.print("y : ");
  Serial.println(EF[1]);
}

void AiroArm::movel(float x, float y, float z)
{
  movez(z);
  movel(x, y);
}

void AiroArm::movez(float z)
{

  int pulse_max = z_pulseNum;
  int z_pulse = z * 75; // 75 = (600/8)
  //  Serial.println(z_pulse);

  if (z < 0)
  {
    digitalWrite(dir, HIGH);
    delay(100);
    while (!digitalRead(SW_B))
    {
      digitalWrite(stp, HIGH);
      delayMicroseconds(600);
      digitalWrite(stp, LOW);
      delayMicroseconds(600);
    }
    Serial.println("ERROR : Z Exceeded");
    z_index = 0;
  }

  if (z_pulse > pulse_max)
  {
    digitalWrite(dir, LOW);
    delay(100);
    while (!digitalRead(SW_U))
    {
      digitalWrite(stp, HIGH);
      delayMicroseconds(600);
      digitalWrite(stp, LOW);
      delayMicroseconds(600);
    }
    Serial.println("ERROR : Z Exceeded");
    z_index = z_pulseNum;
  }

  if ((z_pulse - z_index) >= 0)
  {
    digitalWrite(dir, LOW);
    while (z_index <= z_pulse && !digitalRead(SW_U))
    {
      digitalWrite(stp, HIGH);
      delayMicroseconds(600);
      digitalWrite(stp, LOW);
      delayMicroseconds(600);
      z_index = z_index + 1;
    }
  }
  else
  {
    digitalWrite(dir, HIGH);
    while (z_index >= z_pulse && !digitalRead(SW_B))
    {
      digitalWrite(stp, HIGH);
      delayMicroseconds(600);
      digitalWrite(stp, LOW);
      delayMicroseconds(600);
      z_index = z_index - 1;
    }
  }

  delay(1000);
}
