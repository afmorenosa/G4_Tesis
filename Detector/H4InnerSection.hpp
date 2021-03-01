#ifndef H4INNER_SECTION_HG4
#define H4INNER_SECTION_HG4

// Geant Headers.
#include "GeneralG4.hpp"

// Project Headers.
#include "H4Module.hpp"

//**********************************//
// Class: H4InnerSection            //
//----------------------------------//
//                                  //
// This class build the inner       //
// modules of the detector.         //
//                                  //
//**********************************//
class H4InnerSection : public H4Module {
public:

  H4InnerSection ();
  virtual ~H4InnerSection ();

private:

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
    G4bool surf_chk = false
  ) override;

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
    G4bool surf_chk = false
  ) override;

  void AddWLS (
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
  ) override;

};

#endif // H4INNER_SECTION_HG4
