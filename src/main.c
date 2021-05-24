#include "funciones_cla.h"
#include "funcion_base.h"


#define MAX_CICLCOS 83007452

int main(int argc, char *argv[]) {
    char nombre_log[100] = "";
    long ciclos = MAX_CICLCOS;

    if(parsear_cla(argc,argv,nombre_log,&ciclos) == false) {
        fprintf(stderr,"El Microprocesador se inicia con el siguiente comando:\n$ ./emulador archivo.rom [-ciclos numero] [-log archivo.log]\n");
        return 1;
    }

    if(ejecutar_instrucciones(ciclos,nombre_log, argc, argv) == false) return 1;

    return 0;
}