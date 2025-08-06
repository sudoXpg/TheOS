#include "heap.h"

int8_t heap_table_verification(struct heap_table *table, void *start, void *end){
    uint32_t table_size = (uint32_t) (end-start);
    uint32_t total_blocks = table_size/HEAP_BLOCK_SIZE;
    if(table->total!=total_blocks){
        return -1;
    }
    return 0;
}

int8_t heap_check_alignment(void *ptr){
    if((uint32_t)ptr % HEAP_BLOCK_SIZE!=0){
        return -1;
    }
    return 0;
}


int8_t heap_init(struct heap* heap, void* start, void* end, struct heap_table* table){
    if (heap_check_alignment(start) != 0 || heap_check_alignment(end) != 0) {
        return -1;
    }
    memset(heap, 0, sizeof(struct heap));
    heap->start_addr = start;
    heap->table = table;

    if (heap_table_verification(table, start, end) != 0) {
        return -1;
    }
    uint32_t table_size = sizeof(heap_table_entry) * table->total;
    memset(table->entries, HEAP_TABLE_ENTRY_FREE, table_size);
    return 0;
}

uint32_t heap_align(uint32_t size){
    uint32_t modulo = size % HEAP_BLOCK_SIZE;
    if(modulo==0){
        return size;
    }
    return ((size/HEAP_BLOCK_SIZE)+1)*HEAP_BLOCK_SIZE;
}

uint32_t get_start_block(struct heap *heap, uint32_t total_blocks){
    struct heap_table *table = heap->table;
    uint32_t blocks_found = 0;

    for(uint32_t i = 0; i < table->total; i++) {
        if ((table->entries[i] & 0x0F) != HEAP_TABLE_ENTRY_FREE) {
            blocks_found = 0;
            continue;
        }
        blocks_found++;
        if (blocks_found == total_blocks) {
            // Return start block index
            return i - total_blocks + 1;
        }
    }
    return (uint32_t)-1;
}


void *block_to_address(struct heap *heap, uint32_t block){
    return heap->start_addr + (block * HEAP_BLOCK_SIZE);
}

void mark_block_as_taken(struct heap *heap, uint32_t start_block, uint32_t total_blocks){
    uint32_t end_block = (start_block + total_blocks)-1;
    heap_table_entry entry = HEAP_TABLE_ENTRY_TAKEN | HEAP_TABLE_IS_FIRST;
    if(total_blocks>1){
        entry |= HEAP_TABLE_HAS_NEXT;
    }
    
    for (uint32_t i = start_block; i <= end_block; i++) {
        heap_table_entry entry = HEAP_TABLE_ENTRY_TAKEN;

        if (i == start_block) {
            entry |= HEAP_TABLE_IS_FIRST;
        }
        if (i != end_block) {
            entry |= HEAP_TABLE_HAS_NEXT;
        }
        heap->table->entries[i] = entry;
    }

}

void *malloc_blocks(struct heap *heap, uint32_t total_blocks){
    void *addr = 0;
    uint32_t start_block = get_start_block(heap, total_blocks);
    if (start_block == (uint32_t)-1) {
        return 0;
    }
    addr = block_to_address(heap, start_block);
    mark_block_as_taken(heap, start_block, total_blocks);
    return addr;
}

void mark_blocks_free(struct heap *heap, uint32_t starting_block){
    struct heap_table* table = heap->table;
    for (uint32_t  i = starting_block; i < (uint32_t )table->total; i++){
        heap_table_entry entry = table->entries[i];
        table->entries[i] = HEAP_TABLE_ENTRY_FREE;
        if (!(entry & HEAP_TABLE_HAS_NEXT)){
            break;
        }
    }
}

uint32_t address_to_block(struct heap* heap, void* address){
    return ((uintptr_t)address - (uintptr_t)heap->start_addr) / HEAP_BLOCK_SIZE;
}


void* heap_malloc(struct heap* heap, uint32_t size){
    uint32_t aligned_size = heap_align(size);
    uint32_t total_blocks = aligned_size / HEAP_BLOCK_SIZE;
    return malloc_blocks(heap, total_blocks);
}


void heap_free(struct heap* heap, void* ptr){
    mark_blocks_free(heap, address_to_block(heap, ptr));
}