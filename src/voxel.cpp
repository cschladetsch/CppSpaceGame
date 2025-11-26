#include "voxel.h"
#include <cmath>
#include <fstream>
#include <algorithm>

namespace SpaceGame {

VoxelModel::VoxelModel() {}

void VoxelModel::addVoxel(const Voxel& voxel) {
    if (!voxel.isEmpty()) {
        voxels_.push_back(voxel);
    }
}

void VoxelModel::removeVoxel(int16_t x, int16_t y, int16_t z) {
    auto it = std::remove_if(voxels_.begin(), voxels_.end(),
        [x, y, z](const Voxel& v) {
            return v.x == x && v.y == y && v.z == z;
        });
    voxels_.erase(it, voxels_.end());
}

const Voxel* VoxelModel::getVoxel(int16_t x, int16_t y, int16_t z) const {
    for (const auto& voxel : voxels_) {
        if (voxel.x == x && voxel.y == y && voxel.z == z) {
            return &voxel;
        }
    }
    return nullptr;
}

void VoxelModel::getBounds(glm::vec3& min, glm::vec3& max) const {
    if (voxels_.empty()) {
        min = max = glm::vec3(0, 0, 0);
        return;
    }

    min.x = max.x = voxels_[0].x;
    min.y = max.y = voxels_[0].y;
    min.z = max.z = voxels_[0].z;

    for (const auto& voxel : voxels_) {
        min.x = std::min(min.x, static_cast<float>(voxel.x));
        min.y = std::min(min.y, static_cast<float>(voxel.y));
        min.z = std.min(min.z, static_cast<float>(voxel.z));
        max.x = std::max(max.x, static_cast<float>(voxel.x));
        max.y = std::max(max.y, static_cast<float>(voxel.y));
        max.z = std::max(max.z, static_cast<float>(voxel.z));
    }
}

bool VoxelModel::loadFromFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    // Simple binary format:
    // uint32_t: number of voxels
    // For each voxel: x, y, z, type, r, g, b, a, health
    uint32_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    voxels_.clear();
    voxels_.reserve(count);

    for (uint32_t i = 0; i < count; ++i) {
        Voxel v;
        file.read(reinterpret_cast<char*>(&v.x), sizeof(v.x));
        file.read(reinterpret_cast<char*>(&v.y), sizeof(v.y));
        file.read(reinterpret_cast<char*>(&v.z), sizeof(v.z));
        file.read(reinterpret_cast<char*>(&v.type), sizeof(v.type));
        file.read(reinterpret_cast<char*>(&v.color.r), sizeof(v.color.r));
        file.read(reinterpret_cast<char*>(&v.color.g), sizeof(v.color.g));
        file.read(reinterpret_cast<char*>(&v.color.b), sizeof(v.color.b));
        file.read(reinterpret_cast<char*>(&v.color.a), sizeof(v.color.a));
        file.read(reinterpret_cast<char*>(&v.health), sizeof(v.health));
        voxels_.push_back(v);
    }

    return true;
}

bool VoxelModel::saveToFile(const char* filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    uint32_t count = static_cast<uint32_t>(voxels_.size());
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& v : voxels_) {
        file.write(reinterpret_cast<const char*>(&v.x), sizeof(v.x));
        file.write(reinterpret_cast<const char*>(&v.y), sizeof(v.y));
        file.write(reinterpret_cast<const char*>(&v.z), sizeof(v.z));
        file.write(reinterpret_cast<const char*>(&v.type), sizeof(v.type));
        file.write(reinterpret_cast<const char*>(&v.color.r), sizeof(v.color.r));
        file.write(reinterpret_cast<const char*>(&v.color.g), sizeof(v.color.g));
        file.write(reinterpret_cast<const char*>(&v.color.b), sizeof(v.color.b));
        file.write(reinterpret_cast<const char*>(&v.color.a), sizeof(v.color.a));
        file.write(reinterpret_cast<const char*>(&v.health), sizeof(v.health));
    }

    return true;
}

} // namespace SpaceGame
