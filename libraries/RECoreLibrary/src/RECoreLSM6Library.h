
/*
    RECoreLSM6Library.h - RECore onboard LSM6 Function library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#ifndef RECoreLSM6Library_h
#define RECoreLSM6Library_h

#include <SPI.h>

#define acc_2g 0
#define acc_4g 2
#define acc_8g 3
#define acc_16g 1

#define a_acc_250 0
#define a_acc_500 1
#define a_acc_1000 2
#define a_acc_2000 3
#define a_acc_125 4

class RECoreLSM6Library{
    public:
        
        RECoreLSM6Library();
        
        int16_t getRawAccX();
        int16_t getRawAccY();
        int16_t getRawAccZ();

        float getAccX();
        float getAccY();
        float getAccZ();

        int16_t getRawAngularRateX();
        int16_t getRawAngularRateY();
        int16_t getRawAngularRateZ();

        float getAngularRateX();
        float getAngularRateY();
        float getAngularRateZ();

        float getTemp();
        
        uint8_t getAccScale();
        float getAccScaleConstant();
        uint16_t getAngularRateScale();
        float getAngularRateScaleConstant();

        int16_t get_multibyte_data(uint8_t head_addr);
        uint8_t get_singlebyte_data(uint8_t head_addr);
        void write_singlebyte_data(uint8_t head_addr, uint8_t set_data);

        void setAccDataRate(uint8_t set_data);
        void setAccScale(uint8_t set_data);
        void setAccLpfBandwith(uint8_t set_data);

        void setAngularRateDataRate(uint8_t set_data);
        void setAngularRateScale(uint8_t set_data);

    private:
        SPIClass* SPI_2;

        void init();
        
        void send_spi_data(uint8_t send_data, bool wr);
        void receive_spi_data(uint8_t* receive_data, uint8_t len);

        uint8_t set_acc_rate;
        uint8_t set_acc_scale;
        uint8_t set_acc_plf_bw;
        uint8_t set_arate_rate;
        uint8_t set_arate_scale;

};

#endif
