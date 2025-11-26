#pragma once

#include "entity.h"
#include "voxel.h"

namespace SpaceGame {

class Ship : public Entity {
public:
    Ship();
    ~Ship();

    void setVoxelModel(VoxelModel* model) { model_ = model; }
    const VoxelModel* getVoxelModel() const { return model_; }

    void update(double deltaTime) override;
    void draw() override;

private:
    VoxelModel* model_;
};

} // namespace SpaceGame
