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
    std::regex_match(
      track->GetVolume()->GetName(),
      std::regex("Inner module \\([0-9]{1,2},[0-9]{1,2}\\) - "
      "[a-z]{4,12} tile: [0-9]{1,2}.{0,}")
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

    if (
      std::regex_match(
        track->GetVolume()->GetName(),
        std::regex("Inner module \\([0-9]{1,2},[0-9]{1,2}\\) - "
        "scintillator tile: [0-9]{1,2} - row: [0-9]{1,2} - col: [0-9]{1,2}")
      )
    ) {

      if ( track->GetParticleDefinition()->GetParticleName() == "gamma" ) {
        m_event_action->AppendXGammaScintillator(39 - coordinates[0]);
        m_event_action->AppendYGammaScintillator(coordinates[1] - 20);
        m_event_action->AppendZGammaScintillator(coordinates[2]);
        m_event_action->AppendrGammaScintillator(coordinates[3]);
        m_event_action->AppendcGammaScintillator(coordinates[4]);
      } else if ( track->GetParticleDefinition()->GetParticleName() == "e-" ) {
        m_event_action->AppendXElectronScintillator(39 - coordinates[0]);
        m_event_action->AppendYElectronScintillator(coordinates[1] - 20);
        m_event_action->AppendZElectronScintillator(coordinates[2]);
        m_event_action->AppendrElectronScintillator(coordinates[3]);
        m_event_action->AppendcElectronScintillator(coordinates[4]);
      }

    } else if (
      std::regex_match(
        track->GetVolume()->GetName(),
        std::regex("Inner module \\([0-9]{1,2},[0-9]{1,2}\\) - "
        "lead tile: [0-9]{1,2}")
      )
    ) {

      if ( track->GetParticleDefinition()->GetParticleName() == "gamma" ) {
        m_event_action->AppendXGammaLead(39 - coordinates[0]);
        m_event_action->AppendYGammaLead(coordinates[1] - 20);
        m_event_action->AppendZGammaLead(coordinates[2]);
      } else if ( track->GetParticleDefinition()->GetParticleName() == "e-" ) {
        m_event_action->AppendXElectronLead(39 - coordinates[0]);
        m_event_action->AppendYElectronLead(coordinates[1] - 20);
        m_event_action->AppendZElectronLead(coordinates[2]);
      }

    }

  }

}

//
// H4TrackingAction.cpp ends here.
//
