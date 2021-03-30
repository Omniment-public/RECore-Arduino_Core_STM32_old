/*
   RECore Library
   LSM6 IMU example
*/

#include <RECoreLibrary.h>

RECoreLibrary recore;

void setup() {
  //init serial
  Serial.begin(115200);

  //set Acceleromater Output Data Rate
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

  //set Acceleromater Output Data Scale
  //acc_2g 0x00
  //acc_4g 0x02
  //acc_8g 0x03
  //acc_16g 0x01
  recore.setAccScale(acc_2g);

  //set Gyroscope Output Data Rate
  //a_rate_down 0x00
  //a_rate_12_5_Hz 0x01
  //a_rate_26_Hz 0x02
  //a_rate_52_Hz 0x03
  //a_rate_104_Hz 0x04
  //a_rate_208_Hz 0x05
  //a_rate_416_Hz 0x06
  //a_rate_833_Hz 0x07
  //a_rate_1660_Hz 0x08
  recore.setAngularRateDataRate(a_rate_104_Hz);

  //set Gyroscope Output Data Scale
  //a_rate_250dps 0x00
  //a_rate_500dps 0x01
  //a_rate_1000dps 0x02
  //a_rate_2000dps 0x03
  //a_rate_125dps 0x04
  recore.setAngularRateScale(a_rate_250dps);
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