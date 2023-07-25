#include <AIROARM.h>

AiroArm arm;

void setup() {
  Serial.begin(115200);
  Serial1.begin(1000000);

  arm.pSerial = &Serial1;

  //torque off
  arm.EnableTorque(SHOULDER_ID, 0);
  arm.EnableTorque(ELBOW_ID, 0);
}

void loop() {
  //read current angle and print
  Serial.print("Joint 1 angle : ");
  Serial.print(arm.ReadPos(SHOULDER_ID));
  Serial.print(",\t");
  Serial.print("Joint 2 angle : ");
  Serial.println(arm.ReadPos(ELBOW_ID));

  delay(500);
}
