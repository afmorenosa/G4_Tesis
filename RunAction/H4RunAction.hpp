#ifndef H4RUNACTION_HG4
#define H4RUNACTION_HG4

// Geant Headers.
#include "GeneralG4.hpp"
#include "G4UserRunAction.hh"
#include "g4root.hh"

// Project Headers.
#include <regex>

//************************************//
// Class: H4RunAction                 //
//------------------------------------//
//                                    //
// This class manage the actions      //
// that are done in all the           //
// runs. It will manage the analysis  //
// saving.                            //
//                                    //
//************************************//
class H4RunAction : public G4UserRunAction {
public:
  H4RunAction ();
  virtual ~H4RunAction ();

  virtual void BeginOfRunAction(const G4Run* run);
  virtual void EndOfRunAction(const G4Run* run);
};

#endif // H4RUNACTION_HG4
