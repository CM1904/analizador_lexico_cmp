#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Función para escribir un token en el archivo de salida
void escribirToken(FILE *output, const char *token) {
    fprintf(output, "%s", token);
}

int main() {
    FILE *archivo;
    FILE *salida;
    archivo = fopen("fuente.txt", "r");
    salida = fopen("output.txt", "w");

    if (archivo == NULL || salida == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }
  
    // Define el estado inicial y los estados posibles
    enum { INICIAL, L_LLAVE, R_LLAVE, L_CORCHETE, R_CORCHETE, STRING, NUMBER, PR_FALSE, PR_TRUE, PR_NULL, DOS_PUNTOS, COMA } estado = INICIAL;

    char caracter;

    while ((caracter = fgetc(archivo)) != EOF) {
        switch (estado) {
            case INICIAL:
                if (caracter == '{') {
                    escribirToken(salida, "L_LLAVE ");
                }
                if (caracter == '}') {
                    escribirToken(salida, "R_LLAVE ");
                }
                if (caracter == '[') {
                    escribirToken(salida, "L_CORCHETE ");
                }
                if (caracter == ']') {
                    escribirToken(salida, "R_CORCHETE ");
                }
                if (caracter == '"') {
                    estado = STRING;
                } 
                if(caracter == ':') {
                    escribirToken(salida, "DOS_PUNTOS ");
                } 
                if (caracter == ',') {
                    escribirToken(salida, "COMA ");
                }
                if (caracter == ' ') {
                    escribirToken(salida, " ");
                }
                if (caracter == '\n') {
                    escribirToken(salida, "\n");
                }
                break;
            case STRING:
                if (caracter == '"') {
                    escribirToken(salida, "STRING ");
                    estado = INICIAL;
                }
                break;
        }
    }

    fclose(archivo);
    fclose(salida);

    return 0;
}
