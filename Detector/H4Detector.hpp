#ifndef H4DETECTOR_HG4
#define H4DETECTOR_HG4

// Geant Headers.
#include "GeneralG4.hpp"
#include "G4VUserDetectorConstruction.hh"

// Project Headers.
#include "H4InnerSection.hpp"
#include "H4MiddleSection.hpp"
#include "H4OuterSection.hpp"

//**********************************//
// Class: H4Detector                //
//----------------------------------//
//                                  //
// This class build the Detector.   //
//                                  //
//**********************************//
class H4Detector : public G4VUserDetectorConstruction {
public:
  H4Detector ();
  virtual ~H4Detector ();

  virtual G4VPhysicalVolume *Construct ();

  void BuildMaterials ();
  void BuildCalorimeter (G4LogicalVolume *mother_logical);
  void AddMagneticField (
    G4ThreeVector intensity = G4ThreeVector(0.,0., 10*kilogauss)
  );

private:
  // Section pointer for modules placing.
  H4InnerSection *m_inner_section_builder;
  H4MiddleSection *m_middle_section_builder;
  H4OuterSection *m_outer_section_builder;

  // Matierals.
  G4Material *m_world_mat;
  G4Material *m_lead_mat;
  G4Material *m_aerog_mat;
  G4Material *m_wls_mat;
};

#endif // H4DETECTOR_HG4
