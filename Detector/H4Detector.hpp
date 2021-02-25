#ifndef H4DETECTOR_HG4
#define H4DETECTOR_HG4

#include "GeneralG4.hpp"
#include "G4VUserDetectorConstruction.hh"

#include "H4InnerSection.hpp"

class H4Detector : public G4VUserDetectorConstruction {
public:
  H4Detector ();
  virtual ~H4Detector ();

  virtual G4VPhysicalVolume *Construct();

private:
  H4InnerSection *m_inner_section_builder;
};

#endif // H4DETECTOR_HG4
