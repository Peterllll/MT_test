#include "EventAction.hh"
#include "TrackerHit.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4DCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4HCofThisEvent.hh"

#include "Analysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

	EventAction::EventAction(PrimaryGeneratorAction* thePrim)
: G4UserEventAction(),
	ergt1(0),
	ergt2(0),
	primary(thePrim)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
EventAction::~EventAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
	ergt1 = 0.;
	ergt2 = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
	// get analysis manager
	auto analysisManager = G4AnalysisManager::Instance();

	TrackerHitsCollection *SDdet1 = (TrackerHitsCollection*)event->GetHCofThisEvent()->GetHC(0);
	TrackerHitsCollection *SDdet2 = (TrackerHitsCollection*)event->GetHCofThisEvent()->GetHC(1);

	int n1_hit = SDdet1->entries();
	int n2_hit = SDdet2->entries();

	int n_hit = n1_hit+n2_hit;
	if(n1_hit>1 && n2_hit>1){
		for (int i1 = 0; i1 < n1_hit; ++i1) {
			ergt1+=(*SDdet1)[i1]->GetEdep()/MeV;
		}
		for (int i2 = 0; i2 < n2_hit; ++i2) {
			ergt2+=(*SDdet2)[i2]->GetEdep()/MeV;
		}		
	}

	analysisManager->FillNtupleDColumn(0,event->GetEventID());
	analysisManager->FillNtupleDColumn(1,primary->GetParticleGun()->GetParticleEnergy()/MeV);
	analysisManager->FillNtupleDColumn(2,ergt1);
	analysisManager->FillNtupleDColumn(3,ergt2);
//	analysisManager->FillNtupleDColumn(2,1);
//	analysisManager->FillNtupleDColumn(3,1);
	analysisManager->AddNtupleRow();
}
