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

    // Get the analysis manager.
    G4RootAnalysisManager *analysis_manager = G4RootAnalysisManager::Instance();

    std::string volume_name = track->GetVolume()->GetName();
    std::smatch number;
    std::regex reg("[0-9]{1,2}");

    std::vector< int > coordinates;

    while ( std::regex_search(volume_name, number, reg) ) {
      std::string matched_number = number[0].str();

      coordinates.push_back(std::atoi(matched_number.c_str()));

      volume_name = number.suffix().str();
    }

    analysis_manager->FillH2(0, 40 - coordinates[0], coordinates[1] - 32);

    analysis_manager->FillNtupleDColumn(0, coordinates[0]);
    analysis_manager->FillNtupleDColumn(1, coordinates[1]);
    analysis_manager->FillNtupleDColumn(2, coordinates[2]);
    analysis_manager->FillNtupleDColumn(3, coordinates[3]);
    analysis_manager->FillNtupleDColumn(4, coordinates[4]);
    analysis_manager->AddNtupleRow();

  }

}

//
// H4TrackingAction.cpp ends here.
//
