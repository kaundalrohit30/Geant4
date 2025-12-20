#include "EventAction.hh"
#include <cmath>

EventAction::EventAction(RunAction*){
    fEdepComp = 0;
    fEdepPhotoP = 0;
    fBE_Photop = 0;
    fEdepTotal = 0;
    photonNumTotal = 0;
    photonNumCompton = 0;
    photonNumPhotoP = 0;
    //totalOptPhoton = 0;
    OphotonCount_Primary = 0;
    photonNumFluorescence = 0;

    //recoTheta = 0;
    //simTheta = 0;
    //recoEta = 0;


    photCount1 = 0;
    comptCount1 = 0;
    photCount2 = 0;
    comptCount2 = 0;

    Theta1 = 0;
    Theta2 = 0;
    phi1 = 0;
    phi2 = 0;
    D1 = 0;
    D2 = 0;

    comptDetPos1 = {0,0,0};
    photDetPos1 = {0,0,0};
    comptDetPos2 = {0,0,0};
    photDetPos2 = {0,0,0};

}

EventAction::~EventAction(){

}

void EventAction::BeginOfEventAction(const G4Event*){
    fEdepComp = 0;
    fEdepPhotoP = 0;
    fBE_Photop = 0;
    fEdepTotal = 0;
    photonNumTotal = 0;
    photonNumCompton = 0;
    photonNumPhotoP = 0;
    //totalOptPhoton = 0;
    OphotonCount_Primary = 0;
    photonNumFluorescence = 0;

    //recoTheta = 0;
    //simTheta = 0;
    //recoEta = 0;

    photCount1 = 0;
    comptCount1 = 0;
    photCount2 = 0;
    comptCount2 = 0;

    Theta1 = 0;
    Theta2 = 0;
    phi1 = 0;
    phi2 = 0;
    D1 = 0;
    D2 = 0;

    comptDetPos1 = {0,0,0};
    photDetPos1 = {0,0,0};
    comptDetPos2 = {0,0,0};
    photDetPos2 = {0,0,0};

    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    //if(eventID%1000 == 0){
    G4cout << "**************************************************************************************************************************************************" << G4endl;
    G4cout << "\v==========oooOOOOOOOooooo  Event Number:>  " << eventID << "   oooOOOOOOOooooo==========\v"<< G4endl;
    G4cout << "**************************************************************************************************************************************************" << G4endl;
    //}

}

