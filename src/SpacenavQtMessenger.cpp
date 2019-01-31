#include "SpacenavQtMessenger.hh"
#include "G4Spacenav.hh"
#include <QtGlobal>


SpacenavThreadWorker::SpacenavThreadWorker(G4Spacenav& g4spnav)
: g4spnav_(g4spnav)
{
    
}


void SpacenavThreadWorker::run()
{
    while(!stopthread_)
    {
        auto ev = g4spnav_.WaitSpacenavEvent();
        emit SendMessage(std::get<0>(ev),std::get<1>(ev), std::get<2>(ev));
    }
    
}

void SpacenavThreadWorker::stop()
{
    stopthread_ = true;
}





SpacenavQtMessenger::SpacenavQtMessenger(G4Spacenav& g4spnav)
: g4spnav_(g4spnav)
{    
}

SpacenavQtMessenger::~SpacenavQtMessenger()
{
    emit stopWorker();
    worker_->wait();
}


void SpacenavQtMessenger::RunThread()
{
    worker_ = new SpacenavThreadWorker(g4spnav_);
    
#if QT_VERSION > 0x050000
    connect(worker_, &SpacenavThreadWorker::SendMessage, 
            this, &SpacenavQtMessenger::RotateTranslate);
    connect(this, &SpacenavQtMessenger::stopWorker,
            worker_, &SpacenavThreadWorker::stop);
#else
    connect(worker_, SIGNAL(SendMessage(const G4Vector3D& rot,G4double zoom, 
                                     const std::pair<G4double, G4double>& pan)),
            this, SLOT(RotateTranslate(const G4Vector3D& rot, G4double zoom, 
                                          const std::pair<G4double, G4double>& pan)));
    
    connect(this, SIGNAL(stopWorker), worker_, SLOT(stop));
    
#endif
    
    worker_->start();
    
}



void SpacenavQtMessenger::RotateTranslate(const G4Vector3D& rot, G4double zoom, const std::pair<G4double, G4double>& pan)
{
    g4spnav_.RotateTranslate(rot,zoom,pan);
}
