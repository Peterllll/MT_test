#include "TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::TrackerSD(
		const G4String& name,
		const G4String& hitsCollectionName)
:G4VSensitiveDetector(name),
 fHitsCollection(nullptr)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::~TrackerSD()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//  build collection between hitsclooection and G4Event
//  call before G4Event start

void TrackerSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);

	// Create hits
	fHitsCollection->insert(new TrackerHit());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  // energy deposit
  edep = aStep->GetTotalEnergyDeposit()/MeV;
	if(edep == 0){return false;}

	TrackerHit* newHit = new TrackerHit();//???

  newHit->SetEdep(edep);
	newHit->SetParticleName(aStep->GetTrack()->GetDefinition()->GetParticleName());
	newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
 
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::EndOfEvent(G4HCofThisEvent*)
{
	G4int nofHits = fHitsCollection->entries();
 for(G4int i = 0; i < nofHits; i++){
      (*fHitsCollection)[i]->Print();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
