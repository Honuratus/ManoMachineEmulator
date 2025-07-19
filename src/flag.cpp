#include "flag.h"

uint8_t get_mask_from_type(FlagType type) {
    switch (type) {
        case I:   return I_FLAG;
        case S:   return S_FLAG;
        case E:   return E_FLAG;
        case R:   return R_FLAG;
        case IEN: return IEN_FLAG;
        case FGI: return FGI_FLAG;
        case FGO: return FGO_FLAG;
        default:  return 0; 
    }
}

void set_flag(uint8_t* flags, FlagType type) {
    uint8_t mask = get_mask_from_type(type);
    *flags |= mask;
}

void clear_flag(uint8_t* flags, FlagType type) {
    uint8_t mask = get_mask_from_type(type);
    *flags &= ~mask;
}

int check_flag(uint8_t flags, FlagType type) {
    uint8_t mask = get_mask_from_type(type);
    return (flags & mask) != 0;
}