#include "PrimaryGenerator.hh"
#include "Randomize.hh"
#include <cmath>

PrimaryGenerator::PrimaryGenerator(){

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
    G4double px2 = (G4UniformRand()-0.5);
    G4double py2 = (G4UniformRand()-0.5);
    G4double pz = 1;
    
    G4ThreeVector mom1(px1,py1,pz);
    G4ThreeVector mom2(px2,py2,pz);
    G4ThreeVector mom3(px1, py2, pz);
    G4ThreeVector pol1 = mom1.cross(mom2);
    pol1 = pol1.unit();
    G4ThreeVector pol2 = -mom1.cross(pol1);
    //G4ThreeVector pol2 = -mom1.cross(mom3);  
    pol2 = pol2.unit();

    //G4cout << "Pol1.Pol2:>  " << pol1*pol2 << G4endl;

    fParticleGun1->SetParticleMomentumDirection(mom1);
    fParticleGun1->SetParticlePolarization(pol1);
    fParticleGun1->SetParticleEnergy(511*keV);
    fParticleGun1->GeneratePrimaryVertex(anEvent);

    fParticleGun2->SetParticleMomentumDirection(-mom1);
    fParticleGun2->SetParticlePolarization(pol2);
    fParticleGun2->SetParticleEnergy(511*keV);
    fParticleGun2->GeneratePrimaryVertex(anEvent);


    //fParticleGun2->GeneratePrimaryVertex(anEvent);

}
