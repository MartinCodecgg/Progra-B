#include <stdio.h>
#include <stdlib.h>

/*
3. Implementar un programa que cree dinámicamente 3 variables enteras (pint1, pint2 y pint3),
muestre su suma y su producto. No utilizar estructuras iterativas. Asegurarse de administrar
correctamente la memoria e implementar una función para evitar duplicaciones de código en la
creación y lectura de cada variable(porque tenemos que definir 3) . Desarrollar en primera instancia una función que retorne
un puntero a entero. Para cumplir con el paradigma de programación estructurada, convertir
en una función void que retorne el resultado como parámetro de salida.
*/

void creaEnteroDinamico(int* *ptr); //recibo un puntero a un puntero, pero en si recibo un puntero, luego usando * solo trabajo con el puntero al entero

void muestraProducto(int* *ptr1,int* *ptr2,int* *ptr3);

int main() {

    int *ptr1, *ptr2, *ptr3; //nose cuantas variables se usaran por ello llamar a la funcion para cada una

    creaEnteroDinamico(&ptr1); //Debo pasar la direccion del puntero(no del entero original), porque voy a modificar el puntero
    creaEnteroDinamico(&ptr2);
    creaEnteroDinamico(&ptr3);

    //la suma la hago en el main y el producto en un "procedimiento" para asi cubrir todos los casos
    printf("La suma es: %d \n",*ptr1 + *ptr2 + *ptr3);

    muestraProducto(&ptr1,&ptr2,&ptr3); //Podria pasar los punteros como copia directamente entonces aqui solo seria pasar ptr1,ptr2,ptr3
                                        //Pero decido pasar punteros a punteros

    free(ptr1); free(ptr2); free(ptr3);     //recordar luego liberar la memoria, y si vamos a seguir en el mismo programa hacer puntero = NULL

    return 0;
}

void creaEnteroDinamico(int* *ptr) { //recibo un puntero a un puntero, en los parametros debo declarar lo que recibe la funcion, y justamente recibe un puntero a otro puntero
    //Entonces con *ptr trabajo con ptr1
    *ptr = (int*) malloc(sizeof(int));     //malloc devuelve un puntero a la direccion de memoria creada dinamicamente, por ello lo guardo en *ptr

    printf("Ingrese un valor para el entero dinamico \n");
    scanf("%d",*ptr); //scanf espera la DIRECCION no el entero original, por ello le pasamos solo *ptr que es la direccion al entero (es decir ptr1)
}

void muestraProducto(int* *ptr1,int* *ptr2,int* *ptr3) { //recibo un puntero a puntero, luego si quiero acceder al entero original debo hacer **

    printf("El producto es: %d \n",(**ptr1) * (**ptr2) * (**ptr3));
}
