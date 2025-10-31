#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"

class DetectorConstruction : public G4VUserDetectorConstruction{

    public:
        DetectorConstruction();
        virtual ~DetectorConstruction();

        virtual G4VPhysicalVolume *Construct();

        //void DefineMaterial();

    private:

        virtual void ConstructSDandFields();

        //G4Box *solidWorld, *solidScintillator, *solidDetector;
        //G4LogicalVolume *logicWorld, *logicScintillator, *logicDetector;
        //G4VPhysicalVolume *physWorld, *physScintillator, *physDetcetor;
//
        //G4Element *Gd, *Al, *Ga, *O;
        G4Material *GAGG_mat, *worldMat;
        G4Material *detectorMat;

        void DefineMaterial();
};



#endif