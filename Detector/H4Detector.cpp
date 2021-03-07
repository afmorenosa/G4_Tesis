#include "H4Detector.hpp"

//************************//
// H4Detector constructor //
//------------------------//
//                        //
// Do Nothing.            //
//                        //
//************************//
H4Detector::H4Detector () : G4VUserDetectorConstruction() {
  m_inner_section_builder = new H4InnerSection();
  m_middle_section_builder = new H4MiddleSection();
  m_outer_section_builder = new H4OuterSection();
}

//************************//
// H4Detector destructor  //
//------------------------//
//                        //
// Do Nothing.            //
//                        //
//************************//
H4Detector::~H4Detector () {
}

//************************//
// Construct the detector //
//------------------------//
//                        //
// @return the detector   //
// constructed.           //
//                        //
//************************//
G4VPhysicalVolume *H4Detector::Construct () {
  // Initialize Modules pointer.
  m_inner_section_builder = new H4InnerSection();
  m_middle_section_builder = new H4MiddleSection();
  m_outer_section_builder = new H4OuterSection();

  // Build the materials.
  BuildMaterials();

  // Build world geometry.
  G4Box *world_box = new G4Box("World Box", 5*m, 5*m, 8*m);

  // Build world logical volumes.
  G4LogicalVolume *world_log = new G4LogicalVolume(
    world_box,
    m_world_mat,
    "World"
  );

  // Place the world volumes.
  G4VPhysicalVolume *world = new G4PVPlacement(
    0,
    G4ThreeVector(0, 0, 0),
    world_log,
    "Physical World",
    0,
    false,
    0,
    false
  );

  // Build the calorimeter.
  BuildCalorimeter(world_log);

  // Add the magnetic field.
  AddMagneticField();

  // Deleting modules pointers.
  delete m_inner_section_builder;
  delete m_middle_section_builder;
  delete m_outer_section_builder;

  // Return the world.
  return world;
}

//----------------------------------------//
//                                        //
// Build the materials needed for the     //
// detector.                              //
//                                        //
//----------------------------------------//
void H4Detector::BuildMaterials () {

  // Manager for NIST db, for material searching.
  G4NistManager *nist = G4NistManager::Instance();

  // Declare needed variables for material construction.
  G4double density, a;
  std::vector<G4int> natoms;
  std::vector<G4String> elements;

  // Set the material of the world as air.
  m_world_mat = nist->FindOrBuildMaterial("G4_AIR");

  // Define NIST materials for the construction of aerogel.
  G4Material *H2O  = nist->FindOrBuildMaterial("G4_WATER");
  G4Material *SiO2 = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

  a = 12.01*g/mole;
  G4Element* el_carbon  = new G4Element("Carbon" , "C" , 6., a);

  // Define aerogel.
  density = 0.200*g/cm3;
  m_aerog_mat = new G4Material("Aerogel", density, 3);
  m_aerog_mat->AddMaterial(SiO2, 62.5*perCent);
  m_aerog_mat->AddMaterial(H2O, 37.4*perCent);
  m_aerog_mat->AddElement(el_carbon, 0.1*perCent);

  // Materials for the WLSfiber (PMMA).

  elements.push_back("C"); natoms.push_back(5);
  elements.push_back("H"); natoms.push_back(8);
  elements.push_back("O"); natoms.push_back(2);

  density = 1.190*g/cm3;
  m_wls_mat = nist->ConstructNewMaterial(
    "PMMA",
    elements,
    natoms, density
  );

  elements.clear();
  natoms.clear();

}

//----------------------------------------//
//                                        //
// Build the calorimeter of the detector. //
//                                        //
//----------------------------------------//
void H4Detector::BuildCalorimeter (G4LogicalVolume *mother_logical) {

  // Move the coordinates to the first module.
  G4ThreeVector new_coords_tlate =
  G4ThreeVector(-(12.32 * 31.5)*cm, -(12.32 * 25.5)*cm, 6.0*m);

  for (G4int i = 24; i < 40; i++) {
    for (G4int j = 20; j < 32; j++) {

      // Set the position of the module.
      G4ThreeVector module_position =
      G4ThreeVector((12.32 * i)*cm, (12.32 * j)*cm, 0.);

      if (i > 29 && i < 34 && j > 23 && j < 28) {
        // First check if the coordinates correspond to the middle hole of the
        // calorimeter. If so, continue.
        continue;
      } else {

        // Place the inner modules.
        m_inner_section_builder->BuildModule(
          m_aerog_mat,
          m_world_mat,
          m_wls_mat,
          0,
          new_coords_tlate + module_position,
          "Inner module (" + std::to_string(i) + "," + std::to_string(j) + ")",
          mother_logical
        );

      }

    }
  }

}

//----------------------------------------//
//                                        //
// Add a magnetic field for the detector. //
//                                        //
//----------------------------------------//
void H4Detector::AddMagneticField (G4ThreeVector intensity) {

  // Add a magnetic field.
  G4MagneticField *magField
  = new G4UniformMagField(intensity);

  G4FieldManager* fieldMgr
  = G4TransportationManager::GetTransportationManager()
  ->GetFieldManager();

  fieldMgr->SetDetectorField(magField);
  fieldMgr->CreateChordFinder(magField);
}

//
// H4Detector.cpp ends here.
//
