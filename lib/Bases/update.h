#pragma once
#include <vector> 
#include "Arduino.h"
#include "DebugLog.h"

/* 
Basic interface for controlling general updates 
has two modes periodic and frequent 

*/
namespace base_utilities 
{

class UpdateBase 
{
    private: 
    inline static unsigned int fix_freq = 100; //for fix freq updates 
    inline static std::vector<UpdateBase*> updates; 
    inline static unsigned int last_update = 0; 

    public: 

    UpdateBase(); 

    static void set_fixed(unsigned int freq) { fix_freq = freq; }
    static void run_updates(); 
    static void run_fixed_updates(); 

    virtual void update(); 
    virtual void fix_update(); 

}; 

} //ns base_utilites 