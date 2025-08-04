#ifndef DISPLAY_H
#define DISPLAY_H

#define VGA_HEIGHT  25
#define VGA_WIDTH   80
#define VGA_ADDRESS 0xB8000

#include <stddef.h>
#include <stdint.h>


void disp_init(uint16_t *screen);
uint16_t char_to_terminal(uint8_t c, uint8_t color);
void putchar_at_xy(uint8_t c, uint16_t *x, uint16_t *y, uint16_t *screen);


#endif