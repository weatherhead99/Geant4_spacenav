#pragma once

class G4UImanager;
class spnav;


class G4Spacenav
{
public:
    G4Spacenav(G4UImanager* uiman);
    ~G4Spacenav();
    
private:
    spnav* nav_ = nullptr;
};
