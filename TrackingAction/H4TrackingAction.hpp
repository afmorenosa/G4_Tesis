#ifndef H4TRACKINGACTION_HG4
#define H4TRACKINGACTION_HG4

// Geant Headers.
#include "GeneralG4.hpp"
#include "G4UserTrackingAction.hh"

// Project Headers.
#include <regex>

//**********************************//
// Class: H4TrackingAction          //
//----------------------------------//
//                                  //
// This class manage the actions    //
// that are done in all the         //
// trackings                        //
//                                  //
//**********************************//
class H4TrackingAction : public G4UserTrackingAction {
public:
  H4TrackingAction ();
  virtual ~H4TrackingAction ();

  virtual void PreUserTrackingAction(const G4Track* track);
};

#endif // H4TRACKINGACTION_HG4
