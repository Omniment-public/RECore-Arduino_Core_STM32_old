
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

#define acc_2g 0
#define acc_4g 2
#define acc_8g 3
#define acc_16g 1

#define a_acc_250 0
#define a_acc_500 1
#define a_acc_1000 2
#define a_acc_2000 3
#define a_acc_125 4

#define single_dc   0
#define parallel_dc 1
#define stepping    2

#define unit_a 0
#define unit_b 1

#define coast 0
#define brake 1

class RECoreLibrary : public RECoreAuxFuncLibrary , public RECoreMotorDriverLibrary , public RECoreLSM6Library{
    public:
        RECoreLibrary() : RECoreAuxFuncLibrary() , RECoreMotorDriverLibrary() , RECoreLSM6Library(){
            
        }

    private:

};

#endif
