#include "rtl.h"


void fetch(Computer* comp){
    // R'T₀:  AR ← PC
    write_register(comp->AR, read_register(comp->PC));
    increment_register(comp->SC);

    // R'T₁:  IR ← M[AR]
    write_register(comp->IR, read_memory(comp->mem, read_register(comp->AR)));

    // PC ← PC + 1
    increment_register(comp->PC);
    
    increment_register(comp->SC);
}

void decode(Computer* comp){
    // Decode instruction
    comp->i->raw = read_register(comp->IR);
    decode_instruction(comp->i);


    // write address to adress register
    write_register(comp->AR, comp->i->addr);
    
    // set the I flag 
    if(comp->i->I) set_flag(comp->flags, I); 
    else clear_flag(comp->flags, I);

    increment_register(comp->SC);
}

// indirect memory access
void indirect(Computer* comp){
    write_register(comp->AR, read_memory(comp->mem, read_register(comp->AR)));
    increment_register(comp->SC);
}

void execute_register_ref(Computer* comp) {
    // clear the sequantial counter
    clear_register(comp->SC);

    // read from instruction register
    uint16_t irValue = read_register(comp->IR);

    // CLA 
    if ((irValue & 0x0800) != 0) { // check r11
        // clear accumulator register
        clear_register(comp->AC);
    }

    // CLE 
    if ((irValue & 0x0400) != 0) { // check r10
        // clear the carry flag
        clear_flag(comp->flags, E);
    }

    // CMA
    if ((irValue & 0x0200) != 0) { // check r9
        // assign it's complement to AC
        uint16_t result = ~(read_register(comp->AC));
        write_register(comp->AC, result);
    }

    // CME 
    if ((irValue & 0x0100) != 0) { // check r8
        // assign it's complement to carry flag
        if (check_flag(comp->flags, E) == 1) clear_flag(comp->flags, E);
        else set_flag(comp->flags, E);
    }

    // CIR 
    if ((irValue & 0x0080) != 0) { // check r7
        //circulor rotate right
        uint16_t acValue = read_register(comp->AC);
        int eVal = check_flag(comp->flags, E);
        int lsb = acValue & 1; // get lsb of acValue

        acValue >>= 1; // shift right
        if (eVal == 1) acValue |= 0x8000; 

        if (lsb == 1) set_flag(comp->flags, E);
        else clear_flag(comp->flags, E);

        write_register(comp->AC, acValue);
    }

    // CIL 
    if ((irValue & 0x0040) != 0) { // check r6
        // circulor rotate left
        uint16_t acValue = read_register(comp->AC);
        int eVal = check_flag(comp->flags, E);
        int msb = (acValue & 0x8000) != 0; // get msb of acValue

        acValue <<= 1; // shift left
        if (eVal == 1) acValue |= 1;

        if (msb == 1) set_flag(comp->flags, E);
        else clear_flag(comp->flags, E);

        write_register(comp->AC, acValue);
    }

    // INC 
    if ((irValue & 0x0020) != 0) { // check r5
        increment_register(comp->AC);
    }

    // SPA 
    if ((irValue & 0x0010) != 0) { // check r4
        int msb = (read_register(comp->AC) & 0x8000);
        if (msb == 0) {
            increment_register(comp->PC);
        }
    }

    // SNA
    if ((irValue & 0x0008) != 0) { // check r3
        int msb = (read_register(comp->AC) & 0x8000);
        if (msb != 0) {
            increment_register(comp->PC);
        }
    }

    // SZA 
    if ((irValue & 0x0004) != 0) { // check r2
        if (read_register(comp->AC) == 0) {
            increment_register(comp->PC);
        }
    }

    // SZE 
    if ((irValue & 0x0002) != 0) { // check r1
        if (check_flag(comp->flags, E) == 0) {
            increment_register(comp->PC);
        }
    }

    // HLT
    if ((irValue & 0x0001) != 0) { // check r0
        clear_flag(comp->flags, S);
    }
}

