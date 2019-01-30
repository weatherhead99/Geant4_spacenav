#include <stdexcept>
#include <iostream>
#include "libspnavpp.hh"


spnav::spnav(Display* disp, Window win)
{
    fd_ = spnav_x11_open(disp,win);
    if(fd_ == -1)
    {
        throw std::runtime_error("couldn't connect to spnav daemon!");
    }
        
}

spnav::~spnav()
{
    spnav_close();
}

spnav_event spnav::wait()
{
  spnav_event sev;
  spnav_wait_event(&sev);
  return sev;
  
}

std::array<int, 6> GetMoveEventValues(const spnav_event& sev)
{
    if(sev.type != SPNAV_EVENT_MOTION)
    {
        throw std::out_of_range("not a motion event!");
    }
    
    return std::array<int,6> {sev.motion.x, sev.motion.y, sev.motion.z,
        sev.motion.rx, sev.motion.ry, sev.motion.rz};
    
}
