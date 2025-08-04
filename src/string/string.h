#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>

uint32_t strlen(const char *str);
uint8_t  streq (const char *s1, const char *s2);
void     memcpy(char *dest, const char *src, uint32_t len);

#endif