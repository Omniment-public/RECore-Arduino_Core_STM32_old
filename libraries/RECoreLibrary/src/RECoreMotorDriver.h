/*
    RECoreMotorDriver.h - RECore onboard DRV8848 library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#ifndef RECoreMotorDriver_h
#define RECoreMotorDriver_h

#define single_dc   0
#define parallel_dc 1
#define stepping    2

#define unit_a 0
#define unit_b 1

#define coast 0
#define brake 1

#include <Stepper.h>

class RECoreMotorDriver{
    public:
        RECoreMotorDriver(){
            for(int i = 0; i < 11; i++){
                driver_pin_array[i] = i + 14;
            }
            
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

        void setMotorType(uint8_t set_driver_unit, uint8_t set_motor_type_num, uint16_t stm_steps = 200);
        void setMotorCurrent(float set_motor_current);
        void setBrakeType(uint8_t set_motor_num, uint8_t set_brake_type);
        
        void setMotorSpeed(uint8_t set_motor_num, float set_motor_speed);
        void setMotorSpeedRaw(uint8_t set_motor_num, int set_motor_speed);
        void presetMotorSpeed(uint8_t set_motor_num, float set_motor_speed);
        void presetMotorSpeedRaw(uint8_t set_motor_num, int set_motor_speed);

        void setStep(uint8_t set_driver_unit, uint16_t set_step_count);
        void setSteppingSpeed(uint8_t set_driver_unit, uint16_t set_motor_speed);

        void runMotor(uint8_t set_motor_num = 0);
        void stopMotor(uint8_t set_motor_num = 0);
        bool getMotorFault();
        void setSleep(bool pin_state);
        int getMotorSpeed(uint8_t get_motor_num);

    private:
        Stepper* stm_a;
        Stepper* stm_b;

        //pin array
        //0-3 unit a
        //4-7 unit b
        //8 sleep
        //9 fault
        //10 vref
        uint8_t driver_pin_array[11];
        
        uint8_t driver_mode[2];
        float motor_current;
        uint8_t brake_mode[4];
        uint8_t motor_pwm_value[8];

};

#endif
