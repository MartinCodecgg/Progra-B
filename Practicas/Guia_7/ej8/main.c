#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOP 50

typedef struct nodo {
    char nom[TOP];
    struct nodo *izq, *der;
} nodo;

typedef nodo * Arbol;

// ─────────────────────────────
// Función auxiliar para crear nodos
// ─────────────────────────────
Arbol crearNodo(const char *nombre) {
    Arbol nuevo = (Arbol) malloc(sizeof(nodo));
    strcpy(nuevo->nom, nombre);
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

// ─────────────────────────────
// Carga automática del árbol
// ─────────────────────────────
void cargaA(Arbol *A) {
    *A = crearNodo("Novak Djokovic"); // Ganador

    // Finalistas
    (*A)->izq = crearNodo("Carlos Alcaraz");
    (*A)->der = crearNodo("Jannik Sinner");

    // Semifinalistas
    (*A)->izq->izq = crearNodo("Rafael Nadal");
    (*A)->izq->der = crearNodo("Daniil Medvedev");
    (*A)->der->izq = crearNodo("Alexander Zverev");
    (*A)->der->der = crearNodo("Stefanos Tsitsipas");

    // Cuartos de final
    (*A)->izq->izq->izq = crearNodo("Jugador A1");
    (*A)->izq->izq->der = crearNodo("Jugador A2");
    (*A)->izq->der->izq = crearNodo("Jugador B1");
    (*A)->izq->der->der = crearNodo("Jugador B2");
    (*A)->der->izq->izq = crearNodo("Jugador C1");
    (*A)->der->izq->der = crearNodo("Jugador C2");
    (*A)->der->der->izq = crearNodo("Jugador D1");
    (*A)->der->der->der = crearNodo("Jugador D2");
}

// ─────────────────────────────
// Tus funciones originales
// ─────────────────────────────
void ganador(Arbol A) {
    if(A)
        printf("El ganador es: %s\n", A->nom);
}

void finalistas(Arbol A) {
    if(A) {
        printf("%s\n", A->der->nom); //convenia mas usar un solo printf()
        printf("%s\n", A->izq->nom);
    }
}

void semifinalistas(Arbol A) {
    if(A) {
        printf("%s\n", A->der->izq->nom); //convenia mas usar un solo printf()
        printf("%s\n", A->der->der->nom);
        printf("%s\n", A->izq->der->nom);
        printf("%s\n", A->izq->izq->nom);
    }
}

void competidores(Arbol A, int *cant) {
    if(A) {
        (*cant)++;
        printf("%s\n", A->nom);
        competidores(A->der, cant);
        competidores(A->izq, cant);
    }
}

// ─────────────────────────────
// Programa principal
// ─────────────────────────────
int main() {
    Arbol A = NULL;
    int cant = 0;

    cargaA(&A);

    ganador(A);
    printf("\nFinalistas:\n");
    finalistas(A);

    printf("\nSemifinalistas:\n");
    semifinalistas(A);

    printf("\nCuartos de final:\n");
    competidores(A, &cant);

    printf("\nLa cantidad de jugadores en el torneo es: %d\n", cant);

    return 0;
}
