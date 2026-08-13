//
// ********************************************************************
// * Author: Taylor Contreras                                         *
// * Date: 2026-09-12                                                 *
// * Description: Actions for the NeutronCollimator simulation.       *
// ********************************************************************
//
/// \file ActionInitialization.hh
/// \brief Definition of the NeutronColl::ActionInitialization class

#ifndef NeutronCollActionInitialization_h
#define NeutronCollActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

namespace NeutronColl
{

/// Action initialization class.

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization() = default;
    ~ActionInitialization() override = default;

    void BuildForMaster() const override;
    void Build() const override;
};

}  // namespace NeutronColl

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
