#include "string.h"

uint32_t strlen(const char *str){
    uint32_t len=0;
    for(uint32_t i=0;str[i]!='\0';i++){
        len++;
    }
    return len;
}


uint8_t  streq (const char *s1, const char *s2){
    uint32_t l1, l2;
    l1=strlen(s1);
    l2=strlen(s2);
    if(l1!=l2)
        return 0;
    else{
        for(uint32_t i=0;i<l1;i++){
            if(s1[i]!=s2[i])
                return 0;
        }
    }
    return 1;
}

void     memcpy(char *dest, const char *src, uint32_t len){
    for(uint32_t i=0;i<len;i++){
        dest[i] = src [i];
    }
}
