#pragma once

#include <SDL3/SDL.h>
#include "ship.h"
#include "camera.h"

namespace SpaceGame {

class Ship;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(SDL_Window* window);
    void shutdown();

    void clear();
    void present();

    void drawShip(const Ship& ship, const Camera& camera);

    SDL_Renderer* getSDLRenderer() const { return sdlRenderer_; }

private:
    SDL_Renderer* sdlRenderer_;
};

} // namespace SpaceGame
