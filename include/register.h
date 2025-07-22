#ifndef REGISTER_H
#define REGISTER_H

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    uint16_t bit_width;
    uint16_t value;
}Register;

void write_register(Register* reg,  uint16_t val);

uint16_t read_register(Register* reg);

void clear_register(Register* reg);

void increment_register(Register* reg);

#ifdef __cplusplus
}
#endif

#endif