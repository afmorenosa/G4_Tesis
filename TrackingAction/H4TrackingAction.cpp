#include "H4TrackingAction.hpp"

//**********************************//
// H4TrackingAction constructor     //
//----------------------------------//
//                                  //
//          Do nothing.             //
//                                  //
//**********************************//
H4TrackingAction::H4TrackingAction () : G4UserTrackingAction() { }

//**********************************//
// H4TrackingAction constructor     //
//----------------------------------//
//                                  //
//          Do nothing.             //
//                                  //
//**********************************//
H4TrackingAction::~H4TrackingAction () { }

//******************************//
//                              //
// Actions before the tracking. //
//                              //
//******************************//
void H4TrackingAction::PreUserTrackingAction (const G4Track* track) {

  if (
    track->GetParticleDefinition()->GetParticleName() == "gamma" &&
    std::regex_match(
      track->GetVolume()->GetName(),
      std::regex("Inner module \\([0-9]{1,2},[0-9]{1,2}\\) - "
      "scintillator tile: [0-9]{1,2} - row: [0-9]{1,2} - col: [0-9]{1,2}")
    )
  ) {

    std::cout << "Generado en centellador" << '\n';

  }

}

//
// H4TrackingAction.cpp ends here.
//
