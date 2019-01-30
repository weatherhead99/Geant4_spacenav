#include "SpacenavMessenger.hh"
#include <G4VisManager.hh>
#include "G4X11Utils.hh"
#include <G4UImanager.hh>
#include "libspnavpp.hh"
#include "G4Spacenav.hh"

SpacenavMessenger::SpacenavMessenger() 
: init_{"/spacenav/init",this},
viewer_{"/spacenav/viewer", this}
{
    init_.SetGuidance("initialize spacenavigator support");
    
    viewer_.SetParameterName("scene_name",true);
    viewer_.SetDefaultValue("current");
    viewer_.SetGuidance("attach spacenavigator to a viewer");
    
    visman_ = G4VisManager::GetInstance();
    
}

SpacenavMessenger::~SpacenavMessenger()
{
    if(spacenav_)
        delete spacenav_;
}



void SpacenavMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if(*command == init_)
    {
      Initialise();  
    }
    else if(*command == viewer_)
    {
        if(!inited_)
        {
            G4cerr << "need to initialize first! Call /spacenav/init" << G4endl;
        }
        
        if(newValue == "current")
        {
            G4cout << "using current viewer..." << G4endl;
            spacenav_->SetViewer(visman_->GetCurrentViewer());
        }
        
        
    }
    
    
    
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

