
/*
    RECoreLSM6Library.h - RECore onboard LSM6 Function library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#ifndef RECoreLSM6Library_h
#define RECoreLSM6Library_h

#include <SPI.h>

#define acc_2g 0x00
#define acc_4g 0x02
#define acc_8g 0x03
#define acc_16g 0x01

#define a_rate_250dps 0x00
#define a_rate_500dps 0x01
#define a_rate_1000dps 0x02
#define a_rate_2000dps 0x03
#define a_rate_125dps 0x04

#define acc_rate_down 0x00
#define acc_rate_12_5_Hz 0x01
#define acc_rate_26_Hz 0x02
#define acc_rate_52_Hz 0x03
#define acc_rate_104_Hz 0x04
#define acc_rate_208_Hz 0x05
#define acc_rate_416_Hz 0x06
#define acc_rate_833_Hz 0x07
#define acc_rate_1660_Hz 0x08
#define acc_rate_3330_Hz 0x09
#define acc_rate_6660_Hz 0x0A

#define a_rate_down 0x00
#define a_rate_12_5_Hz 0x01
#define a_rate_26_Hz 0x02
#define a_rate_52_Hz 0x03
#define a_rate_104_Hz 0x04
#define a_rate_208_Hz 0x05
#define a_rate_416_Hz 0x06
#define a_rate_833_Hz 0x07
#define a_rate_1660_Hz 0x08

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
