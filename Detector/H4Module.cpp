#include "H4Module.hpp"

//**********************//
// H4Module constructor //
//----------------------//
//                      //
//       Do nothing.    //
//                      //
//**********************//
H4Module::H4Module (
  G4Material *lead_mat,
  G4Material *aerog_mat,
  G4Material *wls_mat
) {

  // Get the definition of lead as a material.
  m_lead_mat = lead_mat;
  m_aerog_mat = aerog_mat;
  m_wls_mat = wls_mat;

  BuildHoles();

}

//*********************//
// H4Module destructor //
//---------------------//
//                     //
//       Do nothing.   //
//                     //
//*********************//
H4Module::~H4Module () {
  delete m_pb_hole;
  delete m_sc_hole;
}

//*********************************//
//                                 //
// Build the holes for the plates. //
//                                 //
//*********************************//
void H4Module::BuildHoles (
  G4double radius,
  G4double pb_thickness,
  G4double sc_thickness
) {

  m_pb_hole = new G4Tubs(
    "Lead Hole",
    0.,
    radius,
    pb_thickness,
    0.,
    360.*deg
  );

  m_sc_hole = new G4Tubs(
    "Scintillator_Plate Hole",
    0.,
    radius,
    sc_thickness,
    0.,
    360.*deg
  );

}

//****************************//
//                            //
// Build the complete module. //
//                            //
//****************************//
void H4Module::BuildModule (
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

  // Build plates.
  PlacePbScPlates(
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

  // Place the scintillator plates, 67 in total
  for (int i = 0; i < 67; i++) {

    PlaceLargePlate (
      true,
      rot,
      tlate + G4ThreeVector(
        0,
        0,
        (i - 33) * (2 * (pb_thickness + sc_thickness))
      ),
      name + " - scintillator tile: " + std::to_string(i),
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
      rot,
      tlate + G4ThreeVector(
        0,
        0,
        (i - 33) * (2 * (pb_thickness + sc_thickness)) + sc_thickness + pb_thickness
      ),
      name + " - lead tile: " + std::to_string(i),
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
