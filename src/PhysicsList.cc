/*#include "PhysicsList.hh"


PhysicsList::PhysicsList() {

    
    
    RegisterPhysics(new G4EmLivermorePolarizedPhysics());
    //RegisterPhysics(new G4EmStandardPhysics());
    
    //RegisterPhysics(new G4OpticalPhysics());

    
    G4EmParameters *emParams = G4EmParameters::Instance();
    emParams->SetPixe(true);           
    emParams->SetAuger(true);          
    emParams->SetAugerCascade(true);   
    //emParams->SetVerbose(1);           

    //G4cout << ">>> Using G4EmLivermorePolarizedPhysics with PIXE, Auger, and AugerCascade enabled <<<" << G4endl;
}

PhysicsList::~PhysicsList() {}*/













#include "PhysicsList.hh"

PhysicsList::PhysicsList(){

        RegisterPhysics(new G4EmStandardPhysics()); //_Option4()
        RegisterPhysics(new G4OpticalPhysics());
}

PhysicsList::~PhysicsList(){

}