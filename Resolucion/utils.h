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

#define MENSAJE_COMANDO_INVALIDO_ERROR "\n El comando usado es invalido, use -h para ayuda.\n"
#define MENSAJE_GCD_ERROR "\n No se pudo obtener el maximo comun divisor, ocurrio un error.\n"
#define MENSAJE_MEM_DINAMICA_ERROR "\n Problema asignando memoria dinamica.\n"
#define MENSAJE_INPUT_ERROR "\nLa cantidad de numeros ingresada es invalida. Solo se pueden ingresar 2 numeros por cada calculo de GCD.\n"
#define MENSAJE_CONVERTIR_CHAR_ERROR "\nError a la hora de convertir la linea de caracteres.\n"
#define MENSAJE_LINEA_INVALIDA_ERROR "\nProblema leyendo el archivo.\n"
#define MENSAJE_IMPRIMIR_SALIDA_ERROR "\nProblema al imprimir la salida.\n"

#endif //UTILS_H