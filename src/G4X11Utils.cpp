#include <G4UIQt.hh>
#include "G4X11Utils.hh"
#include <G4UImanager.hh>
#include <G4UIbatch.hh>
#include <QMainWindow>
#include <QX11Info>

std::tuple<Display*, Window> GetX11Info(G4UImanager* uiman)
{
  
    auto session = uiman->GetSession();
    
    while(auto batch = dynamic_cast<G4UIbatch*>(session))
    {
        session = batch->GetPreviousSession();
    }
    
    G4UIQt* qtsesh;
    if( (qtsesh = dynamic_cast<G4UIQt*>(session)) )
    {
      return GetX11Info(qtsesh);  
    };
    
    throw std::logic_error("unknown or incompatible session type!");
    
}


std::tuple<Display *, Window> GetX11Info(G4UIQt* ui)
{
    auto* mainwindow = ui->GetMainWindow();
    auto x11info = mainwindow->x11Info(); 
    return std::make_tuple(x11info.display(), mainwindow->winId());
}
