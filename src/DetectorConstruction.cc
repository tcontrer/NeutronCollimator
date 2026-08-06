//
// ********************************************************************
// * Author: Taylor Contreras                                         *
// * Date: 2024-06-10                                                 *
// * Description: Detector construction for the NeutronCollimator     *
// * simulation.                                                      *
// ********************************************************************
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the NeutronColl::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"

namespace NeutronColl
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  G4double env_sizeXY = 5 * m, env_sizeZ = 5 * m;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.2 * env_sizeXY;
  G4double world_sizeZ = 1.2 * env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  auto solidWorld =
    new G4Box("World",  // its name
              0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);  // its size

  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
                                        world_mat,  // its material
                                        "World");  // its name

  auto physWorld = new G4PVPlacement(nullptr,  // no rotation
                                     G4ThreeVector(),  // at (0,0,0)
                                     logicWorld,  // its logical volume
                                     "World",  // its name
                                     nullptr,  // its mother  volume
                                     false,  // no boolean operation
                                     0,  // copy number
                                     checkOverlaps);  // overlaps checking

  //
  // Envelope
  //
  auto solidEnv = new G4Box("Envelope",  // its name
                            0.5 * env_sizeXY, 0.5 * env_sizeXY, 0.5 * env_sizeZ);  // its size

  auto logicEnv = new G4LogicalVolume(solidEnv,  // its solid
                                      env_mat,  // its material
                                      "Envelope");  // its name

  new G4PVPlacement(nullptr,  // no rotation
                    G4ThreeVector(),  // at (0,0,0)
                    logicEnv,  // its logical volume
                    "Envelope",  // its name
                    logicWorld,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking


  //
  // Tapered concrete cylinder with a rectangular hole
  //
  G4Material* taperedCylinder_mat = nist->FindOrBuildMaterial("G4_CONCRETE");
  G4double taperedCylinder_radius1 = 21.0/2. * cm;
  G4double taperedCylinder_radius2 = 10.0/2. * cm;
  G4double taperedCylinder_height = 76.2 * cm;
  auto solidTaperedCylinder = new G4Cons("TaperedCylinder",
                                          0, taperedCylinder_radius1,   // Rmin1, Rmax1 (bottom, -z end)
                                          0, taperedCylinder_radius2,   // Rmin2, Rmax2 (top, +z end)
                                          taperedCylinder_height / 2,
                                          0, 360 * deg);

  // Create a rectangular hole in the tapered cylinder
  G4double hole_width = 5.0 * cm; 
  G4double hole_height = 3.5 * cm;
  G4double hole_depth = taperedCylinder_height + 0.1 * cm;  // Slightly larger than the actual hole width to ensure proper subtraction
  auto solidHole = new G4Box("Hole", hole_width / 2, hole_height / 2, hole_depth / 2);

  // Combine the tapered cylinder and the hole using a subtraction solid
  G4SubtractionSolid* taperedCylinderWithHole = new G4SubtractionSolid("TaperedCylinderWithHole", solidTaperedCylinder, solidHole);
  auto logicTaperedCylinderWithHole = new G4LogicalVolume(taperedCylinderWithHole, taperedCylinder_mat, "TaperedCylinderWithHole");
  G4ThreeVector positionTaperedCylinder(0, 0, 0);  // Position of the tapered cylinder
  new G4PVPlacement(nullptr, positionTaperedCylinder, logicTaperedCylinderWithHole, "TaperedCylinderWithHole", logicEnv, false, 0, checkOverlaps);


  // Create a plane 30cm from the small end of the tapered cylinder
  G4Material* plane_mat = nist->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE"); // PVC material for the plane
  G4double plane_distance_from_small_end = 1.0 * cm;
  G4double plane_thickness = 0.1 * cm;  // Thickness of the plane
  G4double plane_z_position = (taperedCylinder_height / 2) + plane_distance_from_small_end + plane_thickness / 2;  // Position of the plane along the z-axis
  G4double plane_sizeXY = 500.0 * cm;  // Size of the plane
  auto solidPlane = new G4Box("Plane", plane_sizeXY / 2, plane_sizeXY / 2, plane_thickness / 2);  // Thin plane
  auto logicPlane = new G4LogicalVolume(solidPlane, plane_mat, "Plane");
  G4ThreeVector positionPlane(0, 0, plane_z_position);
  new G4PVPlacement(nullptr, positionPlane, logicPlane, "Plane", logicEnv, false, 0, checkOverlaps);


  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicTaperedCylinderWithHole;

  //
  // always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace NeutronColl
