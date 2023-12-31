#include "mode_def.h"
#include "update.h"
#include "Rotary_Encoder.h"
#include "time_select_mode.h"
#include "radio_select_mode.h"
#include "DebugLog.h"

namespace mode_select
{

//toggles between other modes and controls the update
class ModeManger : public base_utilities::UpdateBase
{   
    RadioModes current_mode = RadioModes::DEFAULT; 

    //owns the following devices 
    radio_drivers::RadioTime rad_time{12,12,true}; 
    radio_drivers::SevenSegment seven_seg; 
    radio_drivers::RTCDS3231 rtc; 
    radio_drivers::Si4731 rad_module; 
    RotaryEncoder ro_enc; 

    TimeSelectMode ts_mode;     
    RadioSelect rs_mode;


    void process_default(Input in); 


    public: 
    ModeManger(
        uint8_t disp_clk, uint8_t disp_data, //disp 
        TwoWire& in_wire, //rtc
        uint8_t rst_pin, uint8_t sen_pin, TwoWire& in_wire_2, // radio module
        uint8_t r_inc, uint8_t r_dec, uint8_t r_push
    );

    void init() override; 

    //grabs re outputs and 
    void update() override; 
    void fix_update() override; 
}; 

}; 