#include "RunAction.hh"

RunAction::RunAction(){
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    /*analysisManager->CreateNtuple("Events", "Events");
    analysisManager->CreateNtupleIColumn("Event");
    analysisManager->CreateNtupleDColumn("Energy_Deposited_Compton");
    analysisManager->CreateNtupleDColumn("Energy_Deposited_Photoelectric");
    analysisManager->CreateNtupleDColumn("Energy_Deposited_Total");
    analysisManager->CreateNtupleDColumn("BE_dist_photoE");
    analysisManager->FinishNtuple(0);

    analysisManager->CreateNtuple("Photon_Count", "Photon_Count");
    analysisManager->CreateNtupleIColumn("Scintillation_Photon_Count_Dist_Compton");
    analysisManager->CreateNtupleIColumn("Scintillation_Photon_Count_Dist_Photoelectric");
    analysisManager->CreateNtupleIColumn("Scintillation_Photon_Count_Dist_Total");
    analysisManager->CreateNtupleIColumn("Total_Photon_Count");
    analysisManager->CreateNtupleIColumn("Photon_Count_BE");
    analysisManager->CreateNtupleIColumn("Photon_Count_by_fluorescence_e");
    analysisManager->FinishNtuple(1); */

    /*analysisManager->CreateNtuple("Hit_Position_Module1", "Hit_Position_Module1");
    analysisManager->CreateNtupleDColumn("ComptX1");
    analysisManager->CreateNtupleDColumn("ComptY1");
    analysisManager->CreateNtupleDColumn("ComptZ1");
    analysisManager->CreateNtupleDColumn("PhotX1");
    analysisManager->CreateNtupleDColumn("PhotY1");
    analysisManager->CreateNtupleDColumn("PhotZ1");
    analysisManager->FinishNtuple(2);

    analysisManager->CreateNtuple("Hit_Position_Module2", "Hit_Position_Module2");
    analysisManager->CreateNtupleDColumn("ComptX2");
    analysisManager->CreateNtupleDColumn("ComptY2");
    analysisManager->CreateNtupleDColumn("ComptZ2");
    analysisManager->CreateNtupleDColumn("PhotX2");
    analysisManager->CreateNtupleDColumn("PhotY2");
    analysisManager->CreateNtupleDColumn("PhotZ2");
    analysisManager->FinishNtuple(3);*/

    /*analysisManager->CreateNtuple("Angle", "Angle");
    analysisManager->CreateNtupleDColumn("RecoTheta");
    analysisManager->CreateNtupleDColumn("SimTheta");
    analysisManager->CreateNtupleDColumn("RecoEta");
    //analysisManager->CreateNtupleDColumn("Edep");
    analysisManager->FinishNtuple(0);*/

    analysisManager->CreateNtuple("Detector1", "Detector1");
    //analysisManager->CreateNtupleDColumn("Edep1_compt");
    //analysisManager->CreateNtupleDColumn("Edep1_photoe");
    analysisManager->CreateNtupleDColumn("phi1");
    analysisManager->CreateNtupleDColumn("Theta1");
    analysisManager->CreateNtupleDColumn("PixelDistance1");
    analysisManager->FinishNtuple(0);

    analysisManager->CreateNtuple("Detector2", "Detector2");
    //analysisManager->CreateNtupleDColumn("Edep2_compt");
    //analysisManager->CreateNtupleDColumn("Edep2_photoe");
    analysisManager->CreateNtupleDColumn("phi2");
    analysisManager->CreateNtupleDColumn("Theta2");
    analysisManager->CreateNtupleDColumn("PixelDistance2");
    analysisManager->FinishNtuple(1);

    //analysisManager->CreateNtuple("Dphi", "Dphi");
    //analysisManager->CreateNtupleDColumn("dPhi_dist");
    //analysisManager->FinishNtuple(2);

    /*analysisManager->CreateNtuple("Hit", "Hit");
    analysisManager->CreateNtupleDColumn("hitX");
    analysisManager->CreateNtupleDColumn("hitY");
    analysisManager->CreateNtupleDColumn("hitZ");
    analysisManager->FinishNtuple(0);

    analysisManager->CreateNtuple("Momentum", "Momentum");
    analysisManager->CreateNtupleDColumn("Px");
    analysisManager->CreateNtupleDColumn("Py");
    analysisManager->CreateNtupleDColumn("Pz");
    //analysisManager->CreateNtupleDColumn("magP");
    analysisManager->FinishNtuple(1);

    analysisManager->CreateNtuple("Polarization", "Polarization");
    analysisManager->CreateNtupleDColumn("Pol1.mom1");
    analysisManager->CreateNtupleDColumn("Pol2.mom1");
    analysisManager->CreateNtupleDColumn("Pol1.Pol2");
    analysisManager->CreateNtupleDColumn("Pol1X");
    analysisManager->CreateNtupleDColumn("Pol1Y");
    analysisManager->CreateNtupleDColumn("Pol1Z");
    analysisManager->CreateNtupleDColumn("Pol2X");
    analysisManager->CreateNtupleDColumn("Pol2Y");
    analysisManager->CreateNtupleDColumn("Pol2Z");
    analysisManager->CreateNtupleDColumn("mom2.mom3");
    //analysisManager->CreateNtupleDColumn("magP");
    analysisManager->FinishNtuple(2);*/


    
}

RunAction::~RunAction(){


}

void RunAction::BeginOfRunAction(const G4Run *run){

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    analysisManager->OpenFile("output_UnCorrelated_BothGamma_selected_100M" + strRunID.str() + ".root");
}

void RunAction::EndOfRunAction(const G4Run *run){

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();

    G4int runID = run->GetRunID();
    G4cout << "Finishing Run " << runID << G4endl;
}