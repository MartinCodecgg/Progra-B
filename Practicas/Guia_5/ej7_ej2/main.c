#include <stdio.h>
#include "pilas.h"
/*
2. Ingresar en una pila los caracteres almacenados (uno por línea) en un archivo de texto. Mostrar
el contenido de la pila.
a. Utilizar la implementación estática.
b. Utilizar la implementación dinámica.
c. Mantener la información en la pila.
*/

void muestraManteniendo(TPila* P);

int main() {

    FILE* arch = fopen("caracteres.txt","rt");

    if(arch == NULL)
        printf("Erroe al abrir el archivo");
    else {

    printf("Archivo abierto correctamente");
    TPila P;
    TElementoP elem;
    IniciaP(&P); //P es un struct, IniciaP() espera una direccion de memoria, y por eso debo pasar con &

    //carga de la pila (deberia hacerse en una funcion aparte)
    while(fscanf(arch,"%c\n",&elem) == 1) { //recordar el & en fscanf
        poneP(&P,elem);
    }
    printf("Muestra manteniendo la integridad de la pila\n");
    muestraRec(&P);

    }

    return 0;
}
