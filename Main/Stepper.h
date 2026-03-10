#include <Arduino.h>
//https://www.handsontec.com/dataspecs/module/A4988.pdf
///Class to allow the creation of a stepper instance for control of a stepper motor using an A4988 motor driver
class Stepper{
  private : int numMotorSteps = 200;
  private : int directionPin;
  private : int stepEnablePin;
  private : int stepDelay = 500;
  private : int stepResolution = 0;
  private : int ms1 = 0, ms2 = 1, ms3 = 2;
  private : float currentPosition = 0.0;
  private : int homeSwitchPin = 0;
  private : float gearboxRatio = 1.0;
  private : int setpoint = 0;
  private : float stepCount = 0.0;
  private : bool stepDirection = 0;
  private : float stepDuration = 0.0;
  private : int stepSize = 0.0;

  ///Constructor for creating a stepper motor variable \n
  ///By default the ms pins are 0, 1, and 2, but can be set using the setMsPins function \n
  ///By default the step resolution will be set to full step but can be changed with setStepResolution() \n
  ///Upon initialization, the motor will rotate CCW to look for a zero position 
  public : Stepper(int directionPin, int stepEnablePin, int stepResolution, int ms1Pin, int ms2Pin, int ms3Pin, int res, int homePin){
    setDirectionPin(directionPin);
    setStepEnablePin(stepEnablePin);
    setMsPins(ms1Pin, ms2Pin, ms3Pin);
    setStepResolution(res);
    this->homeSwitchPin = homePin;
  }

  ///A function used to run the motor CCW to look for a constant zero position
  public : void findHome(){
    while(digitalRead(homeSwitchPin) == LOW){
      rotate(0, 1, 1);
    }
    currentPosition = 0;
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

  public : void setGearboxRatio(float ratio){this->gearboxRatio = ratio;}

  public : void setHomePin(int homePin){this->homeSwitchPin = homePin;}

  public : float getCurrentPosition(){return currentPosition;}

  ;public : int getSetpoint(){return setpoint;}

  ///Allows the user to change the step resolution on the motor driver \n
  /// 0=Full, 1=1/2 step, 2=1/4 step, 3=1/8 step, 7=1/16 step \n
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
/////////////////////////////////////////////////////////Problems here somewhere//////////////////////////////////////////////////////////////
  public : void setSetpoint(int coordinate, int delay){
    this->setpoint = coordinate;
    this->stepCount = (numMotorSteps*stepResolution*gearboxRatio)*((coordinate-currentPosition) / 360.0f);
    //stepSize is the duration of each pulse used to hold the value until the coordinate is reached
    this->stepDuration = (delay * 1000.0f) / (2.0f * stepCount);
    this->stepSize = (coordinate - currentPosition)/stepCount;
    if ((coordinate - currentPosition) < 0){this->stepDirection = 0;}
    else{this->stepDirection = 1;}
  }

  public : void setpointRotate(){
    if (stepCount > 0){
      this->stepCount -= 1;
    }else if (abs(setpoint-currentPosition)<stepSize){
      float tempRatio = abs(setpoint-currentPosition)/stepSize;
      this->stepDuration *= tempRatio;
      this->stepSize *= tempRatio;
      this->currentPosition = this->setpoint;
    }

    digitalWrite(directionPin, stepDirection);
    digitalWrite(stepEnablePin,HIGH);
    delayMicroseconds(stepDuration);
    digitalWrite(stepEnablePin,LOW);
    delayMicroseconds(stepDuration);
    currentPosition += stepSize;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///Used to rotate the motor in the 'b' direction a number of steps equal to the value provided \n
  ///The delay defines how long the rotation will take in milliseconds \n
  ///LOW = CCW, HIGH = CW 
  public : void rotate(bool b, float degrees, int delay){
    digitalWrite(directionPin, b);
    float pulses = (numMotorSteps*stepResolution*gearboxRatio)*(degrees / 360.0f);
    //step delay is the requested run time divided by double the number of pulses due to the function
    //delaying half while running the motor is running and half between pulses
    this->stepDelay = (delay * 1000.0f) / (2.0f * pulses);
    for(int x = 0; x < ((int)pulses); x++) {
      digitalWrite(stepEnablePin,HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(stepEnablePin,LOW);
      delayMicroseconds(stepDelay);
    }
    if(b==LOW){currentPosition -= degrees;}
    else{currentPosition += degrees;}
  }
};