#ifndef _ORDENADOR_H_
#define _ORDENADOR_H_

#include "utils.h"
#include "gcd.h"

/*
Pre: Recibe un stream correctamente abierto en modo de lectura
	y otro en modo escritura.
Pos: En el caso que el stream de entrada tenga formato de lineas consecutivas
 	de numeros enteros separados por espacios. Ordena cada linea en modo ascendente
 	y dicho resultado lo imprime en el stream de salida. Devolviendo el flag "EXITO"
 	En caso que no se respete el formato se devuelve "FALLO"
*/
int procesar_archivos(FILE* entrada, FILE* salida);

/*
Pre: Recibe un file stream correctamente abierto en modo lectura.
Pos: Lee una linea de dicho stream, devolviendo por parametros la misma
  	en forma de array de caracteres y el largo de la linea. En forma de retorno	
  	devuelve un flag indicando el resultado de la lectura :
  	FLAG_CONTINUAR:      En caso de que el archivo continue.
  	FLAG_FIN_DE_ARCHIVO: En caso de encontrase con un EOF o una linea
		                que solo contenga -1(indicador para dejar de iterar).
	FLAG_LINEA_INVALIDA: En que se haya tenido que detener la ejecucion debido a un
						caracter invalido encontrado en el stream.
*/	
int leer_linea (FILE* stream, int *largo_linea, char** linea);

/*
Pre: Recibe un array de caracteres que contiene numeros enteros
    separados por un espacio(Esto es previamente validado) junto con su largo.
Pos: Devuelve en forma de retorno el puntero a un array de enteros equivalente al de caracteres
    Y por parametro devuelve su largo.
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
Pos: Responde a la pregunta es numerico?(se considera los signos de + y - como numericos).
*/
bool es_numerico(char caracter);

/*
Pre: Recibe un caracter
Pos: Si el caracter es numerico, EOF, EOL o espacio devuelve TRUE.
   	en otro caso devuelve FALSE. (dicho caracter no se deberia encontrar en el input).
*/
bool es_caracter_invalido(char caracter);

#endif