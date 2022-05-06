#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  virtual ~DetectorConstruction();

  virtual G4VPhysicalVolume* Construct();

  // other methods
  G4LogicalVolume* Getdet1Log(G4String detName);
	G4LogicalVolume* GetconvLog(G4String convName);
	G4LogicalVolume* Getshell1Log(G4String shellName);

private:
  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();
  G4Material* matVacuum;
  G4Material* Si;
	G4Material* C;
	G4Material* Al;
	G4Material* Air;
	G4Material* SiC;
	G4Material* HDPE;
};
#endif
