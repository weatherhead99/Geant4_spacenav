#pragma once

#include <X11/Xlib.h>
#include <array>

class spnav_event;

class spnav
{
public:
    spnav(Display* disp, Window win);
    ~spnav();
    bool wait();
    
    std::array<double,6> GetMoveEventValues(const spnav_event& sev);
private:
    
    int fd_;
};
