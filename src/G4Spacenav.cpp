#include "G4Spacenav.hh"
#include "G4X11Utils.hh"
#include "libspnavpp.hh"
#include <G4Vector3D.hh>





G4Spacenav::G4Spacenav(G4UImanager* uiman)
{
    auto dispwin = GetX11Info(uiman);
    nav_ = new spnav(std::get<0>(dispwin), std::get<1>(dispwin));
    
}


G4Spacenav::~G4Spacenav()
{
    if(nav_)
        delete nav_;
    
}

void G4Spacenav::SetViewer(G4VViewer* viewer)
{
    viewer_ = viewer;
}

void G4Spacenav::SetSensitivity(double val)
{
    sens_ = val;
}

double G4Spacenav::GetSensitivity() const
{
    return sens_;
}

