#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

#define MAX_MENSAJE 150
#define EOL '\n'
#define ERROR 1
#define EXITO 0

#define COMANDO_AYUDA_CORTO 'h'
#define COMANDO_VERSION_CORTO 'V'
#define COMANDO_AYUDA_LARGO "help"
#define COMANDO_VERSION_LARGO "version"
#define COMANDO_INPUT_CORTO 'i'
#define COMANDO_OUTPUT_CORTO 'o'
#define COMANDO_INPUT_LARGO "input"
#define COMANDO_OUTPUT_LARGO "output"

#define RUTA_AYUDA "comandos/help.txt"
#define RUTA_VERSION "comandos/version.txt"

#define MENSAJE_COMANDO_INVALIDO "\n El comando usado es invalido, use -h para ayuda."
#define MENSAJE_GCD_ERROR "\n No se pudo obtener el maximo comun divisor, ocurrio un error."

#endif //UTILS_H