#include <stdio.h>

/*
22. Responder:
a) �Por qu� no es correcta la siguiente sentencia: scanf("%s", &cad)?
b) �Qu� instrucci�n resulta conveniente para leer por teclado apellido y nombre de una
persona: gets o scanf? Justificar la elecci�n.
c) �Qu� representan los valores devueltos por la funci�n strcmp?
*/

int main() {

    //a) �Por qu� no es correcta la siguiente sentencia: scanf("%s", &cad)?

    //Porque no es necesario el ampersand, porque cad ya es un puntero

    //b) �Qu� instrucci�n resulta conveniente para leer por teclado apellido y nombre de una
        //persona: gets o scanf? Justificar la elecci�n.

    //gets ya que contiene un espacio, y el scanf no los maneja bien

    //c) �Qu� representan los valores devueltos por la funci�n strcmp?

    //strcmp(cad1,cad2) , devuelve 0 si son iguales, negativo si cad1 es menor, positivo si cad 1 es mayor


    return 0;
}
