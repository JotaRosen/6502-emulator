#include "instrucciones.h"
#include "funciones_status.h"
#define MASK_CARRY 0x100
#define MASK_SIGN_NEGATIVE 0x80
#define COMPLEMENTO_CTE 256

static void dec_auxiliar(mos6502_t *micro,uint8_t *src){
    --(*src);
    set_status(&(micro->status),ZERO,*src == 0);
    set_status(&(micro->status),NEGATIVE,*src&MASK_SIGN_NEGATIVE);
}
static void inc_auxiliar(mos6502_t *micro,uint8_t *src){
    ++(*src);
    set_status(&(micro->status),ZERO,*src == 0);
    set_status(&(micro->status),NEGATIVE,*src&MASK_SIGN_NEGATIVE);
}

static void load_auxiliar(mos6502_t *micro,uint8_t src, uint8_t *dest){
    *dest = src;
    set_status(&(micro->status),ZERO,src == 0);
    set_status(&(micro->status),NEGATIVE,src&MASK_SIGN_NEGATIVE);

}

void f_adc(mos6502_t *micro, instruccion_t *i){
    uint16_t res = micro->a;
    bool carry_operando = get_status(micro->status,CARRY);
    uint8_t acumulador = micro->a;
    res += *(i->m) + carry_operando;
    micro->a = res;
    set_status(&(micro->status),ZERO,micro->a == 0);
    set_status(&(micro->status),NEGATIVE,micro->a&MASK_SIGN_NEGATIVE);
    set_status(&(micro->status),CARRY,res&MASK_CARRY);
    set_overflow(&(micro->status),acumulador ,*(i->m) , micro->a);
}

void f_and(mos6502_t *micro, instruccion_t *i){

    micro->a &= *(i->m);
    set_status(&(micro->status),ZERO,micro->a == 0);
    set_status(&(micro->status),NEGATIVE,micro->a&MASK_SIGN_NEGATIVE);
}

void f_asl(mos6502_t *micro, instruccion_t *i){
    uint16_t res = *(i->m) <<1;
    *(i->m) <<= 1;
    set_status(&(micro->status),ZERO,*(i->m) == 0);
    set_status(&(micro->status),CARRY,res&MASK_CARRY);
    set_status(&(micro->status),NEGATIVE,*(i->m)&MASK_SIGN_NEGATIVE);
}

void f_clc(mos6502_t *micro, instruccion_t *i){
    set_status(&(micro->status),CARRY,0);
}

void f_cmp(mos6502_t *micro, instruccion_t *i){

    set_status(&(micro->status),ZERO,micro->a == *(i->m));
    set_status(&(micro->status),CARRY,micro->a >= *(i->m));
    set_status(&(micro->status),NEGATIVE,(micro->a - *(i->m))<0);

}
void f_dec(mos6502_t *micro, instruccion_t *i){
    dec_auxiliar(micro,i->m);
}
void f_dex(mos6502_t *micro, instruccion_t *i){
    dec_auxiliar(micro,&micro->x);
}
void f_dey(mos6502_t *micro, instruccion_t *i){
    dec_auxiliar(micro,&micro->y);
}


void f_eor(mos6502_t *micro, instruccion_t *i){
    micro->a^=*(i->m);
    set_status(&(micro->status),ZERO,micro->a == 0);
    set_status(&(micro->status),NEGATIVE,micro->a&MASK_SIGN_NEGATIVE);
}

void f_jmp(mos6502_t *micro, instruccion_t *i){
    micro->pc = i->direccion;
}
void f_lda(mos6502_t *micro, instruccion_t *i){
    load_auxiliar(micro,*i->m,&micro->a);

}
void f_ldy(mos6502_t *micro, instruccion_t *i){
    load_auxiliar(micro,*i->m,&micro->y);

}
void f_ldx(mos6502_t *micro, instruccion_t *i){
    load_auxiliar(micro,*i->m,&micro->x);

}
void f_nop(mos6502_t *micro, instruccion_t *i){

}
void f_sec(mos6502_t *micro, instruccion_t *i){
    set_status(&(micro->status),CARRY,1);
}
void f_sta(mos6502_t *micro, instruccion_t *i){
    *(i->m) = micro->a;

}
void f_sty(mos6502_t *micro, instruccion_t *i){
    *(i->m) = micro->y;

}
void f_stx(mos6502_t *micro, instruccion_t *i){
    *(i->m) = micro->x;
}

