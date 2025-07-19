#include <stdio.h>
#include "rtl.h" 

// program to execute CIR instruction and save it to memory
void load_program(Computer* comp) {

    // setting PC
    comp->PC->value = 0x100;

    // program
    comp->mem->data[0x100] = 0x2106;

    comp->mem->data[0x101] = 0x7400;

    comp->mem->data[0x102] = 0x7100;

    comp->mem->data[0x103] = 0x7080;

    comp->mem->data[0x104] = 0x3007; // save to memory adress 7

    comp->mem->data[0x105] = 0x7001;

    // data
    comp->mem->data[0x106] = 0xA001; 
}

void show_hardware(Computer* comp) {
    printf("PC: %04X  AC: %04X  IR: %04X  AR: %04X  DR: %04X  E: %d  I: %d S: %d R: %d SC: %04X M[AR]: %d\n",
            read_register(comp->PC),
            read_register(comp->AC),
            read_register(comp->IR),
            read_register(comp->AR),
            read_register(comp->DR),
            check_flag(*comp->flags, E),
            check_flag(*comp->flags, I),
            check_flag(*comp->flags, S),
            check_flag(*comp->flags, R),
            read_register(comp->SC)),
            read_memory(comp->mem, read_register(comp->AR));
}

int main() {
    // init computer
    Computer computer;
    init_computer(&computer);

    load_program(&computer);


    printf("Computer Emulation Start:\n");

    // flow of the instruction cycle
    while (check_flag(*computer.flags, S) == 1) {

        show_hardware(&computer);

        // fetch and decode
        if (check_flag(*computer.flags, R) == 1) {
            interrupt_service(&computer);
        } 
        else {
            fetch(&computer);
        }

        decode(&computer);

        
        // check for indirect memory acces else increment the sequantial counter 
        if (computer.i->opcode != 7 && check_flag(*computer.flags, I) == 1) {
            (&computer);
        }
        else increment_register(computer.SC);

        // execute the instruction
        while(read_register(computer.SC) != 0) execute(&computer);


        // check the interrupt request
        if (check_flag(*computer.flags, IEN) == 1 &&
           (check_flag(*computer.flags, FGI) == 1 || check_flag(*computer.flags, FGO) == 1))
        {
            set_flag(computer.flags, R);
        }
    }

    show_hardware(&computer);
    printf("HLT Instruction Encountered.\n");
    printf("Final result at memory address 7: %d\n", computer.mem->data[7]);

    free_computer(&computer);
    return 0;
}