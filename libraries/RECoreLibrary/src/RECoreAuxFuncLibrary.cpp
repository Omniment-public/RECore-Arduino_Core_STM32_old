
/*
    RECoreAuxFuncLibrary.cpp - RECore onboard Function library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#if defined(ARDUINO_ARCH_STM32)

#include <Arduino.h>

#include "RECoreAuxFuncLibrary.h"

float RECoreAuxFuncLibrary::getBatteryVoltage(){
    //(((3.3 / 1024.0) * vbat_adc) + 0.35) * ((120.0 + 51.0) / 51.0)
    float vbat_adc = analogRead(29);
    return (3.35294 * (0.35 + (0.00322266 * vbat_adc)));
}

int RECoreAuxFuncLibrary::getMcuTemp(){
    //10bit adc
    // (1.43 - (adc * 3.3/1024))/0.0043 + 30
    uint16_t adc_val = analogRead(ATEMP);
    float calc_temp = 30.0 + (232.558 * (1.43 - (0.00322266 * adc_val)));
    return calc_temp;
}

#endif // ARDUINO_ARCH_STM32

