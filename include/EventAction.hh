#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "RunAction.hh"
#include "G4RunManager.hh"


#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

class EventAction : public G4UserEventAction{
    public:
        EventAction(RunAction*);
        ~EventAction();

        virtual void BeginOfEventAction(const G4Event*);
        virtual void EndOfEventAction(const G4Event*);

        void E1(G4double eE1){
            //fEdep1 += edep1;
            eEnergy1 = eE1;

        }

        void E2(G4double eE2){
            //fEdep2 += edep2;
            eEnergy2 = eE2;
        }

    private:
        G4double eEnergy1, eEnergy2, RecoTheta1, RecoTheta2;
};

#endif