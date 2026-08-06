//
// ********************************************************************
// * Author: Taylor Contreras                                         *
// * Date: 2024-06-10                                                 *
// * Description: Event action for the NeutronCollimator simulation.  *
// ********************************************************************
//
/// \file EventAction.hh
/// \brief Definition of the NeutronColl::EventAction class

#ifndef NeutronCollEventAction_h
#define NeutronCollEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4Event;

namespace NeutronColl
{

class RunAction;

/// Event action class

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* runAction);
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    void AddEdep(G4double edep) { fEdep += edep; }

  private:
    RunAction* fRunAction = nullptr;
    G4double fEdep = 0.;
};

}  // namespace NeutronColl

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
