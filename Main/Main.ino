#include "Stepper.h"

Stepper stepper1(3,2,2);
Stepper stepper2(5,4,2);

void setup() {
  stepper1.setMsPins(10,9,8);
  stepper1.setStepResolution(2);
  stepper1.setHomePin(0);
  stepper1.findHome(); 

  stepper2.setMsPins(13,12,11);
  stepper2.setStepResolution(2);
  stepper2.setHomePin(7);
  stepper2.findHome(); 
}

void loop() {
  
}