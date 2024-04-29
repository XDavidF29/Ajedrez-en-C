#include "juego.h"
#include <stdio.h>

EstadoJuego manejar_turnos(EstadoJuego estado_actual, Pieza tablero[TAM_TABLERO][TAM_TABLERO]) {
    switch (estado_actual) {
        case TURNO_BLANCAS:
            printf("Turno de las Blancas.\n");
            if (realizar_movimiento(tablero, BLANCO)) {
                return TURNO_NEGRAS; // Transición al turno de las Negras solo si el movimiento es válido
            } else {
                printf("Movimiento inválido. Turno de las Blancas nuevamente.\n");
                return TURNO_BLANCAS; // Permanece en el turno de las Blancas si el movimiento es inválido
            }
        case TURNO_NEGRAS:
            printf("Turno de las Negras.\n");
            if (realizar_movimiento(tablero, NEGRO)) {
                return TURNO_BLANCAS; // Transición al turno de las Blancas solo si el movimiento es válido
            } else {
                printf("Movimiento inválido. Turno de las Negras nuevamente.\n");
                return TURNO_NEGRAS; // Permanece en el turno de las Negras si el movimiento es inválido
            }
        default:
            return estado_actual; // Si no hay cambios de estado, mantener el estado actual
    }
}

int realizar_movimiento(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int color) {
    int fila_origen, columna_origen, fila_destino, columna_destino;
    printf("Ingrese la ficha que desea mover (fila columna): ");
    scanf("%d %d", &fila_origen, &columna_origen);

    if (fila_origen < 0 || fila_origen >= TAM_TABLERO || columna_origen < 0 || columna_origen >= TAM_TABLERO) {
        printf("Posición de origen inválida.\n");
        return 0; // Movimiento inválido
    }

    if (tablero[fila_origen][columna_origen].color != color) {
        printf("No hay una ficha de su color en esa posición.\n");
        return 0; // Movimiento inválido
    }

    printf("Ingrese la posición a la que desea mover la ficha (fila columna): ");
    scanf("%d %d", &fila_destino, &columna_destino);

    if (fila_destino < 0 || fila_destino >= TAM_TABLERO || columna_destino < 0 || columna_destino >= TAM_TABLERO) {
        printf("Posición de destino inválida.\n");
        return 0; // Movimiento inválido
    }

    int movimiento_valido = movimientos(tablero, tablero[fila_origen][columna_origen].tipo, fila_origen, columna_origen, fila_destino, columna_destino);
    if (!movimiento_valido) {
        printf("Movimiento inválido.\n");
        return 0; // Movimiento inválido
    }

    // Si llegamos aquí, el movimiento es válido
    imprimir_tablero(tablero);
    return 1; // Movimiento válido
}

int movimientos(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int ficha, int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    switch (ficha) {
        case VACIO:
            printf("-");
            break;
        case PEON:
            return peon(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
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
    return 0; // Movimiento inválido
}

int peon(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Implementa la lógica de movimiento y captura del peón
    if (fila_destino >= 0 && fila_destino < TAM_TABLERO && columna_destino >= 0 && columna_destino < TAM_TABLERO) {
        // Verificar si la casilla de destino está vacía
        if (tablero[fila_destino][columna_destino].tipo == VACIO) {
            // Movimiento hacia una casilla vacía
            if ((fila_destino == fila_origen + 1 && columna_destino == columna_origen + 1) || // Movimiento diagonal derecho
                (fila_destino == fila_origen + 1 && columna_destino == columna_origen - 1)) { // Movimiento diagonal izquierdo
                tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen]; // Mover la pieza
                tablero[fila_origen][columna_origen].tipo = VACIO; // Limpiar la casilla de origen
                return 1; // Movimiento exitoso
            } else {
                printf("¡Movimiento inválido! El peón solo puede moverse hacia adelante o capturar en diagonal.\n");
                return 0; // Movimiento inválido
            }
        } else {
            // La casilla de destino contiene una pieza
            if ((fila_destino == fila_origen + 1 && columna_destino == columna_origen + 1) || // Movimiento diagonal derecho
                (fila_destino == fila_origen + 1 && columna_destino == columna_origen - 1)) { // Movimiento diagonal izquierdo
                if (tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color) {
                    // La pieza enemiga en la casilla de destino puede ser capturada
                    printf("¡Has capturado una pieza enemiga!\n");
                    tablero[fila_destino][columna_destino].tipo = VACIO; // Eliminar la pieza enemiga
                    tablero[fila_destino][columna_destino].color = -1; // Actualizar el color de la casilla de destino
                    tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen]; // Mover la pieza
                    tablero[fila_origen][columna_origen].tipo = VACIO; // Limpiar la casilla de origen
                    return 1; // Movimiento exitoso
                } else {
                    printf("¡Movimiento inválido! La casilla de destino está ocupada por una pieza de tu propio color.\n");
                    return 0; // Movimiento inválido
                }
            } else {
                printf("¡Movimiento inválido! El peón solo puede moverse hacia adelante o capturar en diagonal.\n");
                return 0; // Movimiento inválido
            }
        }
    } else {
        printf("¡Movimiento inválido! La casilla de destino está fuera del tablero.\n");
        return 0; // Movimiento inválido
    }
}
