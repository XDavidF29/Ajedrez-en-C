#include <stdio.h>
#include "tablero.h"

int main(){
    Tablero tablero;
    
    inicializar_tablero(&tablero);

    imprimir_tablero(&tablero);
}
