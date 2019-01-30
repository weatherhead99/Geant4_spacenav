#pragma once
#include <G4Vector3D.hh>
#include <utility>
#include <thread>
#include <atomic>

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
    void RotateTranslate(const G4Vector3D& rot, G4double zoom, const std::pair<G4double,G4double>& pan);
    
    void RunThread();
    
    
private:
    spnav* nav_ = nullptr;
    G4VViewer* viewer_ = nullptr;
    double sens_ = 1.0;
    std::thread* runthread_ = nullptr;
    std::atomic<bool> stopthread_;
};
