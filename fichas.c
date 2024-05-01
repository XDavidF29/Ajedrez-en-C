#include "fichas.h"
#include <stdio.h>
#include <stdlib.h>

void buscar_rey(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int color, int *fila_rey, int *columna_rey) {
    for (int i = 0; i < TAM_TABLERO; i++) {
        for (int j = 0; j < TAM_TABLERO; j++) {
            if (tablero[i][j].tipo == REY && tablero[i][j].color == color) {
                *fila_rey = i;
                *columna_rey = j;
                return; // Se encontró el rey, salir de la función
            }
        }
    }
}

int rey_en_jaque(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int color_rey) {
    // Encontrar la posición del rey del color dado en el tablero
    int fila_rey, columna_rey;
    for (int fila = 0; fila < TAM_TABLERO; fila++) {
        for (int columna = 0; columna < TAM_TABLERO; columna++) {
            if (tablero[fila][columna].tipo == REY && tablero[fila][columna].color == color_rey) {
                fila_rey = fila;
                columna_rey = columna;
                break;
            }
        }
    }
    
    // Iterar sobre todas las piezas del color opuesto
    int color_opuesto = (color_rey == BLANCO) ? NEGRO : BLANCO;
    for (int fila = 0; fila < TAM_TABLERO; fila++) {
        for (int columna = 0; columna < TAM_TABLERO; columna++) {
            // Verificar si la pieza es del color opuesto
            if (tablero[fila][columna].color == color_opuesto) {
                // Verificar si la pieza puede capturar la posición del rey
                switch (tablero[fila][columna].tipo) {
                    case PEON:
                        if (puede_capturar_peon(tablero, fila, columna, fila_rey, columna_rey)) {
                            return 1; // El rey está en jaque
                        }
                        break;
                    case TORRE:
                        if (puede_capturar_torre(tablero, fila, columna, fila_rey, columna_rey)) {
                            return 1; // El rey está en jaque
                        }
                        break;
                    case CABALLO:
                        if (puede_capturar_caballo(tablero, fila, columna, fila_rey, columna_rey)) {
                            return 1; // El rey está en jaque
                        }
                        break; // Añadir break aquí
                    case ALFIL:
                        if (puede_capturar_alfil(tablero, fila, columna, fila_rey, columna_rey)) {
                            return 1; // El rey está en jaque
                        }
                        break; // Añadir break aquí
                    case REINA:
                        if (puede_capturar_reina(tablero, fila, columna, fila_rey, columna_rey)) {
                            return 1; // El rey está en jaque
                        }
                        break; // Añadir break aquí
                }
            }
        }
    }
    
    // Si ninguna pieza del color opuesto puede capturar la posición del rey, el rey no está en jaque
    return 0;
}

int salir_del_jaque(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int color_rey) {
    // Buscar la posición del rey
    int fila_rey = -1;
    int columna_rey = -1;
    for (int fila = 0; fila < TAM_TABLERO; ++fila) {
        for (int columna = 0; columna < TAM_TABLERO; ++columna) {
            if (tablero[fila][columna].tipo == REY && tablero[fila][columna].color == color_rey) {
                fila_rey = fila;
                columna_rey = columna;
                break;
            }
        }
    }
    // Verificar si hay algún movimiento posible para el rey
    for (int df = -1; df <= 1; ++df) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (df == 0 && dc == 0) continue; // No revisar la posición actual del rey
            int nueva_fila = fila_rey + df;
            int nueva_columna = columna_rey + dc;
            // Verificar si la nueva posición está dentro del tablero
            if (nueva_fila >= 0 && nueva_fila < TAM_TABLERO && nueva_columna >= 0 && nueva_columna < TAM_TABLERO) {
                // Verificar si el movimiento al nuevo lugar evitaría el jaque
                if (!rey_en_jaque_despues_movimiento(tablero, color_rey, fila_rey, columna_rey, nueva_fila, nueva_columna)) {
                    return 1; // Hay al menos un movimiento posible para el rey
                }
            }
        }
    }
    // Verificar si alguna pieza propia puede bloquear el ataque del oponente
    for (int fila = 0; fila < TAM_TABLERO; ++fila) {
        for (int columna = 0; columna < TAM_TABLERO; ++columna) {
            if (tablero[fila][columna].color == color_rey) {
                // Verificar si esta pieza puede bloquear el ataque
                if (puede_bloquear_ataque(tablero, fila, columna, fila_rey, columna_rey)) {
                    return 1; // Hay al menos un movimiento posible para bloquear el ataque
                }
            }
        }
    }
    // No hay movimientos posibles para el rey ni para bloquear el ataque
    return 0;
}

