#include "Stepper.h"
 
Stepper stepper1(5,2,2,13,12,11);

void setup() {
}

void loop() {
  stepper1.rotate(HIGH, 1, 2);
  delay(1000);
  
  stepper1.rotate(LOW, 2, 2);
  delay(5000);

  stepper1.setStepResolution(0);
  stepper1.rotate(HIGH, 3, 9);
  delay(5000);

  stepper1.setStepResolution(7);
  stepper1.rotate(LOW, 5, 10);
  delay(5000);
  
}