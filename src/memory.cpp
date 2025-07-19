#include "memory.h"

uint16_t read_memory(Memory* mem, uint16_t addr){
    if(addr > MEMORY_SIZE){
        // handle error
        return 0;
    }
    return mem->data[addr];
}

void write_memory(Memory* mem, uint16_t addr, uint16_t val){
    if(addr >= MEMORY_SIZE){
        // handle error
        return;
    }
    mem->data[addr] = val;
}
