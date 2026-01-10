#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdio.h>

#include "../inc/mandelbrot.h"
#include "../inc/window.h"

// Width and height
const int WIDTH = 1200;
const int HEIGHT = 600;

int main(int argc, char** argv) {
    // Create window
    Window window;
    initWindow(&window, "test", WIDTH, HEIGHT, 0);

    window.pixels = mandelbrot_color_pixels_generate(
        WIDTH, HEIGHT, 1000, 0, 0,
        HEIGHT / 2);  // width height max_iter camX camY scale

    // Variables used for calculating FPS
    int FPS;
    int frameCount = 0;
    size_t lastFrame = SDL_GetTicks();
    size_t seconds = SDL_GetTicks() / 1000;

    // Main loop
    bool running = true;
    while (running) {
        // Check for quitting
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        renderPixels(&window);

        // Calculate FPS
        size_t ticks = SDL_GetTicks();
        if (ticks - (seconds * 1000) >= 1000) {
            FPS = frameCount;
            frameCount = 0;
            seconds++;
            printf("FPS: %d\n", FPS);
        }

        // Delay
        uint32_t delay = (17 - (SDL_GetTicks() - lastFrame));
        if (delay > 0) {
            SDL_Delay(delay);
        }

        frameCount++;
        lastFrame = SDL_GetTicks();
    }

    SDL_DestroyRenderer(window.renderer);
    SDL_DestroyWindow(window.window);
    SDL_Quit();
    return 0;
}
