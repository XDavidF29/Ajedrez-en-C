#include "juego.h"
#include "fichas.h"
#include <stdio.h>
#include <stdlib.h>

EstadoJuego manejar_turnos(EstadoJuego estado_actual, Pieza tablero[TAM_TABLERO][TAM_TABLERO], Pieza tablero_copia[TAM_TABLERO][TAM_TABLERO]) {
    switch (estado_actual) {
        case TURNO_BLANCAS:
            printf("Turno de las Blancas.\n");
            imprimir_simbolos();

            // Copiar el tablero antes de realizar cualquier movimiento
            copiar_tablero(tablero, tablero_copia);

            if (rey_en_jaque(tablero, BLANCO)) {
                printf("Rey en Jaque.\n");
                if (!salir_del_jaque(tablero, BLANCO)) {
                    printf("¡Jaque mate! Las Negras ganan.\n");
                    return JUEGO_TERMINADO;
                }
            }
            if (realizar_movimiento(tablero, BLANCO)) {
                if (rey_en_jaque(tablero, BLANCO)) {
                    // Deshacer el último movimiento si el rey sigue en jaque
                    deshacer_ultimo_movimiento(tablero, tablero_copia);
                    printf("El rey de las Blancas sigue en jaque.\n");
                    return TURNO_BLANCAS; // Permanecer en el turno de las Blancas
                } else {
                    return TURNO_NEGRAS; // Cambiar al turno de las Negras
                }
            } else {
                printf("Movimiento inválido. Turno de las Blancas nuevamente.\n");
                return TURNO_BLANCAS;
            }
        case TURNO_NEGRAS:
            printf("Turno de las Negras.\n");
            imprimir_simbolos();

            // Copiar el tablero antes de realizar cualquier movimiento
            copiar_tablero(tablero, tablero_copia);

            if (rey_en_jaque(tablero, NEGRO)) {
                printf("Rey en Jaque.\n");
                if (!salir_del_jaque(tablero, NEGRO)) {
                    printf("¡Jaque mate! Las Blancas ganan.\n");
                    return JUEGO_TERMINADO;
                }
            }
            if (realizar_movimiento(tablero, NEGRO)) {
                if (rey_en_jaque(tablero, NEGRO)) {
                    // Deshacer el último movimiento si el rey sigue en jaque
                    deshacer_ultimo_movimiento(tablero, tablero_copia);
                    printf("El rey de las Negras sigue en jaque.\n");
                    return TURNO_NEGRAS; // Permanecer en el turno de las Negras
                } else {
                    return TURNO_BLANCAS; // Cambiar al turno de las Blancas
                }
            } else {
                printf("Movimiento inválido. Turno de las Negras nuevamente.\n");
                return TURNO_NEGRAS;
            }
        default:
            return estado_actual;
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
        // Verificar si el movimiento es válido según la función puede_capturar_peon
        if (puede_capturar_peon(tablero, fila_origen, columna_origen, fila_destino, columna_destino)) {
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
                    if (tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color) {
                        printf("¡Has capturado una pieza enemiga!\n");
                        tablero[fila_destino][columna_destino].tipo = VACIO; // Eliminar la pieza enemiga
                        tablero[fila_destino][columna_destino].color = -1; // Actualizar el color de la casilla de destino
                        tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen]; // Mover la pieza
                        tablero[fila_origen][columna_origen].tipo = VACIO; // Limpiar la casilla de origen
                        return 1; // Movimiento exitoso
                    } else {
                        printf("¡Movimiento inválido! No se puede capturar una pieza si no hay ninguna enemiga en esa casilla.\n");
                        return 0; // Movimiento inválido
                    }
                } else {
                    printf("¡Movimiento inválido! El peón solo puede moverse hacia adelante o capturar en diagonal.\n");
                    return 0; // Movimiento inválido
                }
            } else {
                // La casilla de destino contiene una pieza
                printf("¡Movimiento inválido! La casilla de destino está ocupada.\n");
                return 0; // Movimiento inválido
            }
        } else {
            // El movimiento no es válido según la función puede_capturar_peon
            printf("¡Movimiento inválido!\n");
            return 0; // Movimiento inválido
        }
    } else {
        printf("¡Movimiento inválido! La casilla de destino está fuera del tablero.\n");
        return 0; // Movimiento inválido
    }
}

int torre(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    int fila_rey, columna_rey;
    buscar_rey(tablero, (tablero[fila_origen][columna_origen].color == BLANCO) ? NEGRO : BLANCO, &fila_rey, &columna_rey);

    // Verificar si la casilla de destino está en la misma fila o columna que la torre
    if (puede_capturar_torre(tablero, fila_origen, columna_origen, fila_destino, columna_destino)) {
        // Verificar si la casilla de destino está vacía o contiene una pieza enemiga
        if (tablero[fila_destino][columna_destino].tipo == VACIO ||
            tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color) {
            // Movimiento o captura válidos
            tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen]; // Mover la pieza
            tablero[fila_origen][columna_origen].tipo = VACIO; // Limpiar la casilla de origen

            // Verificar si el movimiento pone al rey enemigo en jaque
            if (fila_destino == fila_rey || columna_destino == columna_rey) {
                printf("Jaque! La torre amenaza al rey enemigo.\n");
            }

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
    // Verificar si el movimiento es válido según las reglas del alfil
    if (puede_capturar_alfil(tablero, fila_origen, columna_origen, fila_destino, columna_destino)) {
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
    if (puede_capturar_caballo(tablero, fila_origen, columna_origen, fila_destino, columna_destino)) {
        // Verificar si la casilla de destino está vacía o contiene una pieza del color opuesto
        if (tablero[fila_destino][columna_destino].tipo == VACIO || tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color) {
            // Actualizar el tablero con el movimiento
            tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
            tablero[fila_origen][columna_origen].tipo = VACIO;
            return 1; // Movimiento exitoso
        }
    }
    printf("¡Movimiento inválido! El caballo solo puede moverse en forma de L.\n");
    return 0; // Movimiento inválido
}

int reina(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Verificar si el movimiento es válido para la reina
    if (puede_capturar_reina(tablero, fila_origen, columna_origen, fila_destino, columna_destino)) {
        // Verificar si la casilla de destino está vacía o contiene una pieza del color opuesto
        if (tablero[fila_destino][columna_destino].tipo == VACIO || tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color) {
            // Actualizar el tablero con el movimiento
            tablero[fila_destino][columna_destino] = tablero[fila_origen][columna_origen];
            tablero[fila_origen][columna_origen].tipo = VACIO;
            return 1; // Movimiento exitoso
        }
    }
    printf("¡Movimiento inválido! La reina solo puede moverse como una torre o un alfil.\n");
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