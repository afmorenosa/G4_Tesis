#include "H4MiddleSection.hpp"

//*****************************//
// H4MiddleSection constructor //
//-----------------------------//
//                             //
//       Do nothing.           //
//                             //
//*****************************//
H4MiddleSection::H4MiddleSection (
  G4Material *lead_mat,
  G4Material *aerog_mat,
  G4Material *wls_mat
) : H4Module(lead_mat, aerog_mat, wls_mat) {}

//*****************************//
// H4MiddleSection destructor  //
//-----------------------------//
//                             //
//       Do nothing.           //
//                             //
//*****************************//
H4MiddleSection::~H4MiddleSection () {}

//*********************************//
//                                 //
// Build the holes for the plates. //
//                                 //
//*********************************//
void H4MiddleSection::BuildPlates (
  G4double radius,
  G4double pb_thickness,
  G4double sc_thickness
) {
//
//   m_pb_hole = new G4Tubs(
//     "Lead Hole",
//     0.,
//     radius,
//     pb_thickness,
//     0.,
//     360.*deg
//   );
//
//   m_sc_hole = new G4Tubs(
//     "Scintillator_Plate Hole",
//     0.,
//     radius,
//     sc_thickness,
//     0.,
//     360.*deg
//   );
//
//   // Main box.
//   G4Box *pd_base_box = new G4Box("Main Box", 6.06*cm, 6.06*cm, pb_thickness);
//
//   G4MultiUnion *pb_holes = new G4MultiUnion("Scintillator Holes");
//
//   for (int i = 0; i < 3; i++) {
//     for (int j = 0; j < 3; j++) {
//
//       G4Transform3D transform = G4Transform3D(
//         G4RotationMatrix(0, 0, 0),
//         G4ThreeVector((i-1) * 4.04 * cm, (j-1) * 4.04 * cm, 0.0)
//       );
//
//       pb_holes->AddNode(*m_pb_hole, transform);
//
//       for (int I = 0; I < 4; I++) {
//         for (int J = 0; J < 4; J++) {
//
//           transform = G4Transform3D(
//             G4RotationMatrix(0, 0, 0),
//             G4ThreeVector((i-1) * 4.04 * cm, (j-1) * 4.04 * cm, 0.0) +
//             G4ThreeVector(
//               -2.02*cm + (0.5 + I) * 1.01*cm,
//               -2.02*cm + (0.5 + J) * 1.01*cm,
//               0
//             )
//           );
//
//           pb_holes->AddNode(*m_pb_hole, transform);
//
//         }
//       }
//     }
//   }
//
//   G4VSolid *pb_main_box = new G4SubtractionSolid(
//     "Main Box",
//     pd_base_box,
//     pb_holes
//   );
//
//   G4LogicalVolume *pb_plate_log = new G4LogicalVolume(
//     pb_main_box,
//     m_lead_mat,
//     "Lead plate"
//   );
//
//   // Main box.
//   G4Box *sc_base_box = new G4Box("Main Box", 2.02*cm, 2.02*cm, sc_thickness);
//
//   G4MultiUnion *sc_holes = new G4MultiUnion("Scintillator Holes");
//
//   G4Transform3D transform = G4Transform3D(
//     G4RotationMatrix(0, 0, 0), G4ThreeVector(0., 0., 0.)
//   );
//
//   sc_holes->AddNode(*m_sc_hole, transform);
//
//   for (int I = 0; I < 4; I++) {
//     for (int J = 0; J < 4; J++) {
//
//       G4Transform3D transform_hole = G4Transform3D(
//         G4RotationMatrix(0, 0, 0),
//         G4ThreeVector(
//           -2.02*cm + (0.5 + I) * 1.01*cm,
//           -2.02*cm + (0.5 + J) * 1.01*cm,
//           0
//         )
//       );
//
//       sc_holes->AddNode(*m_sc_hole, transform_hole);
//
//     }
//   }
//
//   G4VSolid *sc_main_box = new G4SubtractionSolid(
//     "Main Box",
//     sc_base_box,
//     sc_holes
//   );
//
//   G4LogicalVolume *sc_plate_log = new G4LogicalVolume(
//     sc_main_box,
//     m_aerog_mat,
//     "Scintillator plate"
//   );
//
//
}

//***************************************//
//                                       //
// Construct a squared panel with holes. //
//                                       //
//***************************************//
void H4MiddleSection::PlaceHolePlate (
  G4bool is_scintillator,
  G4Material *plate_mat,
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

  // Lead tile.
  if (!is_scintillator) {

    // Main box.
    G4Box *main_box = new G4Box("Main Box", 6.06*cm, 6.06*cm, thickness);

    G4LogicalVolume *plate_log = new G4LogicalVolume(
      main_box,
      plate_mat,
      log_name
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

    return;
  }

  // Main box.
  G4Box *main_box = new G4Box("Main Box", 3.03*cm, 3.03*cm, thickness);

  G4LogicalVolume *plate_log = new G4LogicalVolume(
    main_box,
    plate_mat,
    log_name
  );

  // Place the volumes of the plate.
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

}

//**************************************//
//                                      //
// Construct a squared panel of four    //
// little hole panels                   //
//                                      //
//**************************************//
void H4MiddleSection::PlaceLargePlate (
  G4bool is_scintillator,
  G4Material *plate_mat,
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

  // Place the lead tile.
  if (!is_scintillator) {
    PlaceHolePlate (
      is_scintillator,
      plate_mat,
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

    return;
  }

  // Place the hole panels, four in total.
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {

      PlaceHolePlate (
        is_scintillator,
        plate_mat,
        thickness,
        rot,
        tlate + G4ThreeVector((i-0.5) * 6.06 * cm, (j-0.5) * 6.06 * cm, 0.0),
        name + " - row: " + std::to_string(i) + " - col: " + std::to_string(j),
        log_name,
        mother_logical,
        many,
        copy_no,
        surf_chk
      );

    }
  }

}

//***************//
//               //
// Add WLS wires //
//               //
//***************//
void H4MiddleSection::AddWLS (
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
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {

      new G4PVPlacement(
        rot,
        tlate +
        G4ThreeVector((i - 0.5) * 6.06 * cm, (j - 0.5) * 6.06 * cm, 0.0),
        wire_log,
        name + " - Plate - row: " + std::to_string(i) + " - col: " +
        std::to_string(j) + " - wire - middle",
        mother_logical,
        many,
        copy_no,
        surf_chk
      );

      for (int I = 0; I < 6; I++) {
        for (int J = 0; J < 6; J++) {

          new G4PVPlacement(
            rot,
            tlate +
            G4ThreeVector((i - 0.5) * 6.06 * cm, (j - 0.5) * 6.06 * cm, 0.0) +
            G4ThreeVector(
              -3.03*cm + (0.5 + I) * 1.01*cm,
              -3.03*cm + (0.5 + J) * 1.01*cm,
              0
            ),
            wire_log,
            name + " - Plate - row: " + std::to_string(i) + " - col: " +
            std::to_string(j) + " - wire - row_hole: " + std::to_string(I) +
            " - col_hole: " + std::to_string(J),
            mother_logical,
            many,
            copy_no,
            surf_chk
          );

        }
      }

    }
  }

}

//
// H4MiddleSection.cpp ends here.
//
