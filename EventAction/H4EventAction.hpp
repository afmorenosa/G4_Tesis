#ifndef H4EVENTACTION_HG4
#define H4EVENTACTION_HG4

// Geant Headers.
#include "GeneralG4.hpp"
#include "G4UserEventAction.hh"
#include "g4root.hh"

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
  void AppendXEnergyScintillator(int X) {m_XEnergyScintillator.push_back(X);}
  void AppendYEnergyScintillator(int Y) {m_YEnergyScintillator.push_back(Y);}
  void AppendZEnergyScintillator(int Z) {m_ZEnergyScintillator.push_back(Z);}
  void AppendrEnergyScintillator(int r) {m_rEnergyScintillator.push_back(r);}
  void AppendcEnergyScintillator(int c) {m_cEnergyScintillator.push_back(c);}
  void AppendEEnergyScintillator(float E) {m_EEnergyScintillator.push_back(E);}

  // Counters for lead plates.
  void AppendXEnergyLead(int X) {m_XEnergyLead.push_back(X);}
  void AppendYEnergyLead(int Y) {m_YEnergyLead.push_back(Y);}
  void AppendZEnergyLead(int Z) {m_ZEnergyLead.push_back(Z);}
  void AppendEEnergyLead(float E) {m_EEnergyLead.push_back(E);}

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
  std::vector<int>& GetXEnergyScintillator() {return m_XEnergyScintillator;}
  std::vector<int>& GetYEnergyScintillator() {return m_YEnergyScintillator;}
  std::vector<int>& GetZEnergyScintillator() {return m_ZEnergyScintillator;}
  std::vector<int>& GetrEnergyScintillator() {return m_rEnergyScintillator;}
  std::vector<int>& GetcEnergyScintillator() {return m_cEnergyScintillator;}
  std::vector<float>& GetEEnergyScintillator() {return m_EEnergyScintillator;}

  // Counters for lead plates.
  std::vector<int>& GetXEnergyLead() {return m_XEnergyLead;}
  std::vector<int>& GetYEnergyLead() {return m_YEnergyLead;}
  std::vector<int>& GetZEnergyLead() {return m_ZEnergyLead;}
  std::vector<float>& GetEEnergyLead() {return m_EEnergyLead;}

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
  std::vector<int> m_XEnergyScintillator = {};
  std::vector<int> m_YEnergyScintillator = {};
  std::vector<int> m_ZEnergyScintillator = {};
  std::vector<int> m_rEnergyScintillator = {};
  std::vector<int> m_cEnergyScintillator = {};
  std::vector<float> m_EEnergyScintillator = {};

  // Counters for lead plates.
  std::vector<int> m_XEnergyLead = {};
  std::vector<int> m_YEnergyLead = {};
  std::vector<int> m_ZEnergyLead = {};
  std::vector<float> m_EEnergyLead = {};

  std::map< std::string, int > m_particlesID = {
    {"gamma", 0},
    {"pi0", 1},
    {"e-", 2}
  };

};

#endif // H4EVENTACTION_HG4