void f_bcc(mos6502_t *micro, instruccion_t *i){
    if(get_status(micro->status,CARRY) == 0) {
        if(*(i->m) > 127){
            micro->pc -= (COMPLEMENTO_CTE-*(i->m));
        }
        else micro->pc += *(i->m);
    }
}

void f_bcs(mos6502_t *micro, instruccion_t *i){
    if(get_status(micro->status,CARRY) != 0) {
        if(*(i->m) > 127){
            micro->pc -= (COMPLEMENTO_CTE-*(i->m));
        }
        else micro->pc += *(i->m);
    }
}
void f_beq(mos6502_t *micro, instruccion_t *i){
    if(get_status(micro->status,ZERO) != 0) {
        if(*(i->m) > 127){
            micro->pc -= (COMPLEMENTO_CTE-*(i->m));
        }
        else micro->pc += *(i->m);
    }
}

void f_bit(mos6502_t *micro, instruccion_t *i){
    uint8_t res = *(i->m) & micro->a;
    set_status(&(micro->status),ZERO,res == 0);
    set_status(&(micro->status),OVERFLOW,get_status(*(i->m),OVERFLOW));
    set_status(&(micro->status),NEGATIVE,get_status(*(i->m),NEGATIVE));
}
void f_bmi(mos6502_t *micro, instruccion_t *i){
    if(get_status(micro->status,NEGATIVE) != 0) {
        if(*(i->m) > 127){
            micro->pc -= (COMPLEMENTO_CTE-*(i->m));
        }
        else micro->pc += *(i->m);
    }
}
void f_bne(mos6502_t *micro, instruccion_t *i){
    if(get_status(micro->status,ZERO) == 0){
        if(*(i->m) > 127){
            micro->pc -= (COMPLEMENTO_CTE-*(i->m));
        }
        else {
            micro->pc += *(i->m);
        }
    }
}
void f_bpl(mos6502_t *micro, instruccion_t *i){
    if(get_status(micro->status,NEGATIVE) == 0) {
        if(*(i->m) > 127){
            micro->pc -= (COMPLEMENTO_CTE-*(i->m));
        }
        else micro->pc += *(i->m);
    }
}

void f_brk(mos6502_t *micro, instruccion_t *i){
    uint8_t pc_alto = (micro->pc + 1) >> 8;
    uint8_t pc_bajo = (micro->pc +1);
    apilar_stack(micro,pc_alto);
    apilar_stack(micro,pc_bajo);
    uint8_t status = micro->status;
    set_status(&status,BREAK,1);
    status |= 0x20; //pongo el bit reservado en 1
    apilar_stack(micro,status);
    set_status(&(micro->status),INTERRUPT_DISABLE,1);
    micro->pc =0x0000;
    micro->pc |= micro->mem[0xffff] << 8;
    micro->pc |= micro->mem[0xfffe];
}

void f_bvc(mos6502_t *micro, instruccion_t *i){
    if(get_status(micro->status,OVERFLOW) == 0) {
        if(*(i->m) > 127){
            micro->pc -= (COMPLEMENTO_CTE-*(i->m));
        }
        else micro->pc += *(i->m);
    }
}
void f_bvs(mos6502_t *micro, instruccion_t *i){
    if(get_status(micro->status,OVERFLOW)!= 0) {
        if(*(i->m) > 127){
            micro->pc -= (COMPLEMENTO_CTE-*(i->m));
        }
        else micro->pc += *(i->m);
    }
}
void f_cld(mos6502_t *micro, instruccion_t *i){
    set_status(&(micro->status),DECIMAL,0);
}
void f_cli(mos6502_t *micro, instruccion_t *i){
    set_status(&(micro->status),INTERRUPT_DISABLE,0);
}
void f_clv(mos6502_t *micro, instruccion_t *i){
    set_status(&(micro->status),OVERFLOW,0);
}

