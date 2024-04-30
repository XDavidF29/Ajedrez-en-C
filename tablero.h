#ifndef TABLERO_H
#define TABLERO_H

// Definición de la estructura del tablero
// Definición de las piezas del ajedrez
#define VACIO 0
#define PEON 1
#define TORRE 2
#define CABALLO 3
#define ALFIL 4
#define REINA 5
#define REY 6

// Definición de los colores de las piezas
#define BLANCO 0
#define NEGRO 1

// Definición del tamaño del tablero
#define TAM_TABLERO 8

// Estructura de una pieza
typedef struct {
    int tipo;   // Tipo de pieza
    int color;  // Color de la pieza
} Pieza;

//Declaración de funciones
void inicializar_tablero(Pieza tablero[TAM_TABLERO][TAM_TABLERO]);
void imprimir_tablero(Pieza tablero[TAM_TABLERO][TAM_TABLERO]);
void imprimir_simbolos();
#endif //TABLERO_H