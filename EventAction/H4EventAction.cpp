#include "H4EventAction.hpp"

//***************************//
// H4EventAction constructor //
//---------------------------//
//                           //
//      Do nothing.          //
//                           //
//***************************//
H4EventAction::H4EventAction ()
: G4UserEventAction() { }

//***********************************//
// H4EventAction constructor         //
//-----------------------------------//
//                                   //
// Delere root analysis instance.    //
//                                   //
//***********************************//
H4EventAction::~H4EventAction () {
  delete G4RootAnalysisManager::Instance();
}

//***************************//
//                           //
// Actions before the event. //
//                           //
//***************************//
void H4EventAction::BeginOfEventAction (const G4Event *event) {

  //<><><><><><><><><><><><><><><><><><><>//
  // Clear counters of photons production //
  //<><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  m_XGammaScintillator.clear();
  m_YGammaScintillator.clear();
  m_ZGammaScintillator.clear();
  m_rGammaScintillator.clear();
  m_cGammaScintillator.clear();

  // Counters for lead plates.
  m_XGammaLead.clear();
  m_YGammaLead.clear();
  m_ZGammaLead.clear();

  //<><><><><><><><><><><><><><><><><><><><>//
  // Clear counters of electrons production //
  //<><><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  m_XElectronScintillator.clear();
  m_YElectronScintillator.clear();
  m_ZElectronScintillator.clear();
  m_rElectronScintillator.clear();
  m_cElectronScintillator.clear();

  // Counters for lead plates.
  m_XElectronLead.clear();
  m_YElectronLead.clear();
  m_ZElectronLead.clear();

  //<><><><><><><><><><><><><><><><><><><>//
  //  Clear counters of energy deposition //
  //<><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  m_XStepScintillator.clear();
  m_YStepScintillator.clear();
  m_ZStepScintillator.clear();
  m_rStepScintillator.clear();
  m_cStepScintillator.clear();
  m_EStepScintillator.clear();
  m_SLStepScintillator.clear();

  // Counters for lead plates.
  m_XStepLead.clear();
  m_YStepLead.clear();
  m_ZStepLead.clear();
  m_EStepLead.clear();
  m_SLStepLead.clear();

}

//**************************//
//                          //
// Actions after the event. //
//                          //
//**************************//
void H4EventAction::EndOfEventAction (const G4Event *event) {
  G4int eventNum = event->GetEventID();

  if ((eventNum + 1)%10 == 0) {
    std::cout << "Event: " << eventNum + 1 << '\n';
  }

  // Get the analysis manager.
  G4RootAnalysisManager *analysis_manager = G4RootAnalysisManager::Instance();

  G4String particle =
  event->GetPrimaryVertex()->GetPrimary()
  ->GetParticleDefinition()->GetParticleName();

  analysis_manager->FillNtupleIColumn(0, m_particlesID[particle]);

  // Add tupple row.
  analysis_manager->AddNtupleRow();

}

//
// H4EventAction.cpp ends here.
//
