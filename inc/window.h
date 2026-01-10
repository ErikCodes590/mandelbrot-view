#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>
#include <stdint.h>

// All thing needed for rendering a list of colors
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    uint32_t* pixels;

    int width, height;
} Window;

void initWindow(Window* self, const char* title, int w, int h, SDL_WindowFlags);

void renderPixels(Window* self);

#endif  // !WINDOW_H
