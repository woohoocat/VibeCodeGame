#include "Game.h"
#include <iostream>

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr) {
    // Initial player position and size
    player.x = 100.0f;
    player.y = 100.0f;
    player.w = 50.0f;
    player.h = 50.0f;
    playerSpeed = 0.5f; // Pixel per frame (we will improve this later)
}

Game::~Game() {}

bool Game::init(const char* title, int width, int height, bool fullscreen) {
    if (!SDL_Init(SDL_INIT_VIDEO)) return false;

    Uint32 flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    if (!SDL_CreateWindowAndRenderer(title, width, height, flags, &window, &renderer)) {
        return false;
    }

    isRunning = true;
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            isRunning = false;
        }
    }

    // Get keyboard state for smooth movement
    const bool* keys = SDL_GetKeyboardState(nullptr);
    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP])    player.y -= playerSpeed;
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN])  player.y += playerSpeed;
    if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])  player.x -= playerSpeed;
    if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) player.x += playerSpeed;
}

void Game::update() {
    // Basic collision with window boundaries
    if (player.x < 0) player.x = 0;
    if (player.y < 0) player.y = 0;
    if (player.x + player.w > 800) player.x = 800 - player.w;
    if (player.y + player.h > 600) player.y = 600 - player.h;
}

void Game::render() {
    // Clear screen with dark grey
    SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
    SDL_RenderClear(renderer);

    // Draw Player (Green Square)
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &player);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}