// execute I/O instructions
void execute_io(Computer* comp) {
    // clear the SC register
    clear_register(comp->SC);

    // get the instruction
    uint16_t irValue = read_register(comp->IR);

    // INP
    if ((irValue & 0x0800) != 0) { // check B11
        
        // get values
        uint16_t acVal = read_register(comp->AC);
        uint16_t inprVal = read_register(comp->INPR);

        // load INPR val to AC
        acVal = (acVal & 0xFF00) | (inprVal & 0x00FF); 
        write_register(comp->AC, acVal);

        clear_flag(comp->flags, FGI);
    }

    // OUT 
    if ((irValue & 0x0400) != 0) { // check B10
        // get value
        uint16_t acVal = read_register(comp->AC);

        // load AC val to OUTR
        write_register(comp->OUTR, acVal & 0x00FF); 
        clear_flag(comp->flags, FGO);
    }

    // SKI 
    if ((irValue & 0x0200) != 0) { // check B9
        // skip on input
        if (check_flag(comp->flags, FGI) == 1) {
            increment_register(comp->PC);
        }
    }

    // SKO 
    if ((irValue & 0x0100) != 0) { // check B8
        // skip on output
        if (check_flag(comp->flags, FGO) == 1) {
            increment_register(comp->PC);
        }
    }

    // ION 
    if ((irValue & 0x0080) != 0) { // check B7
        // set IEN flag to 1
        set_flag(comp->flags, IEN);
    }

    // IOF 
    if ((irValue & 0x0040) != 0) { // check B6
        // set IEN flag to 0
        clear_flag(comp->flags, IEN);
    }
}


/* CPU Instruction Executer */
void execute(Computer* comp) {
    int opcode = comp->i->opcode; // get the opcode 
    int scVal = read_register(comp->SC);

    // memory referance instructions
    if (opcode >= 0 && opcode <= 6) { // 000 - 110 -> 0,1,2,3,4,5,6
        switch (opcode) {
            case 0: // AND
                if (scVal == 4) { // sequantial counter t4
                    write_register(comp->DR, read_memory(comp->mem, read_register(comp->AR)));
                    increment_register(comp->SC);
                } 
                else if (scVal == 5) { // sequantial counter t5
                    uint16_t result = read_register(comp->AC) & read_register(comp->DR);
                    write_register(comp->AC, result);

                    clear_register(comp->SC);
                }
                break;

            case 1: // ADD
                if (scVal == 4) { // sequantial counter t4
                    write_register(comp->DR, read_memory(comp->mem, read_register(comp->AR)));
                    increment_register(comp->SC);
                } 

                else if (scVal == 5) { // sequantial counter t5
                    uint32_t result = (uint32_t)read_register(comp->AC) + read_register(comp->DR);
                    write_register(comp->AC, (uint16_t)result);

                    if (result > 0xFFFF) set_flag(comp->flags, E);
                    else clear_flag(comp->flags, E);

                    clear_register(comp->SC);
                }

                break;

            case 2: // LDA
                if (scVal == 4) { // sequantial counter t4
                    write_register(comp->DR, read_memory(comp->mem, read_register(comp->AR)));
                    increment_register(comp->SC);
                } 
                else if (scVal == 5) { // sequantial counter t5
                    write_register(comp->AC, read_register(comp->DR));
                    clear_register(comp->SC);
                }
                break;

            case 3: // STA
                if (scVal == 4) { // sequantial counter t4
                    write_memory(comp->mem, read_register(comp->AR), read_register(comp->AC));
                    clear_register(comp->SC);
                }
                break;

            case 4: // BUN
                if (scVal == 4) { // sequantial counter t4
                    write_register(comp->PC, read_register(comp->AR));
                    clear_register(comp->SC);
                }
                break;

            case 5: // BSA
                if (scVal == 4) { // sequantial counter t4
                    write_memory(comp->mem, read_register(comp->AR), read_register(comp->PC));
                    increment_register(comp->AR);
                    increment_register(comp->SC);
                } else if (scVal == 5) { // sequantial counter t5
                    write_register(comp->PC, read_register(comp->AR));
                    clear_register(comp->SC);
                }
                break;

            case 6: // ISZ
                if (scVal == 4) { // sequantial counter t4
                    write_register(comp->DR, read_memory(comp->mem, read_register(comp->AR)));
                    increment_register(comp->SC);
                }
                else if (scVal == 5) { // sequantial counter t5
                    increment_register(comp->DR);
                    increment_register(comp->SC);
                } 
                else if (scVal == 6) { // sequantial counter t6
                    write_memory(comp->mem, read_register(comp->AR), read_register(comp->DR));
                    if (read_register(comp->DR) == 0) {
                        increment_register(comp->PC);
                    }
                    clear_register(comp->SC);
                }
                break;
        }
    }

    // register referance or I/O
    // if I flag 1 it's I/O 
    // else it's register referance instructions
    else if (opcode == 7) {

        if (check_flag(comp->flags, I) == 0) { 
            execute_register_ref(comp); 
        } else { 
            execute_io(comp); 
        }

    }
}


void interrupt_service(Computer* comp) {
    write_memory(comp->mem, 0, read_register(comp->PC));

    write_register(comp->PC, 1);

    clear_flag(comp->flags, IEN);
    clear_flag(comp->flags, R);

    clear_register(comp->SC);
}
