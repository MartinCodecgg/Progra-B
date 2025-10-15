#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *izq, *der;
} nodo;

typedef nodo * Arbol;

// ─────────────────────────────
// Crear nodo nuevo
// ─────────────────────────────
Arbol crearNodo(int dato) {
    Arbol nuevo = (Arbol)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

// ─────────────────────────────
// Carga automática (ABB válido)
// ─────────────────────────────
// Árbol visualmente:
//
//          10
//         /  \
//        5    20
//       / \   / \
//      3  7  15 30
// ─────────────────────────────
void cargaA(Arbol *A) {
    *A = crearNodo(10);
    (*A)->izq = crearNodo(5);
    (*A)->der = crearNodo(20);

    (*A)->izq->izq = crearNodo(3);
    (*A)->izq->der = crearNodo(7);

    (*A)->der->izq = crearNodo(15);
    (*A)->der->der = crearNodo(30);
}

int minimo(Arbol A) {
    if(A) {
        if(A->izq != NULL)
            return minimo(A->izq);
        else
            return A->dato;
    }
    else
        return 99999;
}

//Adicional haciendo de forma iterativa quedaria: (hecho por IA)

int minimoInt(Arbol A) {
    if (A == NULL)
        return 99999;

    // En un ABB, el mínimo siempre está lo más a la izquierda posible
    while (A->izq != NULL)
        A = A->izq;

    return A->dato;
}

int main(){
    Arbol A;
    cargaA(&A);

    printf("El minimo del ABB es %d\n", minimo(A));
    printf("El minimo del ABB es %d\n", minimoInt(A));


    return 0;
}
