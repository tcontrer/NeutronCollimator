//
// ********************************************************************
// * Author: Taylor Contreras                                         *
// * Date: 2026-09-12                                                 *
// * Description: Stepping action for the NeutronCollimator           *
// * simulation.                                                      *
// ********************************************************************
//
/// \file SteppingAction.cc
/// \brief Implementation of the NeutronColl::SteppingAction class

#include "SteppingAction.hh"

#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Event.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

namespace NeutronColl
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction) : fEventAction(eventAction) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if (!fScoringVolume) {
    const auto detConstruction = static_cast<const DetectorConstruction*>(
      G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detConstruction->GetScoringVolume();
  }

  // get volume of the current step
  G4LogicalVolume* prestep_volume =
    step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  auto postStepTouchable = step->GetPostStepPoint()->GetTouchableHandle();
  auto postStepVolume = postStepTouchable->GetVolume();
  G4LogicalVolume* poststep_volume = postStepVolume ? postStepVolume->GetLogicalVolume() : nullptr;

  // check if we are in scoring volume
  if (prestep_volume == fScoringVolume) {
    // collect energy deposited in this step
    G4double edepStep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edepStep);
  }

  //std::cout << "About to check poststep volume..." << std::endl;
  // Check if the volume has changed from the pre-step to the post-step point and is not null
  if (poststep_volume) {
    //std::cout << "Post-step volume: " << poststep_volume->GetName() << std::endl;
    if (poststep_volume != prestep_volume) {
      //std::cout << "Volume changed from " << prestep_volume->GetName() << " to " << poststep_volume->GetName() << std::endl;
      // Check if the post-step volume is the scoring volume
      if (poststep_volume == fScoringVolume) {
        // For TextGen output, we need the following information:
        fEventAction->PushbackParticleID(step->GetTrack()->GetDefinition()->GetPDGEncoding());
        fEventAction->PushbackMotherID(step->GetTrack()->GetParentID());
        fEventAction->PushbackMomentum(step->GetTrack()->GetMomentum());
        fEventAction->PushbackEnergy(step->GetTrack()->GetTotalEnergy());
        fEventAction->PushbackPosition(step->GetTrack()->GetPosition());
      }
    }
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace NeutronColl
