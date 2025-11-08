#include <stdio.h>
#include <stdlib.h>

#define N 50

// Definición de estructuras
typedef struct Nodo {
    int dato;
    struct Nodo* hijoIzq;    // Primer hijo
    struct Nodo* hnoDer;     // Hermano derecho
} Nodo;

typedef Nodo* Pos;
typedef struct {
    Pos raiz;
} ArbolG;

// Funciones del TDA
int Nulo(Pos p) {
    return p == NULL;
}

Pos hijoMasIzq(Pos p, ArbolG AG) {
    if (Nulo(p)) return NULL;
    return p->hijoIzq;
}

Pos hnoDer(Pos p, ArbolG AG) {
    if (Nulo(p)) return NULL;
    return p->hnoDer;
}

Pos crearNodo(int dato) {
    Pos nuevo = (Pos)malloc(sizeof(Nodo));
    nuevo->dato = dato;
    nuevo->hijoIzq = NULL;
    nuevo->hnoDer = NULL;
    return nuevo;
}

void agregarHijo(Pos padre, Pos hijo) {
    if (padre->hijoIzq == NULL) {
        padre->hijoIzq = hijo;
    } else {
        Pos temp = padre->hijoIzq;
        while (temp->hnoDer != NULL) {
            temp = temp->hnoDer;
        }
        temp->hnoDer = hijo;
    }
}

int grado(ArbolG AG, Pos p) {
    int gr = 0;
    Pos c = hijoMasIzq(p, AG);
    while(!Nulo(c)) {
        gr++;
        c = hnoDer(c, AG);
    }
    return gr;
}

int determinar(ArbolG AG, Pos p) {
    int gr, antGr = -9999, subCumple = 0, actCumple = 1;
    Pos c;

    if(Nulo(p))
        return 0;
    else {
        c = hijoMasIzq(p,AG);
        if(Nulo(c))
            return 0;
        else {
            while(!Nulo(c) && !subCumple) {
                gr = grado(AG,c);
                if(gr < antGr)
                    actCumple = 0;

                if(determinar(AG, c))
                    subCumple = 1;

                c = hnoDer(c,AG);
                antGr = gr;
            }
            return subCumple || actCumple;
        }
    }
}

// Función auxiliar para imprimir el árbol
void imprimirArbol(Pos p, int nivel) {
    if (Nulo(p)) return;
    
    for (int i = 0; i < nivel; i++) printf("  ");
    printf("Nodo %d (grado: ", p->dato);
    
    // Calcular grado para mostrar
    int g = 0;
    Pos temp = p->hijoIzq;
    while (temp != NULL) {
        g++;
        temp = temp->hnoDer;
    }
    printf("%d)\n", g);
    
    // Imprimir hijos
    Pos hijo = p->hijoIzq;
    while (hijo != NULL) {
        imprimirArbol(hijo, nivel + 1);
        hijo = hijo->hnoDer;
    }
}

// Crear árbol de prueba 1: NO cumple
ArbolG crearArbolPrueba1() {
    ArbolG arbol;
    
    // Crear nodos
    Pos A = crearNodo(1);
    Pos B = crearNodo(2);
    Pos C = crearNodo(3);
    Pos D = crearNodo(4);
    Pos E = crearNodo(5);
    Pos F = crearNodo(6);
    Pos G = crearNodo(7);
    Pos H = crearNodo(8);
    
    // Construir árbol
    arbol.raiz = A;
    agregarHijo(A, B);
    agregarHijo(A, C);
    agregarHijo(A, D);
    
    agregarHijo(B, E);
    agregarHijo(B, F);
    agregarHijo(B, G);
    
    agregarHijo(D, H);
    
    return arbol;
}

