#include "mos6502.h"
#include "archivo_log.h"
#include "instrucciones.h"
#include "modos_direccionamiento.h"

#define TAMANO_ROM 0x10000


typedef struct {
    void (*operacion)(mos6502_t *, instruccion_t *);
    void (*direccionamiento)(mos6502_t *, instruccion_t *);
    short ciclos;

} diccionario_t;

const diccionario_t diccionario_instrucciones[256] = {
        ///opcode||instruccion||modo de direccionamiento||#ciclos
        [0x65] = {&f_adc, &direccionamiento_pagina_cero, 3},
        [0x69] = {&f_adc, &direccionamiento_inmediato, 2},
        [0x6D] = {&f_adc, &direccionamiento_absoluto,4},
        [0x75] = {&f_adc, &direccionamiento_pag_cero_x, 4},
        [0x7D] = {&f_adc, &direccionamiento_abs_x, 4},
        [0x79] = {&f_adc, &direccionamiento_abs_y, 4},
        [0x71] = {&f_adc, &direccionamiento_indirecto_y, 5},
        [0x61] = {&f_adc, &direccionamiento_indirecto_x, 6},
        [0x29] = {&f_and,&direccionamiento_inmediato,2},
        [0x2D] = {&f_and,&direccionamiento_absoluto,4},
        [0x25] = {&f_and,&direccionamiento_pagina_cero,3},
        [0x35] = {&f_and,&direccionamiento_pag_cero_x,4},
        [0x3D] = {&f_and,&direccionamiento_abs_x,4},
        [0x39] = {&f_and,&direccionamiento_abs_y,4},
        [0x31] = {&f_and,&direccionamiento_indirecto_y,5},
        [0x21] = {&f_and,&direccionamiento_indirecto_x,6},
        [0x0A] = {&f_asl,&direccionamiento_acumulador,2},
        [0x06] = {&f_asl,&direccionamiento_pagina_cero,5},
        [0x0E] = {&f_asl,&direccionamiento_absoluto,6},
        [0x16] = {&f_asl,&direccionamiento_pag_cero_x,6},
        [0x1E] = {&f_asl,&direccionamiento_abs_x,7},
        [0x90] = {&f_bcc,&direccionamiento_relativo,2},
        [0xB0] = {&f_bcs,&direccionamiento_relativo,2},
        [0xF0] = {&f_beq,&direccionamiento_relativo,2},
        [0x24] = {&f_bit,&direccionamiento_pagina_cero,3},
        [0x2C] = {&f_bit,&direccionamiento_absoluto,4},
        [0x30] = {&f_bmi,&direccionamiento_relativo,2},
        [0xD0] = {&f_bne,&direccionamiento_relativo,2},
        [0x10] = {&f_bpl,&direccionamiento_relativo,2},
        [0x00] = {&f_brk,&direccionamiento_implicito,7},
        [0x50] = {&f_bvc,&direccionamiento_relativo,2},
        [0x70] = {&f_bvs,&direccionamiento_relativo,2},
        [0x18] = {&f_clc,&direccionamiento_implicito,2},
        [0xD8] = {&f_cld,&direccionamiento_implicito,2},
        [0x58] = {&f_cli,&direccionamiento_implicito,2},
        [0xB8] = {&f_clv,&direccionamiento_implicito,2},
        [0xC9] = {&f_cmp,&direccionamiento_inmediato,2},
        [0xCD] = {&f_cmp,&direccionamiento_absoluto,4},
        [0xC5] = {&f_cmp,&direccionamiento_pagina_cero,3},
        [0xD5] = {&f_cmp,&direccionamiento_pag_cero_x,4},
        [0xDD] = {&f_cmp,&direccionamiento_abs_x,4},
        [0xD9] = {&f_cmp,&direccionamiento_abs_y,4},
        [0xD1] = {&f_cmp,&direccionamiento_indirecto_y,5},
        [0xC1] = {&f_cmp,&direccionamiento_indirecto_x,6},
        [0xE0] = {&f_cpx,&direccionamiento_inmediato,2},
        [0xC0] = {&f_cpy,&direccionamiento_inmediato,2},
        [0xE4] = {&f_cpx,&direccionamiento_pagina_cero,3},
        [0xC4] = {&f_cpy,&direccionamiento_pagina_cero,3},
        [0xEC] = {&f_cpx,&direccionamiento_absoluto,4},
        [0xCC] = {&f_cpy,&direccionamiento_absoluto,4},
        [0xC6] = {&f_dec,&direccionamiento_pagina_cero,5},
        [0xCE] = {&f_dec,&direccionamiento_absoluto,6},
        [0xD6] = {&f_dec,&direccionamiento_pag_cero_x,6},
        [0xDE] = {&f_dec,&direccionamiento_abs_x,7},
        [0xCA] = {&f_dex,&direccionamiento_implicito,2},
        [0x88] = {&f_dey,&direccionamiento_implicito,2},
        [0x49] = {&f_eor,&direccionamiento_inmediato,2},
        [0x45] = {&f_eor,&direccionamiento_pagina_cero,3},
        [0x4D] = {&f_eor,&direccionamiento_absoluto,4},
        [0x55] = {&f_eor,&direccionamiento_pag_cero_x,4},
        [0x5D] = {&f_eor,&direccionamiento_abs_x,4},
        [0x59] = {&f_eor,&direccionamiento_abs_y,4},
        [0x41] = {&f_eor,&direccionamiento_indirecto_x,6},
        [0x51] = {&f_eor,&direccionamiento_indirecto_y,5},
        [0xE6] = {&f_inc,&direccionamiento_pagina_cero,5},
        [0xF6] = {&f_inc,&direccionamiento_pag_cero_x,6},
        [0xEE] = {&f_inc,&direccionamiento_absoluto,6},
        [0xFE] = {&f_inc,&direccionamiento_abs_x,7},
        [0xE8] = {&f_inx,&direccionamiento_implicito,2},
        [0xC8] = {&f_iny,&direccionamiento_implicito,2},
        [0x4C] = {&f_jmp,&direccionamiento_absoluto,3},
        [0x6C] = {&f_jmp,&direccionamiento_indirecto,5},
        [0x20] = {&f_jsr,&direccionamiento_absoluto,6},
        [0xA9] = {&f_lda,&direccionamiento_inmediato,2},
        [0xA5] = {&f_lda,&direccionamiento_pagina_cero,3},
        [0xB5] = {&f_lda,&direccionamiento_pag_cero_x,4},
        [0xAD] = {&f_lda,&direccionamiento_absoluto,4},
        [0xBD] = {&f_lda,&direccionamiento_abs_x,4},
        [0xB9] = {&f_lda,&direccionamiento_abs_y,4},
        [0xB1] = {&f_lda,&direccionamiento_indirecto_y,5},
        [0xA1] = {&f_lda,&direccionamiento_indirecto_x,6},
        [0xA2] = {&f_ldx,&direccionamiento_inmediato,2},
        [0xA6] = {&f_ldx,&direccionamiento_pagina_cero,3},
        [0xB6] = {&f_ldx,&direccionamiento_pag_cero_y,4},
        [0xAE] = {&f_ldx,&direccionamiento_absoluto,4},
        [0xBE] = {&f_ldx,&direccionamiento_abs_y,4},
        [0xA0] = {&f_ldy,&direccionamiento_inmediato,2},
        [0xA4] = {&f_ldy,&direccionamiento_pagina_cero,3},
        [0xB4] = {&f_ldy,&direccionamiento_pag_cero_x,4},
        [0xAC] = {&f_ldy,&direccionamiento_absoluto,4},
        [0xBC] = {&f_ldy,&direccionamiento_abs_x,4},
        [0x4A] = {&f_lsr,&direccionamiento_acumulador,2},
        [0x46] = {&f_lsr,&direccionamiento_pagina_cero,5},
        [0x56] = {&f_lsr,&direccionamiento_pag_cero_x,6},
        [0x4E] = {&f_lsr,&direccionamiento_absoluto,6},
        [0x5E] = {&f_lsr,&direccionamiento_abs_x,7},
        [0xEA] = {&f_nop,&direccionamiento_implicito,2},
        [0x09] = {&f_ora,&direccionamiento_inmediato,2},
        [0x05] = {&f_ora,&direccionamiento_pagina_cero,3},
        [0x15] = {&f_ora,&direccionamiento_pag_cero_x,4},
        [0x0D] = {&f_ora,&direccionamiento_absoluto,4},
        [0x1D] = {&f_ora,&direccionamiento_abs_x,4},
        [0x19] = {&f_ora,&direccionamiento_abs_y,4},
        [0x01] = {&f_ora,&direccionamiento_indirecto_x,6},
        [0x11] = {&f_ora,&direccionamiento_indirecto_y,5},
        [0x48] = {&f_pha,&direccionamiento_implicito,3},
        [0x08] = {&f_php,&direccionamiento_implicito,3},
        [0x68] = {&f_pla,&direccionamiento_implicito,4},
        [0x28] = {&f_plp,&direccionamiento_implicito,4},
        [0x2A] = {&f_rol,&direccionamiento_acumulador,2},
        [0x26] = {&f_rol,&direccionamiento_pagina_cero,5},
        [0x36] = {&f_rol,&direccionamiento_pag_cero_x,4},
        [0x2E] = {&f_rol,&direccionamiento_absoluto,6},
        [0x3E] = {&f_rol,&direccionamiento_abs_x,4},
        [0x6A] = {&f_ror,&direccionamiento_acumulador,2},
        [0x66] = {&f_ror,&direccionamiento_pagina_cero,5},
        [0x76] = {&f_ror,&direccionamiento_pag_cero_x,6},
        [0x6E] = {&f_ror,&direccionamiento_absoluto,6},
        [0x7E] = {&f_ror,&direccionamiento_abs_x,7},
        [0x40] = {&f_rti,&direccionamiento_implicito,6},
        [0x60] = {&f_rts,&direccionamiento_implicito,6},
        [0xE9] = {&f_sbc,&direccionamiento_inmediato,2},
        [0xE5] = {&f_sbc,&direccionamiento_pagina_cero,3},
        [0xF5] = {&f_sbc,&direccionamiento_pag_cero_x,4},
        [0xED] = {&f_sbc,&direccionamiento_absoluto,4},
        [0xFD] = {&f_sbc,&direccionamiento_abs_x,4},
        [0xF9] = {&f_sbc,&direccionamiento_abs_y,4},
        [0xF1] = {&f_sbc,&direccionamiento_indirecto_y,5},
        [0xE1] = {&f_sbc,&direccionamiento_indirecto_x,6},
        [0x38] = {&f_sec,&direccionamiento_implicito,2},
        [0xF8] = {&f_sed,&direccionamiento_implicito,2},
        [0x78] = {&f_sei,&direccionamiento_implicito,2},
        [0x85] = {&f_sta,&direccionamiento_pagina_cero,3},
        [0x95] = {&f_sta,&direccionamiento_pag_cero_x,4},
        [0x8D] = {&f_sta,&direccionamiento_absoluto,4},
        [0x9D] = {&f_sta,&direccionamiento_abs_x,5},
        [0x99] = {&f_sta,&direccionamiento_abs_y,5},
        [0x91] = {&f_sta,&direccionamiento_indirecto_y,6},
        [0x81] = {&f_sta,&direccionamiento_indirecto_x,6},
        [0x86] = {&f_stx,&direccionamiento_pagina_cero,3},
        [0x96] = {&f_stx,&direccionamiento_pag_cero_y,4},
        [0x8E] = {&f_stx,&direccionamiento_absoluto,4},
        [0x84] = {&f_sty,&direccionamiento_pagina_cero,3},
        [0x94] = {&f_sty,&direccionamiento_pag_cero_x,4},
        [0x8C] = {&f_sty,&direccionamiento_absoluto,4},
        [0xAA] = {&f_tax,&direccionamiento_implicito,2},
        [0xA8] = {&f_tay,&direccionamiento_implicito,2},
        [0xBA] = {&f_tsx,&direccionamiento_implicito,2},
        [0x8A] = {&f_txa,&direccionamiento_implicito,2},
        [0x9A] = {&f_txs,&direccionamiento_implicito,2},
        [0x98] = {&f_tya,&direccionamiento_implicito,2},

};

