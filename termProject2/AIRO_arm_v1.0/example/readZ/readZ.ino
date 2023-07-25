#include <AIROARM.h>

AiroArm arm;

void setup() {
  Serial.begin(115200);
  Serial1.begin(1000000);

  arm.pSerial = &Serial1;
  arm.EnableTorque(SHOULDER_ID, 0);
  arm.EnableTorque(ELBOW_ID, 0);
  arm._init();
  Serial.print("enter value between 0 and ");
  Serial.println(arm.z_pulseNum / 75);
}

void loop() {
  if(Serial.available())
  {
    int input_z = Serial.parseInt();
    Serial.print("input value : ");
    Serial.println(input_z);
    arm.movez(input_z);
  }
  
  Serial.print("current z pulse : ");
  Serial.println(arm.z_index);

  delay(1000);

}
