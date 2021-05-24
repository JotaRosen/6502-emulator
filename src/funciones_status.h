#ifndef FUNCIONES_STATUS_H
#define FUNCIONES_STATUS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {CARRY, ZERO , INTERRUPT_DISABLE , DECIMAL , BREAK ,OVERFLOW , NEGATIVE } flag_t;

void set_status(uint8_t *reg, flag_t flag, bool status);
bool get_status(uint8_t reg, flag_t flag);
void set_overflow(uint8_t *reg, uint8_t a, uint8_t b, uint8_t res);
void rotate_right(uint16_t *res);
void rotate_left(uint16_t *res);
#endif
