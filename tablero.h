#ifndef TABLERO_H
#define TABLERO_H

// Definición de constantes
#define FILAS 8
#define COLUMNAS 8

// Definición de la estructura del tablero
typedef struct {
    char casillas[FILAS][COLUMNAS]; // Representación del tablero como matriz de caracteres
} Tablero;

// Declaración de funciones
void inicializar_tablero(Tablero *tablero);
void imprimir_tablero(Tablero *tablero);

#endif /* TABLERO_H */
