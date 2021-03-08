#include "H4Module.hpp"

//**********************//
// H4Module constructor //
//----------------------//
//                      //
//       Do nothing.    //
//                      //
//**********************//
H4Module::H4Module () {}

//*********************//
// H4Module destructor //
//---------------------//
//                     //
//       Do nothing.   //
//                     //
//*********************//
H4Module::~H4Module () {}

//****************************//
//                            //
// Build the complete module. //
//                            //
//****************************//
void H4Module::BuildModule (
  G4Material *sc_plate_mat,
  G4Material *wls_mat,
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  G4LogicalVolume *mother_logical,
  G4double pb_thickness,
  G4double sc_thickness,
  const G4String &pb_log_name,
  const G4String &sc_log_name,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {

  // Build plates.
  PlacePbScPlates(
    sc_plate_mat,
    rot,
    tlate,
    name,
    mother_logical,
    pb_thickness,
    sc_thickness,
    pb_log_name,
    sc_log_name,
    many,
    copy_no,
    surf_chk
  );

  // Build Recovery.
  AddRecovery (
    rot,
    tlate,
    name,
    mother_logical,
    pb_thickness,
    sc_thickness,
    many,
    copy_no,
    surf_chk
  );

  // Build WLS wire.
  AddWLS (
    wls_mat,
    rot,
    tlate,
    name,
    mother_logical,
    pb_thickness,
    sc_thickness,
    many,
    copy_no,
    surf_chk
  );

}

//**************************************//
//                                      //
// Place the module panels of lead and  //
// scintillator.                        //
//                                      //
//**************************************//
void H4Module::PlacePbScPlates (
  G4Material *sc_plate_mat,
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  G4LogicalVolume *mother_logical,
  G4double pb_thickness,
  G4double sc_thickness,
  const G4String &pb_log_name,
  const G4String &sc_log_name,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {

  // Manager for NIST db, for material searching.
  G4NistManager *nist = G4NistManager::Instance();

  // Get the definition of lead as a material.
  G4Material *lead_mat = nist->FindOrBuildMaterial("G4_Pb");

  // Place the scintillator plates, 67 in total
  for (int i = 0; i < 67; i++) {

    PlaceLargePlate (
      true,
      sc_plate_mat,
      sc_thickness,
      rot,
      tlate + G4ThreeVector(
        0,
        0,
        (i - 33) * (2 * (pb_thickness + sc_thickness))
      ),
      name + " - scintillator tile: " + std::to_string(i),
      sc_log_name,
      mother_logical,
      many,
      copy_no,
      surf_chk
    );

  }

  // Place the lead plates, 66 in total.
  for (int i = 0; i < 66; i++) {

    PlaceLargePlate (
      false,
      lead_mat,
      pb_thickness,
      rot,
      tlate + G4ThreeVector(
        0,
        0,
        (i - 33) * (2 * (pb_thickness + sc_thickness)) + sc_thickness + pb_thickness
      ),
      name + " - lead tile: " + std::to_string(i),
      pb_log_name,
      mother_logical,
      many,
      copy_no,
      surf_chk
    );

  }

}

//**************************************//
//                                      //
// Add steel recovery for the module.   //
//                                      //
//**************************************//
void H4Module::AddRecovery (
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  G4LogicalVolume *mother_logical,
  G4double pb_thickness,
  G4double sc_thickness,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {

  // Manager for NIST db, for material searching.
  G4NistManager *nist = G4NistManager::Instance();

  // Get the definition of steel as a material.
  G4Material *steel_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

  // Vertical box.
  G4Box *vertical_box = new G4Box(
    "Main Box", 0.05*cm, 6.06*cm,
    sc_thickness * 67 + pb_thickness * 66
  );

  G4LogicalVolume *vertical_log = new G4LogicalVolume(
    vertical_box,
    steel_mat,
    "Cover_Sheet"
  );

  // Horizontal box.
  G4Box *horizontal_box = new G4Box(
    "Main Box", 6.16*cm, 0.05*cm,
    sc_thickness * 67 + pb_thickness * 66
  );

  G4LogicalVolume *horizontal_log = new G4LogicalVolume(
    horizontal_box,
    steel_mat,
    "Cover_Sheet"
  );

  // Place the vertical recovery.
  new G4PVPlacement(
    rot,
    tlate + G4ThreeVector(0.05*cm + 6.06*cm, 0., 0.),
    vertical_log,
    name + " - cover left",
    mother_logical,
    many,
    copy_no,
    surf_chk
  );

  new G4PVPlacement(
    rot,
    tlate + G4ThreeVector(-0.05*cm - 6.06*cm, 0., 0.),
    vertical_log,
    name + " - cover right",
    mother_logical,
    many,
    copy_no,
    surf_chk
  );

  // Place the horizontal recovery.
  new G4PVPlacement(
    rot,
    tlate + G4ThreeVector(0., 0.05*cm + 6.06*cm, 0.),
    horizontal_log,
    name + " - cover top",
    mother_logical,
    many,
    copy_no,
    surf_chk
  );

  new G4PVPlacement(
    rot,
    tlate + G4ThreeVector(0., -0.05*cm - 6.06*cm, 0.),
    horizontal_log,
    name + " - cover bottom",
    mother_logical,
    many,
    copy_no,
    surf_chk
  );

}

//
// H4Module.cpp ends here.
//