int casilla_vacia(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila, int columna) {
    // Verificar si la casilla está vacía (es decir, si la pieza en esa posición es de tipo VACIO)
    return tablero[fila][columna].tipo == VACIO;
}

int puede_bloquear_ataque(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_pieza, int columna_pieza, int fila_rey, int columna_rey) {
    // Verificar si la pieza puede moverse a una posición que bloquee el ataque
    switch (tablero[fila_pieza][columna_pieza].tipo) {
        case PEON:
            // Verificar si el peón puede bloquear el ataque
            // El peón solo puede bloquear el ataque si el rey está en la misma columna y hay una pieza del oponente en la casilla diagonal
            if (columna_pieza == columna_rey) {
                int direccion = (fila_pieza < fila_rey) ? 1 : -1;
                int fila_diagonal = fila_pieza + direccion;
                // Verificar si hay una pieza del oponente en la casilla diagonal
                if (fila_diagonal >= 0 && fila_diagonal < TAM_TABLERO && !casilla_vacia(tablero, fila_diagonal, columna_pieza)) {
                    return 1; // El peón puede bloquear el ataque
                }
            }
            return 0; // El peón no puede bloquear el ataque

        case TORRE:
            // Verificar si la torre puede bloquear el ataque en horizontal o vertical
            if (fila_pieza == fila_rey) {
                // La torre está en la misma fila que el rey, verificar si puede bloquear en horizontal
                int direccion = (columna_pieza < columna_rey) ? 1 : -1;
                for (int columna = columna_pieza + direccion; columna != columna_rey; columna += direccion) {
                    if (!casilla_vacia(tablero, fila_pieza, columna)) {
                        return 0; // Hay una pieza bloqueando el camino
                    }
                }
                return 1; // La torre puede bloquear el ataque en horizontal
            } else if (columna_pieza == columna_rey) {
                // La torre está en la misma columna que el rey, verificar si puede bloquear en vertical
                int direccion = (fila_pieza < fila_rey) ? 1 : -1;
                for (int fila = fila_pieza + direccion; fila != fila_rey; fila += direccion) {
                    if (!casilla_vacia(tablero, fila, columna_pieza)) {
                        return 0; // Hay una pieza bloqueando el camino
                    }
                }
                return 1; // La torre puede bloquear el ataque en vertical
            }
            return 0; // La torre no puede bloquear el ataque en la dirección del rey

        case ALFIL:
            // Verificar si el alfil puede bloquear el ataque en diagonal
            if (abs(fila_pieza - fila_rey) == abs(columna_pieza - columna_rey)) {
                // El alfil puede bloquear el ataque en diagonal si no hay piezas en el camino
                int paso_fila = (fila_rey > fila_pieza) ? 1 : -1;
                int paso_columna = (columna_rey > columna_pieza) ? 1 : -1;
                int fila = fila_pieza + paso_fila;
                int columna = columna_pieza + paso_columna;
                while (fila != fila_rey && columna != columna_rey) {
                    if (!casilla_vacia(tablero, fila, columna)) {
                        return 0; // Hay una pieza bloqueando el camino
                    }
                    fila += paso_fila;
                    columna += paso_columna;
                }
                return 1; // El alfil puede bloquear el ataque en diagonal
            }
            return 0; // El alfil no puede bloquear el ataque en la dirección del rey

        case CABALLO:
            // Verificar si el caballo puede bloquear el ataque
            // El caballo puede bloquear el ataque si puede moverse a la posición del atacante
            for (int df = -2; df <= 2; df++) {
                for (int dc = -2; dc <= 2; dc++) {
                    if (abs(df * dc) == 2) {
                        int nueva_fila = fila_pieza + df;
                        int nueva_columna = columna_pieza + dc;
                        if (nueva_fila >= 0 && nueva_fila < TAM_TABLERO && nueva_columna >= 0 && nueva_columna < TAM_TABLERO &&
                            (nueva_fila != fila_rey || nueva_columna != columna_rey)) {
                            return 1; // El caballo puede bloquear el ataque
                        }
                    }
                }
            }
            return 0; // El caballo no puede bloquear el ataque

        case REINA:
            // Verificar si la reina puede bloquear el ataque en horizontal, vertical o diagonal
            // Utilizar la lógica de la torre y el alfil para verificar las direcciones
            if ((fila_pieza == fila_rey) || (columna_pieza == columna_rey)) {
                // Verificar si la reina puede bloquear en horizontal o vertical
                return puede_bloquear_ataque(tablero, fila_pieza, columna_pieza, fila_rey, columna_rey);
            } else if (abs(fila_pieza - fila_rey) == abs(columna_pieza - columna_rey)) {
                // Verificar si la reina puede bloquear en diagonal
                return puede_bloquear_ataque(tablero, fila_pieza, columna_pieza, fila_rey, columna_rey);
            }
            return 0; // La reina no puede bloquear el ataque en la dirección del rey

        default:
            return 0; // La pieza no puede bloquear el ataque
    }
}

