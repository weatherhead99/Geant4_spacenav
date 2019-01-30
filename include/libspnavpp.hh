#pragma once

#include <X11/Xlib.h>
#include <array>
#include <spnav.h>

std::array<int,6> GetMoveEventValues(const spnav_event& sev);

class spnav
{
public:
    spnav(Display* disp, Window win);
    ~spnav();
    spnav_event wait();
    
private:
    
    int fd_;
};
