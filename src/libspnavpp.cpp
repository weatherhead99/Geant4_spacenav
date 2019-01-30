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
