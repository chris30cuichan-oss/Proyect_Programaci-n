#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validar_entero(int *numero) {
    char linea[100];
    int valido = 0;
    while (!valido) {
        if (fgets(linea, sizeof(linea), stdin) != NULL) {
            linea[strcspn(linea, "\n")] = 0;
            if (strlen(linea) == 0) {
                printf("[ERROR]: No puede dejar el campo vacío. Intente de nuevo: ");
                continue;
            }
            int es_numerico = 1;
            for (int i = 0; linea[i] != '\0'; i++) {
                if (!isdigit((unsigned char)linea[i])) {
                    es_numerico = 0;
                    break;
                }
            }
            if (es_numerico) {
                *numero = atoi(linea);
                valido = 1;
            } else {
                printf("[ERROR]: Entrada inválida. No se permiten letras. Intente de nuevo: ");
            }
        }
    }
    return 1;
}

void validar_texto(char *destino, int longitud_max) {
    char linea[150];
    int valido = 0;
    while (!valido) {
        if (fgets(linea, sizeof(linea), stdin) != NULL) {
            linea[strcspn(linea, "\n")] = 0;
            if (strlen(linea) == 0) {
                printf("[ERROR]: El nombre no puede estar vacío. Intente de nuevo: ");
                continue;
            }
            if ((int)strlen(linea) >= longitud_max) {
                printf("[ERROR]: Texto muy largo. Intente de nuevo: ");
                continue;
            }
            int es_texto_puro = 1;
            for (int i = 0; linea[i] != '\0'; i++) {
                if (!isalpha((unsigned char)linea[i]) && linea[i] != ' ') {
                    es_texto_puro = 0;
                    break;
                }
            }
            if (es_texto_puro) {
                strcpy(destino, linea);
                valido = 1;
            } else {
                printf("[ERROR]: Entrada inválida. No números ni símbolos. Intente de nuevo: ");
            }
        }
    }
}