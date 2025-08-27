#include <stdio.h>
#include <stdlib.h>

int main() {
    int a=1, b=2, c=3;

    if (a < b && b<c)
        printf("ordenados \n");
    else
        printf("desordenados \n");

    (a < b && b<c) ? printf("ordenados") : printf("desordenados");

    //Como vemos, cuando se trata de devolver valores debemos asignar algo a la expresion del operador ternario
    //En cambio cuando queremos ejecutar acciones, no hace falta asignar a nada
}
