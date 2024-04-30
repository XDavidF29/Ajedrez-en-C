#ifndef FICHAS_H
#define FCIHAS_H

#include "tablero.h"
//Buscar Rey
void buscar_rey(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int color, int *fila_rey, int *columna_rey);
//Jaque Rey
int rey_en_jaque(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int color_rey);
//Escapar Jaque
int salir_del_jaque(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int color_rey);
//Verificar casilla vacia
int casilla_vacia(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila, int columna);
//Verificar si se puede bloquear el jaque
int puede_bloquear_ataque(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_pieza, int columna_pieza, int fila_rey, int columna_rey);
//Verificar posibles movimientos del Rey
int rey_en_jaque_despues_movimiento(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int color_rey, int fila_rey, int columna_rey, int nueva_fila, int nueva_columna);
//Copia temporal del tablero para que  no afecte al original en el caso de haber escapado del jaque
void copiar_tablero(Pieza tablero_original[TAM_TABLERO][TAM_TABLERO], Pieza tablero_copia[TAM_TABLERO][TAM_TABLERO]);
//Revertir Movimiento
void deshacer_ultimo_movimiento(Pieza tablero[TAM_TABLERO][TAM_TABLERO], Pieza tablero_copia[TAM_TABLERO][TAM_TABLERO]);
//Capturar Peon
int puede_capturar_peon(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino);
//Capturar Torre
int puede_capturar_torre(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino);
//Capturar Alfil
int puede_capturar_alfil(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino);
//Capturar Caballo
int puede_capturar_caballo(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino);
//Capturar Reina
int puede_capturar_reina(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino);
#endif //TABLERO_H