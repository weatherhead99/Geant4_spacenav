#include <G4UIQt.hh>

#include <iostream>


#include <G4VisExecutive.hh>
#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
#include <G4RunManager.hh>
#include <G4VUserDetectorConstruction.hh>
#include <G4Tubs.hh>
#include <G4SystemOfUnits.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <FTFP_BERT.hh>

#include "SpacenavMessenger.hh"

#include <type_traits>

#include <memory>

class StupidDetector : public G4VUserDetectorConstruction
{
    G4VPhysicalVolume* Construct()
    {
        auto solidWorld = new G4Tubs("world", 0, 100*mm, 100*mm, 0, 2*CLHEP::pi);
        auto logicWorld = new G4LogicalVolume(solidWorld, nullptr, "world");
        return new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicWorld, "world", nullptr, false,0,true);
    };
    
    
};


int main(int argc, char** argv)
{
    std::unique_ptr<G4UIExecutive> ui(new G4UIExecutive(argc,argv));
    std::unique_ptr<G4RunManager> runman(new G4RunManager);
    
    
    G4VisExecutive visman;
    visman.Initialize();
    
    runman->SetUserInitialization(new StupidDetector);
    runman->SetUserInitialization(new FTFP_BERT);
    
    new SpacenavMessenger;
    
    
    auto uiman = G4UImanager::GetUIpointer();

    uiman->ApplyCommand("/vis/open OGL");
    uiman->ApplyCommand("/run/initialize");
    uiman->ApplyCommand("/vis/drawVolume");
    uiman->ApplyCommand("/vis/scene/add/axes");
    
    
    auto vwr = visman.GetCurrentViewer();
    if(!vwr)
        std::cout << "no viewer!" << std::endl;
    
    
    
    
    ui->SessionStart();
    

}
