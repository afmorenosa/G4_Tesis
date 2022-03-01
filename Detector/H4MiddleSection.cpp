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
) : H4Module(lead_mat, aerog_mat, wls_mat) {

  BuildPlates();

}

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
  // Main box.
  G4VSolid *pb_main_box = new G4Box(
    "Lead Main Box", 6.06*cm, 6.06*cm, pb_thickness
  );

  G4Transform3D transform;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {

      transform = G4Transform3D(
        G4RotationMatrix(0, 0, 0),
        G4ThreeVector((i-0.5) * 6.06 * cm, (j-0.5) * 6.06 * cm, 0.0)
      );

      pb_main_box = new G4SubtractionSolid(
        "Lead Main Box solid",
        pb_main_box,
        m_pb_hole,
        transform
      );

      for (int I = 0; I < 6; I++) {
        for (int J = 0; J < 6; J++) {

          transform = G4Transform3D(
            G4RotationMatrix(0, 0, 0),
            G4ThreeVector((i-0.5) * 6.06 * cm, (j-0.5) * 6.06 * cm, 0.0) +
            G4ThreeVector(
              -3.03*cm + (0.5 + I) * 1.01*cm,
              -3.03*cm + (0.5 + J) * 1.01*cm,
              0
            )
          );

          pb_main_box = new G4SubtractionSolid(
            "Lead Main Box solid",
            pb_main_box,
            m_pb_hole,
            transform
          );

        }
      }
    }
  }

  m_pb_plate_log = new G4LogicalVolume(
    pb_main_box,
    m_lead_mat,
    "Lead plate"
  );

  // Main box.
  G4VSolid *sc_main_box = new G4Box(
    "Scintillator Main Box", 3.03*cm, 3.03*cm, sc_thickness
  );

  transform = G4Transform3D(
    G4RotationMatrix(0, 0, 0), G4ThreeVector(0., 0., 0.)
  );

  sc_main_box = new G4SubtractionSolid(
    "Scintillator Main Box solid",
    sc_main_box,
    m_sc_hole,
    transform
  );

  for (int I = 0; I < 6; I++) {
    for (int J = 0; J < 6; J++) {

      transform = G4Transform3D(
        G4RotationMatrix(0, 0, 0),
        G4ThreeVector(
          -3.03*cm + (0.5 + I) * 1.01*cm,
          -3.03*cm + (0.5 + J) * 1.01*cm,
          0
        )
      );

      sc_main_box = new G4SubtractionSolid(
        "Scintillator Main Box solid",
        sc_main_box,
        m_sc_hole,
        transform
      );

    }
  }

  m_sc_plate_log = new G4LogicalVolume(
    sc_main_box,
    m_aerog_mat,
    "Scintillator plate"
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
  G4RotationMatrix *rot,
  const G4ThreeVector &tlate,
  const G4String &name,
  G4LogicalVolume *mother_logical,
  G4bool many,
  G4int copy_no,
  G4bool surf_chk
) {

  // Place the lead tile.
  if (!is_scintillator) {

    // Place the volume of the plate.
    new G4PVPlacement(
      rot,
      tlate,
      m_pb_plate_log,
      name,
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

      // Place the volumes of the plate.
      new G4PVPlacement(
        rot,
        tlate + G4ThreeVector((i-0.5) * 6.06 * cm, (j-0.5) * 6.06 * cm, 0.0),
        m_sc_plate_log,
        name + " - row: " + std::to_string(i) + " - col: " + std::to_string(j),
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
    m_wls_mat,
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
