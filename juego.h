#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"

typedef enum {
    TURNO_BLANCAS,
    TURNO_NEGRAS,
    VICTORIA_BLANCAS,
    VICTORIA_NEGRAS,
    EMPATE,
    JUEGO_TERMINADO
} EstadoJuego;
//Funcionar manejar turnos
EstadoJuego manejar_turnos(EstadoJuego estado_actual, Pieza tablero[TAM_TABLERO][TAM_TABLERO], Pieza tablero_copia[TAM_TABLERO][TAM_TABLERO]);
//Función para realizar movimientos
int realizar_movimiento(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int color);
//Funcion para manejar movimientos de todas las fichas 
int movimientos(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int ficha, int fila_origen, int columna_origen, int fila_destino, int columna_destino);
//Funcion movimiento peon
int peon(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino);
//Funcion movimiento torre
int torre(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino);
//Funcion movimiento caballo
int caballo(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino); 
//Funcion movimiento alfil
int alfil(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino);
//Funcion movimiento reina
int reina(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino);
//Funcion movimiento rey
int rey(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino);
#endif