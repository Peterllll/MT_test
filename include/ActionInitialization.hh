#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include <globals.hh>
#include "G4VUserActionInitialization.hh"

class DetectorConstruction;

// Action initialization class.

class ActionInitialization : public G4VUserActionInitialization
{
public:
  ActionInitialization(DetectorConstruction*, G4int thesaveFlag);
  virtual ~ActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;

private:
  G4int saveFlag;
	DetectorConstruction* detConstruction;
};

#endif
