#ifndef COMPUTER_H
#define COMPUTER_H

#include "decoder.h"
#include "memory.h"
#include "register.h"
#include "flag.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t Flags;

typedef struct{
    Memory* mem;
    Register* IR;
    Register* AR;
    Register* PC;
    Register* AC;
    Register* DR;
    Register* TR;
    Register* INPR;
    Register* OUTR;
    Register* SC;
    Flags* flags;
    Instruction* i;
}Computer;

void init_computer(Computer* comp);
void free_computer(Computer* comp);
void load_program(Computer* comp);


#ifdef __cplusplus
}
#endif

#endif