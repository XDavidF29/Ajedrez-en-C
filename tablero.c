#include "tablero.h"
#include <stdio.h>

// Función para inicializar el tablero con las piezas en sus posiciones iniciales
void inicializar_tablero(Pieza tablero[TAM_TABLERO][TAM_TABLERO]) {
    // Inicializar todas las casillas del tablero como vacías
    for (int i = 0; i < TAM_TABLERO; i++) {
        for (int j = 0; j < TAM_TABLERO; j++) {
            tablero[i][j].tipo = VACIO;
            tablero[i][j].color = -1; // -1 para indicar que está vacía
        }
    }

    // Inicializar las piezas blancas
    tablero[0][0] = (Pieza){TORRE, BLANCO};
    tablero[0][1] = (Pieza){CABALLO, BLANCO};
    tablero[0][2] = (Pieza){ALFIL, BLANCO};
    tablero[0][3] = (Pieza){REINA, BLANCO};
    tablero[0][4] = (Pieza){REY, BLANCO};
    tablero[0][5] = (Pieza){ALFIL, BLANCO};
    tablero[0][6] = (Pieza){CABALLO, BLANCO};
    tablero[0][7] = (Pieza){TORRE, BLANCO};
    for (int i = 0; i < TAM_TABLERO; i++) {
        tablero[1][i] = (Pieza){PEON, BLANCO};
    }

    // Inicializar las piezas negras
    tablero[7][0] = (Pieza){TORRE, NEGRO};
    tablero[7][1] = (Pieza){CABALLO, NEGRO};
    tablero[7][2] = (Pieza){ALFIL, NEGRO};
    tablero[7][3] = (Pieza){REINA, NEGRO};
    tablero[7][4] = (Pieza){REY, NEGRO};
    tablero[7][5] = (Pieza){ALFIL, NEGRO};
    tablero[7][6] = (Pieza){CABALLO, NEGRO};
    tablero[7][7] = (Pieza){TORRE, NEGRO};
    for (int i = 0; i < TAM_TABLERO; i++) {
        tablero[6][i] = (Pieza){PEON, NEGRO};
    }
}
void imprimir_tablero(Pieza tablero[TAM_TABLERO][TAM_TABLERO]) {
    for (int i = 0; i < TAM_TABLERO; i++) {
        for (int j = 0; j < TAM_TABLERO; j++) {
            // Imprimir las piezas en el tablero
            if (tablero[i][j].color == BLANCO) {
                switch (tablero[i][j].tipo) {
                    case VACIO:
                        printf("-");
                        break;
                    case PEON:
                        printf("P");
                        break;
                    case TORRE:
                        printf("T");
                        break;
                    case CABALLO:
                        printf("C");
                        break;
                    case ALFIL:
                        printf("A");
                        break;
                    case REINA:
                        printf("D");
                        break;
                    case REY:
                        printf("R");
                        break;
                }
            } else if (tablero[i][j].color == NEGRO) {
                switch (tablero[i][j].tipo) {
                    case VACIO:                            
                        printf("-");
                        break;
                    case PEON:
                        printf("p");
                        break;
                    case TORRE:
                        printf("t");
                        break;
                    case CABALLO:
                        printf("c");
                        break;
                    case ALFIL:
                        printf("a");
                        break;
                    case REINA:
                        printf("d");
                        break;
                    case REY:
                        printf("r");
                        break;
                }
            }
            printf(" "); // Separador entre columnas
        }
        printf("\n"); // Nueva línea para cada fila
    }
}
