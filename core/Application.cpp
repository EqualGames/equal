#include "Application.h"

bool Application::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    this->window = SDL_CreateWindow(
            "Equal Games",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            this->window_size.w, this->window_size.h,
            SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (this->renderer == nullptr) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

void Application::set_scene(Scene *p_scene) {
    this->scene = p_scene;
    this->scene->app = this;
    this->scene->init(this->renderer);
}

int Application::run() {
    if (this->scene == nullptr) {
        printf("Invalid scene");
        return 1;
    }

    while (this->running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT ||
                event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) { this->running = false; }
        }

        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
        SDL_RenderClear(this->renderer);

        scene->update(this->renderer, this->event);

        SDL_RenderPresent(this->renderer);
    }

    this->scene = nullptr;
    this->renderer = nullptr;
    SDL_DestroyWindow(window);
    this->window = nullptr;

    SDL_Quit();

    return 0;
}
