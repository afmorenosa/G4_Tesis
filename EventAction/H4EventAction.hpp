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

  void AppendXVal(int x) {m_X.push_back(x);}
  void AppendYVal(int y) {m_Y.push_back(y);}
  void AppendZVal(int z) {m_Z.push_back(z);}
  void AppendrVal(int r) {m_r.push_back(r);}
  void AppendcVal(int c) {m_c.push_back(c);}

  std::vector<int>& GetX() {return m_X;}
  std::vector<int>& GetY() {return m_Y;}
  std::vector<int>& GetZ() {return m_Z;}
  std::vector<int>& Getr() {return m_r;}
  std::vector<int>& Getc() {return m_c;}

private:
  std::vector<int> m_X;
  std::vector<int> m_Y;
  std::vector<int> m_Z;
  std::vector<int> m_r;
  std::vector<int> m_c;

  std::map< std::string, int > m_particlesID = {
    {"gamma", 0},
    {"pi0", 1},
    {"e-", 2}
  };

};

#endif // H4EVENTACTION_HG4
