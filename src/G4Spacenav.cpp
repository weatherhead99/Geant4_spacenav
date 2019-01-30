#include "G4Spacenav.hh"
#include "G4X11Utils.hh"
#include "libspnavpp.hh"

G4Spacenav::G4Spacenav(G4UImanager* uiman)
{
    auto dispwin = GetX11Info(uiman);
    nav_ = new spnav(std::get<0>(dispwin), std::get<1>(dispwin));
    
};


G4Spacenav::~G4Spacenav()
{
    if(nav_)
        delete nav_;
    
}
