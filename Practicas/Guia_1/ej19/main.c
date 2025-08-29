#include <stdio.h>

/*
19. Responder, siendo x un arreglo de 10 enteros (int x[10]):
a) ¿Se puede determinar por la siguiente invocación funarr(x, n) si x es parámetro de entrada o
de salida?
b) ¿Se puede acceder al contenido de x[10]? ¿Qué representa el valor obtenido?
*/

int main() {

    funarr(x, n) // a) En C cuando pasamos un puntero como parametro, se pasa un puntero, porque el arreglo es un puntero
                 //Por ello se puede modificar el arreglo dentro de la funcion,
                //pero esto no significa que sea un parametro de salida (su valor se modifica), porque si solo lo leemos no se modifica
                //y no seria un parametro de salida

    /* RECORDAR: Parametro de entrada => Pasar a la funcion como parametro en si
                 Parametro de salida => Cuando su valor de modifica en la funcion

                // b) no se puede acceder, porque va del 0 al 9 las componentes del array

    return 0;
}
