
/*
    RECoreLibrary.h - RECore onboard Function library
    Copyright (c) 2021 Omniment Inc. All right reserved.
    
    MIT License
    
*/

#ifndef RECoreLibrary_h
#define RECoreLibrary_h

#include <RECoreMotorDriver.h>
#include <RECoreAuxFuncLibrary.h>

class RECoreLibrary : public RECoreMotorDriver , public RECoreAuxFuncLibrary{
    public:
        RECoreLibrary() : RECoreMotorDriver(){}

    private:

};

#endif
