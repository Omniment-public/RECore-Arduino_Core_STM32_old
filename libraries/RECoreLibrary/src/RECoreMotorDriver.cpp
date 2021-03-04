/*
    RECoreMotorDriver.cpp - RECore onboard DRV8848 library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#if defined(ARDUINO_ARCH_STM32)

#include <Arduino.h>

#include "RECoreMotorDriver.h"

void RECoreMotorDriver::setMotorType(uint8_t set_driver_unit, uint8_t set_motor_type_num, uint16_t stm_steps){
    //disable driver
    digitalWrite(driver_pin_array[8],0);

    if(set_driver_unit == 0){
        if(set_motor_type_num == 0){// | set_motor_type_num == 2){
            //single dc
            for(int i = 0; i < 4; i++){
                digitalWrite(driver_pin_array[i],0);
            }
        }else if(set_motor_type_num == 1){
            //parallel dc
            //Open AIN
            pinMode(driver_pin_array[0],OUTPUT_OPEN_DRAIN);
            pinMode(driver_pin_array[1],OUTPUT_OPEN_DRAIN);
            digitalWrite(driver_pin_array[2],0);
            digitalWrite(driver_pin_array[3],0);
        }else if(set_motor_type_num == 2){
            stm_a = new Stepper(stm_steps, driver_pin_array[0], driver_pin_array[1], driver_pin_array[2], driver_pin_array[3]);
        }
    }else if(set_driver_unit == 1){
        if(set_motor_type_num == 0){// | set_motor_type_num == 2){
            //single dc
            for(int i = 0; i < 4; i++){
                digitalWrite(driver_pin_array[i+4],0);
            }
        }else if(set_motor_type_num == 1){
            //parallel dc
            //Open AIN
            pinMode(driver_pin_array[4],OUTPUT_OPEN_DRAIN);
            pinMode(driver_pin_array[5],OUTPUT_OPEN_DRAIN);
            digitalWrite(driver_pin_array[6],0);
            digitalWrite(driver_pin_array[7],0);
        }else if(set_motor_type_num == 2){
            stm_b = new Stepper(stm_steps, driver_pin_array[4], driver_pin_array[5], driver_pin_array[6], driver_pin_array[7]);
        }
    }else{
        return;
    }
    //enable driver
    digitalWrite(driver_pin_array[8],1);

    driver_mode[set_driver_unit] = set_motor_type_num;
}

void RECoreMotorDriver::setMotorCurrent(float set_motor_current){
    if(set_motor_current > 1.5 | set_motor_current < 0){
        return;
    }
    
    //calc current to DAC value
    //12bit dac 0-4095 1.98/(3.3/4096)
    //float calc_dac_const = 2457.6;
    
    //8bit dac 0-255 1.98/(3.3/256)
    float calc_dac_const = 153.6;

    float calc_dac = set_motor_current * calc_dac_const;
    uint16_t calc_dac_16 = uint16_t(calc_dac);
    
    analogWrite(driver_pin_array[10], calc_dac);
    motor_current = set_motor_current;
    return;
}

void RECoreMotorDriver::setBrakeType(uint8_t set_motor_num, uint8_t set_brake_type){
    brake_mode[set_motor_num] = set_brake_type;
}

void RECoreMotorDriver::setMotorSpeed(uint8_t set_motor_num, float set_motor_speed){
    presetMotorSpeed(set_motor_num, set_motor_speed);
    runMotor(set_motor_num);
}

void RECoreMotorDriver::presetMotorSpeed(uint8_t set_motor_num, float set_motor_speed){
    //chk over set speed
    if(set_motor_speed > 1.0 | set_motor_speed < -1.0){
        return;
    }

    //calc pwm
    uint8_t calc_motor_pwm = 255 * set_motor_speed;
    bool dir = false;

    if(set_motor_speed > 0){
        //positive dir
        dir = false;
    }else{
        //negative dir
        dir = true;
    }

    //chk motor type
    uint8_t target_driver_unit = 0;

    if(set_motor_num >= 2){
        target_driver_unit = 1;
    }
    if(driver_mode[target_driver_unit] == 1){
        //parallel
        if(set_motor_num == 0 | set_motor_num == 2){
            set_motor_num + 1;
        }
    }else if(driver_mode[target_driver_unit] == 2){
        //stepper
        return;
    }

    uint8_t control_motor_pair_num = target_driver_unit * 2;
    if(brake_mode[set_motor_num] == 0){
        //Coast mode
        motor_pwm_value[control_motor_pair_num] = calc_motor_pwm * dir;
        motor_pwm_value[control_motor_pair_num + 1] = calc_motor_pwm * !dir;
    }else{
        //brake mode
        motor_pwm_value[control_motor_pair_num] = 255 - (calc_motor_pwm * dir);
        motor_pwm_value[control_motor_pair_num + 1] = 255 - (calc_motor_pwm * !dir);
    }
    Serial.println(motor_pwm_value[control_motor_pair_num]);
    Serial.println(motor_pwm_value[control_motor_pair_num+1]);
    return;
}

void RECoreMotorDriver::setStep(uint8_t set_driver_unit, uint16_t set_step_count){
    if(set_driver_unit == 0 && driver_mode[0] == 2){
        stm_a -> step(set_step_count);
    }else if(set_driver_unit == 1 && driver_mode[1] == 2){
        stm_b -> step(set_step_count);
    }else{
        return;
    }
}

void RECoreMotorDriver::setSteppingSpeed(uint8_t set_driver_unit, uint16_t set_motor_speed){
    if(set_driver_unit == 0 && driver_mode[0] == 2){
        stm_a -> setSpeed(set_motor_speed);
    }else if(set_driver_unit == 1 && driver_mode[1] == 2){
        stm_b -> setSpeed(set_motor_speed);
    }else{
        return;
    }
}

void RECoreMotorDriver::runMotor(uint8_t set_motor_num){
    //chk motor type
    uint8_t target_driver_unit = 0;
    
    if(set_motor_num >= 2){
        target_driver_unit = 1;
    }

    if(driver_mode[target_driver_unit] == 1){
        //parallel
        if(set_motor_num == 0 | set_motor_num == 2){
            set_motor_num + 1;
        }
    }else if(driver_mode[target_driver_unit] == 2){
        //stepper
        return;
    }

    uint8_t control_motor_pair_num = set_motor_num * 2;
    analogWrite(driver_pin_array[control_motor_pair_num], motor_pwm_value[control_motor_pair_num]);
    analogWrite(driver_pin_array[control_motor_pair_num + 1], motor_pwm_value[control_motor_pair_num + 1]);
}

//void RECoreMotorDriver::stopMotor(uint8_t set_motor_num);

bool RECoreMotorDriver::getMotorFault(){
    return digitalRead(driver_pin_array[9]);
}

void RECoreMotorDriver::setSleep(bool pin_state){
    digitalWrite(driver_pin_array[8],pin_state);
}

//int RECoreMotorDriver::getMotorSpeed(uint8_t get_motor_num);

#endif // ARDUINO_ARCH_STM32
