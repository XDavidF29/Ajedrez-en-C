#include "juego.h"
#include <stdio.h>
#include <stdlib.h>


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
            return torre(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
            break;
        case CABALLO:
            return caballo(tablero, fila_origen, columna_origen, fila_destino, columna_destino); 
            break;
        case ALFIL:
            return alfil(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
            break;
        case REINA:
            return reina(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
            break;
        case REY:
            return rey(tablero, fila_origen, columna_origen, fila_destino, columna_destino);
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
            if (columna_destino == columna_origen && fila_destino != fila_origen) { // Movimiento hacia adelante
                tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen]; // Mover la pieza
                tablero[fila_origen][columna_origen].tipo = VACIO; // Limpiar la casilla de origen
                return 1; // Movimiento exitoso
            } else if ((fila_destino == fila_origen - 1 && columna_destino == columna_origen + 1) || // Movimiento diagonal derecho
                (fila_destino == fila_origen - 1 && columna_destino == columna_origen - 1)) { // Movimiento diagonal izquierdo
                // Se intenta capturar una pieza enemiga en diagonal
                printf("¡Movimiento inválido! No se puede capturar una pieza si no hay ninguna enemiga en esa casilla.\n");
                return 0; // Movimiento inválido
            } else {
                printf("¡Movimiento inválido! El peón solo puede moverse hacia adelante o capturar en diagonal.\n");
                return 0; // Movimiento inválido
            }
        } else {
            // La casilla de destino contiene una pieza
            if ((fila_destino == fila_origen - 1 && columna_destino == columna_origen + 1) || // Movimiento diagonal derecho
                (fila_destino == fila_origen - 1 && columna_destino == columna_origen - 1)) { // Movimiento diagonal izquierdo
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

int torre(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Implementa la lógica de movimiento y captura de la torre
    if ((fila_destino == fila_origen || columna_destino == columna_origen) &&  // Movimiento horizontal o vertical
        (fila_destino >= 0 && fila_destino < TAM_TABLERO && columna_destino >= 0 && columna_destino < TAM_TABLERO)) {  // Dentro del tablero
        // Verificar si hay piezas intermedias en el camino (para movimientos horizontales)
        if (fila_destino == fila_origen) {
            int paso = (columna_destino > columna_origen) ? 1 : -1; // Determinar la dirección del movimiento horizontal
            for (int j = columna_origen + paso; j != columna_destino; j += paso) {
                if (tablero[fila_origen][j].tipo != VACIO) {
                    printf("¡Movimiento inválido! Hay una pieza bloqueando el camino.\n");
                    return 0; // Movimiento inválido
                }
            }
        }
        // Verificar si hay piezas intermedias en el camino (para movimientos verticales)
        if (columna_destino == columna_origen) {
            int paso = (fila_destino > fila_origen) ? 1 : -1; // Determinar la dirección del movimiento vertical
            for (int i = fila_origen + paso; i != fila_destino; i += paso) {
                if (tablero[i][columna_origen].tipo != VACIO) {
                    printf("¡Movimiento inválido! Hay una pieza bloqueando el camino.\n");
                    return 0; // Movimiento inválido
                }
            }
        }
        // Verificar si la casilla de destino está vacía o contiene una pieza enemiga
        if (tablero[fila_destino][columna_destino].tipo == VACIO ||
            tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color) {
            // Movimiento o captura válidos
            tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen]; // Mover la pieza
            tablero[fila_origen][columna_origen].tipo = VACIO; // Limpiar la casilla de origen
            return 1; // Movimiento exitoso
        } else {
            printf("¡Movimiento inválido! La casilla de destino está ocupada por una pieza de tu propio color.\n");
            return 0; // Movimiento inválido
        }
    } else {
        printf("¡Movimiento inválido! La torre solo puede moverse horizontal o verticalmente.\n");
        return 0; // Movimiento inválido
    }
}

int alfil(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Implementa la lógica de movimiento y captura del alfil
    if (abs(fila_destino - fila_origen) == abs(columna_destino - columna_origen) &&  // Movimiento en diagonal
        (fila_destino >= 0 && fila_destino < TAM_TABLERO && columna_destino >= 0 && columna_destino < TAM_TABLERO)) {  // Dentro del tablero
        int paso_fila = (fila_destino > fila_origen) ? 1 : -1; // Determinar la dirección del movimiento en filas
        int paso_columna = (columna_destino > columna_origen) ? 1 : -1; // Determinar la dirección del movimiento en columnas
        int i = fila_origen + paso_fila;
        int j = columna_origen + paso_columna;
        // Verificar si hay piezas intermedias en el camino
        while (i != fila_destino && j != columna_destino) {
            if (tablero[i][j].tipo != VACIO) {
                printf("¡Movimiento inválido! Hay una pieza bloqueando el camino.\n");
                return 0; // Movimiento inválido
            }
            i += paso_fila;
            j += paso_columna;
        }
        // Verificar si la casilla de destino está vacía o contiene una pieza enemiga
        if (tablero[fila_destino][columna_destino].tipo == VACIO ||
            tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color) {
            // Movimiento o captura válidos
            tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen]; // Mover la pieza
            tablero[fila_origen][columna_origen].tipo = VACIO; // Limpiar la casilla de origen
            return 1; // Movimiento exitoso
        } else {
            printf("¡Movimiento inválido! La casilla de destino está ocupada por una pieza de tu propio color.\n");
            return 0; // Movimiento inválido
        }
    } else {
        printf("¡Movimiento inválido! El alfil solo puede moverse en diagonal.\n");
        return 0; // Movimiento inválido
    }
}

int caballo(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Verificar si el movimiento es válido para el caballo
    int fila_diferencia = fila_destino - fila_origen;
    int columna_diferencia = columna_destino - columna_origen;
    if ((fila_diferencia == 2 || fila_diferencia == -2) && (columna_diferencia == 1 || columna_diferencia == -1)) {
        // Movimiento válido en forma de L vertical
        // Verificar si la casilla de destino está vacía o contiene una pieza del color opuesto
        if (tablero[fila_destino][columna_destino].tipo == VACIO || tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color) {
            // Actualizar el tablero con el movimiento
            tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
            tablero[fila_origen][columna_origen].tipo = VACIO;
            return 1; // Movimiento exitoso
        }
    } else if ((fila_diferencia == 1 || fila_diferencia == -1) && (columna_diferencia == 2 || columna_diferencia == -2)) {
        // Movimiento válido en forma de L horizontal
        // Verificar si la casilla de destino está vacía o contiene una pieza del color opuesto
        if (tablero[fila_destino][columna_destino].tipo == VACIO || tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color) {
            // Actualizar el tablero con el movimiento
            tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
            tablero[fila_origen][columna_origen].tipo = VACIO;
            return 1; // Movimiento exitoso
        }
    }
    return 0; // Movimiento inválido
}

int reina(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Verificar si el movimiento es válido
    // La reina puede moverse como una torre o como un alfil
    // Por lo tanto, verificamos si el movimiento es válido para una torre o un alfil
    if ((fila_origen == fila_destino || columna_origen == columna_destino) ||
        (abs(fila_destino - fila_origen) == abs(columna_destino - columna_origen))) {
        // Verificar si hay una pieza enemiga en la casilla de destino para capturar
        if (tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color || tablero[fila_destino][columna_destino].tipo == VACIO) {
            tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen]; // Mover la reina
            tablero[fila_origen][columna_origen].tipo = VACIO; // Limpiar la casilla de origen
            return 1; // Movimiento exitoso
        }
    }
    return 0; // Movimiento inválido
}

int rey(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Verificar si el movimiento es válido para el rey
    // El rey puede moverse una casilla en cualquier dirección (horizontal, vertical o diagonal)
    // Verificamos que la casilla de destino esté dentro del tablero y no contenga una pieza del mismo color
    if (fila_destino >= 0 && fila_destino < TAM_TABLERO && columna_destino >= 0 && columna_destino < TAM_TABLERO &&
        (tablero[fila_destino][columna_destino].tipo == VACIO || tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color)) {
        int fila_dif = abs(fila_destino - fila_origen);
        int col_dif = abs(columna_destino - columna_origen);
        // Verificamos si el movimiento es de una sola casilla en cualquier dirección
        if ((fila_dif == 1 && col_dif == 0) || (fila_dif == 0 && col_dif == 1) || (fila_dif == 1 && col_dif == 1)) {
            tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen]; // Mover la pieza
            tablero[fila_origen][columna_origen].tipo = VACIO; // Limpiar la casilla de origen
            return 1; // Movimiento exitoso
        }
    }
    return 0; // Movimiento inválido
}