#include <Arduino.h>

///Class to allow the creation of a stepper instance for control of a stepper motor using an A4988 motor driver
class Stepper{
  private : int directionPin;
  private : int stepEnablePin;
  private : int stepDelay = 500;
  private : int stepResolution;
  private : int ms1, ms2, ms3;


  ///Constructor for creating a stepper motor variable
  public : Stepper(int directionPin, int stepEnablePin, int stepResolution, int ms1Pin, int ms2Pin, int ms3Pin){
    setDirectionPin(directionPin);
    setStepEnablePin(stepEnablePin);
    setMsPins(ms1Pin, ms2Pin, ms3Pin);
    setStepResolution(stepResolution);
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

  ///Allows the user to change the step resolution on the motor driver
  /// 0=Full, 1=1/2 step, 2=1/4 step, 3=1/8 step, 7=1/16 step
  ///All other invalid entries will be set to 0
  public : void setStepResolution(int resolution){
    switch (resolution){
      case 0:
        digitalWrite(ms1, LOW);
        digitalWrite(ms2, LOW);
        digitalWrite(ms3, LOW);
        this->stepResolution = 1;
        break;

      case 1:
        digitalWrite(ms1, HIGH);
        digitalWrite(ms2, LOW);
        digitalWrite(ms3, LOW);
        this->stepResolution = 2;
        break;

      case 2:
        digitalWrite(ms1, LOW);
        digitalWrite(ms2, HIGH);
        digitalWrite(ms3, LOW);
        this->stepResolution = 4;
        break;

      case 3:
        digitalWrite(ms1, HIGH);
        digitalWrite(ms2, HIGH);
        digitalWrite(ms3, LOW);
        this->stepResolution = 8;
        break;

      case 7:
        digitalWrite(ms1, HIGH);
        digitalWrite(ms2, HIGH);
        digitalWrite(ms3, HIGH);
        this->stepResolution = 16;
        break;

      default:
        digitalWrite(ms1, LOW);
        digitalWrite(ms2, LOW);
        digitalWrite(ms3, LOW);
        this->stepResolution = 1;
        break;
    }
  }

  ///Allows the user to change the pins that control the step resolution
  public : void setMsPins(int ms1Pin, int ms2Pin, int ms3Pin){
    this->ms1 = ms1Pin;
    pinMode(ms1, OUTPUT);
    this->ms2 = ms2Pin;
    pinMode(ms2, OUTPUT);
    this->ms3 = ms3Pin;
    pinMode(ms3, OUTPUT);
  }

  ///Allows the user to change the delay between the step pulses changing the rotation speed
  public : void setStepDelay(int delay){this->stepDelay = delay;}

  ///Used to rotate the motor in the 'b' direction a number of steps equal to the number of steps provided
  ///LOW = CCW, HIGH = CW
  public : void rotate(bool b, int revolutions){
    digitalWrite(directionPin, b);
    for(int x = 0; x < (revolutions*200*stepResolution); x++) {
      digitalWrite(stepEnablePin,HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(stepEnablePin,LOW);
      delayMicroseconds(stepDelay);
    }
  }
};