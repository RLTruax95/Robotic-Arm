#include "Stepper.h"

Stepper stepper1(3,2,2,10,9,8,2,6);
Stepper stepper2(5,4,2,13,12,11,2,7);

void setup() {
  stepper1.findHome();
  stepper2.findHome(); 
}

void loop() {
  stepper1.rotate(0, 360, 500);
  stepper1.rotate(0, 360, 500);
  delay(3000);
}