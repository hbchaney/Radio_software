#include "rtc_ds3231.h"

using namespace radio_drivers; 

radio_drivers::RTCDS3231::RTCDS3231(TwoWire& in_wire_ref, RadioTime& in_time) : 
    wire_ref{in_wire_ref}, 
    radio_time_ref{in_time}
{}

void RTCDS3231::init()
{
    wire_ref.begin(); //begin the transmission for all the following stuff
}

bool RTCDS3231::set_time(uint8_t hours, uint8_t mins, bool is_am) 
{
    //do some checks first 
    if (hours > 12 || mins >= 60)
    {
        LOG_ERROR("tried to enter an invalid time value"); 
        return false; 
    }

    //setting the time bytes 
    uint8_t min_single = mins % 10; 
    uint8_t min_tenths = mins / 10;

    bool hours_tens = hours / 10; 
    uint8_t hours_single = hours % 10; 


    uint8_t seconds_out = 0x0; //set the seconds to zero
    uint8_t mins_out = min_single | (min_tenths << 4); 
    uint8_t hours_out = 0b01000000 | !(is_am & 0b1) << 5 | hours_single | static_cast<uint8_t>(hours_tens) << 4; 

    wire_ref.beginTransmission(I2C_ADDRESS); 
    wire_ref.write(SECONDS);  
    wire_ref.write(seconds_out); 
    wire_ref.write(mins_out); 
    wire_ref.write(hours_out); 
    auto status = wire_ref.endTransmission(); 
    if (status != 0) 
    {
        //something went wrong 
        LOG_ERROR("error when setting the time : ",status); 
        return false; 
    }

    return true;
}

bool RTCDS3231::check_connection() 
{
    wire_ref.begin();
    wire_ref.beginTransmission(I2C_ADDRESS); 
    auto resp = wire_ref.endTransmission(); 
    if (resp != 0)
    {
        LOG_ERROR("connection returned false with error : ", resp); 
        return false; 
    }
    return true;
}

RadioTime RTCDS3231::get_time() 
{
    RadioTime rad_time{1,1,1}; // setting with defualt time  

    //write to request for for minutes firest 
    wire_ref.beginTransmission(I2C_ADDRESS); 
    wire_ref.write(MINUTES); //requesting to read minutes 
    auto response = wire_ref.endTransmission(false); 
    if (response != 0) 
    {
        LOG_ERROR("get time had error : ", response); 
    }   
    wire_ref.requestFrom(I2C_ADDRESS,2); //requesting two bytes (mins then hours) 
    uint8_t ret_bytes[2]; 
    wire_ref.readBytes(ret_bytes,2); 

    //now parse the return bytes 
    uint8_t mins_tens = (ret_bytes[0] >> 4) * 10; //should be 3 bits after the first 4 
    uint8_t mins_single = ret_bytes[0] & 0b1111; //should be the first 4 bits 
    uint8_t mins = mins_tens + mins_single; 

    uint8_t hours; 
    bool is_am; 

    //check if 24 or 12 hour mode 
    if (ret_bytes[1] & 0b01000000)
    {
        //12 hour mode 
        is_am = !(ret_bytes[1] & 0b00100000); //third bit tells if am or pm high is pm so !
        uint8_t hours_tens =  ((ret_bytes[1] & 0b00010000) >> 4) * 10; 
        uint8_t hours_single = ret_bytes[1] & 0b1111;  
        hours = hours_tens + hours_single; 
    }
    else 
    {
        //24 hour mode 
        bool hour_20 = (ret_bytes[1] & 0b00100000); //20 hour bit 
        bool hour_10 = (ret_bytes[1] & 0b00010000); //10 hour bit
        uint8_t hour_tens = hour_20 * 10 + hour_10 * 10; // I assume both would be set but that might not be true
        uint8_t hour_single = ret_bytes[1] & 0b1111; 
        uint8_t mil_hours = hour_single + hour_tens; 

        //convert back to reg time 
        if (mil_hours > 13)
        {
            hours = mil_hours - 12; 
            is_am = false; 
        }
        else if (mil_hours == 12) 
        {
            hours = mil_hours; 
            is_am = false; 
        }
        else if (mil_hours == 0) 
        {
            hours = 12;
            is_am = true; 
        }
        else 
        {
            hours = mil_hours; 
            is_am = true; 
        }
    }
    rad_time.set_time(hours,mins,is_am); 
    return rad_time; 
}

void RTCDS3231::refresh_time() 
{
    radio_time_ref = get_time(); 
}

void RTCDS3231::set_full_date(uint8_t day, uint8_t month, uint8_t year)
{
    //not implemented for now but might for a calender project later
}