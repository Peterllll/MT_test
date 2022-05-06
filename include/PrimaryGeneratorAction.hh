#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
//#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"

class G4ParticleGun;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();    
  virtual ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event* );

//  const G4ParticleGun* GetParticleGun() const {return ParticleGun;}
  const G4GeneralParticleSource* GetParticleGun() const {return ParticleGun;}

private:
//  G4ParticleGun*          ParticleGun; // G4 particle gun
	G4GeneralParticleSource* ParticleGun;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
