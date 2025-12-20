#include <Arduino.h>

///Class to allow the creation of a stepper instance for control of a stepper motor using an A4988 motor driver
class Stepper{
  private : int directionPin;
  private : int stepEnablePin;
  private : int stepDelay = 500;

  ///Constructor for creating a stepper motor variable
  public : Stepper(int directionPin, int stepEnablePin){
    setDirectionPin(directionPin);
    setStepEnablePin(stepEnablePin);
  }

  ///Allows the user to change the step direction pin
  public : void setDirectionPin(int pin){
      this->directionPin = pin;
      pinMode(directionPin, OUTPUT);
    }

  ///Allows the user to change the step enable pin
  public : void setStepEnablePin(int pin){
      this->stepEnablePin = pin;
      pinMode(stepEnablePin, OUTPUT);
    }
  public : void setStepDelay(int delay){this->stepDelay = delay;}

  ///Used to rotate the motor in the 'b' direction a number of steps equal to the number of steps provided
  ///LOW = CCW, HIGH = CW
  public : void rotate(bool b, int steps){
    digitalWrite(directionPin, b);
    for(int x = 0; x < steps; x++) {
      digitalWrite(stepEnablePin,HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(stepEnablePin,LOW);
      delayMicroseconds(stepDelay);
    }
  }
};