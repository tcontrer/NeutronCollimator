//
// ********************************************************************
// * Author: Taylor Contreras                                         *
// * Date: 2026-09-12                                                 *
// * Description: Event action for the NeutronCollimator simulation.  *
// ********************************************************************
//
/// \file EventAction.hh
/// \brief Definition of the NeutronColl::EventAction class

#ifndef NeutronCollEventAction_h
#define NeutronCollEventAction_h 1

#include "G4UserEventAction.hh"
#include "G4ThreeVector.hh"
#include "G4Accumulable.hh"
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

    void PushbackPosition(const G4ThreeVector& position) { fPositions.push_back(position); }
    void PushbackMomentum(const G4ThreeVector& momentum) { fMomenta.push_back(momentum); }
    void PushbackEnergy(G4double energy) { fEnergies.push_back(energy); }
    void PushbackParticleID(G4int particleID) { fParticleIDs.push_back(particleID); }
    void PushbackMotherID(G4int motherID) { fMotherIDs.push_back(motherID); }

  private:
    RunAction* fRunAction = nullptr;
    G4double fEdep = 0.;

    // Create arrays to store position, momentum, energy, particle ids, mother ids
    std::vector<G4ThreeVector> fPositions;
    std::vector<G4ThreeVector> fMomenta;
    std::vector<G4double> fEnergies;
    std::vector<G4int> fParticleIDs;
    std::vector<G4int> fMotherIDs;
};

}  // namespace NeutronColl

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
