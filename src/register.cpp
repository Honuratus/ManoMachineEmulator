#include "register.h"

void write_register(Register* reg,  uint16_t val){
    reg->value = val;
}
uint16_t read_register(Register* reg){
    return reg->value;
}

void clear_register(Register* reg){
    reg->value = 0;
}

void increment_register(Register* reg){
    reg->value++;
}