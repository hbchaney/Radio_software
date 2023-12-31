#include "time_select_mode.h"
#include "DebugLog.h"

using namespace mode_select; 

TimeSelectMode::TimeSelectMode(radio_drivers::SevenSegment& seg, 
    radio_drivers::RTCDS3231& rtc, 
    radio_drivers::RadioTime& rt) : 
seg_ref{seg}, 
rtc_ref{rtc}, 
time_ref{rt}
{}

void TimeSelectMode::process_display(bool update_time)
{
    //blink the two dots for time set mode  
    
    //first check if update_time needs to updated 
    if (update_time)
    {
        seg_ref.Update(blink_state); 
        return; 
    }

    //check if time has passed to toggle the blink state (.5 sec blinks?)
    if (millis() > last_blink + 500)
    {
        blink_state ^= 1; 
        last_blink = millis(); 
        seg_ref.Update(blink_state); 
    }

}


bool TimeSelectMode::process_input(Input in) 
{
    bool done_setting = false; 
    bool update_disp = false; 
    //check what the current mode is 
    if (current_set == SetType::MINS) 
    {
        if (in == Input::R_INC)
        {
            time_ref.add_time(0,1); 
            update_disp = true; 
        }
        else if  (in == Input::R_DEC)
        {
            time_ref.sub_time(0,1); 
            update_disp = true; 
        }
        else if (in == Input::R_PUSH_SHORT)
        {
            current_set = SetType::HOURS; 
        }
    }
    else // current_set == hours
    {
        if (in == Input::R_INC)
        {
            time_ref.add_time(1,0); 
            update_disp = true; 
        }
        else if  (in == Input::R_DEC)
        {
            time_ref.sub_time(1,0); 
            update_disp = true; 
        }
        else if (in == Input::R_PUSH_SHORT)
        {
            done_setting = true; 
            current_set = SetType::MINS;
            //no way to display am/pm so oh well
            rtc_ref.set_time(time_ref.get_hours(),time_ref.get_mins(),true);
            rtc_ref.refresh_time();   
        }
    }

    process_display(update_disp);
    return done_setting; 
}