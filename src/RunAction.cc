#include "RunAction.hh"

RunAction::RunAction(){
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->CreateNtuple("Events", "Events");
    analysisManager->CreateNtupleIColumn("Event");
    analysisManager->CreateNtupleDColumn("Energy_Deposited_Compton");
    analysisManager->CreateNtupleDColumn("Energy_Deposited_Photoelectric");
    analysisManager->CreateNtupleDColumn("Energy_Deposited_Total");
    analysisManager->CreateNtupleDColumn("BE_dist_photoE");
    analysisManager->FinishNtuple(0);

    analysisManager->CreateNtuple("Photon_Count", "Photon_Count");
    analysisManager->CreateNtupleIColumn("Scintillation_Photon_Count_Dist_Compton");
    analysisManager->CreateNtupleIColumn("Scintillation_Photon_Count_Dist_Photoproduction");
    analysisManager->CreateNtupleIColumn("Scintillation_Photon_Count_Dist_Total");
    analysisManager->CreateNtupleIColumn("Total_Photon_Count");
    analysisManager->CreateNtupleIColumn("Photoproduced_Photon_Count");

    analysisManager->FinishNtuple(1);

    /*analysisManager->CreateNtuple("Angle1", "Angle1");
    //analysisManager->CreateNtupleDColumn("fEdep");
    analysisManager->CreateNtupleDColumn("recoTheta_1");
    analysisManager->CreateNtupleDColumn("simTheta_1");
    analysisManager->FinishNtuple(1);

    analysisManager->CreateNtuple("Angle2", "Angle2");    
    analysisManager->CreateNtupleDColumn("recoTheta_2");
    analysisManager->CreateNtupleDColumn("simTheta_2");
    analysisManager->FinishNtuple(2);*/
}

RunAction::~RunAction(){


}

void RunAction::BeginOfRunAction(const G4Run *run){

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    analysisManager->OpenFile("output_" + strRunID.str() + ".root");
}

void RunAction::EndOfRunAction(const G4Run *run){

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();

    G4int runID = run->GetRunID();
    G4cout << "Finishing Run " << runID << G4endl;
}