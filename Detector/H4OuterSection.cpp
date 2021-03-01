#include "H4OuterSection.hpp"

//****************************//
// H4OuterSection constructor //
//----------------------------//
//                            //
//       Do nothing.          //
//                            //
//****************************//
H4OuterSection::H4OuterSection () {}

//****************************//
// H4OuterSection destructor  //
//----------------------------//
//                            //
//       Do nothing.          //
//                            //
//****************************//
H4OuterSection::~H4OuterSection () {}

//****************************//
//                            //
// Build the complete module. //
//                            //
//****************************//
void H4OuterSection::BuildModule (
  G4Material *sc_plate_mat,
  G4Material *hole_mat,
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
    hole_mat,
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

//***************************************//
//                                       //
// Construct a squared panel with holes. //
//                                       //
//***************************************//
void H4OuterSection::PlaceHolePlate (
  G4Material *plate_mat,
  G4Material *hole_mat,
  G4double thickness,
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  const G4String &log_name,
  G4LogicalVolume *mother_logical,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {

  // Main box.
  G4Box *main_box = new G4Box("Main Box", 6.06*cm, 6.06*cm, thickness);

  G4LogicalVolume *plate_log = new G4LogicalVolume(
    main_box,
    plate_mat,
    log_name
  );

  // Holes tube.
  G4Tubs *hole_tube = new G4Tubs("Hole", 0, .7*mm, thickness, 0.*deg, 360.*deg);

  G4LogicalVolume *hole_log = new G4LogicalVolume(
    hole_tube,
    hole_mat,
    "Hole_Log"
  );

  // Place the volume of the plate.
  new G4PVPlacement(
    rot,
    tlate,
    plate_log,
    name,
    mother_logical,
    many,
    copy_no,
    surf_chk
  );

  // Place the volume for the hole in the middle.
  new G4PVPlacement(
    0,
    G4ThreeVector(0, 0, 0),
    hole_log,
    name + " - middle hole",
    plate_log,
    false,
    0,
    surf_chk
  );

  // Place the volumes for the holes, 64 in total.
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {

      new G4PVPlacement(
        0,
        G4ThreeVector(
          -6.06*cm + i * 1.525*cm + 0.7225*cm,
          -6.06*cm + j * 1.525*cm + 0.7225*cm,
          0
        ),
        hole_log,
        name + " - hole - row_hole: " + std::to_string(i) +
        " - col_hole: " + std::to_string(j),
        plate_log,
        false,
        0,
        surf_chk
      );

    }
  }

}

//**************************************//
//                                      //
// Construct a squared panel of one     //
// little hole panels                   //
//                                      //
//**************************************//
void H4OuterSection::PlaceLargePlate (
  G4Material *plate_mat,
  G4Material *hole_mat,
  G4double thickness,
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  const G4String &log_name,
  G4LogicalVolume *mother_logical,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {

  // Place the hole panels, one in total.
  PlaceHolePlate (
    plate_mat,
    hole_mat,
    thickness,
    rot,
    tlate,
    name,
    log_name,
    mother_logical,
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
void H4OuterSection::PlacePbScPlates (
  G4Material *sc_plate_mat,
  G4Material *hole_mat,
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
      sc_plate_mat,
      hole_mat,
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
      lead_mat,
      hole_mat,
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

//************************************//
//                                    //
// Add steel recovery for the module. //
//                                    //
//************************************//
void H4OuterSection::AddRecovery (
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

  // Get the definition of lead as a material.
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
    "Main Box", 6.06*cm, 0.05*cm,
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

//***************//
//               //
// Add WLS wires //
//               //
//***************//
void H4OuterSection::AddWLS (
  G4Material *wls_mat,
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

  // Wire tube.
  G4Tubs *wire_tube = new G4Tubs("Hole", 0, .6*mm,
  sc_thickness * 67 + pb_thickness * 66, 0.*deg, 360.*deg);

  // Wire logical volume.
  G4LogicalVolume *wire_log = new G4LogicalVolume(
    wire_tube,
    wls_mat,
    "WLS"
  );

  // Add the WLS wire according the holes of the plates.
  new G4PVPlacement(
    rot,
    tlate,
    wire_log,
    name + " - Plate - wire - middle",
    mother_logical,
    false,
    0,
    true
  );

  for (int I = 0; I < 8; I++) {
    for (int J = 0; J < 8; J++) {

      new G4PVPlacement(
        rot,
        tlate +
        G4ThreeVector(
          -6.06*cm + I * 1.525*cm + 0.7225*cm,
          -6.06*cm + J * 1.525*cm + 0.7225*cm,
          0
        ),
        wire_log,
        name + " - Plate - wire - row_hole: " + std::to_string(I) +
        " - col_hole: " + std::to_string(J),
        mother_logical,
        many,
        copy_no,
        surf_chk
      );

    }
  }

}

//
// H4OuterSection.cpp ends here.
//
