/*
    RECoreMotorDriverLibrary.h - RECore onboard DRV8848 library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#ifndef RECoreMotorDriverLibrary_h
#define RECoreMotorDriverLibrary_h

#define single_dc   0
#define parallel_dc 1
#define stepping    2

#define unit_a 0
#define unit_b 1

#define coast 0
#define brake 1

class RECoreMotorDriverLibrary{
    public:
        RECoreMotorDriverLibrary();

        void setMotorType(uint8_t set_driver_unit, uint8_t set_motor_type_num, uint16_t stm_steps = 200);
        void setMotorCurrent(float set_motor_current);
        void setBrakeMode(uint8_t set_motor_num, uint8_t set_brake_type);
        
        void setMotorSpeed(uint8_t set_motor_num, float set_motor_speed);
        void setDrivePwm(uint8_t set_motor_num, int set_drive_pwm);
        void presetMotorSpeed(uint8_t set_motor_num, float set_motor_speed);
        void presetDrivePwm(uint8_t set_motor_num, int set_drive_pwm);

        void setSteppingSpeed(uint8_t set_driver_unit, uint16_t set_motor_speed, bool dir);
        void setSteppingSteps(uint8_t set_driver_unit, uint16_t set_motor_speed, int32_t set_step_count);
        
        void runMotor(uint8_t set_motor_num = 0);
        void stopMotor(uint8_t set_motor_num = 0);
        bool getMotorFault();
        void setSleep(bool pin_state);
        int getMotorSpeed(uint8_t get_motor_num);

    private:
        uint8_t driver_mode[2];
        float motor_current;
        uint8_t brake_mode[4];
        uint8_t motor_pwm_value[8];

        uint16_t motor_step_count[2];
        uint32_t stepping_speed[2];

        void presetSteppingSpeed(uint8_t set_driver_unit, uint16_t set_motor_speed);
};

#endif
