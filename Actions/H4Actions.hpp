#ifndef H4ACTIONS_HG4
#define H4ACTIONS_HG4

// Geant Headers.
#include "GeneralG4.hpp"
#include "G4VUserActionInitialization.hh"

// Project Headers.
#include "H4PrimaryGenerator.hpp"
#include "H4EventAction.hpp"
#include "H4TrackingAction.hpp"
#include "H4RunAction.hpp"

//**********************************//
// Class: H4Actions                 //
//----------------------------------//
//                                  //
// This class add the Primary       //
// Generator.                       //
//                                  //
//**********************************//
class H4Actions : public G4VUserActionInitialization {
public:
  H4Actions (G4String output_path);
  virtual ~H4Actions ();

  virtual void Build() const;

private:

  G4String m_output_path;
};

#endif // H4ACTIONS_HG4
