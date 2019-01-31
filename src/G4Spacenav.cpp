#include "G4Spacenav.hh"
#include "G4X11Utils.hh"
#include "libspnavpp.hh"
#include <utility>
#include <array>
#include <G4VViewer.hh>
#include <thread>
#include <iostream>
#include "SpacenavQtMessenger.hh"

using std::thread;

const double scaling = 1000;

std::tuple<G4Vector3D, G4double, std::pair<G4double,G4double>> ConvertMoveValues(const std::array<int,6>& in)
{ 
   G4double zoom = in[1]/scaling; 
   auto pan = std::make_pair<G4double,G4double>(in[0]/scaling, in[2]/scaling);
   
   G4Vector3D rot{in[3]/scaling, in[4]/scaling, in[5]/scaling};
   
   return {rot, zoom, pan};
}

G4Spacenav::G4Spacenav(G4UImanager* uiman)
{
    auto dispwin = GetX11Info(uiman);
    nav_ = new spnav(std::get<0>(dispwin), std::get<1>(dispwin));
    mess_ = new SpacenavQtMessenger(*this);
    
}


G4Spacenav::~G4Spacenav()
{
    if(nav_)
        delete nav_;
    
    if(mess_)
        delete mess_;
    
}

void G4Spacenav::SetViewer(G4VViewer* viewer)
{
    viewer_ = viewer;
    RunThread();
}

void G4Spacenav::SetSensitivity(double val)
{
    sens_ = val;
}

double G4Spacenav::GetSensitivity() const
{
    return sens_;
}

void G4Spacenav::RotateTranslate(const G4Vector3D& rot, G4double zoom, const std::pair<G4double, G4double>& pan)
{
    //NOTE: making a copy here, seems the only way
    auto viewparams = viewer_->GetViewParameters();
    std::cout << viewparams.GetViewpointDirection() << std::endl;
    viewparams.SetViewpointDirection(viewparams.GetViewpointDirection() + rot);
//     viewparams.IncrementPan(pan.first, pan.second);
//     viewparams.SetZoomFactor(viewparams.GetZoomFactor() + zoom);
    viewer_->SetViewParameters(viewparams);
    viewer_->DrawView();
}

std::tuple<G4Vector3D, G4double, std::pair<G4double, G4double> > G4Spacenav::WaitSpacenavEvent()
{
    auto vals = GetMoveEventValues(this->nav_->wait());
    return ConvertMoveValues(vals);
}


void G4Spacenav::RunThread()
{
    
    
}



