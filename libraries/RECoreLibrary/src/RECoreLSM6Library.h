
/*
    RECoreLSM6Library.h - RECore onboard LSM6 Function library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#ifndef RECoreLSM6Library_h
#define RECoreLSM6Library_h

#include <SPI.h>

class RECoreLSM6Library{
    public:
        
        RECoreLSM6Library()
        {
            
            init();
        }
        
        void init();
        float getAccX();
        float getAccY();
        float getAccZ();

        float getAngularAccX();
        float getAngularAccY();
        float getAngularAccZ();

        float getTemp();

        void send_spi_data(uint8_t send_data, bool wr);
        void receive_spi_data(uint8_t* receive_data, uint8_t len);

        bool get_comp();

    private:
        SPIClass* SPI_2;
        bool init_comp;
};

#endif
