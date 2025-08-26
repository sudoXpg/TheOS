#include "paging.h"

static uint32_t *current_directory = 0;

void paging_load_directory(uint32_t *directory);

struct paging_4gb_chunk *new_4gb_chunk(uint8_t flags){
    uint32_t *directory = kmalloc(sizeof(uint32_t *) * PAGING_TOTAL_ENTRIES_PER_TABLE); // number of page table directories
    memset(directory, 0x00, sizeof(uint32_t *) * PAGING_TOTAL_ENTRIES_PER_TABLE);
    int offset = 0;
    for(int i=0; i<PAGING_TOTAL_ENTRIES_PER_TABLE; i++){
        uint32_t * entry = kmalloc(sizeof(uint32_t *) * PAGING_TOTAL_ENTRIES_PER_TABLE);
        memset(entry, 0x00, sizeof(uint32_t *) * PAGING_TOTAL_ENTRIES_PER_TABLE);

        for(int j=0; j<PAGING_TOTAL_ENTRIES_PER_TABLE; j++){
            entry[j] = (offset + (j*PAGING_PAGE_SIZE)) | flags ;
        }
        offset += (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE);
        directory[i] = (uint32_t) entry | flags | PAGING_IS_WRITEABLE; // only 20 bits for address since its 4096 alogned so the lower 12 will always be zero
    }

    struct paging_4gb_chunk *chunk_4gb = kmalloc(sizeof(struct paging_4gb_chunk));
    memset(chunk_4gb, 0x00, sizeof(struct paging_4gb_chunk));
    chunk_4gb->directory_entry = directory;
    return chunk_4gb;
}

void paging_switch(uint32_t *directory){
    paging_load_directory(directory);
    current_directory = directory;
}

uint32_t *paging_4gb_chunk_get_directory(struct paging_4gb_chunk *chunk){
    return chunk->directory_entry;
}