#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#define MEMORY_SIZE 4096

typedef struct {
    uint16_t data[MEMORY_SIZE];
}Memory;


uint16_t read_memory(Memory* mem, uint16_t addr);
void write_memory(Memory* mem, uint16_t addr, uint16_t val);

#endif