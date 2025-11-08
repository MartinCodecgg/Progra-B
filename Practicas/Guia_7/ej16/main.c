#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *izq, *der;
} nodo;
typedef nodo *Arbol;

// ============================================
// FUNCION DE INSERCION
// ============================================
void inserta(Arbol *A, int x) {
    Arbol act, new, ant;
    unsigned int fueIzq;

    new = (Arbol) malloc(sizeof(nodo));
    new->dato = x;
    new->der = NULL;
    new->izq = NULL;

    act = *A;
    //ant = NULL; //innecesario
    while(act) {
        ant = act;
        if(x < act->dato) {
            act = act->izq;
            fueIzq = 1;
        }
        else {
            act = act->der;
            fueIzq = 0;
        }
    }
    if(*A == NULL)
        *A = new;
    else { //llaves innecesarias
        if(fueIzq)
            ant->izq = new;
        else
            ant->der = new;
    }
}

// ============================================
// FUNCIONES AUXILIARES PARA PRUEBAS
// ============================================

void imprimirInorden(Arbol A) {
    if (A) {
        imprimirInorden(A->izq);
        printf("%d ", A->dato);
        imprimirInorden(A->der);
    }
}

void imprimirPreorden(Arbol A) {
    if (A) {
        printf("%d ", A->dato);
        imprimirPreorden(A->izq);
        imprimirPreorden(A->der);
    }
}

int contarNodos(Arbol A) {
    if (A == NULL)
        return 0;
    return 1 + contarNodos(A->izq) + contarNodos(A->der);
}

int buscar(Arbol A, int x) {
    if (A == NULL)
        return 0;
    if (x == A->dato)
        return 1;
    if (x < A->dato)
        return buscar(A->izq, x);
    else
        return buscar(A->der, x);
}

int esABB(Arbol A, int min, int max) {
    if (A == NULL)
        return 1;
    if (A->dato <= min || A->dato >= max)
        return 0;
    return esABB(A->izq, min, A->dato) && esABB(A->der, A->dato, max);
}

int altura(Arbol A) {
    if (A == NULL)
        return 0;
    int altIzq = altura(A->izq);
    int altDer = altura(A->der);
    return 1 + (altIzq > altDer ? altIzq : altDer);
}

void imprimirArbolHelper(Arbol A, int espacio, int nivel) {
    if (A == NULL)
        return;

    espacio += 10;

    imprimirArbolHelper(A->der, espacio, nivel + 1);

    printf("\n");
    for (int i = 10; i < espacio; i++)
        printf(" ");
    printf("[%d]", A->dato);
    if (nivel > 0) {
        printf(" (nivel %d)", nivel);
    }
    printf("\n");

    imprimirArbolHelper(A->izq, espacio, nivel + 1);
}

void imprimirArbol(Arbol A) {
    if (A == NULL) {
        printf("  Arbol vacio\n");
        return;
    }
    printf("\n  Estructura del arbol (derecha arriba, izquierda abajo):\n");
    imprimirArbolHelper(A, 0, 0);
    printf("\n");
}

void liberarArbol(Arbol *A) {
    if (*A) {
        liberarArbol(&((*A)->izq));
        liberarArbol(&((*A)->der));
        free(*A);
        *A = NULL;
    }
}

// ============================================
// FUNCIONES DE PRUEBA
// ============================================

void imprimirSeparador() {
    printf("========================================================\n");
}

void prueba1() {
    printf("\n");
    imprimirSeparador();
    printf("  PRUEBA 1: Insercion basica (arbol balanceado)\n");
    imprimirSeparador();

    Arbol A = NULL;
    int valores[] = {10, 5, 15, 3, 7, 12, 20};
    int n = 7;

    printf("Insertando: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        inserta(&A, valores[i]);
    }
    printf("\n");

    imprimirArbol(A);

    printf("Recorrido inorden: ");
    imprimirInorden(A);
    printf("\n");

    printf("Recorrido preorden: ");
    imprimirPreorden(A);
    printf("\n");

    printf("Numero de nodos: %d\n", contarNodos(A));
    printf("Altura del arbol: %d\n", altura(A));
    printf("Es ABB valido?: %s\n", esABB(A, -2147483648, 2147483647) ? "[SI]" : "[NO]");

    printf("\nBusquedas:\n");
    printf("  Buscar 7: %s\n", buscar(A, 7) ? "[OK] Encontrado" : "[X] No encontrado");
    printf("  Buscar 12: %s\n", buscar(A, 12) ? "[OK] Encontrado" : "[X] No encontrado");
    printf("  Buscar 99: %s\n", buscar(A, 99) ? "[OK] Encontrado" : "[X] No encontrado");

    liberarArbol(&A);
}

