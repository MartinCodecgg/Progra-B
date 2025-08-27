#include <stdio.h>
#include <stdlib.h>
#define N 8

int main() {
    int i,j;

    for(i = N; i > 0; --i)
        printf("#");

    printf("\n");

    for(i = N - 2; i > 0; --i)  {
        printf("#");

        for(j = N -2; j > 0 ; --j) //Recordar siempre que tenga un ciclo dentro de otro ciclo, debere usar dos variables de iteracion
            printf(" "); //printf() no admite comillas simples

        printf("# \n");
    }

    for(i = N; i > 0; --i)
        printf("#");

    return 0;
}
