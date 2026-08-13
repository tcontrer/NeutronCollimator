//
// ********************************************************************
// * Author: Taylor Contreras                                         *
// * Date: 2026-09-12                                                 *
// * Description: Detector construction for the NeutronCollimator     *
// * simulation.                                                      *
// ********************************************************************
//
/// \file DetectorConstruction.hh
/// \brief Definition of the NeutronColl::DetectorConstruction class

#ifndef NeutronCollDetectorConstruction_h
#define NeutronCollDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

namespace NeutronColl
{

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction() = default;
    ~DetectorConstruction() override = default;

    G4VPhysicalVolume* Construct() override;

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume* fScoringVolume = nullptr;
};

}  // namespace NeutronColl

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
