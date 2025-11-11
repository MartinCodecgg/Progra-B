#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *izq, *der;
} nodo;
typedef nodo * Arbol;

// Función auxiliar para crear un nodo
Arbol crearNodo(int dato) {
    Arbol nuevo = (Arbol)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

//20a (REHACER, solo deberia aumentar el cont (nivel) cuando bajo a izq)
int cantNenNivImpares(Arbol A, int cont) {
    if(A) {
        cont++;
        if(cont % 2 != 0)
            return 1 + cantNenNivImpares(A->izq, cont) + cantNenNivImpares(A->der, cont);
        else
            return cantNenNivImpares(A->izq, cont) + cantNenNivImpares(A->der, cont);
    }
    else
        return 0;
}

//auxiliar para 20b
int grado(Arbol A) {
    int gr = 0;
    A = A->izq;
    while(A) {
        gr++;
        A = A->der;
    }
    return gr;
}

//20b
void promedio(Arbol A, int k, int *acum, int *cont) {
    if(A) {
        if(grado(A) == k) {
            (*cont)++;
            *acum += A->dato;
        }
        promedio(A->izq, k, acum, cont);
        promedio(A->der, k, acum, cont);
    }
}

//20c
void altura(Arbol A, int *alturaMax, int cont) {
    if(A) {
        if(A->izq)
            cont++;
        altura(A->izq, alturaMax, cont);
        altura(A->der, alturaMax, cont);
    }
    else
        if (cont > *alturaMax)
            *alturaMax = cont;
}

int alturaInt(Arbol ABB, int cont) {
    int aux, altIzq, altDer; //la variable aux se podria quitar pero es mas clara que usar directmaente cont
    if(ABB == NULL)
        return -1;
    else {
        altIzq = alturaInt(ABB->izq, cont + 1);
        altDer = alturaInt(ABB->der, cont);
        aux = cont; //no es necesario comparar con el actual, porque el actual siempre sera menor o igual que sus hijos
        if(altIzq > aux) //asi como hice abajo, puedo incrementar con el return y en caso de que los hijos sean NULL al devolver -1 termina quedando cero
            aux = altIzq;
        if(altDer > aux)
            aux = altDer;
    return aux;
    }
} //llamada main: altura(ABB,0);

//optimizada (ia) (complejo)
//no es necesario cont ya que puedo contar la altura con el return y a la vez quedarme con el maximo con una simple comparacion
int alturaInt2(Arbol ABB) {
    if(ABB == NULL)
        return -1;
    else {
        int altIzq = alturaInt2(ABB->izq);
        int altDer = alturaInt2(ABB->der);
        return (altIzq >= altDer) ? altIzq + 1 : altDer;
    }
}
//Se compara el hijo izq y el der como estan y si el izq es mayor se suma uno para contar la diferencia de altura al bajar a izquierda

//20d
void gradoArbolG(Arbol AB, int *grado, int cont) {
    if(AB) {
        gradoArbolG(AB->izq, grado, 1);
        gradoArbolG(AB->der, grado, cont + 1);
    }
    else {
        cont--;
        if(cont > *grado)
            *grado = cont;
    }
}

//version int
int gradoOri(Arbol AB) {
    int grIzq, grDer;
    Arbol act;
    int aux = 0;
    if(AB == NULL)
        return -1;
    else {
        act = AB->izq;
        while(act) {
            aux++;
            act = act->der;
        }
        grIzq = gradoOri(AB);
        grDer = gradoOri(AB);

        if(grIzq > aux)
            aux = grIzq;
        if(grDer > aux)
            aux = grDer;
        
        return aux;
    }
}

//version int optimizada (ia)
//esta version procesa menos nodos, la anterior lo que tenia es que algunos nodos a derecha los procesaba dos veces
int gradoOri(Arbol AB) {
    Arbol act;
    int gr = 0, maxGrado = 0;
    
    if(AB == NULL)
        return 0;
    else {
        act = AB->izq;
        while(act) {
            gr++; //va contando el grado del nodo actual, analizando sus hijos a der
            int gradoHijo = gradoOri(act);
            if(gradoHijo > maxGrado)
                maxGrado = gradoHijo;
            act = act->der;  
        }

        return (gr > maxGrado) ? gr : maxGrado; //compara si el grado del nodo actual es mayor que los grados de sus hijos y devuelve el mayor
    }
}




// Función para imprimir el árbol (para visualización)
void imprimirArbol(Arbol A, int nivel, char lado) {
    if(A) {
        for(int i = 0; i < nivel; i++) printf("  ");
        printf("%c[%d] (grado: %d)\n", lado, A->dato, grado(A));
        if(A->izq || A->der) {
            if(A->izq) imprimirArbol(A->izq, nivel + 1, 'L');
            if(A->der) imprimirArbol(A->der, nivel, 'R');
        }
    }
}

int main() {
    printf("===========================================\n");
    printf("PRUEBA DE FUNCIONES - ARBOL BINARIO\n");
    printf("===========================================\n\n");

    /*
     * Creamos el siguiente árbol GENERAL:
     *
     *           A(10)
     *          /|\
     *         / | \
     *        B  C  D
     *       (20)(30)(40)
     *       /|
     *      / |
     *     E  F
     *   (50)(60)
     *
     * Niveles del árbol general:
     * - Nivel 0: A
     * - Nivel 1: B, C, D (3 nodos) - IMPAR
     * - Nivel 2: E, F (2 nodos)
     *
     * Grados:
     * - A tiene grado 3 (hijos: B, C, D)
     * - B tiene grado 2 (hijos: E, F)
     * - C tiene grado 0
     * - D tiene grado 0
     * - E tiene grado 0
     * - F tiene grado 0
     *
     * Conversión a árbol BINARIO:
     *        A(10)
     *        /
     *       B(20)
     *      /    \
     *    E(50)  C(30)
     *      \      \
     *     F(60)  D(40)
     */

    // Construir el árbol binario
    Arbol A = crearNodo(10);
    A->izq = crearNodo(20);  // B (primer hijo de A)

    A->izq->izq = crearNodo(50);  // E (primer hijo de B)
    A->izq->izq->der = crearNodo(60);  // F (hermano de E)

    A->izq->der = crearNodo(30);  // C (hermano de B)
    A->izq->der->der = crearNodo(40);  // D (hermano de C)

    printf("ESTRUCTURA DEL ARBOL BINARIO:\n");
    printf("(L=hijo izquierdo, R=hermano derecho)\n\n");
    imprimirArbol(A, 0, '*');

    printf("\n===========================================\n");
    printf("ARBOL GENERAL ORIGINAL:\n");
    printf("===========================================\n");
    printf("           A(10)           \n");
    printf("          /|\\              \n");
    printf("         / | \\             \n");
    printf("        /  |  \\            \n");
    printf("      B(20) C(30) D(40)    \n");
    printf("      /|                   \n");
    printf("     / |                   \n");
    printf("   E(50) F(60)             \n\n");

    printf("Niveles:\n");
    printf("  Nivel 0: A(10)\n");
    printf("  Nivel 1: B(20), C(30), D(40)  <- IMPAR\n");
    printf("  Nivel 2: E(50), F(60)\n\n");

    printf("Grados de cada nodo:\n");
    printf("  A: grado 3 (hijos: B, C, D)\n");
    printf("  B: grado 2 (hijos: E, F)\n");
    printf("  C: grado 0\n");
    printf("  D: grado 0\n");
    printf("  E: grado 0\n");
    printf("  F: grado 0\n\n");

    // PRUEBA 20a: Cantidad de nodos en niveles impares
    printf("===========================================\n");
    printf("20a) NODOS EN NIVELES IMPARES\n");
    printf("===========================================\n");
    printf("Llamada: cantNenNivImpares(A, 0)\n");
    printf("Esperado: 3 (nivel 1: B, C, D)\n");
    int resultado_a = cantNenNivImpares(A, 0);
    printf("Resultado: %d %s\n\n", resultado_a, resultado_a == 3 ? "✓" : "✗");

    // PRUEBA 20b: Promedio de claves con grado K
    printf("===========================================\n");
    printf("20b) PROMEDIO DE NODOS CON GRADO K\n");
    printf("===========================================\n");

    // Prueba con K=3
    int acum = 0, cont = 0, k = 3;
    promedio(A, k, &acum, &cont);
    printf("K = 3\n");
    printf("Nodos con grado 3: A(10)\n");
    printf("Esperado: promedio = 10\n");
    if(cont > 0)
        printf("Resultado: promedio = %d %s\n\n", acum/cont, (acum/cont == 10) ? "✓" : "✗");
    else
        printf("Resultado: No hay nodos con grado 3 ✗\n\n");

    // Prueba con K=2
    acum = 0; cont = 0; k = 2;
    promedio(A, k, &acum, &cont);
    printf("K = 2\n");
    printf("Nodos con grado 2: B(20)\n");
    printf("Esperado: promedio = 20\n");
    if(cont > 0)
        printf("Resultado: promedio = %d %s\n\n", acum/cont, (acum/cont == 20) ? "✓" : "✗");
    else
        printf("Resultado: No hay nodos con grado 2 ✗\n\n");

    // Prueba con K=0
    acum = 0; cont = 0; k = 0;
    promedio(A, k, &acum, &cont);
    printf("K = 0\n");
    printf("Nodos con grado 0: C(30), D(40), E(50), F(60)\n");
    printf("Esperado: promedio = (30+40+50+60)/4 = 45\n");
    if(cont > 0)
        printf("Resultado: promedio = %d %s\n\n", acum/cont, (acum/cont == 45) ? "✓" : "✗");
    else
        printf("Resultado: No hay nodos con grado 0 ✗\n\n");

    // PRUEBA 20c: Altura del árbol
    printf("===========================================\n");
    printf("20c) ALTURA DEL ARBOL ORIGINAL\n");
    printf("===========================================\n");
    printf("Llamada: altura(A->izq, &alturaMax, 1)\n");
    printf("Esperado: 2 (A->B->E)\n");
    int alturaMax = -1;
    altura(A->izq, &alturaMax, 1); //LLAMO CON 1 PARA CONTAR EL HIJO IZQUIERDO DE LA RAIZ
    printf("Resultado: %d %s\n\n", alturaMax, alturaMax == 2 ? "✓" : "✗");

    // PRUEBA 20d: Grado del árbol
    printf("===========================================\n");
    printf("20d) GRADO DEL ARBOL ORIGINAL\n");
    printf("===========================================\n");
    printf("Llamada: gradoArbolG(A->izq, &grado, 1)\n");
    printf("Esperado: 3 (A tiene 3 hijos)\n");
    int gradoMax = -1;
    gradoArbolG(A->izq, &gradoMax, 1);
    printf("Resultado: %d %s\n\n", gradoMax, gradoMax == 3 ? "✓" : "✗");

    printf("===========================================\n");
    printf("RESUMEN DE RESULTADOS\n");
    printf("===========================================\n");
    printf("20a) Nodos en niveles impares: %d %s\n", resultado_a, resultado_a == 3 ? "✓ CORRECTO" : "✗ INCORRECTO");

    acum = 0; cont = 0; k = 3;
    promedio(A, k, &acum, &cont);
    printf("20b) Promedio grado 3: %d %s\n", cont > 0 ? acum/cont : -1, (cont > 0 && acum/cont == 10) ? "✓ CORRECTO" : "✗ INCORRECTO");

    printf("20c) Altura: %d %s\n", alturaMax, alturaMax == 2 ? "✓ CORRECTO" : "✗ INCORRECTO");
    printf("20d) Grado máximo: %d %s\n", gradoMax, gradoMax == 3 ? "✓ CORRECTO" : "✗ INCORRECTO");

    // Liberar memoria
    free(A->izq->izq->der);
    free(A->izq->izq);
    free(A->izq->der->der);
    free(A->izq->der);
    free(A->izq);
    free(A);

    return 0;
}
