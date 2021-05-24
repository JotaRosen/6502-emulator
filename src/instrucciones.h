#ifndef INSTRUCCIONES_H
#define INSTRUCCIONES_H

#include "mos6502.h"

/**Encabezados de las instruciones*/
void f_adc(mos6502_t *micro, instruccion_t *i);
void f_and(mos6502_t *micro, instruccion_t *i);
void f_asl(mos6502_t *micro, instruccion_t *i);
void f_clc(mos6502_t *micro, instruccion_t *i);
void f_cmp(mos6502_t *micro, instruccion_t *i);
void f_dec(mos6502_t *micro, instruccion_t *i);
void f_dex(mos6502_t *micro, instruccion_t *i);
void f_dey(mos6502_t *micro, instruccion_t *i);
void f_eor(mos6502_t *micro, instruccion_t *i);
void f_jmp(mos6502_t *micro, instruccion_t *i);
void f_lda(mos6502_t *micro, instruccion_t *i);
void f_ldy(mos6502_t *micro, instruccion_t *i);
void f_ldx(mos6502_t *micro, instruccion_t *i);
void f_nop(mos6502_t *micro, instruccion_t *i);
void f_sec(mos6502_t *micro, instruccion_t *i);
void f_sta(mos6502_t *micro, instruccion_t *i);
void f_sty(mos6502_t *micro, instruccion_t *i);
void f_stx(mos6502_t *micro, instruccion_t *i);
void f_bcc(mos6502_t *micro, instruccion_t *i);
void f_bcs(mos6502_t *micro, instruccion_t *i);
void f_beq(mos6502_t *micro, instruccion_t *i);
void f_bit(mos6502_t *micro, instruccion_t *i);
void f_bmi(mos6502_t *micro, instruccion_t *i);
void f_bne(mos6502_t *micro, instruccion_t *i);
void f_bpl(mos6502_t *micro, instruccion_t *i);
void f_brk(mos6502_t *micro, instruccion_t *i);
void f_bvc(mos6502_t *micro, instruccion_t *i);
void f_bvs(mos6502_t *micro, instruccion_t *i);
void f_cld(mos6502_t *micro, instruccion_t *i);
void f_cli(mos6502_t *micro, instruccion_t *i);
void f_clv(mos6502_t *micro, instruccion_t *i);
void f_cpx(mos6502_t *micro, instruccion_t *i);
void f_cpy(mos6502_t *micro, instruccion_t *i);
void f_inc(mos6502_t *micro, instruccion_t *i);
void f_inx(mos6502_t *micro, instruccion_t *i);
void f_iny(mos6502_t *micro, instruccion_t *i);
void f_jsr(mos6502_t *micro, instruccion_t *i);
void f_lsr(mos6502_t *micro, instruccion_t *i);
void f_ora(mos6502_t *micro, instruccion_t *i);
void f_pha(mos6502_t *micro, instruccion_t *i);
void f_php(mos6502_t *micro, instruccion_t *i);
void f_pla(mos6502_t *micro, instruccion_t *i);
void f_plp(mos6502_t *micro, instruccion_t *i);
void f_rol(mos6502_t *micro, instruccion_t *i);
void f_ror(mos6502_t *micro, instruccion_t *i);
void f_rti(mos6502_t *micro, instruccion_t *i);
void f_rts(mos6502_t *micro, instruccion_t *i);
void f_sbc(mos6502_t *micro, instruccion_t *i);
void f_sed(mos6502_t *micro, instruccion_t *i);
void f_sei(mos6502_t *micro, instruccion_t *i);
void f_tax(mos6502_t *micro, instruccion_t *i);
void f_tay(mos6502_t *micro, instruccion_t *i);
void f_txa(mos6502_t *micro, instruccion_t *i);
void f_tya(mos6502_t *micro, instruccion_t *i);
void f_tsx(mos6502_t *micro, instruccion_t *i);
void f_txs(mos6502_t *micro, instruccion_t *i);



#endif //INSTRUCCIONES_H
