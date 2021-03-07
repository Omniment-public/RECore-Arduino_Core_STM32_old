/*
    RECoreMotorDriverLibrary.cpp - RECore onboard DRV8848 library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#if defined(ARDUINO_ARCH_STM32)

#include <Arduino.h>

#include "RECoreMotorDriverLibrary.h"

const uint8_t driver_pin_array[11] = {14,15,16,17,18,19,20,21,22,23,24};

void proc_steps_a(void);
void proc_steps_b(void);
bool stm_pattern[4][2] = {{1, 1}, {1, 0}, {0, 0}, {0, 1}};
int32_t stepping_count[2];
bool drive_stepping_infinity[2];
HardwareTimer* unit_a_tim;
HardwareTimer* unit_b_tim;

RECoreMotorDriverLibrary::RECoreMotorDriverLibrary(){
    //init pins
    for(int i = 0; i < 9; i++){
        pinMode(driver_pin_array[i], OUTPUT);
        digitalWrite(driver_pin_array[i],0);
    }
    pinMode(driver_pin_array[9], INPUT_PULLUP);
    pinMode(driver_pin_array[10], OUTPUT);
    digitalWrite(driver_pin_array[10],0);

    //driver sleep
    digitalWrite(driver_pin_array[8],0);

    //init motorcurrent;
    setMotorCurrent(0);

    //init motor pwm
    for(int i = 0; i < 8; i++){
        motor_pwm_value[i] = 0;
    }
    analogWriteFrequency(25000);
}

void RECoreMotorDriverLibrary::setMotorType(uint8_t set_driver_unit, uint8_t set_motor_type_num, uint16_t stm_steps){
    //disable driver
    digitalWrite(driver_pin_array[8],0);

    if(set_driver_unit == 0){
        if(set_motor_type_num == 0){
            //single dc
            for(int i = 0; i < 4; i++){
                pinMode(driver_pin_array[i],OUTPUT);
                digitalWrite(driver_pin_array[i],0);
            }
        }else if(set_motor_type_num == 1){
            //parallel dc
            //Open AIN
            pinMode(driver_pin_array[0],OUTPUT_OPEN_DRAIN);
            pinMode(driver_pin_array[1],OUTPUT_OPEN_DRAIN);
            digitalWrite(driver_pin_array[0],1);
            digitalWrite(driver_pin_array[1],1);
            digitalWrite(driver_pin_array[2],0);
            digitalWrite(driver_pin_array[3],0);
        }else if(set_motor_type_num == 2){
            for(int i = 0; i < 4; i++){
                pinMode(driver_pin_array[i],OUTPUT);
                digitalWrite(driver_pin_array[i],0);
            }
            unit_a_tim = new HardwareTimer(TIM2);
            motor_step_count[0] = stm_steps;
            //stm_a = new Stepper(stm_steps, driver_pin_array[0], driver_pin_array[1], driver_pin_array[2], driver_pin_array[3]);
        }
    }else if(set_driver_unit == 1){
        if(set_motor_type_num == 0){
            //single dc
            for(int i = 0; i < 4; i++){
                pinMode(driver_pin_array[i+4],OUTPUT);
                digitalWrite(driver_pin_array[i+4],0);
            }
        }else if(set_motor_type_num == 1){
            //parallel dc
            //Open AIN
            pinMode(driver_pin_array[4],OUTPUT_OPEN_DRAIN);
            pinMode(driver_pin_array[5],OUTPUT_OPEN_DRAIN);
            digitalWrite(driver_pin_array[4],1);
            digitalWrite(driver_pin_array[5],1);
            digitalWrite(driver_pin_array[6],0);
            digitalWrite(driver_pin_array[7],0);
        }else if(set_motor_type_num == 2){
            for(int i = 0; i < 4; i++){
                pinMode(driver_pin_array[i+4],OUTPUT);
                digitalWrite(driver_pin_array[i+4],0);
            }
            unit_b_tim = new HardwareTimer(TIM3);
            motor_step_count[1] = stm_steps;
            //stm_b = new Stepper(stm_steps, driver_pin_array[4], driver_pin_array[5], driver_pin_array[6], driver_pin_array[7]);
        }
    }else{
        return;
    }
    //enable driver
    delay(10);
    digitalWrite(driver_pin_array[8],1);

    driver_mode[set_driver_unit] = set_motor_type_num;
}

void RECoreMotorDriverLibrary::setMotorCurrent(float set_motor_current){
    if(set_motor_current > 1.5 | set_motor_current < 0){
        return;
    }
    
    //calc current to DAC value
    //12bit dac 0-4095 1.98/(3.3/4095)
    //float calc_dac_const = 2457.0;
    
    //8bit dac 0-255 1.98/(3.3/255)
    float calc_dac_const = 153.0;

    float calc_dac = set_motor_current * calc_dac_const;
    uint16_t calc_dac_16 = uint16_t(calc_dac);
    
    analogWrite(driver_pin_array[10], calc_dac);
    motor_current = set_motor_current;
    return;
}

void RECoreMotorDriverLibrary::setBrakeMode(uint8_t set_motor_num, uint8_t set_brake_type){
    brake_mode[set_motor_num] = set_brake_type;
}

void RECoreMotorDriverLibrary::setMotorSpeed(uint8_t set_motor_num, float set_motor_speed){
    presetMotorSpeed(set_motor_num, set_motor_speed);
    runMotor(set_motor_num);
}

void RECoreMotorDriverLibrary::setDrivePwm(uint8_t set_motor_num, int set_drive_pwm){
    presetDrivePwm(set_motor_num, set_drive_pwm);
    uint8_t control_motor_pair_num = set_motor_num * 2;
    analogWrite(driver_pin_array[control_motor_pair_num], motor_pwm_value[control_motor_pair_num]);
    analogWrite(driver_pin_array[control_motor_pair_num + 1], motor_pwm_value[control_motor_pair_num + 1]);
}


void RECoreMotorDriverLibrary::presetMotorSpeed(uint8_t set_motor_num, float set_motor_speed){
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

    uint8_t control_motor_pin_num = set_motor_num * 2;
    if(brake_mode[set_motor_num] == 0){
        //Coast mode
        motor_pwm_value[control_motor_pin_num] = calc_motor_pwm * dir;
        motor_pwm_value[control_motor_pin_num + 1] = calc_motor_pwm * !dir;
    }else{
        //brake mode
        motor_pwm_value[control_motor_pin_num] = 255 - (calc_motor_pwm * dir);
        motor_pwm_value[control_motor_pin_num + 1] = 255 - (calc_motor_pwm * !dir);
    }
    return;
}

void RECoreMotorDriverLibrary::presetDrivePwm(uint8_t set_motor_num, int set_drive_pwm){
    if(set_drive_pwm > 255 | set_drive_pwm < -255){
        return;
    }

    bool dir = false;
    if(set_drive_pwm > 0){
        //positive dir
        dir = false;
    }else{
        //negative dir
        dir = true;
    }

    uint8_t control_motor_pin_num = set_motor_num * 2;
    motor_pwm_value[control_motor_pin_num] = set_drive_pwm * dir;
    motor_pwm_value[control_motor_pin_num + 1] = set_drive_pwm * !dir;
    
    return;
}

void RECoreMotorDriverLibrary::setSteppingSpeed(uint8_t set_driver_unit, uint16_t set_motor_speed){
    if(set_driver_unit > 1){
        return;
    }
    if(driver_mode[set_driver_unit] != 2){
        return;
    }

    if(driver_mode[set_driver_unit] == 2){
        stepping_speed[set_driver_unit] = 60000000/(motor_step_count[set_driver_unit]*set_motor_speed);
        if(set_driver_unit == 0){
            unit_a_tim -> setOverflow(stepping_speed[set_driver_unit], MICROSEC_FORMAT);
            unit_a_tim -> attachInterrupt(proc_steps_a);
        }else{
            unit_b_tim -> setOverflow(stepping_speed[set_driver_unit], MICROSEC_FORMAT);
            unit_b_tim -> attachInterrupt(proc_steps_b);
        }
    }
}

void RECoreMotorDriverLibrary::setSteps(uint8_t set_driver_unit, int32_t set_step_count){
    if(set_driver_unit > 1){
        return;
    }
    if(driver_mode[set_driver_unit] != 2){
        return;
    }

    drive_stepping_infinity[set_driver_unit] = drive_infinity;
    stepping_count[set_driver_unit] = set_step_count;

    if(set_driver_unit == 0){
        unit_a_tim -> resume();
    }else{
        unit_b_tim -> resume();
    }
}

void RECoreMotorDriverLibrary::runMotor(uint8_t set_motor_num){
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

void proc_steps_a(void){
    static int8_t step_index = 0;

    if(stepping_count[0] == 0 && !drive_stepping_infinity[0]){
        unit_a_tim -> pause();
    }else{
        digitalWrite(driver_pin_array[0],stm_pattern[step_index][0]);
        digitalWrite(driver_pin_array[1],!stm_pattern[step_index][0]);
        digitalWrite(driver_pin_array[2],stm_pattern[step_index][1]);
        digitalWrite(driver_pin_array[3],!stm_pattern[step_index][1]);

        if(stepping_count[0] > 0){
            stepping_count[0]--;
            step_index++;
        }else{
            stepping_count[0]++;
            step_index--;
        }
        if(step_index > 3){
            step_index = 0;
        }else if(step_index < 0){
            step_index = 3;
        }
    }
}

void proc_steps_b(void){
    static int8_t step_index = 0;

    if(stepping_count[1] == 0 && !drive_stepping_infinity[1]){
        unit_b_tim -> pause();
    }else{
        digitalWrite(driver_pin_array[4],stm_pattern[step_index][0]);
        digitalWrite(driver_pin_array[5],!stm_pattern[step_index][0]);
        digitalWrite(driver_pin_array[6],stm_pattern[step_index][1]);
        digitalWrite(driver_pin_array[7],!stm_pattern[step_index][1]);

        if(stepping_count[1] > 0){
            stepping_count[1]--;
            step_index++;
        }else{
            stepping_count[1]++;
            step_index--;
        }

        if(step_index > 3){
            step_index = 0;
        }else if(step_index < 0){
            step_index = 3;
        }
    }
}

//void RECoreMotorDriverLibrary::stopMotor(uint8_t set_motor_num);

bool RECoreMotorDriverLibrary::getMotorFault(){
    return digitalRead(driver_pin_array[9]);
}

void RECoreMotorDriverLibrary::setSleep(bool pin_state){
    digitalWrite(driver_pin_array[8],pin_state);
}

//int RECoreMotorDriverLibrary::getMotorSpeed(uint8_t get_motor_num);

#endif // ARDUINO_ARCH_STM32
