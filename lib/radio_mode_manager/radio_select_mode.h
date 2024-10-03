#pragma once 
#include "mode.h"
#include "input.h"
#include "TimeDisplay.h"
#include "rtc_ds3231.h"
#include "DebugLog.h"
#include "Si4731_driver.h"



namespace mode_select
{

class RadioSelect : base_utilities::Mode
{   
    radio_drivers::SevenSegment& seg_ref;  
    radio_drivers::Si4731& rad_mod; 

    bool check_for_timeout(); 
    void change_station(bool inc); //true to toggle up and false to toggle down
    void show_current_station(); //should show the current select station
    void toggle_on_off(); 

    uint last_input = 0; 
    uint timeout_length = 2000;  //timeout until it just switches back to regular default time show mode

    //radio defaults
    uint current_station = 9190; //default radio stations for now
    uint min = 8500;  
    uint max = 11000; 
    bool currently_on = false;

    public: 
    RadioSelect(radio_drivers::SevenSegment& in_seg,  
    radio_drivers::Si4731& in_rad); 

    bool process_input(Input in) override; 

}; 

} //namespace mode_select 