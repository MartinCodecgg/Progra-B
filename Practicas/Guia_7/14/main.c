#include <stdio.h>
#include <stdlib.h>

// Desarrollar una función que compruebe que si un árbol binario es un ABB.

typedef struct nodo {
    int dato;
    struct nodo *izq, *der;
} nodo;

typedef nodo * Arbol;

// --- Tu función original (con paréntesis agregados para mayor claridad) ---
void verifica(Arbol A, int *OK) {
    if (A) {
        if ( (A->der != NULL && A->dato > A->der->dato) ||
             (A->izq != NULL && A->dato < A->izq->dato) )
            *OK = 0;
        else {
            if (A->izq)
                verifica(A->izq, OK);
            if (A->der)
                verifica(A->der, OK);
        }
    }
}

// --- Crear un nuevo nodo ---
Arbol crearNodo(int dato) {
    Arbol nuevo = (Arbol) malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

// --- Crear un ABB válido ---
Arbol crearABBValido() {
    /*
            5
           / \
          3   8
         / \   \
        2   4   9
    */
    Arbol A = crearNodo(5);
    A->izq = crearNodo(3);
    A->der = crearNodo(8);
    A->izq->izq = crearNodo(2);
    A->izq->der = crearNodo(4);
    A->der->der = crearNodo(9);
    return A;
}

// --- Crear un árbol que NO sea ABB ---
Arbol crearNoABB() {
    /*
            5
           / \
          7   3   <-- error: 7 está a la izquierda y es mayor que 5, 3 a la derecha y es menor
    */
    Arbol A = crearNodo(5);
    A->izq = crearNodo(7); // incorrecto
    A->der = crearNodo(3); // incorrecto
    return A;
}

// --- Mostrar resultado ---
void probarArbol(Arbol A, const char *nombre) {
    int OK = 1;
    verifica(A, &OK);
    if (OK)
        printf("El árbol '%s' ES un ABB.\n", nombre);
    else
        printf("El árbol '%s' NO es un ABB.\n", nombre);
}

int main() {
    Arbol abbValido = crearABBValido();
    Arbol noAbb = crearNoABB();

    probarArbol(abbValido, "ABB válido");
    probarArbol(noAbb, "No ABB");

    return 0;
}
