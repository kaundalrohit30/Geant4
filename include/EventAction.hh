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

        void addEdepComp(G4double Edep){
            fEdepComp += Edep;
            
        }

        void addEdepPhotoP(G4double Edep){
            fEdepPhotoP += Edep;
            
        }

        void addEdepTotal(G4double Edep){
            fEdepTotal += Edep;
            
        }

        void addPhotonNumCompt(G4double photonNum){
            photonNumCompton += photonNum;
        }

        void addPhotonNumPhotoP(G4double photonNum){
            photonNumPhotoP += photonNum;
        }

        void addPhotonNumTotal(G4double photonNum){
            photonNumTotal += photonNum;

        }

        //void addAlloptPhoton(G4double photonNum){
        //    totalOptPhoton += photonNum;
        //}
        void optPhotCount(G4double photonNum){
            OphotonCount_Primary = photonNum;
        }

        

    private:
        G4double fEdepComp, fEdepPhotoP, fEdepTotal;
        G4int photonNumTotal, photonNumCompton, photonNumPhotoP, OphotonCount_Primary;//, totalOptPhoton;
};

#endif