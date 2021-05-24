CC=gcc
CFLAGS=-Wall -ansi -std=c99 -pedantic -O3 -c
LFLAGS=-Wall
DEBUG=-g

all: emulador

emulador: main.o
	$(CC) $(LFLAGS) $(DEBUG) -o emulador main.o mos6502.o funcion_base.o modos_direccionamiento.o instrucciones.o funciones_status.o funciones_cla.o archivo_log.o

main.o: main.c funciones_cla.h funcion_base.h mos6502.o funcion_base.o modos_direccionamiento.o instrucciones.o funciones_status.o funciones_cla.o archivo_log.o
	$(CC) $(CFLAGS) $(DEBUG) -o main.o main.c

funcion_base.o: funcion_base.c mos6502.h
	$(CC) $(CFLAGS) $(DEBUG) -o funcion_base.o funcion_base.c

mos6502.o: mos6502.c mos6502.h instrucciones.h modos_direccionamiento.h archivo_log.h modos_direccionamiento.o instrucciones.o archivo_log.o
	$(CC) $(CFLAGS) $(DEBUG) -o mos6502.o mos6502.c

modos_direccionamiento.o: modos_direccionamiento.c modos_direccionamiento.h
	$(CC) $(CFLAGS) $(DEBUG) -o modos_direccionamiento.o modos_direccionamiento.c

instrucciones.o: instrucciones.c instrucciones.h  funciones_status.o
	$(CC) $(CFLAGS) $(DEBUG) -o instrucciones.o instrucciones.c

funciones_status.o: funciones_status.c funciones_status.h
	$(CC) $(CFLAGS) $(DEBUG) -o funciones_status.o funciones_status.c

funciones_cla.o: funciones_cla.c funciones_cla.h
	$(CC) $(CFLAGS) $(DEBUG) -o funciones_cla.o funciones_cla.c

archivo_log.o: archivo_log.c archivo_log.h
	$(CC) $(CFLAGS) $(DEBUG) -o archivo_log.o archivo_log.c

clean:
	rm *.o
	rm emulador