#include "H4RunAction.hpp"

//***********************************//
// H4RunAction constructor           //
//-----------------------------------//
//                                   //
// Create and configure root         //
// analysis instance.                //
//                                   //
//***********************************//
H4RunAction::H4RunAction (H4EventAction *event_action, G4String output_path)
: G4UserRunAction(),
m_event_action(event_action),
m_output_path(output_path) {

  // Create the analysis manager.

  G4RootAnalysisManager *analysis_manager = G4RootAnalysisManager::Instance();

  // Set NTuples directory.
  analysis_manager->SetNtupleDirectoryName("ntuple");

  // Set verbose.
  analysis_manager->SetVerboseLevel(0);

  // Create NTuples
  analysis_manager->CreateNtuple("Photons", "Coordinates of photons");

  analysis_manager->CreateNtupleIColumn("primary");

  //<><><><><><><><><><><><><><><><>//
  //  Counter of photons production //
  //<><><><><><><><><><><><><><><><>//

  // Counters of the photons created in the scintillator plates.
  analysis_manager->CreateNtupleIColumn(
    "X_photons_scintillator",
    event_action->GetXGammaScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "Y_photons_scintillator",
    event_action->GetYGammaScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "Z_photons_scintillator",
    event_action->GetZGammaScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "r_photons_scintillator",
    event_action->GetrGammaScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "c_photons_scintillator",
    event_action->GetcGammaScintillator()
  );

  // Counters of the photons created in the lead plates.
  analysis_manager->CreateNtupleIColumn(
    "X_photons_lead",
    event_action->GetXGammaLead()
  );
  analysis_manager->CreateNtupleIColumn(
    "Y_photons_lead",
    event_action->GetYGammaLead()
  );
  analysis_manager->CreateNtupleIColumn(
    "Z_photons_lead",
    event_action->GetZGammaLead()
  );

  //<><><><><><><><><><><><><><><><><>//
  //  Counter of electrons production //
  //<><><><><><><><><><><><><><><><><>//

  // Counters of the electrons created in the scintillator plates.
  analysis_manager->CreateNtupleIColumn(
    "X_electrons_scintillator",
    event_action->GetXElectronScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "Y_electrons_scintillator",
    event_action->GetYElectronScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "Z_electrons_scintillator",
    event_action->GetZElectronScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "r_electrons_scintillator",
    event_action->GetrElectronScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "c_electrons_scintillator",
    event_action->GetcElectronScintillator()
  );

  // Counters of the electrons created in the lead plates.
  analysis_manager->CreateNtupleIColumn(
    "X_electrons_lead",
    event_action->GetXElectronLead()
  );
  analysis_manager->CreateNtupleIColumn(
    "Y_electrons_lead",
    event_action->GetYElectronLead()
  );
  analysis_manager->CreateNtupleIColumn(
    "Z_electrons_lead",
    event_action->GetZElectronLead()
  );

  //<><><><><><><><><><><><><><><><><><><><><><>//
  //  Counter of energy deposition in each step //
  //<><><><><><><><><><><><><><><><><><><><><><>//

  // Information about energy deposited in the scintillator plates.
  analysis_manager->CreateNtupleIColumn(
    "X_step_scintillator",
    event_action->GetXStepScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "Y_step_scintillator",
    event_action->GetYStepScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "Z_step_scintillator",
    event_action->GetZStepScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "r_step_scintillator",
    event_action->GetrStepScintillator()
  );
  analysis_manager->CreateNtupleIColumn(
    "c_step_scintillator",
    event_action->GetcStepScintillator()
  );
  analysis_manager->CreateNtupleFColumn(
    "E_step_scintillator",
    event_action->GetEStepScintillator()
  );
  analysis_manager->CreateNtupleFColumn(
    "SL_step_scintillator",
    event_action->GetSLStepScintillator()
  );

  // Information about energy deposited in the lead plates.
  analysis_manager->CreateNtupleIColumn(
    "X_step_lead",
    event_action->GetXStepLead()
  );
  analysis_manager->CreateNtupleIColumn(
    "Y_step_lead",
    event_action->GetYStepLead()
  );
  analysis_manager->CreateNtupleIColumn(
    "Z_step_lead",
    event_action->GetZStepLead()
  );
  analysis_manager->CreateNtupleFColumn(
    "E_step_lead",
    event_action->GetEStepLead()
  );
  analysis_manager->CreateNtupleFColumn(
    "SL_step_lead",
    event_action->GetSLStepLead()
  );

  analysis_manager->FinishNtuple();

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
void H4RunAction::BeginOfRunAction (const G4Run *run) {

  // Get the analysis manager.
  G4RootAnalysisManager *analysis_manager = G4RootAnalysisManager::Instance();

  // Open output file.
  G4String output_file = m_output_path +
  std::to_string(run->GetRunID()) + ".root";

  analysis_manager->OpenFile(output_file);
}

//************************//
//                        //
// Actions after the run. //
//                        //
//************************//
void H4RunAction::EndOfRunAction (const G4Run *run) {

  // Get the analysis manager.
  G4RootAnalysisManager *analysis_manager = G4RootAnalysisManager::Instance();

  // Write histograms.
  analysis_manager->Write();
  analysis_manager->CloseFile();
}

//
// H4RunAction.cpp ends here.
//
