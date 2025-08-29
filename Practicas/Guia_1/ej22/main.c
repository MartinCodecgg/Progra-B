#include <stdio.h>

/*
22. Responder:
a) ¿Por qué no es correcta la siguiente sentencia: scanf("%s", &cad)?
b) ¿Qué instrucción resulta conveniente para leer por teclado apellido y nombre de una
persona: gets o scanf? Justificar la elección.
c) ¿Qué representan los valores devueltos por la función strcmp?
*/

int main() {

    //a) ¿Por qué no es correcta la siguiente sentencia: scanf("%s", &cad)?

    //Porque no es necesario el ampersand, porque cad ya es un puntero

    //b) ¿Qué instrucción resulta conveniente para leer por teclado apellido y nombre de una
        //persona: gets o scanf? Justificar la elección.

    //gets ya que contiene un espacio, y el scanf no los maneja bien

    //c) ¿Qué representan los valores devueltos por la función strcmp?

    //strcmp(cad1,cad2) , devuelve 0 si son iguales, negativo si cad1 es menor, positivo si cad 1 es mayor


    return 0;
}
