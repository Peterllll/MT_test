#ifndef TrackerHit_h
#define TrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"
#include "G4VProcess.hh"
#include <string.h>

/// Tracker hit class
///
/// It defines data members to store the trackID, chamberNb, energy deposit,
/// and position of charged particles in a selected volume:
/// - fTrackID, fChamberNB, fEdep, fPos

class TrackerHit: public G4VHit
{
public:
  TrackerHit();
  TrackerHit(const TrackerHit&);
  virtual ~TrackerHit();

  //  operator
  const TrackerHit& operator=(const TrackerHit&);
  G4int operator==(const TrackerHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  // methods from base class
	virtual void Draw();
	virtual void Print();

	// Set methods
	void SetParticleName (G4String thetype) { particleName = thetype; }
	void SetEdep (G4double de) { fEdep = de; }
	void SetTrackID (G4int thetrackID) { trackID = thetrackID; }

	// Get methods
	G4int GetTrackID() const { return trackID; }
	G4double GetEdep() const { return fEdep; }
	G4String GetParticleName() { return particleName; }

private:
	G4String particleName;
  G4double fEdep;
	G4int trackID;
	};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//typedef G4THitsCollection<TrackerHit> TrackerHitsCollection;

using TrackerHitsCollection = G4THitsCollection<TrackerHit>;
extern G4ThreadLocal G4Allocator<TrackerHit>* TrackerHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* TrackerHit::operator new(size_t)
{
  if(!TrackerHitAllocator)
      TrackerHitAllocator = new G4Allocator<TrackerHit>;
  return (void *) TrackerHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void TrackerHit::operator delete(void *hit)
{
  TrackerHitAllocator->FreeSingle((TrackerHit*) hit);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
