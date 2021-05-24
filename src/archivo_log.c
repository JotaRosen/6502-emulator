#include "archivo_log.h"

bool setear_logs(mos6502_t *micro, char *nombre_log, int argc, char *argv[]){
    FILE * archivo_log = fopen(nombre_log,"a");
    if(archivo_log == NULL) return false;
    fseek (archivo_log, 0, SEEK_END);
    if(ftell(archivo_log) == 0){
        for(int i= 0; i < argc; i++){
            fputs(argv[i],archivo_log);
            fputc(' ',archivo_log);
        }
        fputc('\n',archivo_log);
        fputs("PC A X Y status SP\n",archivo_log);
    }
    fprintf(archivo_log,"%04x %02x %02x %02x %02x %02x\n", micro->pc,micro->a,micro->x,micro->y,micro->status,micro->sp);
    fclose(archivo_log);
    return true;
}