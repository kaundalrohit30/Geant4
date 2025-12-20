#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "RunAction.hh"
//#include "DetectorConstruction_LYSO.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"




class SteppingAction : public G4UserSteppingAction{

    public:
        SteppingAction(EventAction* eventAction);
        ~SteppingAction();

        virtual void UserSteppingAction(const G4Step*);

        //G4double edep;
    private:
        EventAction *fEventAction;

        G4double edep, binding_E, optPhotonCount, recoTheta, simTheta, recoEta;
        G4int compt_Count1, phot_Count1, compt_Count2, phot_Count2;
         
        
};

#endif