#include "H4Detector.hpp"

//************************//
// H4Detector constructor //
//------------------------//
//                        //
//       Initialize       //
//       modules          //
//       pointers         //
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
//       Delete           //
//       modules          //
//       pointer          //
//                        //
//************************//
H4Detector::~H4Detector () {
  delete m_inner_section_builder;
  delete m_middle_section_builder;
  delete m_outer_section_builder;
}

//************************//
// Construct the detector //
//------------------------//
//                        //
// @return the detector   //
// constructed            //
//                        //
//************************//
G4VPhysicalVolume *H4Detector::Construct () {

  // Manager for NIST db, for material searching
  G4NistManager *nist = G4NistManager::Instance();

  // Define NIST materials
  G4Material *H2O  = nist->FindOrBuildMaterial("G4_WATER");
  G4Material *SiO2 = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

  G4double a = 12.01*g/mole;
  G4Element* el_carbon  = new G4Element("Carbon" , "C" , 6., a);

  // Define aerogel.
  G4double density = 0.200*g/cm3;
  G4Material *aerog_mat = new G4Material("Aerogel", density, 3);
  aerog_mat->AddMaterial(SiO2, 62.5*perCent);
  aerog_mat->AddMaterial(H2O, 37.4*perCent);
  aerog_mat->AddElement(el_carbon, 0.1*perCent);

  // Set the material of the world as air
  G4Material *world_mat = nist->FindOrBuildMaterial("G4_AIR");

  //--------------------------------------------------
  // WLSfiber PMMA
  //--------------------------------------------------
  std::vector<G4int> natoms;
  std::vector<G4String> elements;

  elements.push_back("C"); natoms.push_back(5);
  elements.push_back("H"); natoms.push_back(8);
  elements.push_back("O"); natoms.push_back(2);

  density = 1.190*g/cm3;
  G4Material *wls_mat = nist->ConstructNewMaterial(
    "PMMA",
    elements,
    natoms, density
  );

  elements.clear();
  natoms.clear();

  // Build world geometry
  G4Box *world_box = new G4Box("World Box", 1*m, 1*m, 1*m);

  // Build logical volumes
  G4LogicalVolume *world_log = new G4LogicalVolume(
    world_box,
    world_mat,
    "World"
  );

  // Place the volumes
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

  m_inner_section_builder->BuildModule(
    aerog_mat,
    world_mat,
    wls_mat,
    0,
    G4ThreeVector(0., 0., 0.),
    "Inner module",
    world_log
  );

  m_middle_section_builder->BuildModule(
    aerog_mat,
    world_mat,
    wls_mat,
    0,
    G4ThreeVector(12.32*cm, 0., 0.),
    "Middle module",
    world_log
  );

  m_outer_section_builder->BuildModule(
    aerog_mat,
    world_mat,
    wls_mat,
    0,
    G4ThreeVector(24.64*cm, 0., 0.),
    "Outer module",
    world_log
  );

  G4MagneticField *magField;
  magField = new G4UniformMagField(G4ThreeVector(0.,0., 10*kilogauss));

  G4FieldManager* fieldMgr
    = G4TransportationManager::GetTransportationManager()
      ->GetFieldManager();
  fieldMgr->SetDetectorField(magField);
  fieldMgr->CreateChordFinder(magField);


  return world;
}


//
// H4Detector.cpp end here
//