void f_cpx(mos6502_t *micro, instruccion_t *i){

    set_status(&(micro->status),ZERO,micro->x == *(i->m));
    set_status(&(micro->status),CARRY,micro->x >= *(i->m));
    set_status(&(micro->status),NEGATIVE,micro->x < *(i->m));

}
void f_cpy(mos6502_t *micro, instruccion_t *i){
    set_status(&(micro->status),ZERO,micro->y == *(i->m));
    set_status(&(micro->status),CARRY,micro->y >= *(i->m));
    set_status(&(micro->status),NEGATIVE,micro->y < *(i->m));
}

void f_inc(mos6502_t *micro, instruccion_t *i){
    inc_auxiliar(micro,i->m);
}

void f_inx(mos6502_t *micro, instruccion_t *i){
    inc_auxiliar(micro,&micro->x);
}

void f_iny(mos6502_t *micro, instruccion_t *i){
    inc_auxiliar(micro,&micro->y);
}

void f_jsr(mos6502_t *micro, instruccion_t *i) {
    uint8_t pc_alto = (micro->pc - 2) >> 8;
    uint8_t pc_bajo = micro->pc - 1;
    apilar_stack(micro, pc_alto);
    apilar_stack(micro, pc_bajo);
    micro->pc = i->direccion;
}
void f_lsr(mos6502_t *micro, instruccion_t *i){
    set_status(&(micro->status),CARRY, get_status(*(i->m),CARRY));
    uint8_t res = *(i->m) >>= 1;
    set_status(&(micro->status),ZERO, res == 0);
    set_status(&(micro->status),NEGATIVE,*(i->m)&MASK_SIGN_NEGATIVE);
}
void f_ora(mos6502_t *micro, instruccion_t *i){
    micro->a |= *(i->m);
    set_status(&(micro->status),ZERO,micro->a == 0);
    set_status(&(micro->status),NEGATIVE,micro->a&MASK_SIGN_NEGATIVE);
}

void f_pha(mos6502_t *micro, instruccion_t *i){
    apilar_stack(micro,micro->a);
}
void f_php(mos6502_t *micro, instruccion_t *i){
    uint8_t status = micro->status;
    set_status(&status,BREAK,1);
    status |= 0x20; //pongo el bit reservado en 1
    apilar_stack(micro, status);
}
void f_pla(mos6502_t *micro, instruccion_t *i){
    //desapilar_stack(micro);
    micro->a = desapilar_stack(micro);
    set_status(&(micro->status),ZERO,micro->a == 0);
    set_status(&(micro->status),NEGATIVE,micro->a&MASK_SIGN_NEGATIVE);
}

void f_plp(mos6502_t *micro, instruccion_t *i){
    bool bit_4 = get_status(micro->status,BREAK);
    bool bit_5 = micro->status&0x20; //Me guardo el bit 5
    micro->status = desapilar_stack(micro);
    set_status(&(micro->status), BREAK, bit_4);
    if(bit_5 == 0) micro->status &= ~0x20;
    else micro->status |= 0x20;
}

