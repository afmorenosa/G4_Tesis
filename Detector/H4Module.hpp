#ifndef H4MODULE_HG4
#define H4MODULE_HG4

// Geant Headers.
#include "GeneralG4.hpp"

//**********************************//
// Class: H4Module                  //
//----------------------------------//
//                                  //
// This class build the middle      //
// modules of the detector.         //
//                                  //
//**********************************//
class H4Module {
public:

  H4Module ();
  virtual ~H4Module ();

  void BuildModule (
    G4Material *sc_plate_mat,
    G4Material *wls_mat,
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
    G4bool surf_chk = false
  );

  void PlacePbScPlates (
    G4Material *sc_plate_mat,
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
    G4bool surf_chk = false
  );

  void AddRecovery (
    G4RotationMatrix *rot,
    const G4ThreeVector &tlate,
    const G4String &name,
    G4LogicalVolume *mother_logical,
    G4double pb_thickness = 1*mm,
    G4double sc_thickness = 2*mm,
    G4bool many = false,
    G4int copy_no = 0,
    G4bool surf_chk = false
  );

private:

  virtual void PlaceHolePlate (
    G4bool is_scintillator,
    G4Material *plate_mat,
    G4double thickness,
    G4RotationMatrix *rot,
    const G4ThreeVector &tlate,
    const G4String &name,
    const G4String &log_name,
    G4LogicalVolume *mother_logical,
    G4bool many = false,
    G4int copy_no = 0,
    G4bool surf_chk = false
  ) = 0;

  virtual void PlaceLargePlate (
    G4bool is_scintillator,
    G4Material *plate_mat,
    G4double thickness,
    G4RotationMatrix *rot,
    const G4ThreeVector &tlate,
    const G4String &name,
    const G4String &log_name,
    G4LogicalVolume *mother_logical,
    G4bool many = false,
    G4int copy_no = 0,
    G4bool surf_chk = false
  ) = 0;

  virtual void AddWLS (
    G4Material *wls_mat,
    G4RotationMatrix *rot,
    const G4ThreeVector &tlate,
    const G4String &name,
    G4LogicalVolume *mother_logical,
    G4double pb_thickness,
    G4double sc_thickness,
    G4bool many = false,
    G4int copy_no = 0,
    G4bool surf_chk = false
  ) = 0;

};

#endif // H4MODULE_HG4
