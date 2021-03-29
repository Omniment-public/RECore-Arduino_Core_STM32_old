/*
   RECore Library
   Single DC motor example

   All motor unit use single DC motor mode.

*/

#include <RECoreLibrary.h>

RECoreLibrary recore;

void setup() {
  //init motor type single_dc mode
  recore.setMotorType(unit_a, single_dc);
  recore.setMotorType(unit_b, single_dc);

  //set all motor current limit
  //current range : 1 ~ 1500
  //setMotorCurrent(current);
  //example set 500mA
  recore.setMotorCurrent(500);

  //set motor brake mode
  //can change motor brake mode
  //motor number : 0 ~ 3
  //brake type : brake , coast (default set brake)
  //setBrakeMode(motor number, brake type);
}

void loop() {
  //set Motor speed
  //motor number : 0 ~ 3
  //motor power : -1.0 ~ 0 ~ 1.0
  //setMotorSpeed(motor number, motor power);
  //set Motor 0 speed forward 50%
  recore.setMotorSpeed(0, 0.5);
  delay(1000);

  //stop motor 0
  recore.setMotorSpeed(0, 0);
  delay(1000);

  //set Motor 0 speed reverse 50%
  recore.setMotorSpeed(0, -0.5);
  delay(1000);

  //stop motor 0
  recore.setMotorSpeed(0, 0);
  delay(1000);
}
