#ifndef PRIMARYGENERATOR_HH
#define PRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
//#include "EventAction.hh"
#include "Randomize.hh"
#include <cmath>



class PrimaryGenerator : public G4VUserPrimaryGeneratorAction{

        public:
            PrimaryGenerator();
            //PrimaryGenerator(EventAction* eventAction);
            ~PrimaryGenerator();

            virtual void GeneratePrimaries(G4Event *);

        private:
            G4ParticleGun *fParticleGun1, *fParticleGun2;
            //EventAction* fEventAction;
            
};

#endif