void f_rol(mos6502_t *micro, instruccion_t *i){
    uint16_t res = 0x0000;
    res += *(i->m);
    if(get_status(micro->status,CARRY)) res |= 0x100;
    rotate_left(&res);
    *(i->m) = res;
    set_status(&(micro->status),ZERO,*(i->m) == 0);
    set_status(&(micro->status),NEGATIVE,*(i->m)&MASK_SIGN_NEGATIVE);
    set_status(&(micro->status),CARRY,res&MASK_CARRY);
}
void f_ror(mos6502_t *micro, instruccion_t *i){
    uint16_t res = 0x0000;
    res += *(i->m);
    if(get_status(micro->status,CARRY)) res |= 0x100;
    rotate_right(&res);
    *(i->m) = res;
    set_status(&(micro->status),ZERO,*(i->m) == 0);
    set_status(&(micro->status),NEGATIVE,*(i->m)&MASK_SIGN_NEGATIVE);
    set_status(&(micro->status),CARRY,res&MASK_CARRY);
}

void f_rti(mos6502_t *micro, instruccion_t *i){
    //primero desapilo el status
    bool bit_4 = get_status(micro->status,BREAK);
    bool bit_5 = micro->status&0x20; //Me guardo el bit 5
    micro->status = desapilar_stack(micro);
    set_status(&(micro->status), BREAK, bit_4);
    if(bit_5 == 0) micro->status &= ~0x20;
    else micro->status |= 0x20;

    //Ahora desapilo el stack
    uint16_t aux = 0x0000;
    micro->pc = 0x0000;
    micro->pc |= desapilar_stack(micro);
    aux |= desapilar_stack(micro);
    aux <<= 8;
    micro->pc += aux;
}

void f_rts(mos6502_t *micro, instruccion_t *i){
    uint16_t aux = 0x0000;
    micro->pc = 0x0000;
    micro->pc |= desapilar_stack(micro);
    aux |= desapilar_stack(micro);
    aux <<= 8;
    micro->pc += aux;
    micro->pc ++;
}

void f_sbc(mos6502_t *micro, instruccion_t *i){
    bool carry_operando = get_status(micro->status,CARRY);
    uint16_t res = micro->a - *(i->m) -(1 - carry_operando);
    uint8_t acumulador = micro->a;
    micro->a = res;
    set_status(&(micro->status),ZERO,micro->a == 0);
    set_status(&(micro->status),NEGATIVE,micro->a&MASK_SIGN_NEGATIVE);
    set_status(&(micro->status),CARRY,!(res&MASK_CARRY));
    set_overflow(&(micro->status),acumulador ,~(*(i->m)) , micro->a);
}

void f_sed(mos6502_t *micro, instruccion_t *i){
    set_status(&(micro->status),DECIMAL,1);
}

void f_sei(mos6502_t *micro, instruccion_t *i){
    set_status(&(micro->status),INTERRUPT_DISABLE,1);
}

void f_tax(mos6502_t *micro, instruccion_t *i){
    micro->x = micro->a;
    set_status(&(micro->status),ZERO,micro->x == 0);
    set_status(&(micro->status),NEGATIVE,micro->x&MASK_SIGN_NEGATIVE);
}
void f_tay(mos6502_t *micro, instruccion_t *i){
    micro->y = micro->a;
    set_status(&(micro->status),ZERO,micro->y == 0);
    set_status(&(micro->status),NEGATIVE,micro->y&MASK_SIGN_NEGATIVE);
}
void f_txa(mos6502_t *micro, instruccion_t *i){
    micro->a = micro->x;
    set_status(&(micro->status),ZERO,micro->a == 0);
    set_status(&(micro->status),NEGATIVE,micro->a&MASK_SIGN_NEGATIVE);
}
void f_tya(mos6502_t *micro, instruccion_t *i){
    micro->a = micro->y;
    set_status(&(micro->status),ZERO,micro->a == 0);
    set_status(&(micro->status),NEGATIVE,micro->a&MASK_SIGN_NEGATIVE);
}
void f_tsx(mos6502_t *micro, instruccion_t *i){
    micro->x = micro->sp;
    set_status(&(micro->status),ZERO,micro->x == 0);
    set_status(&(micro->status),NEGATIVE,micro->x&MASK_SIGN_NEGATIVE);
}

void f_txs(mos6502_t *micro, instruccion_t *i){
    micro->sp = micro->x;
}



