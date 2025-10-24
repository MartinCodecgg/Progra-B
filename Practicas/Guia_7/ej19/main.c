#include <stdio.h>

typedef struct nodo {
    int dato;
    struct nodo *izq, *der;
} nodo;

typedef nodo * Arbol;

int cuenta(Arbol A) {
    unsigned int cont = 0;
    while(A != NULL) {
        cont++;
        A = A->der;
    }
    return cont;
}

int main() {
    Arbol A;
    //cargaA(&A);
    printf("El arbol binario proviene de un bosque de %d arboles generales",cuenta(A));
    return 0;
}
