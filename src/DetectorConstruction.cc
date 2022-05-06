#include "DetectorConstruction.hh"
#include "TrackerSD.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4Tubs.hh"
#include "G4Hype.hh"
#include "G4Trd.hh"
#include "G4Orb.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SDManager.hh"
#include "math.h"


namespace{
  const G4double worldsizeX  = 40 * cm;
  const G4double worldsizeY  = 40 * cm;
  const G4double worldsizeZ  = 40 * cm;
	const G4double R       = 14 * mm;
	const G4double shellThickness   = 2 * mm;
	const G4double convThickness = 0.3 * mm;
	const G4double det1Thickness = 0.3 * mm;
	}

// public methods
DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  matVacuum(nullptr)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  G4double fractionmass;

  G4NistManager* nist = G4NistManager::Instance();
	matVacuum = nist->FindOrBuildMaterial("G4_Galactic");
	Air = nist->FindOrBuildMaterial("G4_AIR");

	G4Element* elC = nist->FindOrBuildElement("C");
	G4Element* elH = nist->FindOrBuildElement("H");
	HDPE = new G4Material("HDPE",0.96*g/cm3,2);
	HDPE->AddElement(elH,4);
	HDPE->AddElement(elC,2);

	G4Element* elSi = nist->FindOrBuildElement("Si");
	SiC = new G4Material("SiC",3.2*g/cm3,2);
	SiC->AddElement(elSi, 1);
  SiC->AddElement(elC, 1);

	C = nist->FindOrBuildMaterial("G4_C");
	Si = nist->FindOrBuildMaterial("G4_Si");
	Al = nist->FindOrBuildMaterial("G4_Al");
	
	G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::Getshell1Log(G4String shellName)
{
  G4LogicalVolume* fshell1Log = NULL;

	G4Tubs* soildshell1 = 
		new G4Tubs("soildshell1",
				0,
				1.5*R,
				0.5*shellThickness,
				0.*deg,
				360.*deg);

  fshell1Log = new G4LogicalVolume(soildshell1,
                 Al,
                 shellName);

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 0.5, 0.0, 0.3));
                    pVisAtt->SetForceSolid(true);
                    fshell1Log->SetVisAttributes(pVisAtt);

  return fshell1Log;
}

G4LogicalVolume* DetectorConstruction::Getdet1Log(G4String detName)
{
  G4LogicalVolume* fdet1Log = NULL;

	G4Tubs* soilddet1 = 
		new G4Tubs("soilddet1",
				0,
				R,
				0.5*det1Thickness,
				0.*deg,
				360.*deg);

  fdet1Log = new G4LogicalVolume(soilddet1,
                 Si,
                 detName);

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.5, 0.3));
                    pVisAtt->SetForceSolid(true);
                    fdet1Log->SetVisAttributes(pVisAtt);

  return fdet1Log;
}

G4LogicalVolume* DetectorConstruction::GetconvLog(G4String convName)
{
	G4LogicalVolume* fconvLog = NULL;

	G4Tubs* soildconv = 
		new G4Tubs("soildconv",
				0,
				R,
				0.5*convThickness,
				0.*deg,
				360.*deg);

	fconvLog = new G4LogicalVolume(soildconv,
	//		HDPE,
	//		matVacuum,
			Air,
			convName);

	//  color
	G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 0.5, 0.0, 0.3));
	pVisAtt->SetForceSolid(true);
	fconvLog->SetVisAttributes(pVisAtt);

	return fconvLog;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  G4cout<<" --->: World construct, begin ....." << G4endl;

  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = false;

  //  define world
  G4Box* solidWorld =
    new G4Box("World",
        0.5 * worldsizeX,
        0.5 * worldsizeY,
        0.5 * worldsizeZ);

  G4LogicalVolume* logicWorld = 
    new G4LogicalVolume(solidWorld,
			//	matVacuum,
        Air,
        "World");

  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,
        G4ThreeVector(),
        logicWorld,
        "World",
        0,
        false,
        0,
        checkOverlaps);

	G4ThreeVector positionshell1 = G4ThreeVector(0., 0., -5.*cm);
  G4LogicalVolume* fshell1Log = Getshell1Log("shell1");
  
  new G4PVPlacement(0,    //  no no rotation
      positionshell1,        //  at (x,y,z)
      fshell1Log,            //  its logical volume
      "shell1",              //  its name
      logicWorld,         //  its mother volume
      false,              //  no boolean operations
      0,                  //  copy number
      checkOverlaps);

	G4ThreeVector positionconv = G4ThreeVector(0., 0., -0.5*convThickness);
	G4LogicalVolume* fconvLog = GetconvLog("conv");

	new G4PVPlacement(0,    //  no no rotation
			positionconv,        //  at (x,y,z)
			fconvLog,            //  its logical volume
			"conv",              //  its name
			logicWorld,         //  its mother volume
			false,              //  no boolean operations
			0,                  //  copy number
			checkOverlaps);

	G4ThreeVector positiondet1 = G4ThreeVector(0., 0., 0.5*det1Thickness);
  G4LogicalVolume* fdet1Log = Getdet1Log("det1");
  
  new G4PVPlacement(0,    //  no no rotation
      positiondet1,        //  at (x,y,z)
      fdet1Log,            //  its logical volume
      "det1",              //  its name
      logicWorld,         //  its mother volume
      false,              //  no boolean operations
      0,                  //  copy number
      checkOverlaps);

	G4SDManager* SDman = G4SDManager::GetSDMpointer();

	TrackerSD* SDdet1= new TrackerSD("SDdet1","SDdet1HitsCollection"); 
  fconvLog->SetSensitiveDetector(SDdet1);
  SDman->AddNewDetector(SDdet1);
	TrackerSD* SDdet2= new TrackerSD("SDdet2","SDdet2HitsCollection"); 
  fdet1Log->SetSensitiveDetector(SDdet2);
  SDman->AddNewDetector(SDdet2);

  return physWorld;
}
