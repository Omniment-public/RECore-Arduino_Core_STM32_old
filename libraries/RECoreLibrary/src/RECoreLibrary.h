
/*
    RECoreLibrary.h - RECore onboard Function library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#ifndef RECoreLibrary_h
#define RECoreLibrary_h

#include <RECoreAuxFuncLibrary.h>
#include <RECoreMotorDriverLibrary.h>
#include <RECoreLSM6Library.h>

#define single_dc   0
#define parallel_dc 1
#define stepping    2

#define unit_a 0
#define unit_b 1

#define coast 0
#define brake 1

#define acc_2g 0
#define acc_4g 2
#define acc_8g 3
#define acc_16g 1

#define a_acc_250 0
#define a_acc_500 1
#define a_acc_1000 2
#define a_acc_2000 3
#define a_acc_125 4

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


class RECoreLibrary : public RECoreAuxFuncLibrary , public RECoreMotorDriverLibrary , public RECoreLSM6Library{
    public:
        RECoreLibrary() : RECoreAuxFuncLibrary() , RECoreMotorDriverLibrary() , RECoreLSM6Library(){
            
        }

    private:

};

#endif
