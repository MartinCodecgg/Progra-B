#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct nodo {
    float dato;  // Cambiado a float para soportar decimales
    struct nodo *izq, *der;
} nodo;
typedef nodo *Arbol;

// Función a verificar
//En realidad el algoritmo funciona a la Vuelta, cosa que mas que antDato deberia llamarse SigDato, compara el hijo con el padre estando parado en el padre. (a la vuelta)
void verificarABB(Arbol A, float *antDato, int *OK) {
    if (A && *OK) {
        verificarABB(A->izq, antDato, OK);
        if (*antDato != INT_MIN && A->dato <= *antDato)
            *OK = 0;
        *antDato = A->dato;
        verificarABB(A->der, antDato, OK);
    }
}

int esABB(Arbol A) {
    int ok = 1;
    float antDato = INT_MIN;
    verificarABB(A, &antDato, &ok);
    return ok;
}

Arbol nuevoNodo(float dato) {
    Arbol n = (Arbol)malloc(sizeof(nodo));
    n->dato = dato;
    n->izq = n->der = NULL;
    return n;
}

void imprimirInorden(Arbol A) {
    if (A) {
        imprimirInorden(A->izq);
        printf("%.1f ", A->dato);
        imprimirInorden(A->der);
    }
}

// ========================================
// ÁRBOL 1: El árbol del dibujo (NO ES ABB)
// ========================================
Arbol arbol1() {
    /*
              9
            /   \
           5     10
          / \    / \
         2   7  9.8 11
                    /
                  10.5
                    \
                    10.8
                      \
                       9
    */
    Arbol A = nuevoNodo(9);
    A->izq = nuevoNodo(5);
    A->der = nuevoNodo(10);

    A->izq->izq = nuevoNodo(2);
    A->izq->der = nuevoNodo(7);

    A->der->izq = nuevoNodo(9.8);
    A->der->der = nuevoNodo(11);

    A->der->der->izq = nuevoNodo(10.5);
    A->der->der->izq->der = nuevoNodo(10.8);
    A->der->der->izq->der->der = nuevoNodo(9);

    return A;
}

// ========================================
// ÁRBOL 2: ABB perfecto y balanceado (ES ABB)
// ========================================
Arbol arbol2() {
    /*
           50
         /    \
        30     70
       / \    / \
      20 40  60 80
    */
    Arbol A = nuevoNodo(50);
    A->izq = nuevoNodo(30);
    A->der = nuevoNodo(70);

    A->izq->izq = nuevoNodo(20);
    A->izq->der = nuevoNodo(40);

    A->der->izq = nuevoNodo(60);
    A->der->der = nuevoNodo(80);

    return A;
}

// ========================================
// ÁRBOL 3: Solo rama derecha (ES ABB)
// ========================================
Arbol arbol3() {
    /*
      1
       \
        2
         \
          3
           \
            4
             \
              5
    */
    Arbol A = nuevoNodo(1);
    A->der = nuevoNodo(2);
    A->der->der = nuevoNodo(3);
    A->der->der->der = nuevoNodo(4);
    A->der->der->der->der = nuevoNodo(5);

    return A;
}

// ========================================
// ÁRBOL 4: Con duplicados (NO ES ABB)
// ========================================
Arbol arbol4() {
    /*
           10
         /    \
        5      15
       / \    / \
      3   5  12  20
    */
    Arbol A = nuevoNodo(10);
    A->izq = nuevoNodo(5);
    A->der = nuevoNodo(15);

    A->izq->izq = nuevoNodo(3);
    A->izq->der = nuevoNodo(5);  // Duplicado

    A->der->izq = nuevoNodo(12);
    A->der->der = nuevoNodo(20);

    return A;
}

// ========================================
// ÁRBOL 5: Violación sutil (NO ES ABB)
// ========================================
Arbol arbol5() {
    /*
           20
         /    \
        10     30
       / \
      5  25   <- 25 > 20, viola ABB
    */
    Arbol A = nuevoNodo(20);
    A->izq = nuevoNodo(10);
    A->der = nuevoNodo(30);

    A->izq->izq = nuevoNodo(5);
    A->izq->der = nuevoNodo(25);  // Error: 25 > 20

    return A;
}

// ========================================
// Función para mostrar resultados
// ========================================
void probarArbol(int num, Arbol A, const char *descripcion) {
    printf("\n========================================\n");
    printf("ÁRBOL %d: %s\n", num, descripcion);
    printf("========================================\n");

    printf("Recorrido inorden: ");
    imprimirInorden(A);
    printf("\n");

    int resultado = esABB(A);
    printf("Resultado: %s\n", resultado ? "✓ ES ABB" : "✗ NO ES ABB");

    // Explicación
    if (num == 1) {
        printf("Explicación: El nodo 9 aparece después de 10.8 en inorden.\n");
        printf("             Secuencia: ...10.5 < 10.8 < 9 (VIOLACIÓN)\n");
    } else if (num == 2) {
        printf("Explicación: ABB perfecto, todos los valores en orden creciente.\n");
    } else if (num == 3) {
        printf("Explicación: Solo rama derecha, siempre creciente.\n");
    } else if (num == 4) {
        printf("Explicación: Tiene duplicados (5 aparece dos veces).\n");
        printf("             Secuencia: ...3 < 5 ≤ 5 (VIOLACIÓN)\n");
    } else if (num == 5) {
        printf("Explicación: 25 está en subárbol izq de 20, pero 25 > 20.\n");
        printf("             Secuencia: ...10 < 20 < 25 < 30 (VIOLACIÓN)\n");
    }
}

int main() {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║   PRUEBA DE VERIFICACIÓN DE ÁRBOLES BINARIOS DE       ║\n");
    printf("║              BÚSQUEDA (ABB)                            ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");

    Arbol arboles[5];
    const char *descripciones[5] = {
        "Árbol del dibujo - Nodo mal ubicado",
        "ABB perfecto y balanceado",
        "Solo rama derecha (degenerado)",
        "Con valores duplicados",
        "Violación sutil (25 > 20 en subárbol izq)"
    };

    arboles[0] = arbol1();
    arboles[1] = arbol2();
    arboles[2] = arbol3();
    arboles[3] = arbol4();
    arboles[4] = arbol5();

    for (int i = 0; i < 5; i++) {
        probarArbol(i + 1, arboles[i], descripciones[i]);
    }

    printf("\n========================================\n");
    printf("RESUMEN DE RESULTADOS\n");
    printf("========================================\n");
    for (int i = 0; i < 5; i++) {
        printf("Árbol %d: %s\n", i + 1, esABB(arboles[i]) ? "✓ ES ABB" : "✗ NO ES ABB");
    }

    return 0;
}
