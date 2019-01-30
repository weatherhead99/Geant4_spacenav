#include "SpacenavMessenger.hh"
#include "G4X11Utils.hh"
#include <G4UImanager.hh>
#include "libspnavpp.hh"
#include "G4Spacenav.hh"

SpacenavMessenger::SpacenavMessenger() 
: init_{"/spacenav/init",this}
{  
}

SpacenavMessenger::~SpacenavMessenger()
{
    if(spacenav_)
        delete spacenav_;
}



void SpacenavMessenger::SetNewValue(G4UIcommand* command, G4String)
{
    if(*command == init_)
    {
      Initialise();  
    };
    
}

void SpacenavMessenger::Initialise()
{
    if(inited_)
    {
        G4cout << "spacenavigator support already initialised, doing nothing." << G4endl;
        return;
    }
    
    G4cout << "initializing spacenavigator support..." << G4endl;
    auto uiman = G4UImanager::GetUIpointer();
    try{
        spacenav_ = new G4Spacenav(uiman);
        inited_ = true;
    }
    catch(std::runtime_error& err)
    {
        G4cout << "couldn't connect to spacenavigator daemon!" << G4endl;
    }
    
}

