#include <stdio.h>
#include <stdlib.h>

/*
4. Desarrollar un programa que cree dinámicamente un arreglo de números reales que contenga
N elementos (N es ingresado por teclado). Ingresar sus elementos y mostrar aquellos que sean
positivos utilizando aritmética de punteros. Al finalizar, liberar la memoria solicitada en tiempo
de ejecución.
*/

void creaArrayDinamico(int* *ptr,unsigned int *n); //recibo un puntero a un puntero, pero en si recibo un puntero, luego usando * solo trabajo con el puntero al entero

int main() {

    int* ptr;
    unsigned int n;

    printf("Ingrese N \n");
    scanf("%d",&n);

    creaArrayDinamico(&ptr, &n);

    //adicional muestro el arraglo generado

    unsigned short i;
    for (i = 0; i<n; ++i)
        printf("%d ",(ptr)[i]); //recordar que los arrays ya son punteros, por ello con solo hacer ptr[] ya accedi al array y no hace falta usar *

    free(ptr);

    return 0;
}

void creaArrayDinamico(int* *ptr, unsigned int *n) {

    *ptr = (int*) malloc( (*n) * sizeof(int));  //int[n] imposible definir la dimension de un array con una variable
                                               //defino para un entero y luego multiplico por la dimension del array

    printf("Ingrese los valores de las componentes del array \n");
    unsigned short i;
    for (i = 0; i<*n; ++i)
        scanf(" %d",&(*ptr)[i]); //recordar que scanF pide la direccion de memoria y no el entero original
                                    //y debo usar & para leer componentes del array
}
