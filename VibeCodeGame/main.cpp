#include "Game.h"

// Pointer to our Game object
Game* game = nullptr;

int main(int argc, char* argv[]) {

    game = new Game();

    // Initialize the game with: Title, Width, Height, Fullscreen mode
    // We use 800x600 as a standard starting resolution
    if (game->init("My First SDL3 Game", 800, 600, true)) {

        // The Game Loop
        while (game->running()) {

            game->handleEvents(); // Listen for input (Keyboard, Window X button)
            game->update();       // Update logic (Movement, Collisions)
            game->render();       // Draw everything to the screen

        }
    }
    else {
        // If initialization fails (e.g., SDL3.dll missing or GPU issues)
        return -1;
    }

    // Clean up memory and SDL subsystems
    game->clean();
    delete game;

    return 0;
}