int rey_en_jaque_despues_movimiento(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int color_rey, int fila_rey, int columna_rey, int nueva_fila, int nueva_columna) {
    // Realizar una copia temporal del tablero para simular el movimiento
    Pieza tablero_temporal[TAM_TABLERO][TAM_TABLERO];
    copiar_tablero(tablero, tablero_temporal);

    // Realizar el movimiento en la copia temporal del tablero
    tablero_temporal[nueva_fila][nueva_columna] = tablero_temporal[fila_rey][columna_rey];
    tablero_temporal[fila_rey][columna_rey].tipo = VACIO;

    // Verificar si el rey está en jaque después del movimiento
    return rey_en_jaque(tablero_temporal, color_rey);
}

void copiar_tablero(Pieza tablero_original[TAM_TABLERO][TAM_TABLERO], Pieza tablero_copia[TAM_TABLERO][TAM_TABLERO]) {
    for (int fila = 0; fila < TAM_TABLERO; fila++) {
        for (int columna = 0; columna < TAM_TABLERO; columna++) {
            tablero_copia[fila][columna].tipo = tablero_original[fila][columna].tipo;
            tablero_copia[fila][columna].color = tablero_original[fila][columna].color;
        }
    }
}

void deshacer_ultimo_movimiento(Pieza tablero[TAM_TABLERO][TAM_TABLERO], Pieza tablero_copia[TAM_TABLERO][TAM_TABLERO]) {
    for (int fila = 0; fila < TAM_TABLERO; fila++) {
        for (int columna = 0; columna < TAM_TABLERO; columna++) {
            tablero[fila][columna].tipo = tablero_copia[fila][columna].tipo;
            tablero[fila][columna].color = tablero_copia[fila][columna].color;
        }
    }
}

void deshacer_penultimo_movimiento(Pieza tablero[TAM_TABLERO][TAM_TABLERO], Pieza tablero_copia[TAM_TABLERO][TAM_TABLERO]) {
    // Copiar el tablero desde la copia
    copiar_tablero(tablero_copia, tablero);
}

