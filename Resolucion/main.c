#include "utils.h"
#include "max_divisor.h"

/*Pre: Recibe una ruta a un archivo en formato de string.
Pos: Muestra por stdin dicho archivo (similar al comando unix "cat".*/
int mostrar_en_pantalla(char* ruta);

/*Pre: Recibe una ruta a un archivo en formato de string.
Pos: Notifica por stderror que se tuvo un error con un archivo de dicha ruta.*/
void notificar_problema_ruta(char *ruta);


int main(int argc, char** argv){

	FILE* stream_entrada = NULL;
	FILE* stream_salida = NULL;
	int flag_divisor = -1;
	int long_index = 0;
	int opt = 0;
	char estandar[] = "-";

	static struct option long_options[] = {
        {COMANDO_VERSION_LARGO,      no_argument,       NULL, COMANDO_VERSION_CORTO },
        {COMANDO_AYUDA_LARGO,         no_argument,       NULL,  COMANDO_AYUDA_CORTO },
        {COMANDO_INPUT_LARGO,    required_argument,     NULL,  COMANDO_INPUT_CORTO },
        {COMANDO_OUTPUT_LARGO,   required_argument,     NULL,  COMANDO_OUTPUT_CORTO },
        {NULL,           0,                     NULL,    0 }
    };


	while ( (opt = getopt_long(argc, argv,"Vhi:o:", 
                   long_options, &long_index )) != -1) {
        switch (opt) {
            case COMANDO_VERSION_CORTO :
             	return mostrar_en_pantalla(RUTA_VERSION);
	        case COMANDO_AYUDA_CORTO :
             	return mostrar_en_pantalla(RUTA_AYUDA);
            case COMANDO_INPUT_CORTO :
				if (strcmp(optarg, estandar)) {
					stream_entrada = fopen(optarg, "r");
					if(stream_entrada == NULL){
						notificar_problema_ruta(optarg);
						if(stream_salida != NULL ){ // se pudo abrir el archivo de salida.
							fclose(stream_salida);
						}
						return ERROR;
					}
				}
            	break;
            case COMANDO_OUTPUT_CORTO :
				if (strcmp(optarg, estandar)) {
					stream_salida = fopen(optarg, "w");
					if(stream_salida == NULL){
						notificar_problema_ruta(optarg);
						if(stream_entrada != NULL ){ // se pudo abrir el archivo de entrada.
							fclose(stream_entrada);
						}
						return ERROR;
					}
				}
                break;
            default:
            	perror(MENSAJE_COMANDO_INVALIDO_ERROR); 
            	return ERROR;
        }
    }

    // Caso en que se usa la entrada/salida estandar.
    if(stream_entrada == NULL ) stream_entrada = stdin;
    if(stream_salida == NULL ) stream_salida = stdout;

	flag_divisor = procesar_archivos(stream_entrada, stream_salida);

	if(stream_salida != stdout) fclose(stream_salida);
	if(stream_entrada != stdin ) fclose(stream_entrada);

	if(flag_divisor == ERROR){
		perror(MENSAJE_GCD_ERROR);
		return ERROR;
	}

	return EXITO;
}

int mostrar_en_pantalla(char * ruta){
	FILE* archivo = fopen(ruta,"r");
	if (archivo == NULL){
		perror("\n No se pudo abrir el archivo. \n");
		return ERROR;
	}

	int caracter  = 1;

	while(caracter != EOF){
		caracter = fgetc(archivo);
		if(caracter != EOF) putc(caracter, stdout);
	}

	fclose(archivo);
	return EXITO;
}

void notificar_problema_ruta(char *ruta){
	char mensaje [MAX_MENSAJE];
	strcpy(mensaje,"\nEl archivo en la ruta: ");
	strcat(mensaje, ruta);
	strcat(mensaje,". No se pudo abrir correctamente\0");
	perror(mensaje);
}