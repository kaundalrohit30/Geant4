#include <iostream>
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#include "PhysicsList.hh"
//#include "DetectorConstruction.hh"
#include "DetectorConstruction_LYSO.hh"
#include "ActionInitialization.hh"


int main(int argc, char** argv){

    G4UIExecutive *ui;// = new G4UIExecutive(argc, argv);

    #ifdef G4MULTITHREAD
       G4MTRunManager *runManager = new G4MTRunManager;
    #else
        G4RunManager *runManager = new G4RunManager;
    #endif

    //Physics List
    runManager->SetUserInitialization(new PhysicsList());
    //runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new DetectorConstruction_LYSO());
    runManager->SetUserInitialization(new ActionInitialization());

    if(argc == 1){
        ui = new G4UIExecutive(argc, argv);
    }

    

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();


    //

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if(ui){
    UImanager->ApplyCommand("/control/execute vis.mac");

    //UImanager->ApplyCommand("/vis/open OGL");
    //UImanager->ApplyCommand("/vis/niewer/set/viewpointVector 1 1 1");
    //UImanager->ApplyCommand("/vis/drawVolume");
    //UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    //UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    //UImanager->ApplyCommand("/vis/scene/add/scale 10 cm");  
    //UImanager->ApplyCommand("/vis/scene/add/axes");
    //UImanager->ApplyCommand("/vis/scene/add/eventID");
    //UImanager->ApplyCommand("/vis/enable");
    //UImanager->ApplyCommand("/vis/viewer/rebuild");

    ui->SessionStart();
    }

    else{
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    runManager->Initialize();

    return 0;
}