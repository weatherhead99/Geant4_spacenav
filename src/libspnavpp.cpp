#include <stdexcept>
#include <iostream>

#include "libspnavpp.hh"
#include <spnav.h>



spnav::spnav(Display* disp, Window win)
{
    fd_ = spnav_x11_open(disp,win);
    if(fd_ == -1)
    {
        throw std::runtime_error("couldn't connect to spnav daemon!");
    }
        
};

spnav::~spnav()
{
    spnav_close();
}

bool spnav::wait()
{
  spnav_event sev;
  spnav_wait_event(&sev);
  
  std::cout << "got event!" << std::endl;
  
  return true;
  
};

std::array<double, 6> spnav::GetMoveEventValues(const spnav_event& sev)
{
    if(sev.type != SPNAV_EVENT_MOTION)
    {
        throw std::out_of_range("not a motion event!");
    }
    
    return std::array<double,6> {sev.motion.x, sev.motion.y, sev.motion.z,
        sev.motion.rx, sev.motion.ry, sev.motion.rz};
    
}
