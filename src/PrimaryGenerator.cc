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

    G4double px = abs(G4UniformRand()-0.5);
    G4double py = abs(G4UniformRand()-0.5);
    G4double pz = 1;
    G4ThreeVector mom(px,py,pz); 

    fParticleGun1->SetParticleMomentumDirection(mom);
    fParticleGun1->SetParticleEnergy(511*keV);
    fParticleGun1->GeneratePrimaryVertex(anEvent);

    fParticleGun2->SetParticleMomentumDirection(-mom);
    fParticleGun2->SetParticleEnergy(511*keV);
    fParticleGun2->GeneratePrimaryVertex(anEvent);


    //fParticleGun2->GeneratePrimaryVertex(anEvent);

}