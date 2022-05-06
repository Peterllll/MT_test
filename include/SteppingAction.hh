#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Track.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"

class PrimaryGeneratorAction;
class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(const DetectorConstruction*   theDetectorConstruction,
			EventAction*            theEventAction);
  virtual ~SteppingAction();
  virtual void UserSteppingAction(const G4Step* step);
	
private:
  const DetectorConstruction*   fDetConstruction;
	EventAction*            eventAction;
	};

#endif
