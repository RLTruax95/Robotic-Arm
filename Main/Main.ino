#include "Stepper.h"

Stepper stepper1(5,2,2);

void setup() {
  stepper1.setMsPins(13,12,11);
  stepper1.setStepResolution(2);
}

void loop() {
  stepper1.setGearboxRatio(2.0);
  stepper1.rotate(HIGH, 360, 1000);
  delay(2000);

  stepper1.setGearboxRatio(3.0);
  stepper1.rotate(LOW, 360, 2000);
  delay(2000);
}