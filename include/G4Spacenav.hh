#pragma once

class G4UImanager;
class spnav;
class G4VViewer;

class G4Spacenav
{
public:
    G4Spacenav(G4UImanager* uiman);
    ~G4Spacenav();
    void SetViewer(G4VViewer* viewer);
    
    void SetSensitivity(double val);
    double GetSensitivity() const;
    
private:
    spnav* nav_ = nullptr;
    G4VViewer* viewer_ = nullptr;
    double sens_ = 1.0;
};
