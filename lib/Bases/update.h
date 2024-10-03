#pragma once
#include <vector> 
#include <list>
#include "Arduino.h"
#include "DebugLog.h"

/* 
Basic interface for controlling general updates 
has two modes periodic and frequent 

*/
namespace base_utilities 
{

//will segfault if something dies 
//everything in update base should last the whole program 
class UpdateBase 
{
    private: 
    inline static unsigned int fix_freq = 1000; //for fix freq updates 
    inline static std::list<UpdateBase*> updates; 
    inline static unsigned int last_update = 0; 

    public: 

    UpdateBase(); //add to the updates list
    ~UpdateBase(); //remove from the updates list 

    static void set_fixed(unsigned int freq) { fix_freq = freq; }
    static void run_inits(); 
    static void run_updates(); 
    static void run_fixed_updates(); 

    virtual void init(); //common init function
    virtual void update(); 
    virtual void fix_update(); 

}; 

} //ns base_utilites 