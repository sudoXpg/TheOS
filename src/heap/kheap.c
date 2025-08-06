#include "kheap.h"
#include "heap.h"
#include "../kernel.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;

void kheap_init(){
    uint32_t total_table_entries = HEAP_TOTAL_SIZE / HEAP_BLOCK_SIZE;
    kernel_heap_table.entries = (heap_table_entry*)(HEAP_TABLE_ADDRESS);
    kernel_heap_table.total = total_table_entries;

    void* end = (void*)(HEAP_START_ADDRESS + HEAP_TOTAL_SIZE);
    uint32_t res = heap_init(&kernel_heap, (void*)(HEAP_START_ADDRESS), end, &kernel_heap_table);
    if (res < 0){
        print("Failed to create heap\n");
    }

}

void* kmalloc(size_t size){
    return heap_malloc(&kernel_heap, size);
}

void kfree(void* ptr){
    heap_free(&kernel_heap, ptr);
}