#ifndef H4EVENTACTION_HG4
#define H4EVENTACTION_HG4

// Geant Headers.
#include "GeneralG4.hpp"
#include "G4UserEventAction.hh"
#include "G4RootAnalysisManager.hh"

// Project Headers.
#include <regex>

//************************************//
// Class: H4EventAction               //
//------------------------------------//
//                                    //
// This class manage the actions      //
// that are done in all the           //
// events. It will manage the         //
// analysis files.                    //
//                                    //
//************************************//
class H4EventAction : public G4UserEventAction {
public:
  H4EventAction ();
  virtual ~H4EventAction ();

  virtual void BeginOfEventAction(const G4Event *event);
  virtual void EndOfEventAction(const G4Event *event);

  //<><><><><><><><><><><><><><><><><><><><><><><><><>//
  //  Add value to the counters of photons production //
  //<><><><><><><><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  void AppendXGammaScintillator(int X) {m_XGammaScintillator.push_back(X);}
  void AppendYGammaScintillator(int Y) {m_YGammaScintillator.push_back(Y);}
  void AppendZGammaScintillator(int Z) {m_ZGammaScintillator.push_back(Z);}
  void AppendrGammaScintillator(int r) {m_rGammaScintillator.push_back(r);}
  void AppendcGammaScintillator(int c) {m_cGammaScintillator.push_back(c);}

  // Counters for lead plates.
  void AppendXGammaLead(int X) {m_XGammaLead.push_back(X);}
  void AppendYGammaLead(int Y) {m_YGammaLead.push_back(Y);}
  void AppendZGammaLead(int Z) {m_ZGammaLead.push_back(Z);}

  //<><><><><><><><><><><><><><><><><><><><><><><><><><>//
  //  Add value to the counters of electrons production //
  //<><><><><><><><><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  void AppendXElectronScintillator(int X) {m_XElectronScintillator.push_back(X);}
  void AppendYElectronScintillator(int Y) {m_YElectronScintillator.push_back(Y);}
  void AppendZElectronScintillator(int Z) {m_ZElectronScintillator.push_back(Z);}
  void AppendrElectronScintillator(int r) {m_rElectronScintillator.push_back(r);}
  void AppendcElectronScintillator(int c) {m_cElectronScintillator.push_back(c);}

  // Counters for lead plates.
  void AppendXElectronLead(int X) {m_XElectronLead.push_back(X);}
  void AppendYElectronLead(int Y) {m_YElectronLead.push_back(Y);}
  void AppendZElectronLead(int Z) {m_ZElectronLead.push_back(Z);}

  //<><><><><><><><><><><><><><><><><><><><><><><><><>//
  //  Add value to the counters of energy deposition  //
  //<><><><><><><><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  void AppendXStepScintillator(int X) {m_XStepScintillator.push_back(X);}
  void AppendYStepScintillator(int Y) {m_YStepScintillator.push_back(Y);}
  void AppendZStepScintillator(int Z) {m_ZStepScintillator.push_back(Z);}
  void AppendrStepScintillator(int r) {m_rStepScintillator.push_back(r);}
  void AppendcStepScintillator(int c) {m_cStepScintillator.push_back(c);}
  void AppendEStepScintillator(float E) {m_EStepScintillator.push_back(E);}
  void AppendSLStepScintillator(float SL) {m_SLStepScintillator.push_back(SL);}

  // Counters for lead plates.
  void AppendXStepLead(int X) {m_XStepLead.push_back(X);}
  void AppendYStepLead(int Y) {m_YStepLead.push_back(Y);}
  void AppendZStepLead(int Z) {m_ZStepLead.push_back(Z);}
  void AppendEStepLead(float E) {m_EStepLead.push_back(E);}
  void AppendSLStepLead(float SL) {m_SLStepLead.push_back(SL);}

  //<><><><><><><><><><><><><><><><><><><><>//
  // Get the counters of photons production //
  //<><><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  std::vector<int>& GetXGammaScintillator() {return m_XGammaScintillator;}
  std::vector<int>& GetYGammaScintillator() {return m_YGammaScintillator;}
  std::vector<int>& GetZGammaScintillator() {return m_ZGammaScintillator;}
  std::vector<int>& GetrGammaScintillator() {return m_rGammaScintillator;}
  std::vector<int>& GetcGammaScintillator() {return m_cGammaScintillator;}

