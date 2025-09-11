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
    TPila P;
    TElementoP elem;
    IniciaP(&P); //P es un struct, IniciaP() espera una direccion de memoria, y por eso debo pasar con &

    while(fscanf(arch,"%c\n",&elem) == 1) { //recordar el & en fscanf
        poneP(&P,elem);
    }

    printf("Muestro contenido manteniendo la informacion de la cola\n");
    muestraManteniendo(&P);
    printf("Muestro contenido perdiendo la informacion de la cola\n");

    while(!VaciaP(P)) {
        sacaP(&P,&elem);
        printf("%c\n",elem);
    }
    return 0;
}

void muestraManteniendo(TPila* P) {

    TPila Paux;
    TElementoP elem;
    IniciaP(&Paux);

    while(!VaciaP(*P)) {
        sacaP(P,&elem);
        poneP(&Paux,elem);
        printf("%c\n",elem);
    }

    while(!VaciaP(Paux)) {
        sacaP(&Paux,&elem);
        poneP(P,elem);
    }
}
