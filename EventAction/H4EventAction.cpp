#include "H4EventAction.hpp"

//***************************//
// H4EventAction constructor //
//---------------------------//
//                           //
//      Do nothing.          //
//                           //
//***************************//
H4EventAction::H4EventAction ()
: G4UserEventAction(),
m_X({}),
m_Y({}),
m_Z({}),
m_r({}),
m_c({}) { }

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

  m_X.clear();
  m_Y.clear();
  m_Z.clear();
  m_r.clear();
  m_c.clear();

}

//**************************//
//                          //
// Actions after the event. //
//                          //
//**************************//
void H4EventAction::EndOfEventAction (const G4Event *event) {
  G4int eventNum = event->GetEventID();

  if ((eventNum + 1)%10 == 0) {
    std::cout << "Event: " << eventNum << '\n';
  }

  // Get the analysis manager.
  G4RootAnalysisManager *analysis_manager = G4RootAnalysisManager::Instance();

  G4String particle =
  event->GetPrimaryVertex()->GetPrimary()
  ->GetParticleDefinition()->GetParticleName();

  for (int i = 0; i < m_X.size(); i++) {
    analysis_manager->FillH2(0, 40 - m_X[0], m_Y[1] - 20);
  }

  analysis_manager->FillNtupleIColumn(0, m_particlesID[particle]);
  // Add tupple row.
  analysis_manager->AddNtupleRow();

}

//
// H4EventAction.cpp ends here.
//
