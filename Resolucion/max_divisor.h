#ifndef _ORDENADOR_H_
#define _ORDENADOR_H_

#include "utils.h"
#include "gcd.h"

/*
Pre: Recibe un stream correctamente abierto en modo de lectura
	y otro en modo escritura.
Pos: En el caso que el stream de entrada tenga formato de lineas consecutivas
 	de pares de numeros enteros separados por espacios. Calcula el maximo comun divisor
 	y dicho resultado lo imprime en el stream de salida. Devolviendo el flag "EXITO".
 	En caso que no se respete el formato se devuelve "FALLO".
*/
int procesar_archivos(FILE* entrada, FILE* salida);

/*
Pre: Recibe un file stream correctamente abierto en modo lectura.
Pos: Lee una linea de dicho stream, devolviendo por parametros la misma
  	en forma de array de caracteres y el largo de la linea. En forma de retorno	
  	devuelve un valor indicando el resultado de la lectura:
  	FIN_DE_ARCHIVO: En caso de encontrase con un EOF.
	ERROR_LINEA_INVALIDA: En caso que se haya tenido que detener la ejecucion debido a un
						caracter invalido encontrado en el stream.
	ERROR_DE_MEMORIA: En caso que se haya tenido que detener la ejecucion debido a un 
					problema a la hora de reservar o asignar memoria dinamica.
	0: En caso de que el archivo continue.
*/	
int leer_linea (FILE* stream, int *largo_linea, char** linea);

/*
Pre: Recibe un array de caracteres que contiene pares numeros enteros
    separados por un espacio(Esto es previamente validado) junto con su largo.
Pos: Devuelve por parametro el array de enteros y su largo.
*/
int pasar_a_enteros(char* linea, int largo_linea, int *enteros);

/*
Pre : Recibe un array de enteros, su largo y un stream de salida.
Pos:  "Imprime" dicho array en el stream.
*/
void imprimir_salida(struct gcd *gcd, size_t n, FILE* salida);

/*
Pre: Recibe un caracter.
Pos: Devuelve TRUE si el caracter indica el fin de linea.
*/
bool es_fin_de_linea(char caracter);

/*
Pre: Recibe un caracter.
Pos: Devuelve TRUE si el caracter es considerado como numerico
	(se considera los signos de + y - como numericos).
*/
bool es_numerico(char caracter);

/*
Pre: Recibe un caracter
Pos: Si el caracter es numerico, EOF, EOL o espacio devuelve TRUE.
   	en otro caso devuelve FALSE. (dicho caracter no se deberia encontrar en el input).
*/
bool es_caracter_invalido(char caracter);

#endif