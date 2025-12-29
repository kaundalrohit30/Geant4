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

        void addEdepPhotoP(G4double Edep, G4double BE){
            fEdepPhotoP += Edep;
            fBE_Photop += BE;
            
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
            OphotonCount_Primary += photonNum;
        }

        void addPhotonNumFluorescence(G4double photonNum){
            photonNumFluorescence += photonNum;
        }


        /*void Angle(G4double theta1, G4double theta2, G4double theta3){
            recoTheta = theta1;
            simTheta = theta2;
            recoEta = theta3;
        }*/


        void ComptCount1(G4int count, G4ThreeVector& detPos, G4double theta){//G4double x, G4double y, G4double z, G4double theta){
            comptCount1 += count;
            comptDetPos1 = detPos;
            //comptX1 = x;
            //comptY1 = y;
            //comptZ1 = z;
            Theta1 = theta;
        }
        void PhotCount1(G4int count, G4ThreeVector& detPos){//G4double x, G4double y, G4double z){
            photCount1 += count;
            photDetPos1 =  detPos;
            //photX1 = x;
            //photY1 = y;
            //photZ1 = z;
            //photEdep1 = Edep;
        }

        void ComptCount2(G4int count, G4ThreeVector& detPos, G4double theta){//G4double x, G4double y, G4double z, G4double theta){
            comptCount2 += count;
            comptDetPos2 = detPos;
            //comptX2 = x;
            //comptY2 = y;
            //comptZ2 = z;
            Theta2 = theta;
        }
        void PhotCount2(G4int count, G4ThreeVector& detPos){//G4double x, G4double y, G4double z){
            photCount2 += count;
            photDetPos2 =  detPos;
            //photX2 = x;
            //photY2 = y;
            //photZ2 = z;
            //photEdep2 = Edep;
        }

        //void checkOrthogonality(G4double val){
        //    orthogonality = val;
        //}
        

    private:
        G4double fEdepComp, fEdepPhotoP, fEdepTotal, fBE_Photop, Theta1, Theta2, phi1, phi2, D1, D2;//, orthogonality;//, recoTheta, simTheta, recoEta;
        G4int photonNumTotal, photonNumCompton, photonNumPhotoP, OphotonCount_Primary, photonNumFluorescence, comptCount1, comptCount2, photCount1, photCount2;//, totalOptPhoton;
        //G4double comptX1, comptY1, comptZ1, photX1, photY1, photZ1, comptX2, comptY2, comptZ2, photX2, photY2, photZ2, Theta1, Theta2, phi1, phi2, D1, D2;
        G4ThreeVector comptDetPos1, photDetPos1, comptDetPos2, photDetPos2;
};

#endif