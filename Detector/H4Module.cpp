#include "H4Detector.hpp"

//**************************************//
//                                      //
// Construct a squared panel with holes //
//                                      //
//**************************************//
void H4Detector::PlaceHolePlate (
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
  G4Box *main_box = new G4Box("Main Box", 2.2*cm, 2.2*cm, thickness);

  G4LogicalVolume *plate_log = new G4LogicalVolume(
    main_box,
    plate_mat,
    log_name
  );

  // Holes tube.
  G4Tubs *hole_tube = new G4Tubs("Hole", 0, .6*mm, thickness, 0.*deg, 360.*deg);

  G4LogicalVolume *hole_log = new G4LogicalVolume(
    hole_tube,
    hole_mat,
    "Hole_Log"
  );

  // Place the volumes
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

  // Place the volumes
  new G4PVPlacement(
    0,
    G4ThreeVector(0, 0, 0),
    hole_log,
    "Hole",
    plate_log,
    false,
    0,
    true
  );

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {

      new G4PVPlacement(
        0,
        G4ThreeVector(
          -2.2*cm + (1 + i) * (4.4 / 5)*cm,
          -2.2*cm + (1 + j) * (4.4 / 5)*cm,
          0
        ),
        hole_log,
        "Hole",
        plate_log,
        false,
        0,
        true
      );

    }
  }

}

//**************************************//
//                                      //
// Construct a squared panel of nine    //
// little hole panels                   //
//                                      //
//**************************************//
void H4Detector::PlaceLargePlate (
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

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {

      PlaceHolePlate (
        plate_mat,
        hole_mat,
        thickness,
        rot,
        tlate + G4ThreeVector((i-1) * 4.4 * cm, (j-1) * 4.4 * cm, 0.0),
        name,
        log_name,
        mother_logical,
        many,
        copy_no,
        surf_chk
      );

    }
  }

}

//**************************************//
//                                      //
// Construct a squared panel of nine    //
// little hole panels                   //
//                                      //
//**************************************//
void H4Detector::PlacePbScPlates (
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

  // Manager for NIST db, for material searching
  G4NistManager *nist = G4NistManager::Instance();

  // Get the definition of lead as a material
  G4Material *lead_mat = nist->FindOrBuildMaterial("G4_Pb");

  for (int i = 0; i < 37; i++) {

    std::cout << name + " Lead" << '\n';

    PlaceLargePlate (
      sc_plate_mat,
      hole_mat,
      sc_thickness,
      rot,
      tlate + G4ThreeVector(
        0,
        0,
        (i - 34) * (2 * (pb_thickness + sc_thickness))
      ),
      name,
      sc_log_name,
      mother_logical,
      many,
      copy_no,
      surf_chk
    );

  }

  for (int i = 0; i < 36; i++) {

    std::cout << name + " Lead" << '\n';

    PlaceLargePlate (
      lead_mat,
      hole_mat,
      pb_thickness,
      rot,
      tlate + G4ThreeVector(
        0,
        0,
        (i - 34) * (2 * (pb_thickness + sc_thickness)) + sc_thickness + pb_thickness
      ),
      name,
      pb_log_name,
      mother_logical,
      many,
      copy_no,
      surf_chk
    );

  }

}

//
// H4Module.cpp end here
//
