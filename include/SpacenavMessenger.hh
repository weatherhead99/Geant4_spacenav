#pragma once
#include <G4UImessenger.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcmdWithAString.hh>

class G4Spacenav;
class G4VisManager;

class SpacenavMessenger : public G4UImessenger
{
public:
    SpacenavMessenger();
    ~SpacenavMessenger();
    void SetNewValue(G4UIcommand * command, G4String newValue) override;
    
private: 
    void Initialise();
    
    
    G4UIdirectory dir_{"/spacenav/"};
    G4UIcmdWithoutParameter init_;
    G4UIcmdWithAString viewer_;
    G4Spacenav* spacenav_ = nullptr;
    bool inited_ = false;
    G4VisManager* visman_ = nullptr;
    
};
