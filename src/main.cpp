#include <Arduino.h>
#define DEBUGLOG_DEFAULT_LOG_LEVEL_INFO
#include "DebugLog.h"
#include "rtc_ds3231.h"
#include "Rotary_Encoder.h"

// radio_drivers::RadioTime rad_time{1,1,1}; 

radio_drivers::RadioTime r_time(8,24,false); 
// radio_drivers::RTCDS3231 rtc_clk{Wire1,r_time}; 

radio_drivers::SevenSegment disp(17,16,r_time); 
RotaryEncoder re{11,12,10}; 

unsigned long last_log = 0; 

void setup() 
{
//     rtc_clk.init(); 
//     rtc_clk.check_connection(); 

//     const char current_time[] = __TIME__; 
//     char hours_str[] = {current_time[0], current_time[1]}; 
//     char min_str[] = {current_time[3],current_time[4]}; 
//     int hours = std::atoi(hours_str); 
//     int mins = std::atoi(min_str); 

//     bool am; 
//     if (hours > 12) 
//     {
//         am = false; 
//         hours = hours - 12; 
//     }
//     else 
//     {
//         am = true; 
//     }

//     rtc_clk.set_time(hours,mins,am); 
    re.setup(); 

    disp.setBrightness(1); 

}


void loop() 
{
    base_utilities::UpdateBase::run_updates(); 
    auto out = re.pull_cache(); 
    if (out != Input::R_NOP)
    {
        LOG_INFO("the output is : ", static_cast<int>(out)); 
    }

    if (millis() - last_log > 5000)
    {
        last_log = millis(); 
        LOG_INFO("alive log "); 
    }

    // sleep_ms(2000);
    // LOG_INFO("checking connection ... "); 
    // auto status = rtc_clk.check_connection(); 
    // LOG_INFO(status); 
    // LOG_INFO("checking time : "); 
    // auto tm = rtc_clk.get_time(); 
    // LOG_INFO("time : h-",tm.get_hours(), " m-", tm.get_mins(), " am/pm-",tm.is_am());  
    // rtc_clk.refresh_time(); 
    // rtc_clk.check_connection(); 
    // disp.Update(); 
    // sleep_ms(200); 
    // r_time.add_time(0,2); 
}