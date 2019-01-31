#pragma once
#include <QObject>
#include <memory>
#include <G4Vector3D.hh>
#include <QMetaType>
#include <QThread>

class G4Spacenav;

Q_DECLARE_METATYPE(G4Vector3D)

class SpacenavThreadWorker : public QThread
{
    
    
};



class SpacenavQtMessenger : public QObject
{
    Q_OBJECT
 
public:
    ~SpacenavQtMessenger();
    void RunThread();
 
signals:
    void SendMessage(const G4Vector3D& rot, 
                     G4double zoom, const std::pair<G4double, G4double>& pan);
 
public slots:
    void RotateTranslate(const G4Vector3D& rot, 
                         G4double zoom, const std::pair<G4double, G4double>& pan);
    
    
private:
    SpacenavQtMessenger(G4Spacenav& g4spnav);
    G4Spacenav& g4spnav_;
    QThread workerthread_;
    
    
};
