
/*
    RECoreLibrary.h - RECore onboard Function library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#ifndef RECoreLibrary_h
#define RECoreLibrary_h

#include <RECoreMotorDriverLibrary.h>
#include <RECoreAuxFuncLibrary.h>

class RECoreLibrary : public RECoreMotorDriverLibrary , public RECoreAuxFuncLibrary{
    public:
        RECoreLibrary() : RECoreMotorDriverLibrary(){}

    private:

};

#endif