void ejecutar_instruccion(mos6502_t *m, char *archivo_de_log, int argc, char *argv[]){
    instruccion_t instruccion_actual;
    instruccion_actual.codigo = m->mem[m->pc];
    if(strcmp(archivo_de_log,"") != 0) setear_logs(m, archivo_de_log, argc, argv);
    m->pc ++;
    instruccion_actual.ciclos = diccionario_instrucciones[instruccion_actual.codigo].ciclos;
    diccionario_instrucciones[instruccion_actual.codigo].direccionamiento(m, &instruccion_actual);
    diccionario_instrucciones[instruccion_actual.codigo].operacion(m, &instruccion_actual);
    m->ciclos += instruccion_actual.ciclos;

}

mos6502_t *crear_micro(){
    mos6502_t *m = malloc(sizeof(mos6502_t));
    if(m == NULL) return NULL;
    m->mem = NULL;
    resetear_micro(m);
    return m;
}


bool cargar_rom(mos6502_t *m, char *rom){
    FILE * archivo_rom = fopen(rom,"rb");
    if(archivo_rom == NULL)
        return false;
    m->mem = malloc(sizeof(uint8_t) * TAMANO_ROM);
    if(m->mem == NULL){
        fclose(archivo_rom);
        return false;
    }
    fread(m->mem, sizeof(uint8_t), TAMANO_ROM, archivo_rom);
    fclose(archivo_rom);
    resetear_micro(m);
    return true;
}

void resetear_micro(mos6502_t *m){
    m->a = m->x = m->y = 0;
    m->status = 0x00;
    m->ciclos = 0;
    (m->sp) = 0xFF;
    //Recorda que sp me lleva a la ultima posicion libre del stack
    //Esto tiene sentido porque cualquier operacion que haga sobre el stack
    //tanto apilar como desapilar se hara sobre la ulitma posicion apuntada siempre.
    if(m->mem == NULL) m->pc = 0x0000;
    else{
        m->pc = (m->mem[0xfffd])<<8;
        m->pc += m->mem[0xfffc];

    }
}

void destruir_micro(mos6502_t *m){
    free(m->mem);
    free(m);
}



void apilar_stack(mos6502_t *m, uint8_t valor){
    //256 bytes de la primer pagina....0x0100 hasta 0x01FF
    uint16_t direccion_stack = 0x0100 + m->sp;
    //solo accedo a registros que pertenecen al stack
    m->mem[direccion_stack] = valor;
    m->sp --;
}

uint8_t desapilar_stack(mos6502_t *m){
    uint16_t direccion_stack = 0x0100;
    m->sp ++;
    direccion_stack += m->sp;
    return m->mem[direccion_stack];
}