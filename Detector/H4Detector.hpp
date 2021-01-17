#ifndef H4DETECTOR_HG4
#define H4DETECTOR_HG4

#include "GeneralG4.hpp"
#include "G4VUserDetectorConstruction.hh"

class H4Detector : public G4VUserDetectorConstruction {
public:
  H4Detector ();
  virtual ~H4Detector ();

  virtual G4VPhysicalVolume *Construct();

  void PlaceHolePlate (
    G4Material *plate_mat,
    G4Material *hole_mat,
    G4double thickness,
    G4RotationMatrix *rot,
    const G4ThreeVector &tlate,
    const G4String &name,
    const G4String &log_name,
    G4LogicalVolume *mother_logical,
    G4bool many = false,
    G4int copy_no = 0,
    G4bool surf_chk = true
  );

  void PlaceLargePlate (
    G4Material *plate_mat,
    G4Material *hole_mat,
    G4double thickness,
    G4RotationMatrix *rot,
    const G4ThreeVector &tlate,
    const G4String &name,
    const G4String &log_name,
    G4LogicalVolume *mother_logical,
    G4bool many = false,
    G4int copy_no = 0,
    G4bool surf_chk = true
  );

  void PlacePbScPlates (
    G4Material *sc_plate_mat,
    G4Material *hole_mat,
    G4RotationMatrix *rot,
    const G4ThreeVector &tlate,
    const G4String &name,
    G4LogicalVolume *mother_logical,
    G4double pb_thickness = 1*mm,
    G4double sc_thickness = 2*mm,
    const G4String &pb_log_name = "Lead_Plate",
    const G4String &sc_log_name = "Scintillator_Plate",
    G4bool many = false,
    G4int copy_no = 0,
    G4bool surf_chk = true
  );

};

#endif // H4DETECTOR_HG4
