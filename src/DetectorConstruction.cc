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
    //detectorMat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");

    G4double density = 6.63*g/cm3;
    GAGG_mat = new G4Material("GAGG_mat", density, 4);
    GAGG_mat->AddElement(nist->FindOrBuildElement("Gd"), 3);
    GAGG_mat->AddElement(nist->FindOrBuildElement("Al"), 2);
    GAGG_mat->AddElement(nist->FindOrBuildElement("Ga"), 3);
    GAGG_mat->AddElement(nist->FindOrBuildElement("O"),12);

    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rIndexAir[2] = {1, 1};

    G4double energyGAGG[6] = {1.56 *eV, 2.19 *eV, 2.38 *eV, 3.47 *eV, 4.24 *eV, 4.65 *eV};
    G4double rIndexGAGG[6] = {1.872, 1.873, 1.870, 1.887, 1.914, 1.940};
    
    std::vector<G4double> ScintPhoEnergy = {1.771 *eV, 1.791 *eV, 1.816 *eV, 1.834 *eV, 1.857 *eV, 1.878 *eV, 1.901 *eV, 1.916 *eV, 1.933 *eV, 1.951 *eV,
					  1.970 *eV, 1.988 *eV, 2.010 *eV, 2.025 *eV, 2.040 *eV, 2.056 *eV, 2.074 *eV, 2.091 *eV, 2.106 *eV, 2.122 *eV,
					  2.133 *eV, 2.143 *eV, 2.155 *eV, 2.164 *eV, 2.174 *eV, 2.181 *eV, 2.190 *eV, 2.196 *eV, 2.207 *eV, 2.217 *eV,
					  2.230 *eV, 2.243 *eV, 2.254 *eV, 2.264 *eV, 2.274 *eV, 2.286 *eV, 2.296 *eV, 2.310 *eV, 2.319 *eV, 2.329 *eV,
					  2.342 *eV, 2.354 *eV, 2.372 *eV, 2.389 *eV, 2.405 *eV, 2.421 *eV, 2.431 *eV, 2.444 *eV, 2.450 *eV, 2.453 *eV,
					  2.460 *eV, 2.467 *eV, 2.471 *eV, 2.475 *eV, 2.479 *eV, 2.485 *eV, 2.491 *eV, 2.496 *eV, 2.499 *eV, 2.506 *eV,
					  2.510 *eV, 2.515 *eV, 2.519 *eV, 2.522 *eV, 2.526 *eV, 2.531 *eV, 2.536 *eV, 2.539 *eV, 2.543 *eV, 2.548 *eV,
					  2.557 *eV, 2.565 *eV, 2.571 *eV, 2.580 *eV, 2.589 *eV, 2.598 *eV, 2.613 *eV, 2.631 *eV, 2.645 *eV, 2.665 *eV};

    std::vector<G4double> ScintFastArray = {0.032, 0.036, 0.039, 0.045, 0.051, 0.057, 0.063, 0.069, 0.073, 0.078,
					  0.086, 0.093, 0.104, 0.112, 0.122, 0.128, 0.140, 0.157, 0.174, 0.191,
					  0.201, 0.214, 0.225, 0.236, 0.244, 0.253, 0.261, 0.268, 0.278, 0.289,
					  0.301, 0.313, 0.324, 0.334, 0.343, 0.353, 0.360, 0.366, 0.374, 0.381,
					  0.385, 0.389, 0.392, 0.392, 0.391, 0.388, 0.381, 0.373, 0.364, 0.355,
					  0.345, 0.335, 0.324, 0.314, 0.306, 0.292, 0.279, 0.266, 0.254, 0.236,
					  0.218, 0.204, 0.193, 0.183, 0.170, 0.157, 0.145, 0.133, 0.121, 0.110,
					  0.099, 0.087, 0.078, 0.065, 0.051, 0.039, 0.028, 0.017, 0.008, 0.002};
  

    std::vector<G4double> ScintSlowArray = {0.050, 0.055, 0.061, 0.069, 0.079, 0.088, 0.097, 0.107, 0.114, 0.122,
					  0.134, 0.144, 0.161, 0.174, 0.189, 0.199, 0.217, 0.244, 0.270, 0.296,
					  0.312, 0.332, 0.348, 0.365, 0.379, 0.392, 0.405, 0.416, 0.432, 0.448,
					  0.466, 0.486, 0.502, 0.517, 0.533, 0.548, 0.558, 0.568, 0.579, 0.591,
					  0.598, 0.603, 0.608, 0.608, 0.606, 0.602, 0.591, 0.578, 0.565, 0.551,
					  0.535, 0.519, 0.503, 0.486, 0.474, 0.453, 0.433, 0.413, 0.394, 0.365,
					  0.339, 0.317, 0.300, 0.284, 0.264, 0.244, 0.224, 0.207, 0.188, 0.171,
					  0.153, 0.136, 0.121, 0.100, 0.079, 0.061, 0.044, 0.027, 0.013, 0.003};
    
    
    
    
    G4MaterialPropertiesTable *ptAir = new G4MaterialPropertiesTable();
    ptAir->AddProperty("RINDEX", energy, rIndexAir, 2);
    worldMat->SetMaterialPropertiesTable(ptAir);

    G4MaterialPropertiesTable *ptGAGG = new G4MaterialPropertiesTable();
    ptGAGG->AddProperty("RINDEX", energyGAGG, rIndexGAGG, 6);
    ptGAGG->AddProperty("SCINTILLATIONCOMPONENT1", ScintPhoEnergy, ScintFastArray, false, true);
    ptGAGG->AddProperty("SCINTILLATIONCOMPONENT2", ScintPhoEnergy, ScintSlowArray, false, true);
    ptGAGG->AddConstProperty("SCINTILLATIONYIELD", 1000/MeV );//28244 / MeV);
    ptGAGG->AddConstProperty("RESOLUTIONSCALE", 1.0);
    ptGAGG->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 50.1 * ns);
    ptGAGG->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 321.5 * ns);
    ptGAGG->AddConstProperty("SCINTILLATIONYIELD1", 0.392);
    ptGAGG->AddConstProperty("SCINTILLATIONYIELD2", 0.608);
    ptGAGG->AddConstProperty("SCINTILLATIONRISETIME1", 8 * ns);
    GAGG_mat->GetIonisation()->SetBirksConstant(0. * mm / MeV);
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