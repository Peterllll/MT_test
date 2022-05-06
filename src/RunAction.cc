#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"
#include "G4Timer.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleGun.hh"
#include "unistd.h"
#include <fstream>
#include <string>
#include "Analysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(PrimaryGeneratorAction* thefPriGen)
: G4UserRunAction(),
  fPriGen(thefPriGen)
{ 
  // set printing event number per each 100000 events
  G4RunManager::GetRunManager()->SetPrintProgress(100000);

  fTimer = new G4Timer;

	// Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B4Analysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

	// Create directories 
  //analysisManager->SetHistoDirectoryName("histograms");
//  analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output

	// Book ntuple
  // Creating ntuple
  analysisManager->CreateNtuple("tree", "Si Data");
  analysisManager->CreateNtupleDColumn("eventIDt");
  analysisManager->CreateNtupleDColumn("ParticleINEnergyt");
  analysisManager->CreateNtupleDColumn("depositEnergy1t");
  analysisManager->CreateNtupleDColumn("depositEnergy2t");
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  delete fTimer;
  fTimer = NULL;
	delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* frun)
{ 
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

	// Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

	// Open an output file
  //
  
	G4String fileName = "./data/Si_data.root";
  analysisManager->OpenFile(fileName);

  int fRunID = frun->GetRunID();
  fTimer->Start();
//  G4cout << "======================   RunID = " 
//         << fRunID << "  ======================" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RunAction::EndOfRunAction(const G4Run* frun)
{
	auto analysisManager = G4AnalysisManager::Instance();

	// save ntuple
  analysisManager->Write();
  analysisManager->CloseFile();

  fTimer->Stop();
  G4cout << "number of event = " 
         << frun->GetNumberOfEvent() << G4endl;

  G4cout << " time:  " << *fTimer << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
