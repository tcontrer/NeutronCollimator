//
// ********************************************************************
// * Author: Taylor Contreras                                         *
// * Date: 2026-09-12                                                 *
// * Description: Stepping action for the NeutronCollimator           *
// * simulation.                                                      *
// ********************************************************************
//
/// \file SteppingAction.hh
/// \brief Definition of the NeutronColl::SteppingAction class

#ifndef NeutronCollSteppingAction_h
#define NeutronCollSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class G4LogicalVolume;
class G4Step;

namespace NeutronColl
{

class EventAction;

/// Stepping action class

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction* eventAction);
    ~SteppingAction() override = default;

    // method from the base class
    void UserSteppingAction(const G4Step*) override;

  private:
    EventAction* fEventAction = nullptr;
    G4LogicalVolume* fScoringVolume = nullptr;
};

}  // namespace NeutronColl

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
