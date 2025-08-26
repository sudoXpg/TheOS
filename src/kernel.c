#include "kernel.h"
#include "display/display.h"
#include "idt/idt.h"
#include "port/port.h"
#include "heap/kheap.h"
#include "paging/paging.h"


uint16_t *videomem = (uint16_t *)VGA_ADDRESS;
uint16_t videomem_x = 0;
uint16_t videomem_y = 0;

static struct paging_4gb_chunk *kernel_chunk = 0;

void print(const char *str){
    for(int i=0;str[i]!='\0';i++){
        putchar_at_xy(str[i], &videomem_x,&videomem_y,videomem);
    }
}

void kernel_init(void){
    disp_init(videomem);
    print("Welcome to TheOS\n-v0.01");

    idt_init();
    kheap_init();

    kernel_chunk = new_4gb_chunk(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));
    enable_paging();


    enable_interrupts();
}