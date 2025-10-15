#include <stdio.h>
#include <stdlib.h>
#define TOP 50

typedef struct nodo {
    char dato;
    struct nodo *izq, *der;
} nodo;

typedef nodo *Arbol;

// --- Función para crear un nuevo nodo ---
Arbol crearNodo(char dato) {
    Arbol nuevo = (Arbol) malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

// --- Función para insertar un nodo en el ABB ---
Arbol insertar(Arbol A, char dato) {
    if (!A) return crearNodo(dato);
    if (dato < A->dato)
        A->izq = insertar(A->izq, dato);
    else if (dato > A->dato)
        A->der = insertar(A->der, dato);
    // Si es igual, no lo insertamos
    return A;
}

// --- Función para generar el vector descendente ---
void generar(Arbol A, char vec[], int *n) {
    if(A) {
        generar(A->der, vec, n);    // Primero derecha (mayores)
        vec[*n] = A->dato;          // Guardar dato
        (*n)++;
        generar(A->izq, vec, n);    // Luego izquierda (menores)
    }
}

// --- Función para mostrar el vector ---
void mostrarVector(char vec[], int n) {
    printf("Vector descendente: ");
    for(int i = 0; i < n; i++) {
        printf("%c ", vec[i]);
    }
    printf("\n");
}

int main() {
    Arbol A = NULL;
    char vec[TOP];
    int n = 0;

    // --- Cargar el ABB con algunas claves de prueba ---
    char claves[] = {'F','B','A','D','C','E','G','I','H'};
    int t = sizeof(claves)/sizeof(claves[0]);
    for(int i = 0; i < t; i++) {
        A = insertar(A, claves[i]);
    }

/* Arbol en cuestion
          F
        /   \
       B     G
      / \      \
     A   D      I
        / \    /
       C   E  H

*/
    // --- Generar el vector descendente ---
    generar(A, vec, &n);

    // --- Mostrar el vector ---
    mostrarVector(vec, n);

    return 0;
}
