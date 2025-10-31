#include "EventAction.hh"
#include <cmath>

EventAction::EventAction(RunAction*){
    eEnergy1 = 0;
    eEnergy2 = 0;
}

EventAction::~EventAction(){

}

void EventAction::BeginOfEventAction(const G4Event*){
    eEnergy1 = 0;
    eEnergy2 = 0;
}

void EventAction::EndOfEventAction(const G4Event*){

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    //G4double inE = 0.511;
    //G4double eMass = 0.511;

    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    analysisManager->FillNtupleIColumn(0,0,eventID);
    analysisManager->AddNtupleRow(0);

    
    /*if(eEnergy1 != 0){
        RecoTheta1 = acos(eMass*(1/inE - 1/(inE-eEnergy1)) - 1);//*(180/M_PI);

        G4cout << "Energy gamma:> " << eEnergy1 << "  Theta:>" << RecoTheta1 << G4endl;
        
        //analysisManager->FillNtupleDColumn(0, 0, fEdep1);
        analysisManager->FillNtupleDColumn(1,0, RecoTheta1);
        analysisManager->AddNtupleRow(1);
    }

    if(eEnergy2 != 0){
        RecoTheta2 = acos(eMass*(1/inE - 1/(inE-eEnergy2)) - 1);//*(180/M_PI);

        G4cout << "Energy gamma:> " << eEnergy1 << "  Theta:>" << RecoTheta1 << G4endl;
        
        //analysisManager->FillNtupleDColumn(0, 0, fEdep2);
        analysisManager->FillNtupleDColumn(1,1, RecoTheta2);
        analysisManager->AddNtupleRow(1);
    }*/

    //analysisManager->AddNtupleRow(0);
    
}