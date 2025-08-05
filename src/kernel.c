#include "kernel.h"
#include "display/display.h"
#include "idt/idt.h"


uint16_t *videomem = (uint16_t *)VGA_ADDRESS;
uint16_t videomem_x = 0;
uint16_t videomem_y = 0;

void print(const char *str){
    for(int i=0;str[i]!='\0';i++){
        putchar_at_xy(str[i], &videomem_x,&videomem_y,videomem);
    }
}

void kernel_init(void){
    disp_init(videomem);
    print("Welcome to TheOS\n-v0.01");

    idt_init();


}