#include "EventAction.hh"
#include <cmath>

EventAction::EventAction(RunAction*){
    fEdepComp = 0;
    fEdepPhotoP = 0;
    fEdepTotal = 0;
    photonNumTotal = 0;
    photonNumCompton = 0;
    photonNumPhotoP = 0;
    //totalOptPhoton = 0;
    OphotonCount_Primary = 0;
}

EventAction::~EventAction(){

}

void EventAction::BeginOfEventAction(const G4Event*){
    fEdepComp = 0;
    fEdepPhotoP = 0;
    fEdepTotal = 0;
    photonNumTotal = 0;
    photonNumCompton = 0;
    photonNumPhotoP = 0;
    //totalOptPhoton = 0;
    OphotonCount_Primary = 0;

    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    if(eventID%1000 == 0){
    G4cout << "**************************************************************************************************************************************************" << G4endl;
    G4cout << "\v==========oooOOOOOOOooooo  Event Number:>  " << eventID << "   oooOOOOOOOooooo==========\v"<< G4endl;
    G4cout << "**************************************************************************************************************************************************" << G4endl;
    }

}

void EventAction::EndOfEventAction(const G4Event*){

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    //G4double inE = 0.511;
    //G4double eMass = 0.511;

    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    analysisManager->FillNtupleIColumn(0,0,eventID);
    analysisManager->FillNtupleDColumn(0,1,fEdepComp);
    analysisManager->FillNtupleDColumn(0,2,fEdepPhotoP);
    analysisManager->FillNtupleDColumn(0,3,fEdepTotal);
    analysisManager->AddNtupleRow(0);

    analysisManager->FillNtupleIColumn(1,0,photonNumCompton);
    analysisManager->FillNtupleIColumn(1,1,photonNumPhotoP);
    analysisManager->FillNtupleIColumn(1,2,photonNumTotal);
    analysisManager->FillNtupleIColumn(1, 3, photonNumTotal+OphotonCount_Primary);//(1,3,totalOptPhoton);
    analysisManager->AddNtupleRow(1);

    //G4cout << "Compton Photons:>  " << photonNumCompton << "   Photoelectric Photons:>  " << photonNumPhotoP << "   Total:>  " << photonNumTotal << "  All Scint Photon:>  " <<  totalOptPhoton << G4endl;


    //if(fEdepTotal > 0.43)
    //    G4cout << "EdepC:>  " << fEdepComp << ",  EdepP:>  " << fEdepPhotoP << ",  EdepT:>  " << fEdepTotal << G4endl;

    
}