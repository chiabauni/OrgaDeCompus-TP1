#include "max_divisor.h"

#define FIN_DE_ARCHIVO 1 
#define ERROR_LINEA_INVALIDA -1
#define ERROR_DE_MEMORIA -2 
#define ERROR_DE_INPUT -3

#define SEPARADOR ' '

int procesar_archivos(FILE* entrada, FILE* salida) {

	int lectura = 0;
	int enteros[2];
	int largo_linea = 0;
	char* linea = NULL;

	int largo_buffer = 20;
	size_t largo_arreglo = 0;
	struct gcd* arreglo_structs = malloc(sizeof(struct gcd) * largo_buffer);
	if((arreglo_structs) == NULL) {
		perror(MENSAJE_MEM_DINAMICA_ERROR);
		free(arreglo_structs);
		return ERROR_DE_MEMORIA;
	}

	while(lectura == 0) {
		if((largo_arreglo) == (largo_buffer-1)) { // Tengo que agrandar mi memoria.
	     	 	
			largo_buffer += 10; //Voy agregando de a 10 lugares. 
			arreglo_structs = realloc(arreglo_structs, sizeof(struct gcd) * largo_buffer); // Re ubico en la memoria.
	      		
			if((arreglo_structs) == NULL) {
				perror(MENSAJE_MEM_DINAMICA_ERROR);
				free(arreglo_structs);
				return ERROR_DE_MEMORIA;
			}
		}

		lectura = leer_linea(entrada, &largo_linea, &linea);

		if(lectura == ERROR_DE_MEMORIA) {
			perror(MENSAJE_MEM_DINAMICA_ERROR);
			free(arreglo_structs);
			free(linea);
			return ERROR_DE_MEMORIA;
		}
		
		if(lectura != ERROR_LINEA_INVALIDA) {
			int conversion = pasar_a_enteros(linea, largo_linea, enteros);
			if(conversion == ERROR_DE_INPUT) {
				perror(MENSAJE_INPUT_ERROR);
				free(arreglo_structs);
				free(linea);
				return ERROR_DE_INPUT;
			}
			if(conversion == ERROR_DE_MEMORIA) {
				perror(MENSAJE_MEM_DINAMICA_ERROR);
				free(arreglo_structs);
				free(linea);
				return ERROR_DE_MEMORIA;
			}

			arreglo_structs[largo_arreglo].num_a = enteros[0];
			arreglo_structs[largo_arreglo].num_b = enteros[1];
			arreglo_structs[largo_arreglo].gcd_ab = 0; 
			largo_arreglo += 1;
		}
		free(linea);
	}

	if(lectura == ERROR_LINEA_INVALIDA) {
		perror(MENSAJE_LINEA_INVALIDA_ERROR);
		free(arreglo_structs);
		return ERROR_LINEA_INVALIDA;
	}
    
	euclides(arreglo_structs, largo_arreglo);

	if(imprimir_salida(arreglo_structs, largo_arreglo, salida)) {
		perror(MENSAJE_IMPRIMIR_SALIDA_ERROR);
		free(arreglo_structs);
		return ERROR;
	}
	free(arreglo_structs);
	return EXITO; 
}

int leer_linea(FILE* stream, int *largo_linea, char** linea) {
	int largo_buffer = 20;
	*linea = (char*) malloc(sizeof(char) * largo_buffer); // Asigno un lugar en memoria para el linea.

	if( (*linea) == NULL) {
		return ERROR_DE_MEMORIA;
	}

	(*largo_linea) = 0;
	int caracter = 1; // Un valor trivial
	bool primer_numero_leido = false;
	bool separador_leido = false;
	bool segundo_numero_leido = false;

	while ((caracter != EOL ) && (caracter != EOF)) {

	    	if((*largo_linea) == (largo_buffer-1)) { // Tengo que agrandar mi memoria.
			largo_buffer +=10; // Voy agregando de a 10 lugares. 
			(*linea) = (char*) realloc((*linea), sizeof(char) * largo_buffer); // Re ubico en la memoria.
	      		if( (*linea) == NULL) {
					return ERROR_DE_MEMORIA;
				}
	    	}

	    	caracter = getc(stream); // Leo un caracter del stream.
	    	if(ferror(stream)) {
	    		return ERROR_LINEA_INVALIDA;
	    	}

			primer_numero_leido |= (es_numerico(caracter));
			separador_leido |= (primer_numero_leido && caracter == SEPARADOR);
			segundo_numero_leido |= (separador_leido && es_numerico(caracter));

	    	if(es_caracter_invalido(caracter)) {
				return ERROR_LINEA_INVALIDA; // Si lee un caracter que no corresponde, devuelve linea invalida.	
	    	}
	    	(*linea) [ (*largo_linea) ] = (char) caracter; //Lo guardo en el linea.
	    	(*largo_linea)+=1; // Incremento mi tope.

	}

	if (!(primer_numero_leido && separador_leido && segundo_numero_leido) && (*largo_linea) > 1) {
		return ERROR_LINEA_INVALIDA;
	}

	if(caracter == EOF || (*largo_linea) <=1) { // Siempre va a leer por lo menos un caracter, sea eof o fin de linea
		return FIN_DE_ARCHIVO;
	}

	return 0;
		
}

int pasar_a_enteros(char* linea, int largo_linea, int *enteros) {
	char temporal [largo_linea];
	char caracter = 'A';
 	int largo_enteros = 0;

	int i = 0;
 	int j = 0;

	while(i < largo_linea) {
		caracter = linea[i]; i++;
        if(largo_enteros >= 2) {
            perror(MENSAJE_INPUT_ERROR);
            return ERROR_DE_INPUT;
        } else if(es_numerico(caracter)) {
			temporal[j] = caracter; j++;	
		} else if((caracter ==SEPARADOR || es_fin_de_linea(caracter)) && j!=0) {
			temporal[j] = '\0';
			enteros[largo_enteros] = atoi(temporal);
			largo_enteros += 1;
			j = 0;
		}
	}
	return 0;
}

int imprimir_salida(struct gcd *gcd, size_t largo, FILE* salida) {
	if(largo == 0) return 0;
	for (int i = 0; i <= (largo-1); i++) {
		fprintf(salida, "GCD(%i, %i) = %i \n", gcd[i].num_a, gcd[i].num_b, gcd[i].gcd_ab);
		if(ferror(salida)) {
    		return 1;
    	}
	}
	return 0;
}

bool es_fin_de_linea(char caracter) {
	return(caracter == EOL || caracter == (char) EOF);
}

bool es_numerico(char caracter) {
	return((caracter >= '0' && caracter <= '9') || caracter=='-'||caracter=='+');
}

bool es_caracter_invalido(char caracter) {
	return !(es_numerico(caracter) || es_fin_de_linea(caracter) || caracter ==SEPARADOR);
}
