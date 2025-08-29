#include <stdio.h> //verif C

int main() {
    //Cambie un poco las declaraciones respecto de la guia para que el programa compile pero los comentarios estan bien

    //Enumerar los valores de todos los componentes de los siguientes arreglos

    int v1[4] = {0}; // Un vector de 0 a 3 inicializado en cero
    int v2[5] = {6}; // Un vector de 0 a , su primer componente tiene 6 y las demas 0
    int v3[] = {2,4,6}; // Un vector de 0 a 2 con las componentes asignadas, el compilador intuye su dimension (3)

    // Especificar los arreglos de caracteres que pueden ser utilizados correctamente como cadenas. (ninguno)

    char s1[4] = {'h','o','y'}; // Usa backtips y no comillas simples, falta caracter nulo, la dimension es 4 y lo
                                //asignado tiene dimension 3, por lo que el caracter nulo se agrega solo y es una cadena Valida

    /* La regla de C dice que los elementos que sobren se rellenan automáticamente con cero binario (0), haciendo valida esta cadena */

    char s2[] = {'h','o','y'}; // Usa backtips y no comillas simples, falta caracter nulo, igual que el caso anterior pero no es valida ya que
                               //no se agrega el caracter nulo automaticamente, porque la dimension que se infiere es 3, solo es un array de caracteres

    char s3[4]= {'h','o','y','\0'}; //// Usa backtips y no comillas simples, luego lo demas esta bien

    return 0;
}
