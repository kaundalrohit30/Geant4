#include "DetectorConstruction_LYSO.hh"

DetectorConstruction_LYSO::DetectorConstruction_LYSO(){

    DefineMaterial();

}

DetectorConstruction_LYSO::~DetectorConstruction_LYSO(){

}

void DetectorConstruction_LYSO::DefineMaterial(){

    //Gd₃Al₂Ga₃O₁₂

    G4NistManager *nist = G4NistManager::Instance();
    
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    //detectorMat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");


    Lu = nist->FindOrBuildElement("Lu");
    Y  = nist->FindOrBuildElement("Y");
    Si = nist->FindOrBuildElement("Si");
    O  = nist->FindOrBuildElement("O");

    G4double density = 7.2*g/cm3;

    LYSO = new G4Material("LYSO", density, 4);
    LYSO->AddElement(Lu, 71.4*perCent);
    LYSO->AddElement(Y,   4.0*perCent);
    LYSO->AddElement(Si,  6.4*perCent);
    LYSO->AddElement(O,  18.2*perCent);


    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rIndexLYSO[2] = {1.79, 1.83};
    G4double rIndexAir[2] = {1, 1};

    G4MaterialPropertiesTable *ptAir = new G4MaterialPropertiesTable();
    ptAir->AddProperty("RINDEX", energy, rIndexAir, 2);
    worldMat->SetMaterialPropertiesTable(ptAir);

    G4MaterialPropertiesTable *ptLYSO = new G4MaterialPropertiesTable();
    ptLYSO->AddProperty("RINDEX", energy, rIndexLYSO, 2);
    LYSO->SetMaterialPropertiesTable(ptLYSO);



}

G4VPhysicalVolume *DetectorConstruction_LYSO::Construct(){

    //DefineMaterial();


    G4bool checkOverlaps = true;


    G4double xWorld = 8.7*mm;
    G4double yWorld = 8.7*mm;
    G4double zWorld = 35*mm;

    G4Box *solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    G4double xScintPos = 1*mm;
    G4double yScintPos = 1*mm;
    G4double zScintPos = 10*mm;

    G4double xPos[8] = {-7.7, -5.5, -3.3, -1.1, 1.1, 3.3, 5.5, 7.7};
    G4double yPos[8] = {-7.7, -5.5, -3.3, -1.1, 1.1, 3.3, 5.5, 7.7};
    G4double zPos = 25*mm;


    G4Box *solidScintillator = new G4Box("solidScintillator", xScintPos, yScintPos, zScintPos);
    G4LogicalVolume *logicScintillator = new G4LogicalVolume(solidScintillator, LYSO, "logicScintillator");
    //G4VPhysicalVolume *physScintillator = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicScintillator, "physScintillator", logicWorld, false, 0, checkOverlaps);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            G4VPhysicalVolume *physScintillator = new G4PVPlacement(0, G4ThreeVector(xPos[i],yPos[j],zPos), logicScintillator, "physScintillator", logicWorld, false, j+i*64, checkOverlaps);

        }

        for(int j = 0; j < 8; j++){
            G4VPhysicalVolume *physScintillator = new G4PVPlacement(0, G4ThreeVector(xPos[i],yPos[j],-zPos), logicScintillator, "physScintillator", logicWorld, false, -j-i*64, checkOverlaps);
        }

    }

    G4VisAttributes *ScintillatorVis = new G4VisAttributes(G4Color(1,1,0,0.5));
    ScintillatorVis->SetForceSolid(true);
    logicScintillator->SetVisAttributes(ScintillatorVis);

    return physWorld;

}

void DetectorConstruction_LYSO::ConstructSDandFields(){

}