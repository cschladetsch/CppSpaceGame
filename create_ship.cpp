#include "src/voxel.h"
#include <iostream>
#include <cmath>

void createEnterprise(SpaceGame::VoxelModel& model) {
    using namespace SpaceGame;

    Color hullColor(200, 200, 210);
    Color detailColor(180, 180, 190);
    Color bussardColor(255, 100, 100);
    Color warpGrillColor(100, 200, 255);
    Color deflectorColor(120, 180, 255);

    // --- Saucer Section (Primary Hull) ---
    int saucerRadius = 14;
    int saucerHeight = 3;
    for (int y = -saucerRadius; y <= saucerRadius; ++y) {
        for (int x = -saucerRadius; x <= saucerRadius; ++x) {
            if (std::sqrt(x*x + y*y) <= saucerRadius) {
                for (int z = 0; z < saucerHeight; ++z) {
                     model.addVoxel({(int16_t)x, (int16_t)y, (int16_t)z, VoxelType::Hull, hullColor});
                }
            }
        }
    }
    // Bridge
    model.addVoxel({0, 0, (int16_t)saucerHeight, VoxelType::Hull, detailColor});
    model.addVoxel({0, 1, (int16_t)saucerHeight, VoxelType::Hull, detailColor});


    // --- Neck ---
    int neckHeight = 5;
    for (int z = -neckHeight; z < 0; ++z) {
        for (int y = -1; y <= 1; ++y) {
            model.addVoxel({0, (int16_t)(y + saucerRadius - 2), (int16_t)z, VoxelType::Hull, detailColor});
        }
    }

    // --- Secondary Hull ---
    int secHullLength = 20;
    int secHullRadius = 4;
    int secHullOffsetY = saucerRadius + 2;
    int secHullOffsetZ = -neckHeight - secHullRadius;

    for (int y = -secHullRadius; y <= secHullRadius; ++y) {
        for (int x = -secHullRadius; x <= secHullRadius; ++x) {
            if (std::sqrt(x*x + y*y) <= secHullRadius) {
                for (int k = 0; k < secHullLength; ++k) {
                    model.addVoxel({(int16_t)x, (int16_t)(k + secHullOffsetY), (int16_t)(y + secHullOffsetZ), VoxelType::Hull, hullColor});
                }
            }
        }
    }
    // Deflector Dish
    for (int y = -secHullRadius+1; y <= secHullRadius-1; ++y) {
        for (int x = -secHullRadius+1; x <= secHullRadius-1; ++x) {
             if (std::sqrt(x*x + y*y) <= secHullRadius-1) {
                model.addVoxel({(int16_t)x, (int16_t)secHullOffsetY, (int16_t)(y + secHullOffsetZ), VoxelType::System, deflectorColor});
             }
        }
    }


    // --- Nacelle Pylons & Nacelles ---
    int pylonLength = 12;
    int nacelleLength = 18;
    int nacelleRadius = 2;
    int nacelleOffsetZ = -10;

    for (int side = -1; side <= 1; side += 2) {
        // Pylons
        for (int i = 0; i < pylonLength; ++i) {
             model.addVoxel({(int16_t)(side * (saucerRadius/2 + i/2)), (int16_t)(secHullOffsetY + secHullLength - pylonLength + i), (int16_t)(nacelleOffsetZ + i/3), VoxelType::Hull, detailColor});
        }

        // Nacelles
        int nacelleOffsetX = side * (saucerRadius/2 + pylonLength/2);
        int nacelleOffsetY = secHullOffsetY + secHullLength;

        for (int y = -nacelleRadius; y <= nacelleRadius; ++y) {
            for (int x = -nacelleRadius; x <= nacelleRadius; ++x) {
                if (std::sqrt(x*x + y*y) <= nacelleRadius) {
                    for (int k = 0; k < nacelleLength; k++) {
                        Color c = (k == 0) ? bussardColor : hullColor;
                        VoxelType t = (k==0) ? VoxelType::System : VoxelType::Engine;
                         model.addVoxel({(int16_t)(x + nacelleOffsetX), (int16_t)(k + nacelleOffsetY), (int16_t)(y + nacelleOffsetZ + pylonLength/3), t, c});
                    }
                    // Warp Grills
                    model.addVoxel({(int16_t)(x + nacelleOffsetX), (int16_t)(nacelleOffsetY + nacelleLength/2), (int16_t)(y + nacelleOffsetZ+ pylonLength/3), VoxelType::Thruster, warpGrillColor});
                }
            }
        }
    }
}


int main() {
    SpaceGame::VoxelModel model;
    createEnterprise(model);

    if (model.saveToFile("data/ship.bin")) {
        std::cout << "Enterprise model saved successfully." << std::endl;
    } else {
        std::cerr << "Error saving Enterprise model." << std::endl;
    }

    return 0;
}
