#ifndef MANDELBROT_H

#define MANDELBROT_H

#include <stddef.h>
#include <stdint.h>

uint32_t* mandelbrot_color_pixels_generate(int width, int height, int max_iter,
                                           double camX, double camY,
                                           size_t scale);

#endif  // !MANDELBROT_H
