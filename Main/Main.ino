#include "Stepper.h"

Stepper stepper1(3,2,2,10,9,8,2,6);
Stepper stepper2(5,4,2,13,12,11,2,7);

void setup() {
  stepper1.findHome();
  stepper2.findHome(); 
}

void loop() {
  setCoordinate(1,1,1);
  setpointCheck();

  delay(30000);
  setCoordinate(-10,20,5);
  setpointCheck();

  exit(1);
}

void setCoordinate(int xCoordinate, int yCoordinate, int delay){
  stepper1.setSetpoint(xCoordinate, delay);
  stepper2.setSetpoint(yCoordinate, delay);
}

bool setpointCheck(){
  while (abs(stepper1.getSetpoint()-stepper1.getCurrentPosition()) > 0.1 &&
      abs(stepper2.getSetpoint()-stepper2.getCurrentPosition()) > 0.1){
        stepper1.setpointRotate();
        stepper2.setpointRotate();
        continue;
      }
  return;
}