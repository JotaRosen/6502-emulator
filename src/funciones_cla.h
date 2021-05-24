#ifndef FUNCIONES_CLA_H
#define FUNCIONES_CLA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool validar_falgs(int argc);
bool parsear_cla(int argc, char *argv[],char log[50], long *ciclos);

#endif
