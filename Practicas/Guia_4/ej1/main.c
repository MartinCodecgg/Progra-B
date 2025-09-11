#include <stdio.h>
#include "fracciones.h"

int main() {

    int n,d;
    fraccion f1,f2,faux;

    printf("Ingrese el numerador y denominador de la fraccion\n");
    scanf("%d %d",&n,&d);

    f1 = crear(n,d);

    printf("Ingrese el numerador y denominador de la 2da fraccion\n");
    scanf("%d %d",&n,&d);

    f2 = crear(n,d);

    faux = sumar(f1,f2);

    printf("La suma equivale a: %d/%d\n",numerador(faux),denominador(faux));

    if(iguales(f1,f2))
        printf("Las fracciones son iguales");
    else
        printf("Las fracciones no son iguales");

    return 0;
}
