#include "Stepper.h"
 
Stepper stepper1(5,2);

void setup() {
}
void loop() {
  stepper1.rotate(HIGH, 800);
  delay(5000);
  stepper1.rotate(LOW, 1600);
  stepper1.rotate()
}