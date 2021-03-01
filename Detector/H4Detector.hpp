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

  virtual G4VPhysicalVolume *Construct();

private:
  // Section pointer for modules placing.
  H4InnerSection *m_inner_section_builder;
  H4MiddleSection *m_middle_section_builder;
  H4OuterSection *m_outer_section_builder;
};

#endif // H4DETECTOR_HG4
