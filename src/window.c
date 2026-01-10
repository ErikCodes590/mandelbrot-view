#include "../inc/window.h"

#include <SDL3/SDL.h>
#include <stdio.h>

void initWindow(Window* self, const char* title, int w, int h,
                SDL_WindowFlags flags) {
    // Init SDL3
    if (!SDL_Init(0)) {
        printf("%s", "Init failed!");
        printf("%s\n", SDL_GetError());
        return;
    }

    // Create window, renderer and texture
    self->window = SDL_CreateWindow(title, w, h, flags);
    if (!self->window) {
        printf("%s", "Window init failed!\n");
        printf("%s\n", SDL_GetError());
        return;
    }

    self->renderer = SDL_CreateRenderer(self->window, NULL);
    if (!self->renderer) {
        printf("%s", "Renderer init failed!\n");
        printf("%s\n", SDL_GetError());
        return;
    }

    self->texture = SDL_CreateTexture(self->renderer, SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_STREAMING, w, h);

    self->width = w;
    self->height = h;
}

// Render a list of pixels stored in self->pixels
void renderPixels(Window* self) {
    SDL_UpdateTexture(self->texture, NULL, self->pixels,
                      self->width * sizeof(uint32_t));

    SDL_RenderClear(self->renderer);
    SDL_RenderTexture(self->renderer, self->texture, NULL, NULL);
    SDL_RenderPresent(self->renderer);
}
