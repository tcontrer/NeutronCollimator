//
// ********************************************************************
// * Author: Taylor Contreras                                         *
// * Date: 2026-09-12                                                 *
// * Description: Event action for the NeutronCollimator simulation.  *
// ********************************************************************
//
/// \file EventAction.cc
/// \brief Implementation of the NeutronColl::EventAction class

#include "EventAction.hh"
#include "RunAction.hh"

#include "G4ThreeVector.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4AccumulableManager.hh"
#include <fstream>

namespace NeutronColl
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RunAction* runAction) : fRunAction(runAction) {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep = 0.;
  fPositions.clear();
  fMomenta.clear();
  fEnergies.clear();
  fParticleIDs.clear();
  fMotherIDs.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* evt)
{
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);

  // For TextGen output, we need the following information:
  // <Event number> <Number of entries in this event> # lines after this line are particle entries
  // <Status> <PDG ID> <1st Mother> <2nd Mother> <1st Daughter> <2nd Daughter> <Px> <Py> <Px> <E> <Mass> <x> <y> <z> <t>
  // Add this info to the output file
  std::ofstream outfile(fRunAction->GetOutputFileName(), std::ios_base::app);
  int numParticlesInEvent = fParticleIDs.size();
  std::cout << "Event " << evt->GetEventID() << ": Number of particles in event = " << numParticlesInEvent << std::endl;
  if (outfile.is_open() and numParticlesInEvent > 0) {
    outfile <<  evt->GetEventID() << " " << numParticlesInEvent << std::endl; // Event number and number of entries in this event
    for (size_t i = 0; i < fParticleIDs.size(); ++i) {
      G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle(fParticleIDs[i]);
      G4double particle_mass = particle->GetPDGMass();

      outfile << evt->GetEventID() << " " << numParticlesInEvent << " "
              << "1 " << fParticleIDs[i] << " 0 0 0 0 " // Status, PDG ID, Mother IDs, Daughter IDs
              << fMomenta[i].x() << " " << fMomenta[i].y() << " " << fMomenta[i].z() << " "
              << fEnergies[i] << " " << particle_mass << " "
              << fPositions[i].x() << " " << fPositions[i].y() << " " << fPositions[i].z() << " 0" << std::endl;
      std::cout << "1 " << fParticleIDs[i] << " 0 0 0 0 " // Status, PDG ID, Mother IDs, Daughter IDs
              << fMomenta[i].x() << " " << fMomenta[i].y() << " " << fMomenta[i].z() << " "
              << fEnergies[i] << " " << particle_mass << " "
              << fPositions[i].x() << " " << fPositions[i].y() << " " << fPositions[i].z() << " 0" << std::endl;
    }
  }
  outfile.close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace NeutronColl
