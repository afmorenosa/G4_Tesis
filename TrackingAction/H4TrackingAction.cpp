#include "H4TrackingAction.hpp"

//**********************************//
// H4TrackingAction constructor     //
//----------------------------------//
//                                  //
//          Do nothing.             //
//                                  //
//**********************************//
H4TrackingAction::H4TrackingAction (H4EventAction *event_action)
: G4UserTrackingAction(),
m_event_action(event_action) { }

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
void H4TrackingAction::PreUserTrackingAction (const G4Track *track) {

  if (
    track->GetParticleDefinition()->GetParticleName() == "gamma" &&
    std::regex_match(
      track->GetVolume()->GetName(),
      std::regex("Inner module \\([0-9]{1,2},[0-9]{1,2}\\) - "
      "scintillator tile: [0-9]{1,2} - row: [0-9]{1,2} - col: [0-9]{1,2}")
    )
  ) {

    std::string volume_name = track->GetVolume()->GetName();
    std::smatch number;
    std::regex reg("[0-9]{1,2}");

    std::vector< int > coordinates;

    while ( std::regex_search(volume_name, number, reg) ) {
      std::string matched_number = number[0].str();

      coordinates.push_back(std::atoi(matched_number.c_str()));

      volume_name = number.suffix().str();
    }

    m_event_action->AppendXVal(39 - coordinates[0]);
    m_event_action->AppendYVal(coordinates[1] - 20);
    m_event_action->AppendZVal(coordinates[2]);
    m_event_action->AppendrVal(coordinates[3]);
    m_event_action->AppendcVal(coordinates[4]);

  }

}

//
// H4TrackingAction.cpp ends here.
//
