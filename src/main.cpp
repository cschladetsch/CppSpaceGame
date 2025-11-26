#include <SDL3/SDL.h>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "renderer.h"
#include "camera.h"
#include "voxel.h"
#include "ship.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        std::cerr << "Platform: " << SDL_GetPlatform() << std::endl;
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("SpaceGame", 800, 600, SDL_WINDOW_RESIZABLE);
    if (win == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SpaceGame::Renderer renderer;
    if (!renderer.init(win)) {
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SpaceGame::Camera camera;
    camera.setPosition(glm::dvec3(0, 10, -30));
    

    SpaceGame::VoxelModel shipModel;
    if (!shipModel.loadFromFile("data/ship.bin")) {
        std::cerr << "Error loading ship.bin" << std::endl;
        renderer.shutdown();
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SpaceGame::Ship playerShip;
    playerShip.setVoxelModel(&shipModel);
    playerShip.setPosition(glm::dvec3(0, 0, 20));

    camera.lookAt(playerShip.getPosition());

    bool quit = false;
    SDL_Event e;

    const int TARGET_FPS = 60;
    const double frameDelay = 1000.0 / TARGET_FPS;

    Uint64 lastTime = SDL_GetTicks();
    double deltaTime = 0;

    while (!quit) {
        Uint64 frameStart = SDL_GetTicks();
        deltaTime = (frameStart - lastTime) / 1000.0;
        lastTime = frameStart;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (e.type == SDL_EVENT_KEY_DOWN) {
                switch (e.key.scancode) {
                    case SDL_SCANCODE_W:
                        camera.moveForward(10.0 * deltaTime);
                        break;
                    case SDL_SCANCODE_S:
                        camera.moveForward(-10.0 * deltaTime);
                        break;
                    case SDL_SCANCODE_A:
                        camera.moveRight(-10.0 * deltaTime);
                        break;
                    case SDL_SCANCODE_D:
                        camera.moveRight(10.0 * deltaTime);
                        break;
                    case SDL_SCANCODE_UP:
                        camera.rotate(1.0 * deltaTime, 0, 0);
                        break;
                    case SDL_SCANCODE_DOWN:
                        camera.rotate(-1.0 * deltaTime, 0, 0);
                        break;
                    case SDL_SCANCODE_LEFT:
                        camera.rotate(0, 1.0 * deltaTime, 0);
                        break;
                    case SDL_SCANCODE_RIGHT:
                        camera.rotate(0, -1.0 * deltaTime, 0);
                        break;
                }
            }
        }

        // Rotate the ship
        glm::dvec3 rotation = playerShip.getRotation();
        rotation.y += 0.5 * deltaTime;
        playerShip.setRotation(rotation);

        playerShip.update(deltaTime);

        renderer.clear();
        renderer.drawShip(playerShip, camera);
        renderer.present();

        Uint64 frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay((Uint32)(frameDelay - frameTime));
        }
    }

    renderer.shutdown();
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
