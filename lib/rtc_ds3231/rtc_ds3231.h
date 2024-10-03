#pragma once 
#include <Arduino.h>
#include <Wire.h>
#include "DebugLog.h"
#include "TimeDisplay.h"

namespace radio_drivers
{

class RTCDS3231 
{
    public:
    RTCDS3231(TwoWire& in_wire_ref, RadioTime& in_time); 
    void init(); //calls the begin function of the wire

    bool set_time(uint8_t hours, uint8_t mins, bool is_am);    

    bool check_connection(); 

    //grabs radio time reference (for debug purposes)
    RadioTime get_time();  //also used in the refresh time function

    //refresh radio time 
    void refresh_time(); //check the rtc for time changes

    //set date (will be used sparsely for and only through firmware update)
    void set_full_date(uint8_t day, uint8_t month, uint8_t year); 
    private: 
    TwoWire& wire_ref; 
    RadioTime& radio_time_ref; 

    static constexpr uint8_t SECONDS = 0x00; // 0b 0 | 000 (10s place) | 0000 seconds 
    static constexpr uint8_t MINUTES = 0x01; // 0b 0 | 000 (10s place) | 0000 minutes
    static constexpr uint8_t HOURS = 0x02; // 0b 0 | 0 (12/24 hour) | 0 (am/pm or 20 hour (for 24 hour)) | 0 (10 hour) | 0000 (1-12 hours)
    static constexpr uint8_t DAY = 0x03; // 0b00000 | 000 (day-week) (1-7)
    static constexpr uint8_t DATE = 0x04; //0b00 | 00 (10 day) | 0000 (day) 
    static constexpr uint8_t MONTH = 0x05; //0b | 0 (century) | 00 | 

    static constexpr uint8_t I2C_ADDRESS = 0b1101000; // 7 bit address of device 
}; 

} // radio driver namespace