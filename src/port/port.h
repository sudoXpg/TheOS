#ifndef PORT_H
#define PORT_H

#include <stddef.h>
#include <stdint.h>

uint8_t in_byte(uint8_t port);
uint16_t in_word(uint8_t port);

void out_byte(uint8_t port, uint8_t val);
void out_word(uint8_t port, uint16_t val);

#endif