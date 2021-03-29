/*
   RECore Library
   LSM6 IMU example
*/

#include <RECoreLibrary.h>

RECoreLibrary recore;

void setup() {
  //init serial
  Serial.begin(115200);

  //set Acceleromater ODR Rate
  //acc_rate_down
  //acc_rate_12_5_Hz
  //acc_rate_26_Hz
  //acc_rate_52_Hz
  //acc_rate_104_Hz
  //acc_rate_208_Hz
  //acc_rate_416_Hz
  //acc_rate_833_Hz
  //acc_rate_1660_Hz
  //acc_rate_3330_Hz
  //acc_rate_6660_Hz
  recore.setAccDataRate(acc_rate_104_Hz);

  //set Gyroscope ODR Rate
  //a_acc_rate_down
  //a_acc_rate_12_5_Hz
  //a_acc_rate_26_Hz
  //a_acc_rate_52_Hz
  //a_acc_rate_104_Hz
  //a_acc_rate_208_Hz
  //a_acc_rate_416_Hz
  //a_acc_rate_833_Hz
  //a_acc_rate_1660_Hz
  recore.setAngularRateDataRate(a_acc_rate_104_Hz);
}

void loop() {
  //get IMU data
  //get Acceleromater Raw data
  //int16_t getRawAccX()
  //int16_t getRawAccY()
  //int16_t getRawAccZ()

  //Get Acceleromater unit-converted data(g)
  //float getAccX()
  //float getAccY()
  //float getAccZ()

  //get Gyroscope Raw data
  //int16_t getRawAngularRateX()
  //int16_t getRawAngularRateY()
  //int16_t getRawAngularRateZ()

  //get Gyroscope unit-converted data(dps)
  //float getAngularRateX()
  //float getAngularRateY()
  //float getAngularRateZ()

  Serial.print(recore.getAccX());
  Serial.print(",");
  Serial.print(recore.getAccY());
  Serial.print(",");
  Serial.print(recore.getAccZ());
  Serial.print(",");
  Serial.print(recore.getAngularRateX());
  Serial.print(",");
  Serial.print(recore.getAngularRateY());
  Serial.print(",");
  Serial.println(recore.getAngularRateZ());
  
  delay(5);
}
