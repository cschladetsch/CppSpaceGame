#pragma once

#include <cstdint>
#include <vector>
#include <array>

#include <glm/glm.hpp>

namespace SpaceGame {

// RGB color for voxels
struct Color {
    uint8_t r, g, b, a;

    Color() : r(0), g(0), b(0), a(255) {}
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r), g(g), b(b), a(a) {}
};

// Voxel types for different materials/properties
enum class VoxelType : uint8_t {
    Empty = 0,
    Hull,           // Standard ship hull
    Engine,         // Engine block
    Thruster,       // Directional thruster
    Weapon,         // Weapon mount
    Armor,          // Heavy armor
    System          // Internal systems
};

// Single voxel with position and properties
struct Voxel {
    int16_t x, y, z;        // Position in local space
    VoxelType type;
    Color color;
    double health;           // 0.0 to 1.0, for damage model

    Voxel() : x(0), y(0), z(0), type(VoxelType::Empty), health(1.0) {}
    Voxel(int16_t x, int16_t y, int16_t z, VoxelType type, Color color)
        : x(x), y(y), z(z), type(type), color(color), health(1.0) {}

    bool isEmpty() const { return type == VoxelType::Empty || health <= 0.0; }
};

// Voxel model - collection of voxels forming an object
class VoxelModel {
public:
    VoxelModel();

    void addVoxel(const Voxel& voxel);
    void removeVoxel(int16_t x, int16_t y, int16_t z);
    const Voxel* getVoxel(int16_t x, int16_t y, int16_t z) const;

    const std::vector<Voxel>& getVoxels() const { return voxels_; }
    void getBounds(glm::dvec3& min, glm::dvec3& max) const;

    bool loadFromFile(const char* filename);
    bool saveToFile(const char* filename) const;

private:
    std::vector<Voxel> voxels_;
};

} // namespace SpaceGame
