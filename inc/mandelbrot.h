#ifndef MANDELBROT_H

#define MANDELBROT_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

uint32_t* mandelbrot_color_pixels_generate(int width, int height,
                                           size_t max_iter, double camX,
                                           double camY, ssize_t scale);

#endif  // !MANDELBROT_H
