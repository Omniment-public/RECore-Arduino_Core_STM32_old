
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

class RECoreLibrary : public RECoreAuxFuncLibrary , public RECoreMotorDriverLibrary , public RECoreLSM6Library{
    public:
        RECoreLibrary() : RECoreAuxFuncLibrary() , RECoreMotorDriverLibrary() , RECoreLSM6Library(){
            
        }

    private:

};

#endif
