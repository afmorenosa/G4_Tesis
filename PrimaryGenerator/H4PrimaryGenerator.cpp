#include "H4PrimaryGenerator.hpp"

//**********************************//
// H4PrimaryGenerator constructor   //
//----------------------------------//
//                                  //
//  Set the values for the          //
//  particle gun.                   //
//                                  //
//**********************************//
H4PrimaryGenerator::H4PrimaryGenerator (
  G4String particle_name,
  G4double energy,
  G4ThreeVector position,
  G4ThreeVector momentum_direction
) : G4VUserPrimaryGeneratorAction(),
m_particle_gun(0) {
  // Set the number of particles that will be shooted with the gun.
  G4int n_of_particles = 1;
  m_particle_gun = new G4ParticleGun(n_of_particles);

  // Find the definition of the particle by name.
  G4ParticleTable* particle_table = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particle_table->FindParticle(particle_name);

  // Set particle for the gun.
  m_particle_gun->SetParticleDefinition(particle);

  // Set the energy of the particle.
  m_particle_gun->SetParticleEnergy(energy);

  // Set the position of the particle gun.
  m_particle_gun->SetParticlePosition(position);

  // Set the direction in which the particle will be shooted.
  m_particle_gun->SetParticleMomentumDirection(momentum_direction);
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
  m_particle_gun->GeneratePrimaryVertex(an_event);
}

//
// H4PrimaryGenerator.cpp ends here.
//
