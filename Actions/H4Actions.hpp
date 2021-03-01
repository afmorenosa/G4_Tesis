#ifndef H4ACTIONS_HG4
#define H4ACTIONS_HG4

// Geant Headers.
#include "GeneralG4.hpp"
#include "G4VUserActionInitialization.hh"

// Project Headers.
#include "H4PrimaryGenerator.hpp"

//**********************************//
// Class: H4Actions                 //
//----------------------------------//
//                                  //
// This class add the Primary      //
// Generator.                       //
//                                  //
//**********************************//
class H4Actions : public G4VUserActionInitialization {
public:
  H4Actions ();
  virtual ~H4Actions ();

  virtual void Build() const;
};

#endif // H4ACTIONS_HG4
