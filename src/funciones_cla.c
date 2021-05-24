#include "funciones_cla.h"

#define FLAG_CICLO "-ciclos"
#define FLAG_LOG "-log"

bool validar_falgs(int argc) {
    if (argc > 1 && argc < 7 && argc % 2 == 0) return true;
    //para una correcta ejecucion la cantidad de argunmentos debe ser par
    return false;
}

bool parsear_cla(int argc, char *argv[], char log[100], long *ciclos) {
    int i = 2;
    char *ptr_final;
    if (validar_falgs(argc) == false) return false;
    while ((i + 1) < argc) {
        if (i % 2 == 0) {
            if (strcmp(argv[i], FLAG_CICLO) == 0) {
                *ciclos = strtol(argv[i + 1], &ptr_final, 10);
                if (strcmp(ptr_final, "") != 0) return false;
            } else if (strcmp(argv[i], FLAG_LOG) == 0) {
                if((strlen(argv[i + 1]) + 1) > 100) return false; // Que el nombre del archivo de log no supere el maximo
                strcpy(log, argv[i + 1]);
            } else
                return false;
        }
        i++;
    }
    return true;
}