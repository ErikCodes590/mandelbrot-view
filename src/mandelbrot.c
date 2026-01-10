#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Function used to check if pixel is in mandelbrot set
size_t checkpixel(double r, double i, int iter) {
    double currentR = 0;
    double currentI = 0;

    for (int j = 0; j < iter; ++j) {
        // Square the complex number
        double tmpR = (currentR * currentR - currentI * currentI + r);
        double tmpI = (2 * currentR * currentI + i);

        // Check if pixel is in grid
        if (tmpR * tmpR > 4 || tmpI * tmpI > 1) {
            return j;
        } else {
            currentR = tmpR;
            currentI = tmpI;
        }
    }

    return iter;
}

// This calculates the complex number of the pixel
void getVar(int w, int h, double* r, double* i, size_t pixel, double camX,
            double camY, size_t scale) {
    // Get the pixel with the display settings
    int px = ((pixel % w) - (w / 2));
    int py = ((h / 2) - (pixel / w));

    // Apply scale and cam params
    *r = ((double)px / scale + camX);
    *i = ((double)py / scale + camY);
}

// This calculates the mandelbrot set with no color
size_t* mandelbrot(int w, int h, int iter, double camX, double camY,
                   size_t scale) {
    // res is the "screen"
    size_t* res = malloc(w * h * sizeof(size_t));

    // Iterate thru pixels of the screen
    for (int j = 0; j < (w * h); ++j) {
        double r = 0, i = 0;
        getVar(w, h, &r, &i, j, camX, camY, scale);

        res[j] = checkpixel(r, i, iter);
    }

    return res;
}

// A very simple function that calculates the color of the pixel
uint32_t px_col(size_t px, int iter) {
    if (px == iter) {
        // Black if iter == max_iter
        return 0x000000FF;
    } else {
        px *= 2000;
        return px | 0x000000FF;
    }
}

// This function appies color to the mandelbrot set
uint32_t* to_col(size_t* mandelbrot, int w, int h, int iter) {
    // res is the colored "screen"
    uint32_t* res = malloc(w * h * sizeof(uint32_t));

    // Apply color
    for (int i = 0; i < (w * h); ++i) {
        res[i] = px_col(mandelbrot[i], iter);
    }

    return res;
}

// This function calculates the mandelbrot set with colors
uint32_t* mandelbrot_color_pixels_generate(int w, int h, int iter, double camX,
                                           double camY, size_t scale) {
    // Mandel is the raw mandelbrot set
    size_t* mandel = mandelbrot(w, h, iter, camX, camY, scale);

    // Colorize it
    uint32_t* res = to_col(mandel, w, h, iter);

    free(mandel);
    return res;
}
