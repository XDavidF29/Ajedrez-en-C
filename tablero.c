#include "tablero.h"
#include <stdio.h>

// Implementación de la función para inicializar el tablero
void inicializar_tablero(Tablero *tablero) {
    // Inicializamos todas las casillas del tablero con espacios en blanco (' ')
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            // Si la suma de los índices es par, la casilla será blanca (' ')
            // Si la suma de los índices es impar, la casilla será negra ('X')
            if ((i + j) % 2 == 0) {
                tablero->casillas[i][j] = ' ';
            } else {
                tablero->casillas[i][j] = '#'; // Casilla negra
            }
        }
    }
}

// Implementación de la función para imprimir el tablero en la consola
void imprimir_tablero(Tablero *tablero) {
    // Imprimimos el tablero fila por fila
    for (int i = 0; i < FILAS; i++) {
        // Imprimimos el borde izquierdo
        printf("|");

        // Imprimimos cada casilla de la fila
        for (int j = 0; j < COLUMNAS; j++) {
            printf(" %c |", tablero->casillas[i][j]);
        }

        // Imprimimos un salto de línea al final de cada fila
        printf("\n");

        // Imprimimos la línea divisoria entre filas
        for (int j = 0; j < COLUMNAS; j++) {
            printf("----");
        }
        printf("-\n");
    }
}
