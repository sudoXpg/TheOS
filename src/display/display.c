#include "display.h"

uint16_t char_to_terminal(uint8_t c, uint8_t color){
    return (color << 8) | c;
}

void putchar_at_xy(uint8_t c, uint16_t *x, uint16_t *y, uint16_t *screen){
    if(c=='\n'){
        (*y)++;
        (*x)=0;
        return;
    }
    screen[((*y) * VGA_WIDTH) + (*x)] = char_to_terminal(c,0x07);
    (*x)++;
    if(*x>=VGA_WIDTH){
        (*y)++;
        (*x)=0;
    }
}

void disp_init(uint16_t *screen){
    for(int i=0;i<VGA_WIDTH;i++){
        for(int j=0;j<VGA_HEIGHT;j++){
            screen[(j * VGA_WIDTH) + i] = char_to_terminal(' ',0x0F);
        }
    }
}

