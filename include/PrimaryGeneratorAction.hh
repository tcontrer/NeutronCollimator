//
// ********************************************************************
// * Author: Taylor Contreras                                         *
// * Date: 2026-09-12                                                 *
// * Description: Primary generator action for the NeutronCollimator  *
// * simulation.                                                      *
// ********************************************************************
//
/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the NeutronColl::PrimaryGeneratorAction class

#ifndef NeutronCollPrimaryGeneratorAction_h
#define NeutronCollPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class G4Event;
class G4Box;

namespace NeutronColl
{

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued
/// in front of the phantom across 80% of the (X,Y) phantom size.

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    // method from the base class
    void GeneratePrimaries(G4Event*) override;

    // method to access particle gun
    const G4GeneralParticleSource* GetGeneralParticleSource() const { return fGeneralParticleSource; }

  private:
    G4GeneralParticleSource* fGeneralParticleSource = nullptr;  // pointer a to G4 particle source class
    G4Box* fEnvelopeBox = nullptr;
};

}  // namespace NeutronColl

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
