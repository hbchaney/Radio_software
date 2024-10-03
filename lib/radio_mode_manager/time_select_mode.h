#pragma once 
#include "mode.h"
#include "rtc_ds3231.h"
#include "TimeDisplay.h"

namespace mode_select 
{

//mode for selecting the current time 
class TimeSelectMode : public base_utilities::Mode
{
    radio_drivers::SevenSegment& seg_ref; 
    radio_drivers::RTCDS3231& rtc_ref; 
    radio_drivers::RadioTime& time_ref;  

    enum class SetType
    {
        HOURS, 
        MINS
    }; 

    SetType current_set = SetType::MINS; 

    void process_display(bool update_time); 

    bool blink_state = false; 
    unsigned long last_blink = 0; 

    public: 

    TimeSelectMode(radio_drivers::SevenSegment& seg, 
    radio_drivers::RTCDS3231& rtc, 
    radio_drivers::RadioTime& rt); 

    bool process_input(Input in) override; // 
    
}; 

} //mode_select 

