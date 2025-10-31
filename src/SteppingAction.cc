#include "SteppingAction.hh"

SteppingAction::SteppingAction(EventAction *eventAction){
    fEventAction = eventAction;
}

SteppingAction::~SteppingAction(){

}

void SteppingAction::UserSteppingAction(const G4Step *step){

    //G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    //const DetectorConstruction *detectorConstruction = static_cast<const DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    //G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();

    //if(volume != fScoringVolume)
    //    return;


    G4StepPoint *preStepPoint = step->GetPreStepPoint();
    G4StepPoint *postStepPoint = step->GetPostStepPoint();

    G4ThreeVector preStepPos = preStepPoint->GetPosition();
    G4ThreeVector postStepPos = postStepPoint->GetPosition();

    const G4VTouchable *touchable = step->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();
    //G4cout << "Copy Number" << copyNo << G4endl;
    //G4VPhysicalVolume *physDet = touchable->GetVolume();
    //G4ThreeVector posDet = physDet->GetTranslation();

    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    /*if(copyNo > 0){
        G4double edep1 = step->GetTotalEnergyDeposit();
        //G4cout << "Each Step Energy: " << edep << ", Pixel position: " << posDet << ", Hit position: " << postStepPos << G4endl;
        fEventAction->AddEdep1(edep1);
    }

    if(copyNo < 0){
        G4double edep2 = step->GetTotalEnergyDeposit();
        //G4cout << "Each Step Energy: " << edep << ", Pixel position: " << posDet << ", Hit position: " << postStepPos << G4endl;
        fEventAction->AddEdep2(edep2);
    }*/

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    //G4double inE = 0.511;
    G4double eMass = 0.511;

    G4Track *currentTrack = step->GetTrack();
    const G4ParticleDefinition *currentParticleDef = currentTrack->GetDefinition();
    G4String currentParticleName = currentParticleDef->GetParticleName();
    G4double currentParticleE = currentTrack->GetKineticEnergy();
    G4ThreeVector currentParticleMom = currentTrack->GetMomentumDirection();
    G4double currentParticleTheta = currentParticleMom.theta();

    const std::vector<const G4Track*> *secondaries = step->GetSecondaryInCurrentStep();
    //G4cout << copyNo << "   Parent Particle:> " << parentParticleName <<  "  Parent KE:> " << parentParticleE << "  no. of secondaries:> " << secondaries->size() << G4endl;


    if(secondaries->size() > 0){
        //G4cout << "/n ooooOOOOoooo   Secondaries created in this step oooooOOOOOOooooo" << G4endl;
        
        //G4Track *parentTrack = step->GetTrack();
        //G4double parentParticleE = parentTrack->GetKineticEnergy();

        for(int i = 0; i < secondaries->size(); i++){
            const G4Track *secTrack = (*secondaries)[i];
            const G4ParticleDefinition *particleDef = secTrack->GetDefinition();
            G4String particleName = particleDef->GetParticleName();
            G4double particleEnergy = secTrack->GetKineticEnergy();
            G4ThreeVector mom = secTrack->GetMomentumDirection();
            G4int trackID = secTrack->GetTrackID();
            G4int parentID = secTrack->GetParentID();
            G4double theta = mom.theta();
            
            const G4VProcess *productionProcess = secTrack->GetCreatorProcess();
            G4String processName = productionProcess->GetProcessName();

            //if(processName == "compt")
            //    G4cout << "secE:> " << particleEnergy << G4endl;
            
                //G4cout << i << "  Particle: " << particleName << "  Process: " << processName << "  ParentID: " << parentID << "  K Energy: " << particleEnergy << "  Angle: " << theta << G4endl; 
            
            if(processName == "compt" and copyNo > 0){// and parentParticleE >= particleEnergy){
                //fEventAction->E1(particleEnergy);
                RecoTheta1 = acos(eMass*(1/currentParticleE+particleEnergy - 1/(currentParticleE)) - 1)*(180/M_PI);
                analysisManager->FillNtupleDColumn(1,0, RecoTheta1);
                analysisManager->FillNtupleDColumn(1,1, currentParticleTheta*(180/M_PI));
                analysisManager->AddNtupleRow(1);

                //G4cout << copyNo << "   Parent particle:> " << parentParticleName << "  ParentKE:> " << parentParticleE << "  eEnergy:> " << particleEnergy << G4endl; 
                //G4cout << copyNo << "    e Energy:> " << particleEnergy << "  sctGamma Energy:> " << parentParticleE-particleEnergy << "  Gamma Angle:> " << RecoTheta1 <<   G4endl;
            }
            if(processName == "compt" and copyNo < 0){// and parentParticleE >= particleEnergy){
                //fEventAction->E2(particleEnergy);
                RecoTheta2 = acos(eMass*(1/currentParticleE+particleEnergy - 1/(currentParticleE)) - 1)*(180/M_PI);
                analysisManager->FillNtupleDColumn(2,0, RecoTheta2);
                analysisManager->FillNtupleDColumn(2,1, currentParticleTheta*(180/M_PI));
                analysisManager->AddNtupleRow(2);

                //G4cout << copyNo << "   Parent particle:> " << parentParticleName << "  ParentKE:> " << parentParticleE << "  eEnergy:> " << particleEnergy << G4endl;
                //G4cout << copyNo << "    e Energy:> " << particleEnergy << "  sctGamma Energy:> " << parentParticleE-particleEnergy << "  Gamma Angle:> " << RecoTheta2 <<   G4endl;

            }
            
        }
    }
}