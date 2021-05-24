#include "mos6502.h"

bool ejecutar_instrucciones(long ciclos_cla, char *archivo_de_log, int argc, char *argv[]){
    mos6502_t *m = crear_micro();
    if(m == NULL)
        return false;


    if(cargar_rom(m,argv[1]) == false){
        destruir_micro(m);
        return false;
    }
    //ciclos_cla indica la cantidad de ciclos pasados como argumento en la linea de comandos
    while (m->ciclos < ciclos_cla) ejecutar_instruccion(m, archivo_de_log, argc, argv);

    destruir_micro(m);

    return true;


}
