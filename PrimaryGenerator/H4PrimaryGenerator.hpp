#ifndef H4PRIMARYGENERATOR_HG4
#define H4PRIMARYGENERATOR_HG4

#include "GeneralG4.hpp"
#include "G4VUserPrimaryGeneratorAction.hh"

class H4PrimaryGenerator : public G4VUserPrimaryGeneratorAction {
private:
  G4ParticleGun *particle_gun;

public:
  H4PrimaryGenerator (
    G4String particle_name = "e-",
    G4double energy = 2*GeV,
    G4ThreeVector position = G4ThreeVector(0.01*m, 0.0*m, -1.0*m),
    G4ThreeVector momentum_direction = G4ThreeVector(0.0, 0.00, 1.0)
  );
  virtual ~H4PrimaryGenerator ();

  virtual void GeneratePrimaries(G4Event* an_event);
};

#endif // H4PRIMARYGENERATOR_HG4
