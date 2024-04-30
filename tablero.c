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
     for (int i = 2; i < 6; i++){
        for (int j= 0; j< TAM_TABLERO; j++){
            tablero[i][j]= (Pieza){VACIO};
        }
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
    printf("    ");
    for (int i = 0; i < TAM_TABLERO; i++) {
        printf("  %d   ", i);
    }
    printf("\n");
    for (int i = 0; i < TAM_TABLERO; i++) {
        printf("  ");
        for (int k = 0; k < TAM_TABLERO; k++) {
            printf("+-----");
        }
        printf("+\n");

        printf(" %d ", i);
        for (int j = 0; j < TAM_TABLERO; j++) {
            printf("|");
            if ((i + j) % 2 == 0) { // Si la suma de las coordenadas es par
                printf("\033[47m\033[30m"); // Fondo blanco, texto negro
            } else {
                printf("\033[40m\033[37m"); // Fondo negro, texto blanco
            }
            switch (tablero[i][j].color) {
                case BLANCO:
                    switch (tablero[i][j].tipo) {
                        case VACIO:
                            printf("     ");
                            break;
                        case PEON:
                            printf("\033[1;31m  \u25A0  \033[0m"); // Rojo para las primeras fichas
                            break;
                        case TORRE:
                            printf("\033[1;31m  \u2660  \033[0m"); // Rojo para las primeras fichas
                            break;
                        case CABALLO:
                            printf("\033[1;31m  \xC2\xA7  \033[0m"); // Rojo para las primeras fichas
                            break;
                        case ALFIL:
                            printf("\033[1;31m  \u2663  \033[0m"); // Rojo para las primeras fichas
                            break;
                        case REINA:
                            printf("\033[1;31m  \u2665  \033[0m"); // Rojo para las primeras fichas
                            break;
                        case REY:
                            printf("\033[1;31m  \u2666  \033[0m"); // Rojo para las primeras fichas
                            break;
                    }
                    break;
                case NEGRO:
                    switch (tablero[i][j].tipo) {
                        case VACIO:
                            printf("     ");
                            break;
                        case PEON:
                            printf("\033[1;35m  \u25A0  \033[0m"); // Magenta para las fichas negras
                            break;
                        case TORRE:
                            printf("\033[1;35m  \u2660  \033[0m"); // Magenta para las fichas negras
                            break;
                        case CABALLO:
                            printf("\033[1;35m  \xC2\xA7  \033[0m"); // Magenta para las fichas negras
                            break;
                        case ALFIL:
                            printf("\033[1;35m  \u2663  \033[0m"); // Magenta para las fichas negras
                            break;
                        case REINA:
                            printf("\033[1;35m  \u2665  \033[0m"); // Magenta para las fichas negras
                            break;
                        case REY:
                            printf("\033[1;35m  \u2666  \033[0m"); // Magenta para las fichas negras
                            break;
                    }
                    break;
            }
            printf("\033[0m"); // Restaurar color original
        }
        printf("|\n");
    }
    printf("  ");
    for (int k = 0; k < TAM_TABLERO; k++) {
        printf("+-----");
    }
    printf("+\n");
}

void imprimir_simbolos() {
    printf("Símbolos de las piezas de ajedrez:\n");
    printf("PEON:     \u25A0  (♟ )\n");
    printf("TORRE:    \u2660  (♜ )\n");
    printf("CABALLO:  \xC2\xA7  (♞ )\n");
    printf("ALFIL:    \u2663  (♝ )\n");
    printf("REINA:    \u2665  (♛ )\n");
    printf("REY:      \u2666  (♚ )\n");
}
