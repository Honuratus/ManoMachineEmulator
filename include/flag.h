#ifndef FLAG_H
#define FLAG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define I_FLAG 0x01
#define S_FLAG 0x02
#define E_FLAG 0x04
#define R_FLAG 0x08
#define IEN_FLAG 0x10
#define FGI_FLAG 0x20
#define FGO_FLAG 0x40

typedef enum{
    I,
    S,
    E,
    R,
    IEN,
    FGI,
    FGO
}FlagType;


void set_flag(uint8_t* flags, FlagType type);
void clear_flag(uint8_t* flags, FlagType type);
int check_flag(uint8_t* flags, FlagType type);

#ifdef __cplusplus
}
#endif

#endif
