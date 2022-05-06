#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4RunManager.hh"
#include "math.h"
#include "RunAction.hh"
#include "G4Run.hh"
SteppingAction::SteppingAction(const DetectorConstruction* detConstruction,
		EventAction*            theEventAction)
  : G4UserSteppingAction(),
  fDetConstruction(detConstruction),
	eventAction(theEventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void SteppingAction::UserSteppingAction(const G4Step* step) 
{
	/*
	if(step->GetTrack()->GetTrackID()==1
	&& step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary
	&& step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()=="det1"
	){
		G4RunManager* theRunManager = G4RunManager::GetRunManager();
		const PrimaryGeneratorAction* generatorAction
			= static_cast<const PrimaryGeneratorAction*>
			(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
		if (!generatorAction)
		{
			G4cout<<">>>>  cannot get particle gun..."<<G4endl;
		}

		fRootIO->FillTrees(
				theRunManager->GetCurrentEvent()->GetEventID()
				);
	}
	*/
}
