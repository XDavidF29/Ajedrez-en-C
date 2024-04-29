#include <stdio.h>
#include "tablero.h"
#include "juego.h"

int main() {
    Pieza tablero[TAM_TABLERO][TAM_TABLERO];
    EstadoJuego estado_actual = TURNO_BLANCAS; // Comenzamos con el turno de las Blancas
    
    inicializar_tablero(tablero);
    imprimir_tablero(tablero);
    
    // Simulación de la lógica de juego
    for (int i = 0; i < 20; i++) { // Simulamos 5 turnos de juego
        estado_actual = manejar_turnos(estado_actual, tablero);
       // imprimir_tablero(tablero);
    }
    
    return 0;
}