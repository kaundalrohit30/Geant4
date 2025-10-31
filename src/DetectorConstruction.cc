#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction(){

    DefineMaterial();

}

DetectorConstruction::~DetectorConstruction(){

}

void DetectorConstruction::DefineMaterial(){

    //Gd₃Al₂Ga₃O₁₂

    G4NistManager *nist = G4NistManager::Instance();
    
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    detectorMat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");

    G4double density = 6.63*g/cm3;
    GAGG_mat = new G4Material("GAGG_mat", density, 4);
    GAGG_mat->AddElement(nist->FindOrBuildElement("Gd"), 3);
    GAGG_mat->AddElement(nist->FindOrBuildElement("Al"), 2);
    GAGG_mat->AddElement(nist->FindOrBuildElement("Ga"), 3);
    GAGG_mat->AddElement(nist->FindOrBuildElement("O"),12);

    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rIndexGAGG[2] = {1.85, 1.91};
    G4double rIndexAir[2] = {1, 1};

    G4MaterialPropertiesTable *ptAir = new G4MaterialPropertiesTable();
    ptAir->AddProperty("RINDEX", energy, rIndexAir, 2);
    worldMat->SetMaterialPropertiesTable(ptAir);

    G4MaterialPropertiesTable *ptGAGG = new G4MaterialPropertiesTable();
    ptGAGG->AddProperty("RINDEX", energy, rIndexGAGG, 2);
    GAGG_mat->SetMaterialPropertiesTable(ptGAGG);



}

G4VPhysicalVolume *DetectorConstruction::Construct(){

    //DefineMaterial();


    G4bool checkOverlaps = true;


    G4double xWorld = 12.7*mm;
    G4double yWorld = 12.7*mm;
    G4double zWorld = 35*mm;

    G4Box *solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    G4double xScintPos = 1.5*mm;
    G4double yScintPos = 1.5*mm;
    G4double zScintPos = 10*mm;

    G4double xPos[8] = {-11.2, -8, -4.8, -1.6, 1.6, 4.8, 8, 11.2};
    G4double yPos[8] = {-11.2, -8, -4.8, -1.6, 1.6, 4.8, 8, 11.2};
    G4double zPos = 25*mm;


    G4Box *solidScintillator = new G4Box("solidScintillator", xScintPos, yScintPos, zScintPos);
    G4LogicalVolume *logicScintillator = new G4LogicalVolume(solidScintillator, GAGG_mat, "logicScintillator");
    //G4VPhysicalVolume *physScintillator = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicScintillator, "physScintillator", logicWorld, false, 0, checkOverlaps);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            G4VPhysicalVolume *physScintillator = new G4PVPlacement(0, G4ThreeVector(xPos[i],yPos[j],zPos), logicScintillator, "physScintillator", logicWorld, false, j+i*64, checkOverlaps);

        }

        for(int j = 0; j < 8; j++){
            G4VPhysicalVolume *physScintillator = new G4PVPlacement(0, G4ThreeVector(xPos[i],yPos[j],-zPos), logicScintillator, "physScintillator", logicWorld, false, -j-i*64, checkOverlaps);
        }

    }

    G4VisAttributes *ScintillatorVis = new G4VisAttributes(G4Color(1,0,0,0.5));
    ScintillatorVis->SetForceSolid(true);
    logicScintillator->SetVisAttributes(ScintillatorVis);

    return physWorld;

}

void DetectorConstruction::ConstructSDandFields(){

}