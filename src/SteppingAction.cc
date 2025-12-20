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

    G4double preStepEnergy = preStepPoint->GetKineticEnergy();
    G4double postStepEnergy = postStepPoint->GetKineticEnergy();
    edep = preStepEnergy - postStepEnergy;

    const G4VProcess *process = postStepPoint->GetProcessDefinedStep();
    //const G4VProcess *process = preStepPoint->GetProcessDefinedStep();
    //G4String currentStepProcess = (process) ? process->GetProcessName() : "Gun";
    
    G4String currentStepProcess = process->GetProcessName();
    //G4cout << currentStepProcess << G4endl;

    G4ThreeVector preStepPos = preStepPoint->GetPosition();
    G4ThreeVector postStepPos = postStepPoint->GetPosition();

    G4ThreeVector preStepPol = preStepPoint->GetPolarization();

    const G4VTouchable *touchable = preStepPoint->GetTouchable();
    //const G4VTouchable *touchable = postStepPoint->GetTouchable();
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
    G4double currentTrackParentID = currentTrack->GetParentID();
    G4double currentTrackID = currentTrack->GetTrackID();
    const G4ParticleDefinition *currentParticleDef = currentTrack->GetDefinition();
    G4String currentParticleName = currentParticleDef->GetParticleName();
    

    G4double currentParticleE = currentTrack->GetKineticEnergy();
    G4ThreeVector currentParticleMom = currentTrack->GetMomentumDirection();
    G4double currentParticleTheta = currentParticleMom.theta();

    G4ThreeVector preStepMom = preStepPoint->GetMomentumDirection();
    G4ThreeVector postStepMom = postStepPoint->GetMomentumDirection();
    simTheta = acos(preStepMom*postStepMom/(preStepMom.mag()*postStepMom.mag()))*(180/M_PI); //preStepMom.angle(postStepMom);


    G4Track *Track = step->GetTrack();
    const G4VProcess *PproductionProcess = Track->GetCreatorProcess();
    G4String PprocessName = (PproductionProcess) ? PproductionProcess->GetProcessName() : "Primary";

    ///////////////////Scattering angle///////////////


    /*if(copyNo < 0 and currentStepProcess == "compt" and currentTrackParentID == 0 and preStepEnergy == 0.511){
        recoTheta = acos(1-eMass*(1/postStepEnergy - 1/preStepEnergy))*(180/M_PI);  
        G4ThreeVector N1 = postStepMom.cross(preStepMom);
        G4ThreeVector N2 = preStepPol.cross(preStepMom);
        G4ThreeVector refDir = G4ThreeVector(0,0,1);

        edep = preStepEnergy - preStepEnergy/(1+preStepEnergy*(1-cos(recoTheta/(180/M_PI)))/eMass);

        //G4cout << "Theta:>  " << recoTheta << "   Edep1:>  " << edep << "  Edep2(pre-post):>" << preStepEnergy - postStepEnergy <<  G4endl;

        if(N1.cross(N2)*refDir < 0){
            recoEta = -acos((N1*N2)/(N1.mag()*N2.mag()))*(180/M_PI);
        }
        else recoEta = acos((N1*N2)/(N1.mag()*N2.mag()))*(180/M_PI);
        //G4RotationMatrix  rot;
        //rot.rotateZ(-preStepMom.phi());
        //rot.rotateY(-preStepMom.theta());
//
        //G4ThreeVector rot_ScatMom = rot*postStepMom;
        //recoEta = rot_ScatMom.phi()*(180/M_PI);
//
        //G4cout << "Before rotation:>  " << postStepMom << "   Rotation Matrix:>  " << rot <<  "   After rotaion:>  " << rot_ScatMom << G4endl;


        

        //fEventAction->Angle(recoTheta*(180/M_PI), simTheta*(180/M_PI), RecoEta*(180/M_PI));


        analysisManager->FillNtupleDColumn(0,0,recoTheta);
        analysisManager->FillNtupleDColumn(0,1,simTheta);
        analysisManager->FillNtupleDColumn(0,2,recoEta);
        //analysisManager->FillNtupleDColumn(0,3,edep);
        analysisManager->AddNtupleRow(0);
        
        //G4cout << "RecoTheta:>  " << recoTheta << G4endl;
    } */





    

    if(copyNo > 0 and currentStepProcess == "phot"){//} and (currentTrackID == 1 or currentTrackParentID == 1) ){
    
        
        const std::vector<const G4Track*> *primaryPhoton_Secondaries = step->GetSecondaryInCurrentStep();

        //G4cout << "TrackID:>  " << currentTrackID<< "  Secondaries:>  " << primaryPhoton_Secondaries->size() << "   ParentID:>  " << currentTrackParentID << G4endl; 

        if(primaryPhoton_Secondaries->size() > 1){
            int count = 0;
            for(int i = 0; i < primaryPhoton_Secondaries->size(); i++){
                const G4Track *secTrack = (*primaryPhoton_Secondaries)[i];
                const G4ParticleDefinition *particleDef = secTrack->GetDefinition();
                G4String particleName = particleDef->GetParticleName();
                const G4VProcess *productionProcess = secTrack->GetCreatorProcess();
                G4String processName = productionProcess->GetProcessName();

                if(particleName == "opticalphoton" and processName == "Scintillation"){
                    count++;
                }
                //G4cout << "eIon Particles:>  " << particleName << "   Productoion Process:>   " << processName << G4endl;
            }
            //optPhotonCount = primaryPhoton_Secondaries->size() - 1;
            fEventAction->optPhotCount(count);

                //G4cout << "eIon Particles:>  " << particleName << "   Productoion Process:>   " << processName << G4endl;
            }

        }

        //if(currentParticleName == "opticalphoton" and PprocessName == "Scintillation" and currentTrackParentID == 1){
        //    G4cout << "\vOOOOOOOOOOOOOoooooooooooooooooooo YES I am Present ooooooooooooOOOOOOOOOOOOOOOOOOOO\v" << G4endl;
        //}
    //}
    
    
    if(copyNo >0 and currentTrackID == 1  and currentTrackParentID == 0){
                
                fEventAction->addEdepTotal(edep);
                //G4cout << " Copy No:>  " << copyNo << " Particle:>  " << currentParticleName << "  Deposited Energy:>  " << edep  << G4endl;
    }
    
    
    if(copyNo >0 and currentTrackID == 1  and currentTrackParentID == 0 and  currentStepProcess == "compt"){  
                 //step->GetTotalEnergyDeposit();
                fEventAction->addEdepComp(edep);
                //G4cout << " Copy No:>  " << copyNo << " Particle:>  " << currentParticleName << "  Deposited Energy:>  " << edep  << G4endl;
                //G4cout << "Compton>>>>>    Edep:>  " << edep << " PreStepEnergy:>  " << preStepEnergy << "   PostStepEnergy:>  " << postStepEnergy  << G4endl;
    }

    else if(copyNo >0 and currentTrackID == 1  and currentTrackParentID == 0 and currentStepProcess == "phot"){ 
        binding_E = step->GetTotalEnergyDeposit();
        fEventAction->addEdepPhotoP(edep, binding_E);
        //G4cout << "Photopr>>>>>     Edep:>  " << edep << " PreStepEnergy:>  " << preStepEnergy << "   PostStepEnergy:>  " << postStepEnergy  << G4endl;
    }


    //const std::vector<const G4Track*> *secondaries = step->GetSecondaryInCurrentStep();


    const G4Track* track = step->GetTrack();
    const G4VProcess* creatorProc = track->GetCreatorProcess();
    G4String creatorName = (creatorProc) ? creatorProc->GetProcessName() : "Primary";

    //const std::vector<const G4Track*> *electron_Secondaries = step->GetSecondaryInCurrentStep();


    if(copyNo > 0 and currentParticleName == "e-" and creatorName == "compt"){//} and currentTrackParentID == 1){
        //G4cout << "electronTrackID:>    " << currentTrackID << G4endl;
        const std::vector<const G4Track*> *electron_Secondaries = step->GetSecondaryInCurrentStep();
        int count = 0;
        for(int i = 0; i < electron_Secondaries->size(); i++){
                const G4Track *secTrack = (*electron_Secondaries)[i];
                const G4ParticleDefinition *particleDef = secTrack->GetDefinition();
                G4String particleName = particleDef->GetParticleName();
                const G4VProcess *productionProcess = secTrack->GetCreatorProcess();
                G4String processName = productionProcess->GetProcessName();

                if(particleName == "opticalphoton" and processName == "Scintillation"){
                    count++;
                }
                //G4cout << "eIon Particles:>  " << particleName << "   Productoion Process:>   " << processName << G4endl;
            }

            fEventAction->addPhotonNumCompt(count);

        //G4cout << "Particle Name:>   " << currentParticleName << "   electronTrackID:>  " << currentTrackID << "   electron secondaries:>  " << electron_Secondaries->size() << "   Process:>  " << currentStepProcess << G4endl;
        //G4cout << "Process Name:>  " << currentStepProcess << "  Secondaries:>   " << electron_Secondaries->size() << G4endl;
        
    
    
    }


    else if(copyNo > 0 and currentParticleName == "e-" and creatorName == "phot"){//} and currentTrackParentID == 1){
        const std::vector<const G4Track*> *electron_Secondaries = step->GetSecondaryInCurrentStep();
        int count = 0;
        for(int i = 0; i < electron_Secondaries->size(); i++){
                const G4Track *secTrack = (*electron_Secondaries)[i];
                const G4ParticleDefinition *particleDef = secTrack->GetDefinition();
                G4String particleName = particleDef->GetParticleName();
                const G4VProcess *productionProcess = secTrack->GetCreatorProcess();
                G4String processName = productionProcess->GetProcessName();

                if(particleName == "opticalphoton" and processName == "Scintillation"){
                    count++;
                }

                
                //G4cout << "eIon Particles:>  " << particleName << "   Productoion Process:>   " << processName << G4endl;
            }

            fEventAction->addPhotonNumPhotoP(count); 
    
    }


    if(copyNo > 0 and currentParticleName == "e-"){//} and currentTrackParentID == 1){
        const std::vector<const G4Track*> *electron_Secondaries = step->GetSecondaryInCurrentStep();
        int count = 0;
        for(int i = 0; i < electron_Secondaries->size(); i++){
                const G4Track *secTrack = (*electron_Secondaries)[i];
                const G4ParticleDefinition *particleDef = secTrack->GetDefinition();
                G4String particleName = particleDef->GetParticleName();
                const G4VProcess *productionProcess = secTrack->GetCreatorProcess();
                G4String processName = productionProcess->GetProcessName();

                if(particleName == "opticalphoton" and processName == "Scintillation"){
                    count++;
                }

                
                //G4cout << "eIon Particles:>  " << particleName << "   Productoion Process:>   " << processName << G4endl;
            }

            fEventAction->addPhotonNumTotal(count);
    
    }

    if(copyNo > 0 and currentParticleName == "e-" and creatorName == "phot" and currentTrackParentID != 1 and currentTrackParentID != 2){
        const std::vector<const G4Track*> *electron_Secondaries = step->GetSecondaryInCurrentStep();
        int count = 0;
        for(int i = 0; i < electron_Secondaries->size(); i++){
                const G4Track *secTrack = (*electron_Secondaries)[i];
                const G4ParticleDefinition *particleDef = secTrack->GetDefinition();
                G4String particleName = particleDef->GetParticleName();
                const G4VProcess *productionProcess = secTrack->GetCreatorProcess();
                G4String processName = productionProcess->GetProcessName();

                if(particleName == "opticalphoton" and processName == "Scintillation"){
                    count++;
                }

                
                //G4cout << "eIon Particles:>  " << particleName << "   Productoion Process:>   " << processName << G4endl;
            }

            fEventAction->addPhotonNumFluorescence(count);
    }




    ////for azimuthal angle calculation///////////

    G4VPhysicalVolume *physScintillator = touchable->GetVolume();
    G4ThreeVector posDet = physScintillator->GetTranslation();
    
    if(copyNo > 0 and currentTrackID == 1 and currentTrackParentID == 0 and currentStepProcess == "compt"){
        compt_Count1 = 1;
        fEventAction->ComptCount1(compt_Count1, posDet, simTheta);//posDet[0], posDet[1], posDet[2], simTheta);
        //G4cout << posDet << G4endl;
        
    }

    else if(copyNo > 0 and currentTrackID == 1  and currentTrackParentID == 0 and currentStepProcess == "phot"){
        phot_Count1 = 1;
        fEventAction->PhotCount1(phot_Count1, posDet);//posDet[0], posDet[1], posDet[2]);
        
    }

    if(copyNo < 0 and currentTrackID == 2  and currentTrackParentID == 0 and currentStepProcess == "compt"){
        compt_Count2 = 1;
        fEventAction->ComptCount2(compt_Count2, posDet, simTheta);//posDet[0], posDet[1], posDet[2], simTheta);
        
    }

    else if(copyNo < 0 and currentTrackID == 2  and currentTrackParentID == 0 and currentStepProcess == "phot"){
        phot_Count2 = 1;
        fEventAction->PhotCount2(phot_Count2, posDet);//posDet[0], posDet[1], posDet[2]);
        
    }  

    

    
}










