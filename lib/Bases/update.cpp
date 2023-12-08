#include "update.h"

using namespace base_utilities; 

void UpdateBase::update() {}
void UpdateBase::fix_update() {}


UpdateBase::UpdateBase() {
        updates.push_back(this); 
}


void UpdateBase::run_updates() 
{
    for (auto u : updates) 
    {
        u->update(); 
    }
} 

void UpdateBase::run_fixed_updates()
{
    if (millis() > fix_freq + last_update) 
    {
        last_update = millis(); 
        for (auto u : updates) 
        {
            u->fix_update(); 
        }
    }
}
