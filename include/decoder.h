#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
    IAM, // indirect access memory instruction type
    DAM, // direct access memory instruction type
    REG, // register instruction type
    IO // input / output instruction type
}InstructionType;

typedef struct{
    uint16_t raw; // raw instruction
    uint8_t I; // 1 bit
    uint8_t opcode; // 3 bit
    uint16_t addr; // address
    InstructionType type;
}Instruction;


void decode_instruction(Instruction* i);
void determine_type_instruction(Instruction* i);

#ifdef __cplusplus
}
#endif

#endif