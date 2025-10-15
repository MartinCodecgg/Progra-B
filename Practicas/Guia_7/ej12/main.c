#include <stdio.h>
#include <stdlib.h>

/*
12. Determinar cuántos elementos de un ABB son mayores que A y menores que B.
A y B son parámetros de entrada.
*/

typedef struct nodo {
    int dato;
    struct nodo *izq, *der;
} nodo;

typedef nodo * Arbol;

// --- Función para crear un nuevo nodo ---
Arbol crearNodo(int dato) {
    Arbol nuevo = (Arbol) malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

// --- Función para insertar un dato en el ABB ---
Arbol insertar(Arbol ABB, int dato) {
    if (ABB == NULL)
        return crearNodo(dato);
    if (dato < ABB->dato)
        ABB->izq = insertar(ABB->izq, dato);
    else if (dato > ABB->dato)
        ABB->der = insertar(ABB->der, dato);
    // Si es igual, no lo insertamos (para mantener el ABB sin repetidos)
    return ABB;
}

// --- Tu función original (solo corregí el parámetro cont) ---
void determinar(Arbol ABB, int A, int B, int *cont) {
    if (ABB) {
        if (ABB->dato > A && ABB->dato < B)
            (*cont)++;

        if (ABB->dato < B)
            determinar(ABB->der, A, B, cont);
        if (ABB->dato > A)
            determinar(ABB->izq, A, B, cont);
    }
}

// --- Función para mostrar el árbol en orden (opcional, para verificar) ---
void inorden(Arbol ABB) {
    if (ABB) {
        inorden(ABB->izq);
        printf("%d ", ABB->dato);
        inorden(ABB->der);
    }
}

int main() {
    Arbol ABB = NULL;
    int cont = 0;
    int A = 4, B = 8;

    // --- Carga de prueba ---
    // Puedes cambiar los valores o pedirlos al usuario
    int valores[] = {5, 2, 8, 1, 3, 6, 9, 7};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++) {
        ABB = insertar(ABB, valores[i]);
    }

    printf("Elementos del ABB en orden: ");
    inorden(ABB);
    printf("\n");

/* Arbol en cuestion
        5
       / \
      2   8
     / \  / \
    1   3 6  9
           \
            7
*/

    determinar(ABB, A, B, &cont);
    printf("Cantidad de elementos mayores que %d y menores que %d: %d\n", A, B, cont);

    return 0;
}
