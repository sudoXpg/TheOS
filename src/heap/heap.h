#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdint.h>
#include "../memory/mem.h"


#define HEAP_START_ADDRESS      0x01000000               // free mem region - memory map _x86
#define HEAP_TOTAL_SIZE         (104857600)         // 100MB
#define HEAP_BLOCK_SIZE         (4096)                // 2KB
#define HEAP_TOTAL_BLOCKS       (HEAP_TOTAL_SIZE/HEAP_BLOCK_SIZE)
#define HEAP_TABLE_ADDRESS      0x00007E00


#define HEAP_TABLE_ENTRY_TAKEN  0x01
#define HEAP_TABLE_ENTRY_FREE   0x00
#define HEAP_TABLE_HAS_NEXT     0x80
#define HEAP_TABLE_IS_FIRST     0x40

typedef uint8_t heap_table_entry;

struct heap_table{
    heap_table_entry    *entries;
    uint32_t            total;
};

struct heap{
    struct heap_table   *table;
    void                *start_addr;
};

int8_t heap_init(struct heap* heap, void* start, void* end, struct heap_table* table);
void* heap_malloc(struct heap* heap, uint32_t size);
void heap_free(struct heap* heap, void* ptr);

#endif