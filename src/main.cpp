#include <Arduino.h>
#define DEBUGLOG_DEFAULT_LOG_LEVEL_INFO
#include "DebugLog.h"
#include "rtc_ds3231.h"
#include "Rotary_Encoder.h"
#include "time_select_mode.h"
#include "radio_mode_manager.h"

// radio_drivers::RadioTime rad_time{1,1,1}; 

// radio_drivers::RadioTime r_time(8,24,false); 
// radio_drivers::RTCDS3231 rtc_clk{Wire1,r_time}; 

// radio_drivers::SevenSegment disp(17,16,r_time); 
// RotaryEncoder re{12,11,10}; 
// mode_select::TimeSelectMode time_selector{disp,rtc_clk,r_time}; 

mode_select::ModeManger manager{17,16,
    Wire1,
    8,7,Wire,
    12,11,10}; 

unsigned long last_log = 0; 

void setup() 
{

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
// sleep_ms(10000); 
LOG_INFO("before starting the inits\n"); 
// manager.init(); 

base_utilities::UpdateBase::run_inits(); 

}


void loop() 
{
    base_utilities::UpdateBase::run_updates(); 
    base_utilities::UpdateBase::run_fixed_updates(); 

}
