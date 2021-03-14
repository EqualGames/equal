#ifndef EQUAL_APPLICATION_H
#define EQUAL_APPLICATION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Scene.h"
#include "Types.h"

struct Application {
    Scene *scene{nullptr};
    bool running{true};
    Size window_size{800, 600};

    SDL_Window *window{nullptr};
    SDL_Event event{};
    SDL_Renderer *renderer{nullptr};

    Application() = default;

    explicit Application(Scene *scene) : scene(scene) {}

    bool init();

    void set_scene(Scene *scene);

    int run();
};


#endif //EQUAL_APPLICATION_H