void EventAction::EndOfEventAction(const G4Event*){

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    //G4double inE = 0.511;
    //G4double eMass = 0.511;

    /*G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    analysisManager->FillNtupleIColumn(0,0,eventID);
    analysisManager->FillNtupleDColumn(0,1,fEdepComp);
    analysisManager->FillNtupleDColumn(0,2,fEdepPhotoP);
    analysisManager->FillNtupleDColumn(0,3,fEdepTotal);
    analysisManager->FillNtupleDColumn(0,4,fBE_Photop);
    analysisManager->AddNtupleRow(0);

    analysisManager->FillNtupleIColumn(1,0,photonNumCompton);
    analysisManager->FillNtupleIColumn(1,1,photonNumPhotoP);
    analysisManager->FillNtupleIColumn(1,2,photonNumTotal);
    analysisManager->FillNtupleIColumn(1, 3, photonNumTotal+OphotonCount_Primary);//(1,3,totalOptPhoton);
    analysisManager->FillNtupleIColumn(1, 4, OphotonCount_Primary);
    analysisManager->FillNtupleIColumn(1,5, photonNumFluorescence);
    analysisManager->AddNtupleRow(1);*/
    double dy1, dx1, dy2, dx2;
    dy1 = (photDetPos1.y() - comptDetPos1.y());
    dx1 = (photDetPos1.x() - comptDetPos1.x());
    dy2 = (photDetPos2.y() - comptDetPos2.y());
    dx2 = (photDetPos2.x() - comptDetPos2.x());

    phi1 = atan2(dy1, dx1)*(180/M_PI); //atan((photY1 - comptY1)/(photX1-comptX1))*(180/M_PI);
    phi2 = atan2(dy2, dx2)*(180/M_PI); //atan((photY2 - comptY2)/(photX2-comptX2))*(180/M_PI);
    D1 = sqrt((photDetPos1.x() - comptDetPos1.x())*(photDetPos1.x() - comptDetPos1.x()) + (photDetPos1.y() - comptDetPos1.y())*(photDetPos1.y() - comptDetPos1.y()));
    D2 = sqrt((photDetPos2.x() - comptDetPos2.x())*(photDetPos2.x() - comptDetPos2.x()) + (photDetPos2.y() - comptDetPos2.y())*(photDetPos2.y() - comptDetPos2.y()));
    //if(phi1>=0 or phi1 < 0)
    //G4cout << "Phi1:>   " << phi1 << "   Theta1:>   " << Theta1 << "   Phi2:>  "<< phi2 << "   Theta2:>   " << Theta2 << G4endl;
    //if(phi1>=0 or phi1 < 0){}
    //else{
    //    G4cout << comptY1-photY1 << "/" << comptX1-photX1 << "      " << comptY2-photY2 << "/" <<  comptX2-photX2 << G4endl;
    //}

    //G4cout << "compt,PhotCount Module1:>  " << comptCount1<<","<< photCount1 << "   compt,PhotCount Module2:>  " << comptCount2<<","<< photCount2 << G4endl;

    //G4cout << photDetPos1.y() - comptDetPos1.y() << "  " << photDetPos1.x() - comptDetPos1.x() << "  " << (photDetPos1.y() - comptDetPos1.y())/ (photDetPos1.x() - comptDetPos1.x()) << "   " << phi1 << G4endl;

    if(comptCount1 == 1 and photCount1 == 1 and (dy1/dx1 >= 0 or dy1/dx1 < 0)){// and comptCount2 == 1 and photCount2 == 1 and (dy2/dx2>=0 or dy2/dx2 < 0)){//} and comptCount2 == 1 and photCount2 == 1 and (phi2>=0 or phi2 < 0) ){
        //G4cout << photDetPos1.y() - comptDetPos1.y() << "  " << photDetPos1.x() - comptDetPos1.x() << "  " << (photDetPos1.y() - comptDetPos1.y())/ (photDetPos1.x() - comptDetPos1.x()) << "   " << phi1 << G4endl;
        //G4cout << "Selected Module1:>  " << comptCount1<<","<< photCount1 << G4endl;

        //analysisManager->FillNtupleDColumn(0, 0, comptEdep1);
        //analysisManager->FillNtupleDColumn(0, 1, photEdep1);
        //G4cout << "phi:>   " << phi1 << "   dy =  " << comptY1-photY1 << "   dx =  " << comptX1-photX1 << "  dy/dx = " << (comptY1-photY1)/(comptX1-photX1) << G4endl;
        analysisManager->FillNtupleDColumn(0, 0, phi1);
        analysisManager->FillNtupleDColumn(0, 1, Theta1);
        analysisManager->FillNtupleDColumn(0, 2, D1);
        analysisManager->AddNtupleRow(0);

        /*analysisManager->FillNtupleDColumn(1, 0, phi2);
        analysisManager->FillNtupleDColumn(1, 1, Theta2);
        analysisManager->FillNtupleDColumn(1, 2, D2);
        analysisManager->AddNtupleRow(1);
//  
        double dPhiUncorr = phi1-phi2;

        if(dPhiUncorr > 180) dPhiUncorr -= 2*180;
                        
        else if(dPhiUncorr < -180) dPhiUncorr += 2*180;

        analysisManager->FillNtupleDColumn(2,0,dPhiUncorr);
        analysisManager->AddNtupleRow(2);*/

    }
    
    
    if(comptCount2 == 1 and photCount2 == 1 and (dy2/dx2>=0 or dy2/dx2 < 0)){
        //G4cout << "Selected Module2:>  " << comptCount2<<","<< photCount2 << G4endl;
        //analysisManager->FillNtupleDColumn(1, 0, comptEdep2);
        //analysisManager->FillNtupleDColumn(1, 1, photEdep2);
        analysisManager->FillNtupleDColumn(1, 0, phi2);
        analysisManager->FillNtupleDColumn(1, 1, Theta2);
        analysisManager->FillNtupleDColumn(1, 2, D2);
        analysisManager->AddNtupleRow(1);
    }

    
    //analysisManager->FillNtupleDColumn(0, 0, RecoTheta);
    //analysisManager->FillNtupleDColumn(0, 1, SimTheta);
    //analysisManager->FillNtupleDColumn(0, 2, RecoEta);
    //analysisManager->AddNtupleRow(1);

    


}







    /*comptX1=0;
    comptY1=0;
    comptZ1=0;
    photX1=0;
    photY1=0;
    photZ1=0;
    comptX2=0;
    comptY2=0;
    comptZ2=0;
    photX2=0;
    photY2=0;
    photZ2=0;*/


/*if(comptCount1 == 1 and photCount1 == 1 and comptCount2 == 1 and photCount2 == 1){

        analysisManager->FillNtupleDColumn(2, 0, ComptX1);
        analysisManager->FillNtupleDColumn(2, 1, ComptY1);
        analysisManager->FillNtupleDColumn(2, 2, ComptZ1);
        analysisManager->FillNtupleDColumn(2, 3, PhotX1);
        analysisManager->FillNtupleDColumn(2, 4, PhotY1);
        analysisManager->FillNtupleDColumn(2, 5, PhotZ1);
        analysisManager->AddNtupleRow(2);

        analysisManager->FillNtupleDColumn(3, 0, ComptX2);
        analysisManager->FillNtupleDColumn(3, 1, ComptY2);
        analysisManager->FillNtupleDColumn(3, 2, ComptZ2);
        analysisManager->FillNtupleDColumn(3, 3, PhotX2);
        analysisManager->FillNtupleDColumn(3, 4, PhotY2);
        analysisManager->FillNtupleDColumn(3, 5, PhotZ2);
        analysisManager->AddNtupleRow(3);
    }

    else{
        analysisManager->FillNtupleDColumn(2, 0, 0);
        analysisManager->FillNtupleDColumn(2, 1, 0);
        analysisManager->FillNtupleDColumn(2, 2, 0);
        analysisManager->FillNtupleDColumn(2, 3, 0);
        analysisManager->FillNtupleDColumn(2, 4, 0);
        analysisManager->FillNtupleDColumn(2, 5, 0);
        analysisManager->AddNtupleRow(2);

        analysisManager->FillNtupleDColumn(3, 0, 0);
        analysisManager->FillNtupleDColumn(3, 1, 0);
        analysisManager->FillNtupleDColumn(3, 2, 0);
        analysisManager->FillNtupleDColumn(3, 3, 0);
        analysisManager->FillNtupleDColumn(3, 4, 0);
        analysisManager->FillNtupleDColumn(3, 5, 0);
        analysisManager->AddNtupleRow(3);
    }*/
