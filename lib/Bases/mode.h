#pragma once 
#include "input.h"


namespace base_utilities 
{

class Mode 
{
    public: 

    //return true to switch out of mode 
    virtual bool process_input(Input in); 
}; 


} //base_utilities 