#include "Stepper.h"

Stepper stepper1(5,2,2,13,12,11);

void setup() {
}

void loop() {
  for(int x=0; x<10; x++){
    stepper1.rotate(HIGH, 36, 100);
    delay(2000);
  }
}