#include "H4OuterSection.hpp"

//****************************//
// H4OuterSection constructor //
//----------------------------//
//                            //
//       Do nothing.          //
//                            //
//****************************//
H4OuterSection::H4OuterSection () : H4Module() {}

//****************************//
// H4OuterSection destructor  //
//----------------------------//
//                            //
//       Do nothing.          //
//                            //
//****************************//
H4OuterSection::~H4OuterSection () {}

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

  // // Holes tube.
  // G4Tubs *hole_tube = new G4Tubs("Hole", 0, .7*mm, thickness, 0.*deg, 360.*deg);
  //
  // G4LogicalVolume *hole_log = new G4LogicalVolume(
  //   hole_tube,
  //   hole_mat,
  //   "Hole_Log"
  // );

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

  // // Place the volume for the hole in the middle.
  // new G4PVPlacement(
  //   0,
  //   G4ThreeVector(0, 0, 0),
  //   hole_log,
  //   name + " - middle hole",
  //   plate_log,
  //   many,
  //   copy_no,
  //   surf_chk
  // );
  //
  // // Place the volumes for the holes, 64 in total.
  // for (int i = 0; i < 8; i++) {
  //   for (int j = 0; j < 8; j++) {
  //
  //     new G4PVPlacement(
  //       0,
  //       G4ThreeVector(
  //         -6.06*cm + i * 1.525*cm + 0.7225*cm,
  //         -6.06*cm + j * 1.525*cm + 0.7225*cm,
  //         0
  //       ),
  //       hole_log,
  //       name + " - hole - row_hole: " + std::to_string(i) +
  //       " - col_hole: " + std::to_string(j),
  //       plate_log,
  //       many,
  //       copy_no,
  //       surf_chk
  //     );
  //
  //   }
  // }

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
    many,
    copy_no,
    surf_chk
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
