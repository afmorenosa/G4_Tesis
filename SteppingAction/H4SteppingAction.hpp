#ifndef H4STEPPINGACTION_HG4
#define H4STEPPINGACTION_HG4

// Geant Headers.
#include "GeneralG4.hpp"
#include "G4UserSteppingAction.hh"

// Project Headers.
#include "H4EventAction.hpp"
#include <regex>

//**********************************//
// Class: H4SteppingAction          //
//----------------------------------//
//                                  //
// This class manage the actions    //
// that are done in all the         //
// steps of the simulation.         //
//                                  //
//**********************************//
class H4SteppingAction : public G4UserSteppingAction {
public:
  H4SteppingAction (H4EventAction *event_action);
  virtual ~H4SteppingAction ();

  virtual void UserSteppingAction(const G4Step *step);

private:
  H4EventAction *m_event_action;
};

#endif // H4STEPPINGACTION_HG4
