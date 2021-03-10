#include "H4RunAction.hpp"

//***********************************//
// H4RunAction constructor           //
//-----------------------------------//
//                                   //
// Create and configure root         //
// analysis instance.                //
//                                   //
//***********************************//
H4RunAction::H4RunAction () : G4UserRunAction() {
  // Create the analysis manager.

  G4RootAnalysisManager *analysis_manager = G4RootAnalysisManager::Instance();

  // Create histograms directories.
  analysis_manager->SetHistoDirectoryName("histograms");

  // Set verbose.
  analysis_manager->SetVerboseLevel(0);

  // Create histograms.
  analysis_manager->CreateH2("Photons", "Photons", 32, 0, 17, 24, 0, 13);
}

//***********************************//
// H4RunAction constructor           //
//-----------------------------------//
//                                   //
// Delere root analysis instance.    //
//                                   //
//***********************************//
H4RunAction::~H4RunAction () {
  delete G4RootAnalysisManager::Instance();
}

//*************************//
//                         //
// Actions before the run. //
//                         //
//*************************//
void H4RunAction::BeginOfRunAction (const G4Run* run) {
  std::cout << "/==================================================================================================================================================/" << '\n';
  std::cout << "/ Begin of the run" << '\n';
  std::cout << "/==================================================================================================================================================/" << '\n';

  // Get the analysis manager.
  G4RootAnalysisManager *analysis_manager = G4RootAnalysisManager::Instance();

  // Open output file.
  G4String file_name = "calo_Ecal";
  analysis_manager->OpenFile(file_name);
}

//************************//
//                        //
// Actions after the run. //
//                        //
//************************//
void H4RunAction::EndOfRunAction (const G4Run* run) {
  std::cout << "/==================================================================================================================================================/" << '\n';
  std::cout << "/ Begin of the run" << '\n';
  std::cout << "/==================================================================================================================================================/" << '\n';

  // Get the analysis manager.
  G4RootAnalysisManager *analysis_manager = G4RootAnalysisManager::Instance();

  // Write histograms.
  analysis_manager->Write();
  analysis_manager->CloseFile();
}

//
// H4RunAction.cpp ends here.
//
