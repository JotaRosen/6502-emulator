#ifndef ARCHIVO_LOG_H
#define ARCHIVO_LOG_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "utils.h"

bool setear_logs(mos6502_t *micro, char *nombre_log, int argc, char *argv[]);

#endif