// Crear árbol de prueba 2: SÍ cumple
ArbolG crearArbolPrueba2() {
    ArbolG arbol;
    
    /*
            A
           / \
          B   C
         /   /|\
        D   E F G
    */
    
    Pos A = crearNodo(1);
    Pos B = crearNodo(2);
    Pos C = crearNodo(3);
    Pos D = crearNodo(4);
    Pos E = crearNodo(5);
    Pos F = crearNodo(6);
    Pos G = crearNodo(7);
    
    arbol.raiz = A;
    agregarHijo(A, B);  // B grado 1
    agregarHijo(A, C);  // C grado 3
    
    agregarHijo(B, D);  // D hoja
    
    agregarHijo(C, E);  // E, F, G hojas
    agregarHijo(C, F);
    agregarHijo(C, G);
    
    return arbol;
}

// Crear árbol de prueba 3: SÍ cumple (caso más complejo)
ArbolG crearArbolPrueba3() {
    ArbolG arbol;
    
    /*
            A
           /|\
          B C D
            | |\
            E F G
    */
    
    Pos A = crearNodo(1);
    Pos B = crearNodo(2);
    Pos C = crearNodo(3);
    Pos D = crearNodo(4);
    Pos E = crearNodo(5);
    Pos F = crearNodo(6);
    Pos G = crearNodo(7);
    
    arbol.raiz = A;
    agregarHijo(A, B);  // B grado 0
    agregarHijo(A, C);  // C grado 1
    agregarHijo(A, D);  // D grado 2
    
    agregarHijo(C, E);
    
    agregarHijo(D, F);
    agregarHijo(D, G);
    
    return arbol;
}

int main() {
    printf("=== PRUEBA DE ÁRBOL N-ARIO - GRADOS CRECIENTES ===\n\n");
    
    // Prueba 1
    printf("--- ÁRBOL DE PRUEBA 1 (NO debe cumplir) ---\n");
    printf("Estructura:\n");
    printf("        A\n");
    printf("       /||\\\n");
    printf("      B C D\n");
    printf("     /|\\  |\n");
    printf("    E F G H\n\n");
    
    ArbolG arbol1 = crearArbolPrueba1();
    printf("Árbol generado:\n");
    imprimirArbol(arbol1.raiz, 0);
    
    ArbolG ag1 = {arbol1.raiz};
    int resultado1 = determinar(ag1, arbol1.raiz);
    printf("\nResultado: %d (0 = NO cumple, 1 = SÍ cumple)\n", resultado1);
    printf("Análisis: Nodo A tiene hijos con grados [3,0,1] -> NO creciente\n");
    
    // Prueba 2
    printf("\n\n--- ÁRBOL DE PRUEBA 2 (SÍ debe cumplir) ---\n");
    printf("Estructura:\n");
    printf("        A\n");
    printf("       / \\\n");
    printf("      B   C\n");
    printf("     /   /|\\\n");
    printf("    D   E F G\n\n");
    
    ArbolG arbol2 = crearArbolPrueba2();
    printf("Árbol generado:\n");
    imprimirArbol(arbol2.raiz, 0);
    
    ArbolG ag2 = {arbol2.raiz};
    int resultado2 = determinar(ag2, arbol2.raiz);
    printf("\nResultado: %d (0 = NO cumple, 1 = SÍ cumple)\n", resultado2);
    printf("Análisis: Nodo A tiene hijos con grados [1,3] -> SÍ creciente\n");
    
    // Prueba 3
    printf("\n\n--- ÁRBOL DE PRUEBA 3 (SÍ debe cumplir) ---\n");
    printf("Estructura:\n");
    printf("        A\n");
    printf("       /|\\\n");
    printf("      B C D\n");
    printf("        | |\\\n");
    printf("        E F G\n\n");
    
    ArbolG arbol3 = crearArbolPrueba3();
    printf("Árbol generado:\n");
    imprimirArbol(arbol3.raiz, 0);
    
    ArbolG ag3 = {arbol3.raiz};
    int resultado3 = determinar(ag3, arbol3.raiz);
    printf("\nResultado: %d (0 = NO cumple, 1 = SÍ cumple)\n", resultado3);
    printf("Análisis: Nodo A tiene hijos con grados [0,1,2] -> SÍ creciente\n");
    
    printf("\n=== FIN DE LAS PRUEBAS ===\n");
    
    return 0;
}