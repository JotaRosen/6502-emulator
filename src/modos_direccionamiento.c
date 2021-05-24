#include "modos_direccionamiento.h"

///---DIRECCIONAMIENTOS NO INDEXADOS Y NO EN MEMORIA------
void direccionamiento_implicito(mos6502_t *micro, instruccion_t *i){
    return;
}
void direccionamiento_acumulador(mos6502_t *micro, instruccion_t *i){
    (i->m) = &micro->a;
}
void direccionamiento_inmediato(mos6502_t *micro, instruccion_t *i) {
    i->direccion = micro->pc;
    micro->pc++;
    i->m = &micro->mem[i->direccion];
}
///---DIRECCIONAMIENTOS NO INDEXADOS Y EN MEMORIA-----
void direccionamiento_absoluto(mos6502_t *micro, instruccion_t *i){
    i->direccion = 0x0000;
    i->direccion |= micro->mem[micro->pc + 1];
    i->direccion<<=8;
    i->direccion |= micro->mem[micro->pc];
    i->m = &micro->mem[i->direccion];
    micro->pc += 2;
}

void direccionamiento_relativo(mos6502_t *micro, instruccion_t *i) {
    i->direccion = micro->pc;
    i->m = &micro->mem[i->direccion];
    micro->pc++;
}

void direccionamiento_pagina_cero(mos6502_t *micro, instruccion_t *i){
    i->direccion = 0x0000;
    micro->pc++;
    i->direccion += micro->mem[micro->pc-1];
    i->m = &micro->mem[i->direccion];
}
void direccionamiento_indirecto(mos6502_t *micro, instruccion_t *i){
    uint16_t aux = 0x0000;
    i->direccion = 0x0000;
    aux |= micro->mem[micro->pc + 1];
    aux<<=8;
    aux |= micro->mem[micro->pc];
    micro->pc+=2;
    i->direccion |= micro->mem[aux + 1];
    i->direccion<<=8;
    i->direccion |= micro->mem[aux];
    (i->m) = &micro->mem[i->direccion];;

}
///----DIRECCIONAMIENTOS INDEXADOS-----
void direccionamiento_abs_x(mos6502_t *micro, instruccion_t *i){
    i->direccion = 0x0000;
    i->direccion += micro->mem[micro->pc + 1];
    i->direccion <<= 8;
    i->direccion += micro->mem[micro->pc];
    i->direccion += micro->x;
    i->m = &micro->mem[i->direccion];
    micro->pc += 2;
}

void direccionamiento_abs_y(mos6502_t *micro, instruccion_t *i) {
    i->direccion = 0x0000;
    i->direccion += micro->mem[micro->pc + 1];
    i->direccion <<= 8;
    i->direccion += micro->mem[micro->pc];
    i->direccion += micro->y;
    i->m = &(micro->mem[i->direccion]);
    micro->pc += 2;
}

void direccionamiento_pag_cero_x(mos6502_t *micro, instruccion_t *i){
    i->direccion = 0x0000;
    micro->pc ++;
    i->direccion += micro->mem[micro->pc-1];
    i->direccion += micro->x;
    i->direccion &= 0x00FF; //descarto un posible  carry
    i->m = &micro->mem[i->direccion];
}

void direccionamiento_pag_cero_y(mos6502_t *micro, instruccion_t *i){
    i->direccion = 0x0000;
    micro->pc ++;
    i->direccion += micro->mem[micro->pc-1];
    i->direccion += micro->y;
    i->direccion &= 0x00FF; //descarto un posible  carry
    i->m = &micro->mem[i->direccion];
}

void direccionamiento_indirecto_x(mos6502_t *micro, instruccion_t *i){
    uint16_t  aux = 0x0000;
    i->direccion = 0x0000;
    micro->pc ++;
    aux += micro->mem[micro->pc -1];
    aux += micro->x;
    aux &= 0x00FF;
    i->direccion += micro->mem[aux + 1];
    i->direccion <<= 8;
    i->direccion += micro->mem[aux];
    i->m = &micro->mem[i->direccion];

}
void direccionamiento_indirecto_y(mos6502_t *micro, instruccion_t *i){
    uint16_t  aux = 0x0000;
    i->direccion = 0x0000;
    micro->pc ++;
    aux += micro->mem[micro->pc -1];
    i->direccion += micro->mem[aux + 1];
    i->direccion<<=8;
    i->direccion += micro->mem[aux];
    i->direccion += micro->y;
    i->m = &micro->mem[i->direccion];

}



