#include "radio_select_mode.h"


using namespace mode_select; 


RadioSelect::RadioSelect(radio_drivers::SevenSegment& in_seg, 
    radio_drivers::Si4731& in_rad) : 
seg_ref{in_seg}, 
rad_mod{in_rad}
{}

bool RadioSelect::check_for_timeout()
{
    if (millis() > last_input + timeout_length)
    {
        return true; //timeout reached
    }
    return false; 
}

void RadioSelect::change_station(bool inc)
{
    LOG_INFO("changing the radio station : ",inc); 
    rad_mod.tune_frequency(inc); 
    current_station = rad_mod.get_radio_frequency().freq;
    show_current_station(); 
}

void RadioSelect::show_current_station()
{
    seg_ref.display_station(current_station); 
}

bool RadioSelect::process_input(Input in)
{
    //no op option 
    if (in == Input::R_NOP)
    {
        //check for timeout 
        if (check_for_timeout()) 
        {
            return true; //okay to exit 
        }
    }
    else 
    {
        last_input = millis(); 
    }


    if (in == Input::R_PUSH_SHORT)
    {
        currently_on ^= 1; //alternate currently on 
        rad_mod.set_audio_enabled(currently_on); 
        return true; 
    }
    else if (in == Input::R_INC && currently_on)
    {
        change_station(true); //change up
    }
    else if (in == Input::R_DEC && currently_on)
    {
        change_station(false); //change down 
    }
    return false; 
    
}