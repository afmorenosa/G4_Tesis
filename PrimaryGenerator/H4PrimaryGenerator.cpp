#include "H4PrimaryGenerator.hpp"

//**********************************//
// H4PrimaryGenerator constructor   //
//----------------------------------//
//                                  //
//  Set the values for the          //
//  particle gun.                   //
//                                  //
//**********************************//
H4PrimaryGenerator::H4PrimaryGenerator () : G4VUserPrimaryGeneratorAction(),
m_particle_gun(0) {

  // Set the number of particles that will be shooted with the gun.
  G4int n_of_particles = 1;
  m_particle_gun = new G4ParticleGun(n_of_particles);

  // Find the definition of the particle by name.
  G4ParticleTable* particle_table = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particle_table->FindParticle("gamma");

  // Set particle for the gun.
  m_particle_gun->SetParticleDefinition(particle);

  // Set the energy of the particle.
  m_particle_gun->SetParticleEnergy(20*GeV);

  // Set the position of the particle gun.
  m_particle_gun->SetParticlePosition(G4ThreeVector(0.01*m, 0.0*m, -7.0*m));

  // Set momentum ranges.
  G4double d = 13; // Distance from the vertex to the detector.
  G4double h_min = 0.2424; // Distance frpm the center to the first module.
  G4double hx_max = 0.7272; // Distance frpm the center to the last module (H).
  G4double hy_max = 0.9696; // Distance frpm the center to the last module (V).

  G4double norm_min = std::sqrt(d * d + h_min * h_min + h_min * h_min);

  G4double norm_max = std::sqrt(d * d + hx_max * hx_max + hy_max * hy_max);

  m_px_min = h_min / norm_min;
  m_py_min = h_min / norm_min;

  m_px_max = hx_max / norm_max;
  m_py_max = hy_max / norm_max;

  m_pz_min = d / norm_min;
  m_pz_max = d / norm_max;

}

//**********************************//
// H4PrimaryGenerator constructor   //
//----------------------------------//
//                                  //
//  Delete the particle gun         //
//                                  //
//**********************************//
H4PrimaryGenerator::~H4PrimaryGenerator () {
  delete m_particle_gun;
}

//***************//
// Run an event. //
//***************//
void H4PrimaryGenerator::GeneratePrimaries (G4Event* an_event) {

  // Set the direction in which the particle will be shooted.
  m_particle_gun->SetParticleMomentumDirection(
    G4ThreeVector((m_px_min + m_px_max) / 2, (m_py_min + m_py_max) / 2, (m_pz_min + m_pz_max) / 2)
  );

  m_particle_gun->GeneratePrimaryVertex(an_event);
}

//
// H4PrimaryGenerator.cpp ends here.
//
