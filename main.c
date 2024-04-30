#include <stdio.h>
#include "tablero.h"
#include "juego.h"

int main() {
    Pieza tablero[TAM_TABLERO][TAM_TABLERO];
    Pieza tablero_copia[TAM_TABLERO][TAM_TABLERO];
    EstadoJuego estado_actual = TURNO_BLANCAS; // Comenzamos con el turno de las Blancas
    
    inicializar_tablero(tablero);
    imprimir_tablero(tablero);
    
    // Bucle infinito hasta que haya un ganador
    while (1) {
        estado_actual = manejar_turnos(estado_actual, tablero, tablero_copia);
        if (estado_actual == JUEGO_TERMINADO) {
            break; // Salir del bucle si el juego ha terminado
        }
    }
    
    return 0;
}
