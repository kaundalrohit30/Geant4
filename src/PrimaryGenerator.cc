#include "PrimaryGenerator.hh"


PrimaryGenerator::PrimaryGenerator(){
//PrimaryGenerator::PrimaryGenerator(EventAction* eventAction): G4VUserPrimaryGeneratorAction(), fEventAction(eventAction){

        fParticleGun1 = new G4ParticleGun(1);
        fParticleGun2 = new G4ParticleGun(1);

        G4double x = 0*mm;
        G4double y = 0*mm;
        G4double z = 0*mm;

        G4ThreeVector pos(x,y,z);


        G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition *particle = particleTable->FindParticle("gamma");

        fParticleGun1->SetParticlePosition(pos); 
        //fParticleGun1->SetParticleMomentum(mom);            
        //fParticleGun1->SetParticleEnergy(511*keV);
        fParticleGun1->SetParticleDefinition(particle);

        fParticleGun2->SetParticlePosition(pos); 
        //fParticleGun2->SetParticleMomentum(-mom);            
        //fParticleGun2->SetParticleEnergy(511*keV);
        fParticleGun2->SetParticleDefinition(particle);
    

    
}

PrimaryGenerator::~PrimaryGenerator(){
    delete fParticleGun1;
    delete fParticleGun2;
}

void PrimaryGenerator::GeneratePrimaries(G4Event *anEvent){

    G4double px1 = (G4UniformRand()-0.5);
    G4double py1 = (G4UniformRand()-0.5);
    //G4double px2 = G4UniformRand();
    //G4double py2 = G4UniformRand();
    G4double pz = 1;
    
    G4ThreeVector mom1(px1,py1,pz);
    G4ThreeVector ref1(0, 0, 1);
    G4ThreeVector mom2(G4UniformRand(), G4UniformRand(), 0);
    G4ThreeVector mom3(G4UniformRand(), G4UniformRand(), 0);
    //G4ThreeVector pol1 = mom1.cross(ref1);
    //G4ThreeVector pol2 = -mom1.cross(pol1);
    G4ThreeVector pol1 = mom1.cross(mom2);
    G4ThreeVector pol2 = -mom1.cross(mom3);  
    //pol2 = pol2.unit();
    //pol1 = pol1.unit();

    //G4cout << "Pol1.Pol2:>  " << pol1*pol2 << G4endl;

    fParticleGun1->SetParticleMomentumDirection(mom1);
    fParticleGun1->SetParticlePolarization(pol1);
    fParticleGun1->SetParticleEnergy(511*keV);
    fParticleGun1->GeneratePrimaryVertex(anEvent);

    fParticleGun2->SetParticleMomentumDirection(-mom1);
    fParticleGun2->SetParticlePolarization(pol2);
    fParticleGun2->SetParticleEnergy(511*keV);
    fParticleGun2->GeneratePrimaryVertex(anEvent);

    //G4cout << pol1*pol2 << G4endl;
    //fParticleGun2->GeneratePrimaryVertex(anEvent);

    //fEventAction->checkOrthogonality(pol1*pol2);

    /*G4ThreeVector primaryMom = fParticleGun1->GetParticleMomentumDirection();
    //G4cout << primaryMom[0] << "  " << primaryMom[1] << "  " << primaryMom[2] << "  " << primaryMom.mag() << G4endl;
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(1, 0, primaryMom[0]);
    analysisManager->FillNtupleDColumn(1, 1, primaryMom[1]);
    analysisManager->FillNtupleDColumn(1, 2, primaryMom[2]);
    //analysisManager->FillNtupleDColumn(0, 3, primaryMom.mag());
    analysisManager->AddNtupleRow(1);

//if(pol1*pol2 == 0){
    analysisManager->FillNtupleDColumn(2, 0, pol1*mom1);
    analysisManager->FillNtupleDColumn(2, 1, pol2*(-mom1));
    analysisManager->FillNtupleDColumn(2, 2, pol1*pol2);
    analysisManager->FillNtupleDColumn(2, 3, pol1[0]);
    analysisManager->FillNtupleDColumn(2, 4, pol1[1]);
    analysisManager->FillNtupleDColumn(2, 5, pol1[2]);
    analysisManager->FillNtupleDColumn(2, 6, pol2[0]);
    analysisManager->FillNtupleDColumn(2, 7, pol2[1]);
    analysisManager->FillNtupleDColumn(2, 8, pol2[2]);
    analysisManager->FillNtupleDColumn(2, 9, mom2*mom3);
    //analysisManager->FillNtupleDColumn(0, 3, primaryMom.mag());
    analysisManager->AddNtupleRow(2);*/
    //}
}