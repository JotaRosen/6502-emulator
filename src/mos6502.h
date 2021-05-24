#ifndef MOS6502_H
#define MOS6502_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"


/**Funciones del mos6502*/
void ejecutar_instruccion(mos6502_t *m,char *archivo_de_log, int argc, char *argv[]);
mos6502_t *crear_micro();
bool cargar_rom(mos6502_t *m,char *str);
void resetear_micro(mos6502_t *m);
void destruir_micro(mos6502_t *m);
void apilar_stack(mos6502_t *m, uint8_t valor);
uint8_t desapilar_stack(mos6502_t *m);

#endif
