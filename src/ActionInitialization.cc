#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization(DetectorConstruction* detConstructionn, G4int thesaveFlag)
: G4VUserActionInitialization(),
	detConstruction(detConstructionn),
  saveFlag(thesaveFlag)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
  PrimaryGeneratorAction* fPriGen = new PrimaryGeneratorAction();

  SetUserAction(new RunAction(fPriGen));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* fPriGen = new PrimaryGeneratorAction();
	EventAction* eventAction = new EventAction(fPriGen);

  SetUserAction(fPriGen);
  SetUserAction(new RunAction(fPriGen));
  SetUserAction(eventAction);
	SetUserAction(new SteppingAction(detConstruction,eventAction));
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
