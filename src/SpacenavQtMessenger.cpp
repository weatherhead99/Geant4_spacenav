#include "SpacenavQtMessenger.hh"
#include "G4Spacenav.hh"
#include <QtGlobal>

SpacenavQtMessenger::SpacenavQtMessenger(G4Spacenav& g4spnav)
: g4spnav_(g4spnav)
{
#if QT_VERSION > 0x050000
    connect(this, &SpacenavQtMessenger::SendMessage, 
            this, &SpacenavQtMessenger::RotateTranslate);
#else
    connect(this, SIGNAL(SendMessage(const G4Vector3D& rot,G4double zoom, 
                                     const std::pair<G4double, G4double>& pan)),
            this, SLOT(RotateTranslate(const G4Vector3D& rot, G4double zoom, 
                                          const std::pair<G4double, G4double>& pan)));
#endif

    
}

SpacenavQtMessenger::~SpacenavQtMessenger()
{
    workerthread_.quit();
}


void SpacenavQtMessenger::RunThread()
{
    
    
    
}



void SpacenavQtMessenger::RotateTranslate(const G4Vector3D& rot, G4double zoom, const std::pair<G4double, G4double>& pan)
{
    g4spnav_.RotateTranslate(rot,zoom,pan);
}
