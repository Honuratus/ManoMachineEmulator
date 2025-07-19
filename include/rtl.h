#ifndef RTL_H
#define RTL_H

#include "computer.h"


void fetch(Computer* comp);
void decode(Computer* comp);
void indirect(Computer* comp);
void execute(Computer* comp);
void interrupt_service(Computer* comp);

#endif