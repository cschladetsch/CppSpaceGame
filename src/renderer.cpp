#include "renderer.h"
#include "ship.h"
#include <iostream>
#include <vector>

namespace SpaceGame {

Renderer::Renderer() : sdlRenderer_(nullptr) {}

Renderer::~Renderer() {
    shutdown();
}

bool Renderer::init(SDL_Window* window) {
    sdlRenderer_ = SDL_CreateRenderer(window, NULL);
    if (sdlRenderer_ == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Renderer::shutdown() {
    if (sdlRenderer_) {
        SDL_DestroyRenderer(sdlRenderer_);
        sdlRenderer_ = nullptr;
    }
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(sdlRenderer_, 0, 0, 0, 255);
    SDL_RenderClear(sdlRenderer_);
}

void Renderer::present() {
    SDL_RenderPresent(sdlRenderer_);
}

void Renderer::drawShip(const Ship& ship, const Camera& camera) {
    int width, height;
    SDL_GetRenderOutputSize(sdlRenderer_, &width, &height);

    const VoxelModel* model = ship.getVoxelModel();
    if (!model) {
        return;
    }

    glm::dmat4 modelMatrix = ship.getModelMatrix();

    for (const auto& voxel : model->getVoxels()) {
        double screenX, screenY, depth;
        glm::dvec3 modelPos(voxel.x, voxel.y, voxel.z);
        glm::dvec4 worldPos4 = modelMatrix * glm::dvec4(modelPos, 1.0);
        glm::dvec3 worldPos(worldPos4);

        if (camera.worldToScreen(worldPos, width, height, screenX, screenY, depth)) {
            if (depth > 0.0 && depth < 1.0) { // Check if within NDC depth range
                // Calculate the size of the voxel on screen
                glm::dvec3 modelPosX = modelPos + glm::dvec3(0.5, 0.0, 0.0);
                glm::dvec4 worldPosX4 = modelMatrix * glm::dvec4(modelPosX, 1.0);
                glm::dvec3 worldPosX(worldPosX4);
                
                double screenX2, screenY2, depth2;
                if (camera.worldToScreen(worldPosX, width, height, screenX2, screenY2, depth2)) {
                    double pixelSize = std::abs(screenX2 - screenX) * 2.0;

                    SDL_FRect rect = {
                        (float)(screenX - pixelSize / 2.0), 
                        (float)(screenY - pixelSize / 2.0), 
                        (float)pixelSize, 
                        (float)pixelSize
                    };
                    SDL_SetRenderDrawColor(sdlRenderer_, voxel.color.r, voxel.color.g, voxel.color.b, voxel.color.a);
                    SDL_RenderFillRect(sdlRenderer_, &rect);
                }
            }
        }
    }
}

} // namespace SpaceGame