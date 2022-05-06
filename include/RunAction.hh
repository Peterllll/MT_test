#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;
class G4Timer;
class PrimaryGeneratorAction;

class RunAction: public G4UserRunAction
{
public:
  RunAction(PrimaryGeneratorAction* thefPriGen);
  virtual ~RunAction();

  virtual void BeginOfRunAction(const G4Run* run);
  virtual void   EndOfRunAction(const G4Run* run);

private:
  G4Timer* fTimer;
  PrimaryGeneratorAction* fPriGen;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
