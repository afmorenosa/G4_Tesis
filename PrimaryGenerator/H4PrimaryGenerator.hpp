#ifndef H4PRIMARYGENERATOR_HG4
#define H4PRIMARYGENERATOR_HG4

#include "GeneralG4.hpp"
#include "G4VUserPrimaryGeneratorAction.hh"

//**********************************//
// Class: H4PrimaryGenerator        //
//----------------------------------//
//                                  //
// This class add the Primary       //
// Generator.                       //
//                                  //
//**********************************//
class H4PrimaryGenerator : public G4VUserPrimaryGeneratorAction {
private:
  G4ParticleGun *m_particle_gun;

  G4double m_px_min, m_py_min, m_pz_min, m_px_max, m_py_max, m_pz_max;

public:
  H4PrimaryGenerator ();
  virtual ~H4PrimaryGenerator ();

  virtual void GeneratePrimaries(G4Event* an_event);
};

#endif // H4PRIMARYGENERATOR_HG4
