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

  // Set seed for random numbers.
  srand (time(NULL));

  // Set the number of particles that will be shooted with the gun.
  G4int n_of_particles = 1;
  m_particle_gun = new G4ParticleGun(n_of_particles);

  // Find the definition of the particle by name.
  G4ParticleTable* particle_table = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particle_table->FindParticle("gamma");

  // Set particle for the gun.
  m_particle_gun->SetParticleDefinition(particle);

  // Set the position of the particle gun.
  m_particle_gun->SetParticlePosition(G4ThreeVector(0.0, 0.0, -7.0*m));

  // Set momentum ranges.

  m_px_min = 0.2424;
  m_py_min = 0.2424;

  m_px_max = 0.9696;
  m_py_max = 0.7272;

  m_pz = 13;

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

  // Create random indices.
  std::vector< float > index(3, 0.0);

  for (size_t i = 0; i < index.size(); i++) {
    index[i] = (float)rand() / (float)RAND_MAX;
  }

  double px, py;

  px = m_px_max * (2 * index[0] - 1);

  py = (m_py_max - m_py_min) * index[1] + m_py_min;

  // Set the energy of the particle.
  m_particle_gun->SetParticleEnergy(18 + (4 *  index[2]) * GeV);

  // Set the direction in which the particle will be shooted.
  m_particle_gun->SetParticleMomentumDirection(
    G4ThreeVector(px, py, m_pz)
  );

  m_particle_gun->GeneratePrimaryVertex(an_event);
}

//
// H4PrimaryGenerator.cpp ends here.
//
