#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct nodo {
    int dato;
    struct nodo *izq, *der;
} nodo;
typedef nodo *Arbol;

// ---------------------------
// FUNCIÓN CORRECTA
// ---------------------------
void verificarABB(Arbol A, int *antDato, int *OK) {
    if (A && *OK) {
        // 1. Recorrer subárbol izquierdo
        verificarABB(A->izq, antDato, OK);
        // 2. Verificar nodo actual (debe ser mayor que el anterior)
        if (*antDato != INT_MIN && A->dato <= *antDato)
            *OK = 0;
        // 3. Actualizar el valor anterior
        *antDato = A->dato;
        // 4. Recorrer subárbol derecho
        verificarABB(A->der, antDato, OK);
    }
}

/*
void verificarABB(Arbol A, int *antDato, int *OK) {
    if (A && *OK) {
        verificarABB(A->izq, antDato, OK);
        if (*antDato != INT_MIN && A->dato <= *antDato)
            *OK = 0;
        *antDato = A->dato;
        verificarABB(A->der, antDato, OK);
    }
}
*/

// ---------------------------
// Función wrapper más limpia
// ---------------------------
int esABB(Arbol A) {
    int ok = 1;
    int antDato = INT_MIN;
    verificarABB(A, &antDato, &ok);
    return ok;
}

// ---------------------------
// Funciones auxiliares
// ---------------------------
Arbol nuevoNodo(int dato) {
    Arbol n = (Arbol)malloc(sizeof(nodo));
    n->dato = dato;
    n->izq = n->der = NULL;
    return n;
}

// ---------------------------
// Árboles de prueba
// ---------------------------
Arbol arbol1() { // ES ABB
    Arbol A = nuevoNodo(5);
    A->izq = nuevoNodo(3);
    A->der = nuevoNodo(8);
    A->izq->izq = nuevoNodo(2);
    A->izq->der = nuevoNodo(4);
    A->der->der = nuevoNodo(9);
    return A;
}

Arbol arbol2() { // NO ES ABB
    Arbol A = nuevoNodo(5);
    A->izq = nuevoNodo(3);
    A->der = nuevoNodo(8);
    A->izq->izq = nuevoNodo(2);
    A->izq->der = nuevoNodo(7); // 7 > 5, viola la propiedad
    return A;
}

Arbol arbol3() { // ES ABB (en línea)
    Arbol A = nuevoNodo(1);
    A->der = nuevoNodo(2);
    A->der->der = nuevoNodo(3);
    return A;
}

Arbol arbol4() { // NO ES ABB (duplicados)
    Arbol A = nuevoNodo(5);
    A->izq = nuevoNodo(3);
    A->der = nuevoNodo(5); // Duplicado
    return A;
}

Arbol arbol5() { // ES ABB (caso mínimo)
    return nuevoNodo(42);
}

// ---------------------------
// Programa principal
// ---------------------------
int main() {
    Arbol arboles[] = {arbol1(), arbol2(), arbol3(), arbol4(), arbol5()};
    const char *nombres[] = {"Árbol 1", "Árbol 2", "Árbol 3", "Árbol 4", "Árbol 5"};

    printf("=== Verificación de Árboles Binarios de Búsqueda ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("%s: %s\n", nombres[i], esABB(arboles[i]) ? "✓ ES ABB" : "✗ NO ES ABB");
    }

    return 0;
}
