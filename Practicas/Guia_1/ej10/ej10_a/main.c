#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 2, b=3, c;

    if(a < b)
        c = a;
    else
        c = b;

    printf("%d \n",c);

    //(a < b) ? c = a : c = b;
    //Los operadores ternarios esperan devolver un valor en cada rama, no hacer asignaciones en cada rama
    c = (a < b) ? a : b;

    printf("%d",c);

}