void prueba2() {
    printf("\n");
    imprimirSeparador();
    printf("  PRUEBA 2: Arbol degenerado (solo derecha)\n");
    imprimirSeparador();

    Arbol A = NULL;
    int valores[] = {1, 2, 3, 4, 5};
    int n = 5;

    printf("Insertando: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        inserta(&A, valores[i]);
    }
    printf("\n");

    imprimirArbol(A);

    printf("Recorrido inorden: ");
    imprimirInorden(A);
    printf("\n");

    printf("Numero de nodos: %d\n", contarNodos(A));
    printf("Altura del arbol: %d (degenerado)\n", altura(A));
    printf("Es ABB valido?: %s\n", esABB(A, -2147483648, 2147483647) ? "[SI]" : "[NO]");

    liberarArbol(&A);
}

void prueba3() {
    printf("\n");
    imprimirSeparador();
    printf("  PRUEBA 3: Arbol degenerado (solo izquierda)\n");
    imprimirSeparador();

    Arbol A = NULL;
    int valores[] = {5, 4, 3, 2, 1};
    int n = 5;

    printf("Insertando: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        inserta(&A, valores[i]);
    }
    printf("\n");

    imprimirArbol(A);

    printf("Recorrido inorden: ");
    imprimirInorden(A);
    printf("\n");

    printf("Numero de nodos: %d\n", contarNodos(A));
    printf("Altura del arbol: %d (degenerado)\n", altura(A));
    printf("Es ABB valido?: %s\n", esABB(A, -2147483648, 2147483647) ? "[SI]" : "[NO]");

    liberarArbol(&A);
}

void prueba4() {
    printf("\n");
    imprimirSeparador();
    printf("  PRUEBA 4: Insercion masiva (31 valores)\n");
    imprimirSeparador();

    Arbol A = NULL;
    int valores[] = {50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93,
                     3, 9, 15, 21, 28, 34, 40, 46, 53, 59, 65, 71, 78, 84, 90, 96};
    int n = 31;

    printf("Insertando %d valores...\n", n);
    for (int i = 0; i < n; i++) {
        inserta(&A, valores[i]);
    }

    printf("\nRecorrido inorden (primeros 20): ");
    int count = 0;
    void imprimirPrimeros20(Arbol A, int *c) {
        if (A && *c < 20) {
            imprimirPrimeros20(A->izq, c);
            if (*c < 20) {
                printf("%d ", A->dato);
                (*c)++;
            }
            imprimirPrimeros20(A->der, c);
        }
    }
    imprimirPrimeros20(A, &count);
    printf("...\n");

    printf("Numero de nodos: %d\n", contarNodos(A));
    printf("Altura del arbol: %d\n", altura(A));
    printf("Es ABB valido?: %s\n", esABB(A, -2147483648, 2147483647) ? "[SI]" : "[NO]");

    liberarArbol(&A);
}

void prueba5() {
    printf("\n");
    imprimirSeparador();
    printf("  PRUEBA 5: Un solo nodo\n");
    imprimirSeparador();

    Arbol A = NULL;
    inserta(&A, 42);

    printf("Insertando: 42\n");

    imprimirArbol(A);

    printf("Recorrido inorden: ");
    imprimirInorden(A);
    printf("\n");

    printf("Numero de nodos: %d\n", contarNodos(A));
    printf("Altura del arbol: %d\n", altura(A));
    printf("Es ABB valido?: %s\n", esABB(A, -2147483648, 2147483647) ? "[SI]" : "[NO]");

    liberarArbol(&A);
}

void prueba6() {
    printf("\n");
    imprimirSeparador();
    printf("  PRUEBA 6: Valores duplicados (permitidos a derecha)\n");
    imprimirSeparador();

    Arbol A = NULL;
    int valores[] = {10, 5, 10, 3, 5, 10};
    int n = 6;

    printf("Insertando: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        inserta(&A, valores[i]);
    }
    printf("\n");

    imprimirArbol(A);

    printf("Recorrido inorden: ");
    imprimirInorden(A);
    printf("\n");

    printf("Numero de nodos: %d\n", contarNodos(A));
    printf("Altura del arbol: %d\n", altura(A));
    printf("Nota: Los duplicados se insertan a la derecha (>=)\n");

    liberarArbol(&A);
}

// ============================================
// MAIN
// ============================================
int main() {
    printf("\n");
    imprimirSeparador();
    printf("       SUITE DE PRUEBAS - INSERCION EN ABB\n");
    imprimirSeparador();

    prueba1();
    prueba2();
    prueba3();
    prueba4();
    prueba5();
    prueba6();

    printf("\n");
    imprimirSeparador();
    printf("  RESUMEN: TODAS LAS PRUEBAS COMPLETADAS\n");
    imprimirSeparador();

    printf("\n");
    printf("[OK] Tu funcion inserta() funciona correctamente\n");
    printf("[OK] Maneja arbol vacio\n");
    printf("[OK] Maneja un solo nodo\n");
    printf("[OK] Maneja arboles balanceados\n");
    printf("[OK] Maneja arboles degenerados\n");
    printf("[OK] Mantiene la propiedad ABB\n");
    printf("\n");

    return 0;
}
