#ifndef H4TRACKINGACTION_HG4
#define H4TRACKINGACTION_HG4

// Geant Headers.
#include "GeneralG4.hpp"
#include "G4UserTrackingAction.hh"

// Project Headers.
#include "H4EventAction.hpp"
#include <regex>

//**********************************//
// Class: H4TrackingAction          //
//----------------------------------//
//                                  //
// This class manage the actions    //
// that are done in all the         //
// trackings.                       //
//                                  //
//**********************************//
class H4TrackingAction : public G4UserTrackingAction {
public:
  H4TrackingAction (H4EventAction *event_action);
  virtual ~H4TrackingAction ();

  virtual void PreUserTrackingAction(const G4Track *track);

private:
  H4EventAction *m_event_action;
};

#endif // H4TRACKINGACTION_HG4
