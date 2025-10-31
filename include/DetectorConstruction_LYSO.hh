#ifndef DETECTORCONSTRUCTION_LYSO_HH
#define DETECTORCONSTRUCTION_LYSO_HH

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

class DetectorConstruction_LYSO : public G4VUserDetectorConstruction{

    public:
        DetectorConstruction_LYSO();
        virtual ~DetectorConstruction_LYSO();

        virtual G4VPhysicalVolume *Construct();

        //void DefineMaterial();

    private:

        virtual void ConstructSDandFields();

        //G4Box *solidWorld, *solidScintillator, *solidDetector;
        //G4LogicalVolume *logicWorld, *logicScintillator, *logicDetector;
        //G4VPhysicalVolume *physWorld, *physScintillator, *physDetcetor;
//
        G4Element *Lu, *Y, *Si, *O, *Ce;
        G4Material *LYSO, *worldMat;
        //G4Material *detectorMat;

        void DefineMaterial();
};



#endif