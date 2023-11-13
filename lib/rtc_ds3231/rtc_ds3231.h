#pragma once 
#include <Arduino.h>
#include <Wire.h>
#include "DebugLog.h"

namespace radio_drivers
{

class RTCDS3231 
{
    public:
    RTCDS3231(TwoWire& in_wire_ref); 

    bool set_time(uint8_t hours, uint8_t mins, bool is_am);    

    //debug function 
    bool print_time(); 

    private: 
    TwoWire& wire_ref; 
}; 

} // radio driver namespace