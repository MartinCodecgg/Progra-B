#include <stdio.h>
#include "pilas.h"

/*
3. Ingresar los números de DNI de los votantes de una mesa a medida que van votando y mostrar
los últimos N (es dato) votantes
a. en orden inverso, comenzando por el último votante.
*/

int main() {

    TPila P;
    IniciaP(&P);
    float dni;
    int n,i;
    printf("Ingrese la cantidad de DNI's que quiere ingresar\n");
    scanf(" %d",&n);

    printf("A continuacion ingrese los %d que quiere ingresar\n",n);
    for(i=0; i<n; ++i) {
        scanf(" %f",&dni);
        poneP(&P,dni);
    }

    //Mostrar los datos guardados
    printf("Muestra los datos de forma recursiva\n");

    muestraRec(&P);

    printf("Muestra los datos de forma recursiva de forma invertida\n");

    muestraRecInverso(&P);

    return 0;
}
