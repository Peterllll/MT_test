#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "PrimaryGeneratorAction.hh"

#include "globals.hh"

// Event action class

class EventAction: public G4UserEventAction
{
public:
  EventAction(PrimaryGeneratorAction* thePrim);
  virtual ~EventAction();

  virtual void  BeginOfEventAction(const G4Event* );
  virtual void  EndOfEventAction(const G4Event* );

private:
	G4double ergt1;
	G4double ergt2;

  PrimaryGeneratorAction* primary;
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
