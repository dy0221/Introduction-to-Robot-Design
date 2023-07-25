#include <AIROARM.h>

AiroArm arm;


void setup() {
  arm.offset.m1_deg = 3;
  arm.offset.m2_deg = 54;
  Serial.begin(115200);
  Serial1.begin(1000000);

  arm.pSerial = &Serial1;
  arm._init();
  
}

void loop() {
  
  arm.movep(100, 150);
  delay(2000);
  
  arm.movep(-100, 150);
  delay(2000);
  
  arm.movel(100, 150);
  delay(2000);
  
  arm.movel(-100, 150);
  delay(2000);
  
}