/*G4int count = 0;
    //G4cout << optPhotonId << "     " << currentTrackID << G4endl;
    if(copyNo > 0 and currentParticleName == "opticalphoton" and PprocessName == "Scintillation" and optPhotonId != currentTrackID and currentTrackParentID != 2){ //" 
        
        optPhotonId = currentTrackID;
        count++;
        fEventAction->addAlloptPhoton(count);
        //G4cout << "currentTrackID:>   " << optPhotonId << "   ParentID:>   " << currentTrackParentID << G4endl;
        
        //G4cout << "TrackID:>  " << optPhotonId << " Creator Process:>  " << PprocessName << "  Count:>  " << count << G4endl;
    }*/




//G4cout << electronTrackID << G4endl;
    //if(currentTrackID == electronTrackID){
    //    const std::vector<const G4Track*> *electron_Secondaries = step->GetSecondaryInCurrentStep();
    //    //G4cout << "Particle Name:>   " << particleName << "   electronTrackID:>  " << electronTrackID << "   electron secondaries:>  " << electron_Secondaries->size() << G4endl;
    //}






    // << "Process Name:>  " << currentStepProcess << ",  Secondaries:>  " << secondaries->size() << ",  Energydep:>  " << edep << G4endl;
    
    //G4cout << theta << "  secondaries:>" << secondaries->size() << G4endl;
    //G4cout << copyNo << "   Parent Particle:> " << parentParticleName <<  "  Parent KE:> " << parentParticleE << "  no. of secondaries:> " << secondaries->size() << G4endl;
    //G4cout << "Pre Step Mom:> " << preStepMom << "   post Step Mom:> " << postStepMom << "  current particle mom:> " << currentParticleMom << "  secondaries:>" << secondaries->size() << G4endl;

    /*if(secondaries->size() > 0){
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
                analysisManager->FillNtupleDColumn(1,1, theta*(180/M_PI));
                analysisManager->AddNtupleRow(1);

                //G4cout << copyNo << "   Parent particle:> " << parentParticleName << "  ParentKE:> " << parentParticleE << "  eEnergy:> " << particleEnergy << G4endl; 
                //G4cout << copyNo << "    e Energy:> " << particleEnergy << "  sctGamma Energy:> " << parentParticleE-particleEnergy << "  Gamma Angle:> " << RecoTheta1 <<   G4endl;
            }
            if(processName == "compt" and copyNo < 0){// and parentParticleE >= particleEnergy){
                //fEventAction->E2(particleEnergy);
                RecoTheta2 = acos(eMass*(1/currentParticleE+particleEnergy - 1/(currentParticleE)) - 1)*(180/M_PI);
                analysisManager->FillNtupleDColumn(2,0, RecoTheta2);
                analysisManager->FillNtupleDColumn(2,1, theta*(180/M_PI));
                analysisManager->AddNtupleRow(2);

                //G4cout << copyNo << "   Parent particle:> " << parentParticleName << "  ParentKE:> " << parentParticleE << "  eEnergy:> " << particleEnergy << G4endl;
                //G4cout << copyNo << "    e Energy:> " << particleEnergy << "  sctGamma Energy:> " << parentParticleE-particleEnergy << "  Gamma Angle:> " << RecoTheta2 <<   G4endl;

            }       
            
        }
    }*/