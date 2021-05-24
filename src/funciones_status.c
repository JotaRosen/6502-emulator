#include "funciones_status.h"

#define MASK_BIT_7 0x80
#define MASK_BIT_CARRY 0x01

const uint8_t  mask_array[] = {0x01, 0x02, 0x04, 0x08, 0x10,0x40,0x80};
void set_status(uint8_t *reg, flag_t flag, bool status){
    if(!status) *reg &= ~mask_array[flag];
    else *reg |= mask_array[flag];
}

bool get_status(uint8_t reg, flag_t flag){
    return reg & mask_array[flag];
}
void set_overflow(uint8_t *reg, uint8_t a, uint8_t b, uint8_t res){

    set_status(reg,OVERFLOW, ((a < 128 && b < 128) && res > 127) || ((a > 127 && b > 127) && res < 128));
}
void rotate_left(uint16_t *res){
    uint8_t LSB = *res&0x100 ? 0x01 : 0x00;
    *res <<=1;
    *res |= LSB;

}

void rotate_right(uint16_t *res){
    uint16_t MSB = *res&0x01? 0x100 : 0x00;
    *res >>= 1;
    *res |= MSB;
}