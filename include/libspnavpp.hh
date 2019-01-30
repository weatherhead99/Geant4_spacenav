#pragma once

#include <X11/Xlib.h>


class spnav
{
public:
    spnav(Display* disp, Window win);
    ~spnav();
    bool wait();
    
    
private:
    
    int fd_;
};