  // Counters for lead plates.
  std::vector<int>& GetXGammaLead() {return m_XGammaLead;}
  std::vector<int>& GetYGammaLead() {return m_YGammaLead;}
  std::vector<int>& GetZGammaLead() {return m_ZGammaLead;}

  //<><><><><><><><><><><><><><><><><><><><><>//
  // Get the counters of electrons production //
  //<><><><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  std::vector<int>& GetXElectronScintillator() {return m_XElectronScintillator;}
  std::vector<int>& GetYElectronScintillator() {return m_YElectronScintillator;}
  std::vector<int>& GetZElectronScintillator() {return m_ZElectronScintillator;}
  std::vector<int>& GetrElectronScintillator() {return m_rElectronScintillator;}
  std::vector<int>& GetcElectronScintillator() {return m_cElectronScintillator;}

  // Counters for lead plates.
  std::vector<int>& GetXElectronLead() {return m_XElectronLead;}
  std::vector<int>& GetYElectronLead() {return m_YElectronLead;}
  std::vector<int>& GetZElectronLead() {return m_ZElectronLead;}

  //<><><><><><><><><><><><><><><><><><><><>//
  //  Get the counters of energy deposition //
  //<><><><><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  std::vector<int>& GetXStepScintillator() {return m_XStepScintillator;}
  std::vector<int>& GetYStepScintillator() {return m_YStepScintillator;}
  std::vector<int>& GetZStepScintillator() {return m_ZStepScintillator;}
  std::vector<int>& GetrStepScintillator() {return m_rStepScintillator;}
  std::vector<int>& GetcStepScintillator() {return m_cStepScintillator;}
  std::vector<float>& GetEStepScintillator() {return m_EStepScintillator;}
  std::vector<float>& GetSLStepScintillator() {return m_SLStepScintillator;}

  // Counters for lead plates.
  std::vector<int>& GetXStepLead() {return m_XStepLead;}
  std::vector<int>& GetYStepLead() {return m_YStepLead;}
  std::vector<int>& GetZStepLead() {return m_ZStepLead;}
  std::vector<float>& GetEStepLead() {return m_EStepLead;}
  std::vector<float>& GetSLStepLead() {return m_SLStepLead;}

private:

  //<><><><><><><><><><><><><><><><>//
  //  Counter of photons production //
  //<><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  std::vector<int> m_XGammaScintillator = {};
  std::vector<int> m_YGammaScintillator = {};
  std::vector<int> m_ZGammaScintillator = {};
  std::vector<int> m_rGammaScintillator = {};
  std::vector<int> m_cGammaScintillator = {};

  // Counters for lead plates.
  std::vector<int> m_XGammaLead = {};
  std::vector<int> m_YGammaLead = {};
  std::vector<int> m_ZGammaLead = {};

  //<><><><><><><><><><><><><><><><><>//
  //  Counter of electrons production //
  //<><><><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  std::vector<int> m_XElectronScintillator = {};
  std::vector<int> m_YElectronScintillator = {};
  std::vector<int> m_ZElectronScintillator = {};
  std::vector<int> m_rElectronScintillator = {};
  std::vector<int> m_cElectronScintillator = {};

  // Counters for lead plates.
  std::vector<int> m_XElectronLead = {};
  std::vector<int> m_YElectronLead = {};
  std::vector<int> m_ZElectronLead = {};

  //<><><><><><><><><><><><><><><>//
  // Counter of energy deposition //
  //<><><><><><><><><><><><><><><>//

  // Counters for scintillator plates.
  std::vector<int> m_XStepScintillator = {};
  std::vector<int> m_YStepScintillator = {};
  std::vector<int> m_ZStepScintillator = {};
  std::vector<int> m_rStepScintillator = {};
  std::vector<int> m_cStepScintillator = {};
  std::vector<float> m_EStepScintillator = {};
  std::vector<float> m_SLStepScintillator = {};

  // Counters for lead plates.
  std::vector<int> m_XStepLead = {};
  std::vector<int> m_YStepLead = {};
  std::vector<int> m_ZStepLead = {};
  std::vector<float> m_EStepLead = {};
  std::vector<float> m_SLStepLead = {};

  std::map< std::string, int > m_particlesID = {
    {"gamma", 0},
    {"pi0", 1},
    {"e-", 2}
  };

};

#endif // H4EVENTACTION_HG4
