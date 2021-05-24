#ifndef MODOS_DIRECCIONAMIENTO_H
#define MODOS_DIRECCIONAMIENTO_H

#include "utils.h"

///---DIRECCIONAMIENTOS NO INDEXADOS Y NO EN MEMORIA-----
void direccionamiento_implicito(mos6502_t *micro, instruccion_t *i);
void direccionamiento_acumulador(mos6502_t *micro, instruccion_t *i);
void direccionamiento_inmediato(mos6502_t *micro, instruccion_t *i);

///---DIRECCIONAMIENTOS NO INDEXADOS Y EN MEMORIA-----
void direccionamiento_absoluto(mos6502_t *micro, instruccion_t *i);
void direccionamiento_relativo(mos6502_t *micro, instruccion_t *i);
void direccionamiento_pagina_cero(mos6502_t *micro, instruccion_t *i);
void direccionamiento_indirecto(mos6502_t *micro, instruccion_t *i);

///----DIRECCIONAMIENTOS INDEXADOS-----
void direccionamiento_abs_x(mos6502_t *micro, instruccion_t *i);
void direccionamiento_abs_y(mos6502_t *micro, instruccion_t *i);
void direccionamiento_pag_cero_x(mos6502_t *micro, instruccion_t *i);
void direccionamiento_pag_cero_y(mos6502_t *micro, instruccion_t *i);
void direccionamiento_indirecto_x(mos6502_t *micro, instruccion_t *i);
void direccionamiento_indirecto_y(mos6502_t *micro, instruccion_t *i);

#endif