int puede_capturar_peon(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Verificar si la casilla de destino está vacía
    if (tablero[fila_destino][columna_destino].tipo == VACIO) {
        // Movimiento hacia una casilla vacía
        if (columna_destino == columna_origen && fila_destino != fila_origen) { // Movimiento hacia adelante
            return 1; // Movimiento exitoso
        } else if ((fila_destino == fila_origen - 1 && columna_destino == columna_origen + 1) || // Movimiento diagonal derecho
            (fila_destino == fila_origen - 1 && columna_destino == columna_origen - 1)) { // Movimiento diagonal izquierdo
            // Se intenta capturar una pieza enemiga en diagonal
            if (tablero[fila_destino][columna_destino].color != tablero[fila_origen][columna_origen].color) {
                return 1; // Movimiento exitoso
            } else {
                return 0; // Movimiento inválido
            }
        } else {
            return 0; // Movimiento inválido
        }
    } else {
        // La casilla de destino contiene una pieza
        //printf("¡Movimiento inválido! La casilla de destino está ocupada.\n");
        return 0; // Movimiento inválido
    }
}

int puede_capturar_torre(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Verifica si la casilla de destino está en la misma fila o columna que la torre
    if (fila_destino == fila_origen || columna_destino == columna_origen) {
        // Verifica si hay piezas intermedias entre la torre y la casilla de destino
        int paso_fila = (fila_destino > fila_origen) ? 1 : ((fila_destino < fila_origen) ? -1 : 0);
        int paso_columna = (columna_destino > columna_origen) ? 1 : ((columna_destino < columna_origen) ? -1 : 0);
        int i = fila_origen + paso_fila;
        int j = columna_origen + paso_columna;
        while (i != fila_destino || j != columna_destino) {
            if (tablero[i][j].tipo != VACIO) {
                // Hay una pieza intermedia, la torre no puede capturar al rey
                return 0;
            }
            i += paso_fila;
            j += paso_columna;
        }
        // No hay piezas intermedias, la torre puede capturar al rey
        return 1;
    }
    // La casilla de destino no está en la misma fila ni columna que la torre, no puede capturar al rey
    return 0;
}

int puede_capturar_alfil(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Verificar si el movimiento es en diagonal y está dentro del tablero
    if (abs(fila_destino - fila_origen) == abs(columna_destino - columna_origen) && 
        fila_destino >= 0 && fila_destino < TAM_TABLERO && columna_destino >= 0 && columna_destino < TAM_TABLERO) {
        
        // Determinar la dirección del movimiento en filas y columnas
        int paso_fila = (fila_destino > fila_origen) ? 1 : -1;
        int paso_columna = (columna_destino > columna_origen) ? 1 : -1;

        // Verificar si hay piezas intermedias en el camino
        int i = fila_origen + paso_fila;
        int j = columna_origen + paso_columna;
        while (i != fila_destino && j != columna_destino) {
            if (tablero[i][j].tipo != VACIO) {
                // Hay una pieza intermedia, el alfil no puede capturar la casilla de destino
                return 0;
            }
            i += paso_fila;
            j += paso_columna;
        }
        
        // No hay piezas intermedias, el alfil puede capturar la casilla de destino
        return 1;
    } else {
        // El movimiento no es en diagonal o está fuera del tablero
        return 0;
    }
}

int puede_capturar_caballo(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Verificar si el movimiento es válido para el caballo
    int fila_diferencia = fila_destino - fila_origen;
    int columna_diferencia = columna_destino - columna_origen;
    if ((fila_diferencia == 2 || fila_diferencia == -2) && (columna_diferencia == 1 || columna_diferencia == -1)) {
        // Movimiento válido en forma de L vertical
        return 1;
    } else if ((fila_diferencia == 1 || fila_diferencia == -1) && (columna_diferencia == 2 || columna_diferencia == -2)) {
        // Movimiento válido en forma de L horizontal
        return 1;
    }
    return 0; // Movimiento inválido
}

int puede_capturar_reina(Pieza tablero[TAM_TABLERO][TAM_TABLERO], int fila_origen, int columna_origen, int fila_destino, int columna_destino) {
    // Verificar si el movimiento es válido para la reina
    if ((fila_origen == fila_destino || columna_origen == columna_destino) ||
        (abs(fila_destino - fila_origen) == abs(columna_destino - columna_origen))) {
        return 1; // Movimiento válido
    }
    return 0; // Movimiento inválido
}