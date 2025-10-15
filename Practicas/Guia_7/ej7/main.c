#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *izq, *der;
} nodo;

typedef nodo * Arbol;

void suma(Arbol A, int *acum, int nivelActual, int x) {
    if(A) {
        nivelActual++;
        if((A->der == NULL && A->izq != NULL ||
            A->der != NULL && A->izq == NULL)&&
            nivelActual == x)
                *acum += A->dato;

        if(nivelActual < x) {
            suma(A->izq, acum, nivelActual, x);
            suma(A->der, acum, nivelActual, x);
        }
    }
}

int sumaInt(Arbol A, int nivelActual, int x) {
    int aux;
    if(A) {
        nivelActual++;
        aux = 0;
        if((A->der == NULL && A->izq != NULL ||
            A->der != NULL && A->izq == NULL)&&
            nivelActual == x)
                aux = A->dato;

        if(nivelActual < x)
            return aux + sumaInt(A->izq, nivelActual, x) + sumaInt(A->der, nivelActual, x);
        else
            return aux;
    }
    else
        return 0; //este return no seria del todo necesario pero me evita un warning, solo haria falta si el nivel que ingresa el usuairo no es valido, el cual no afirma que es validado asi que si es necesario
} //cuando solo hay que realizar una suma y no hay que ir llevando algun dato que debe mantenerse al recorrer todo el arbol, convendra la funcion int

//------------------------- ARBOL DE ENTEROS -------------------------

void addnodo(Arbol* A, int e) {
    *A = (Arbol)malloc(sizeof(nodo));
    (*A)->dato = e;
    (*A)->izq = NULL;
    (*A)->der = NULL;
}

void cargaArbolINT(Arbol *A) {
    addnodo(A, 5); // raíz
    addnodo(&(*A)->izq, 8);
    addnodo(&(*A)->der, 4);
    addnodo(&(*A)->izq->izq, 3);
    addnodo(&(*A)->izq->der, 6);
    addnodo(&(*A)->der->izq, 1);
    addnodo(&(*A)->der->izq->der, 2);

    /* Arbol en cuestion
           5
         /   \
        8     4
       / \   /
      3   6 1
             \
              2
    */
}

int main() {
    Arbol A;
    int x, acum = 0;
    cargaArbolINT(&A);

    /*
    printf("Ingrese X");
    scanf("%d",&x);
    */

    x = 2; //para no tener que andar ingresando el valor.
    suma(A, &acum, 0, x);

    printf("La suma de los nodos que cumplen la condicione es %d\n", acum);
    printf("La suma de los nodos que cumplen la condicion es %d\n", sumaInt(A, 0, x));
    return 0;
}
