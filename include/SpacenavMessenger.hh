#pragma once
#include <G4UImessenger.hh>
#include <G4UIcmdWithoutParameter.hh>

class G4Spacenav;

class SpacenavMessenger : public G4UImessenger
{
public:
    SpacenavMessenger();
    ~SpacenavMessenger();
    void SetNewValue(G4UIcommand * command, G4String) override;
    
private: 
    void Initialise();
    
    
    G4UIdirectory dir_{"/spacenav/"};
    G4UIcmdWithoutParameter init_;
    G4Spacenav* spacenav_ = nullptr;
    bool inited_ = false;
};
