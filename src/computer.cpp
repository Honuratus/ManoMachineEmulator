#include "computer.h"

#include <stdlib.h>

void init_computer(Computer* comp){
    comp->AC = (Register*)malloc(sizeof(Register));
    comp->AR = (Register*)malloc(sizeof(Register));
    comp->DR = (Register*)malloc(sizeof(Register));
    comp->INPR = (Register*)malloc(sizeof(Register));
    comp->IR = (Register*)malloc(sizeof(Register));
    comp->OUTR = (Register*)malloc(sizeof(Register));
    comp->PC = (Register*)malloc(sizeof(Register));
    comp->SC = (Register*)malloc(sizeof(Register));
    comp->TR = (Register*)malloc(sizeof(Register));
    comp->i = (Instruction*)malloc(sizeof(Instruction));
    
    comp->mem = (Memory*)malloc(sizeof(Memory));    
    
    *(comp->flags) = 0;
    clear_register(comp->AC);
    clear_register(comp->AR);
    clear_register(comp->DR);
    clear_register(comp->INPR);
    clear_register(comp->OUTR);
    clear_register(comp->IR);
    clear_register(comp->SC);
    clear_register(comp->PC);
    clear_register(comp->TR);

    set_flag(comp->flags, S);
}

void free_computer(Computer* comp){
    free(comp->AC);
    free(comp->AR);
    free(comp->DR);
    free(comp->INPR);
    free(comp->IR);
    free(comp->OUTR);
    free(comp->PC);
    free(comp->SC);
    free(comp->TR);
    free(comp->mem);
    free(comp->i);
}
