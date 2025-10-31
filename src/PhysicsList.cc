#include "PhysicsList.hh"
#include "G4EmLivermorePolarizedPhysics.hh"
#include "G4EmStandardPhysics.hh"
//#include "G4OpticalPhysics.hh"
#include "G4EmParameters.hh"

PhysicsList::PhysicsList() {

    
    
    //RegisterPhysics(new G4EmLivermorePolarizedPhysics());
    RegisterPhysics(new G4EmStandardPhysics());
    
    //RegisterPhysics(new G4OpticalPhysics());

    
    //G4EmParameters *emParams = G4EmParameters::Instance();
    //emParams->SetPixe(true);           // Enable PIXE (Particle-Induced X-ray Emission)
    //emParams->SetAuger(true);          // Enable Auger electron emission
    //emParams->SetAugerCascade(true);   // Enable Auger cascade for realistic de-excitation
    //emParams->SetVerbose(1);           // Optional: print configuration summary

    //G4cout << ">>> Using G4EmLivermorePolarizedPhysics with PIXE, Auger, and AugerCascade enabled <<<" << G4endl;
}

PhysicsList::~PhysicsList() {}













/*#include "PhysicsList.hh"

PhysicsList::PhysicsList(){

        RegisterPhysics(new G4EmStandardPhysics());
        RegisterPhysics(new G4OpticalPhysics());
}

PhysicsList::~PhysicsList(){

}*/