#include "radio_mode_manager.h"

using namespace mode_select; 

ModeManger::ModeManger(uint8_t disp_clk,
        uint8_t disp_data, 
        TwoWire& in_wire,
        uint8_t rst_pin, uint8_t sen_pin, TwoWire& in_wire_2, 
        uint8_t r_inc, uint8_t r_dec, uint8_t r_push) : 
seven_seg{disp_clk, disp_data,rad_time}, 
rtc{in_wire, rad_time}, 
rad_module{rst_pin,sen_pin,in_wire_2},
ro_enc{r_inc, r_dec, r_push},
ts_mode{seven_seg, rtc,rad_time}, 
rs_mode{seven_seg, rad_module}
{}

void ModeManger::init() 
{
    ro_enc.init(); 
    LOG_INFO("running rtc init"); 
    rtc.init(); 
    rtc.refresh_time();
    seven_seg.setBrightness(0); 
    seven_seg.Update(); //update the time from the rtc
    rad_module.init(); 
}

void ModeManger::update() 
{
    //check on the input from the encoder 
    auto input = ro_enc.pull_cache(); 

    if (input != Input::R_NOP) 
    {
        LOG_INFO("input entered : ", static_cast<int>(input)); 
    }

    switch(current_mode)
    {
        case RadioModes::DEFAULT: 
            process_default(input); 
            break; 
        case RadioModes::SET_TIME: 
            if (ts_mode.process_input(input)) 
            {
                current_mode = RadioModes::DEFAULT; //ts_mode set back to default
            }
            break; 
        case RadioModes::SET_STATION: 
            if (rs_mode.process_input(input))
            {
                current_mode = RadioModes::DEFAULT; 
            }
        default: 
            //unimplemented for now 
            break; 

    } 
}

//mainly used to update the time when in default mode
void ModeManger::fix_update()
{
    //check that the mode is default 
    if (current_mode == RadioModes::DEFAULT)
    {
        //update the time from the rtc 
        rtc.refresh_time(); 
        seven_seg.Update(); 
    }
}

void ModeManger::process_default(Input in)
{
    if (in == Input::R_PUSH_LONG)
    {
        LOG_INFO("setting to set time mode"); 
        //set to ts select mode 
        current_mode = RadioModes::SET_TIME; 
    }
    else if (in != Input::R_NOP)
    {
        LOG_INFO("switching to radio select mode"); 
        current_mode = RadioModes::SET_STATION; 
        //run through the first command as well 
        if (rs_mode.process_input(in)) 
        {
            //return back to normal mode (case for turing radio off)
            current_mode == RadioModes::DEFAULT;
        }
    }
}