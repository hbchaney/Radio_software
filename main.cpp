#include <Arduino.h>
#include "TM1637Display.h"
#include "TimeDisplay.h"


void setup() 
{
    disp.setBrightness(1); 
}


void loop() 
{
    disp.Update(); 
    sleep_ms(200); 
    rad_time.add_time(0,2); 
}