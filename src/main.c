#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "../inc/mandelbrot.h"
#include "../inc/window.h"

// Width and height
const size_t WIDTH = 1200;
const size_t HEIGHT = 600;

int main(int argc, char** argv) {
    // Create window
    Window window;
    initWindow(&window, "Mandelbrot viewer", WIDTH, HEIGHT, 0);

    size_t max_iter = 1000;
    double camX = 0, camY = 0;
    size_t scale = HEIGHT / 2;

    window.pixels = mandelbrot_color_pixels_generate(WIDTH, HEIGHT, max_iter,
                                                     camX, camY, scale);

    // Variables used for calculating FPS
    int FPS;
    int frameCount = 0;
    size_t lastFrame = SDL_GetTicks();
    size_t seconds = SDL_GetTicks() / 1000;

    // Main loop
    bool running = true;
    bool new_needed = false;  // True if new set needed
    while (running) {
        // Check for quitting
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // Get keystate
        const bool* keystate = SDL_GetKeyboardState(NULL);

        // Live controls
        if (keystate[SDL_SCANCODE_Q]) {
            scale *= 2;
            new_needed = true;
        } else if (keystate[SDL_SCANCODE_W]) {
            camY += (double)HEIGHT / (scale * 4);
            new_needed = true;
        } else if (keystate[SDL_SCANCODE_E]) {
            scale /= 2;
            new_needed = true;
        } else if (keystate[SDL_SCANCODE_A]) {
            camX -= (double)HEIGHT / (scale * 4);
            new_needed = true;
        } else if (keystate[SDL_SCANCODE_S]) {
            camY -= (double)HEIGHT / (scale * 4);
            new_needed = true;
        } else if (keystate[SDL_SCANCODE_D]) {
            camX += (double)HEIGHT / (scale * 4);
            new_needed = true;
        }

        // New set if needed
        if (new_needed) {
            window.pixels = mandelbrot_color_pixels_generate(
                WIDTH, HEIGHT, max_iter, camX, camY, scale);
            new_needed = false;
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
        ssize_t delay = (17 - (SDL_GetTicks() - lastFrame));
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
