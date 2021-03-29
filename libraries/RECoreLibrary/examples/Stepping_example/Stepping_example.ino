/*
   RECore Library
   Stepping motor example

   All motor unit use stepping motor mode.

*/

#include <RECoreLibrary.h>

RECoreLibrary recore;

void setup() {
  //init motor type stepping mode
  //stepping mode need step/rev
  //setMotorType(unit, stepping, step/rev)
  //example set 200step/rev
  recore.setMotorType(unit_a, stepping, 200);
  recore.setMotorType(unit_b, stepping, 200);

  //set all motor current limit
  //setMotorCurrent(current);
  //current range : 1 ~ 1500
  
  //example set 100mA
  recore.setMotorCurrent(300);
}

void loop() {
  //set Stepping speed
  //keep rotate stepping motor
  //setSteppingSpeed(motor unit, set speed, dir);
  //motor unit : unit_a , unit_b
  //set speed : set min^-1
  //dir : true , false

  //example set unit_a 200min^-1
  recore.setSteppingSpeed(unit_a, 200, true);
  
  delay(1000);
  recore.setSteppingSpeed(unit_a, 0, true);
  
  //set Stepping steps
  //Rotate set value times
  //setSteppingSpeed(motor unit, set speed, rotate value);
  //motor unit : unit_a , unit_b
  //set speed : set min^-1
  //rotate value : int32_t
  recore.setSteppingSteps(unit_a, 200, 200);
  delay(1000);
}
