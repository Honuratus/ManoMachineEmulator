#ifndef RTL_H
#define RTL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "computer.h"


void fetch(Computer* comp);
void decode(Computer* comp);
void indirect(Computer* comp);
void execute(Computer* comp);
void interrupt_service(Computer* comp);

#ifdef __cplusplus
}
#endif

#endif