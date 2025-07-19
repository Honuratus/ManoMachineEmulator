
#include "decoder.h"

// decode the instruction in IR
void decode_instruction(Instruction* i){
    i->I = i->raw >> 15; // msb 

    // get 3-bit opcode from bit 12 to 14
    i->opcode = (i->raw >> 12) & 0x7;  

    // get least 12 bits as addr
    i->addr = i->raw & 0x0FFF;
}


// if i->opcode is 7 then I/O or register instruction | determined by I flag
// else memory instruction | direct or indirect
void determine_type_instruction(Instruction* i){
    if (i->opcode == 7){
        if(i->I == 0) i->type = REG;
        else i->type = IO;
    }
    else{
        if(i->I == 0) i->type = DAM;
        else i->type = IAM;
    }
}