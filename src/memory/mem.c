#include "mem.h"

void* memset(void *dst, uint8_t c, uint32_t size){

    for(uint32_t i=0;i<size;i++){
        uint8_t *ptr = (uint8_t *)dst;
        ptr[i] = c;
    }
    return dst;
}