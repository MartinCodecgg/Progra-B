#include <stdio.h>
#include <stdlib.h>
#define TOP 50

typedef struct nodo {
    int dato;
    struct nodo *izq, *der;
} nodo;
typedef nodo * Arbol;

// ==================== TUS FUNCIONES ORIGINALES (SIN CAMBIOS) ====================

//La verdad no estoy del todo seguro de si funciona el 21a, las pruebas de la IA creo que estan MAL
void altura(Arbol A, int k, int *alturaMax, int cont) { //verificada
    if(A && *alturaMax < k) {
        if(A->izq)
            cont++;
        altura(A->izq, k, alturaMax, cont);
        altura(A->der, k, alturaMax, cont);
    }
    else
        if (cont > *alturaMax)
            *alturaMax = cont;
}
//21 a auxiliar
void cantH(Arbol A, int k, int *cant) { //verificada
    int alturaAct;
    while(A) {
        alturaAct = 0;
        altura(A->izq, k, &alturaAct, 1);
        if(alturaAct >= k)
            (*cant)++;
        A = A->der;
    }
}

//21 a) Con funcion int

int cantA(Arbol AB, int k) {
    int cont = 0;
    Arbol act = AB;
    while(act) {
        if((k == 0 && act->izq == NULL) || alturaInt(act->izq,1,k)) //logica adicional para k = 0
            cont++;
        act = act->der;
    }
    return cont;
}

int alturaInt(Arbol AB, int altu, int k) {
    if(AB == NULL)
        return 0;
    else {
        if(altu < k)
            return alturaInt(AB->izq, altu + 1, k) || alturaInt(AB->der, altu, k);
        else
            return 1;
    }
}

//21b auxiliar
int maxClave(Arbol A) { //verificada
    int maxIzq, maxDer, aux;
    if(A) {
        maxIzq = maxClave(A->izq);
        maxDer = maxClave(A->der);
        aux = (maxIzq > maxDer) ? maxIzq : maxDer; //conviene encontrar el maximo o minimo de los hijos y luego comparar aux con el adtual, es mas prolijo
        if (A->dato > aux)
            aux = A->dato;
        return aux;
    }
    else
        return -99999;
}

//21b
void generaV(Arbol A, int vec[], int *n) { //verificada
    int aux;
    while(A) {
        aux = maxClave(A->izq);
        if(A->dato > aux)
            vec[*n] = A->dato;
        else
            vec[*n] = aux;
        *n += 1;
        A = A->der;
    }
}

//21c auxiliar
void gradoArbolG(Arbol AB, int k, int cont, int *OK) { //verificada
    if(AB && !*OK) {
        gradoArbolG(AB->izq, k, 1, OK);
        gradoArbolG(AB->der, k, cont + 1, OK); //sumo uno inclusive cuando en realidad es NULL
    }
    else {
        cont--; //Aqui decremento para salvar el incremento para cuando ya era NULL
        if(cont == k)
            *OK = 1;
    }
}

//21c
//funcion auxiliar
void verificar(Arbol A, int k, int *cond) { //verificada
    int OK;
    while(A) {
        OK = 0;
        gradoArbolG(A->izq, k, 1, &OK);
        if(!OK)
            *cond = 0;
        A = A->der;
    }
}

//21c INT
int tieneGrK(Arbol AB, int k) {
    Arbol act = AB;
    int tiene = 0, gr = 0;
    while(act != NULL && !tiene && gr != k) {
        gr++;
        if(act->izq && tieneGrK(AB->izq,k))
            tiene = 1;
        act = act->der;
    }
    if(gr == k)
        tiene = 1;
    return tiene;
}
//
int verif(Arbol AB, int k) {
    Arbol act = AB; 
    int todosTienen = 1;
    while(act && todosTienen) {
        if(!tieneGrK(act->izq,k))
            todosTienen = 0;
        act = act->der;
    }
    return todosTienen;
}






// ==================== FUNCIONES AUXILIARES ====================
Arbol crearNodo(int dato) {
    Arbol nuevo = (Arbol)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

void liberarArbol(Arbol A) {
    if(A) {
        liberarArbol(A->izq);
        liberarArbol(A->der);
        free(A);
    }
}

void imprimirArbol(Arbol A, int nivel, char tipo) {
    if(A) {
        for(int i = 0; i < nivel; i++) printf("  ");
        printf("%c[%d]\n", tipo, A->dato);
        if(A->izq) imprimirArbol(A->izq, nivel + 1, 'L');
        if(A->der) imprimirArbol(A->der, nivel, 'R');
    }
}

int encontrarMaximoReal(Arbol A) {
    if(!A) return -99999;

    int maxActual = A->dato;
    int maxIzq = encontrarMaximoReal(A->izq);
    int maxDer = encontrarMaximoReal(A->der);

    if(maxIzq > maxActual) maxActual = maxIzq;
    if(maxDer > maxActual) maxActual = maxDer;

    return maxActual;
}

void imprimirVector(int vec[], int n) {
    printf("[");
    for(int i = 0; i < n; i++) {
        printf("%d", vec[i]);
        if(i < n-1) printf(", ");
    }
    printf("]\n");
}

// ==================== CASOS DE PRUEBA ====================

void prueba1() {
    printf("\n==========================================\n");
    printf("PRUEBA 1: Un solo arbol simple\n");
    printf("==========================================\n");

    /*
        Bosque:
            Arbol1
              50
             / \
            30  70
           /
          20

        Maximo: 70
    */

    Arbol A = crearNodo(50);
    A->izq = crearNodo(30);
    A->izq->izq = crearNodo(20);
    A->izq->der = crearNodo(70);

    printf("Estructura:\n");
    imprimirArbol(A, 0, '*');

    int maxEsperado = encontrarMaximoReal(A);
    printf("\nMaximo esperado del arbol: %d\n", maxEsperado);

    int vec[TOP], n = 0;
    generaV(A, vec, &n);

    printf("\nVector generado: ");
    imprimirVector(vec, n);

    printf("Cantidad de arboles: %d\n", n);
    printf("Resultado: vec[0]=%d, Esperado=%d %s\n",
           vec[0], maxEsperado, (vec[0] == maxEsperado) ? "OK" : "FALLO");

    liberarArbol(A);
}

void prueba2() {
    printf("\n==========================================\n");
    printf("PRUEBA 2: Bosque con 3 arboles\n");
    printf("==========================================\n");

    /*
        Bosque:
            Arbol1      Arbol2      Arbol3
              10          40          25
             / \         /           / \
            5  15       35          20  30
           /
          3

        Maximos: 15, 40, 30
    */

    Arbol A = crearNodo(10);
    A->izq = crearNodo(5);
    A->izq->izq = crearNodo(3);
    A->izq->der = crearNodo(15);

    A->der = crearNodo(40);
    A->der->izq = crearNodo(35);

    A->der->der = crearNodo(25);
    A->der->der->izq = crearNodo(20);
    A->der->der->izq->der = crearNodo(30);

    printf("Estructura del bosque completo:\n");
    imprimirArbol(A, 0, '*');

    // Calcular maximos esperados
    int max1 = encontrarMaximoReal(A);
    int max2 = encontrarMaximoReal(A->der);
    int max3 = encontrarMaximoReal(A->der->der);

    printf("\nMaximos esperados:\n");
    printf("  Arbol 1: %d\n", max1);
    printf("  Arbol 2: %d\n", max2);
    printf("  Arbol 3: %d\n", max3);

    int vec[TOP], n = 0;
    generaV(A, vec, &n);

    printf("\nVector generado: ");
    imprimirVector(vec, n);

    printf("\nVerificacion:\n");
    printf("  vec[0]=%d, Esperado=%d %s\n", vec[0], max1, (vec[0]==max1) ? "OK":"FALLO");
    printf("  vec[1]=%d, Esperado=%d %s\n", vec[1], max2, (vec[1]==max2) ? "OK":"FALLO");
    printf("  vec[2]=%d, Esperado=%d %s\n", vec[2], max3, (vec[2]==max3) ? "OK":"FALLO");

    liberarArbol(A);
}

void prueba3() {
    printf("\n==========================================\n");
    printf("PRUEBA 3: Arbol con raiz maxima\n");
    printf("==========================================\n");

    /*
        Bosque:
            Arbol1
              100
             /  \
            50   80
           /
          30

        Maximo: 100 (la raiz)
    */

    Arbol A = crearNodo(100);
    A->izq = crearNodo(50);
    A->izq->izq = crearNodo(30);
    A->izq->der = crearNodo(80);

    printf("Estructura:\n");
    imprimirArbol(A, 0, '*');

    int maxEsperado = 100;
    printf("\nMaximo esperado: %d (la raiz del arbol)\n", maxEsperado);

    int vec[TOP], n = 0;
    generaV(A, vec, &n);

    printf("\nVector generado: ");
    imprimirVector(vec, n);

    printf("Resultado: vec[0]=%d, Esperado=%d %s\n",
           vec[0], maxEsperado, (vec[0] == maxEsperado) ? "OK" : "FALLO");

    liberarArbol(A);
}

void prueba4() {
    printf("\n==========================================\n");
    printf("PRUEBA 4: Arboles sin hijos\n");
    printf("==========================================\n");

    /*
        Bosque:
            10    20    30    (todos sin hijos)

        Maximos: 10, 20, 30
    */

    Arbol A = crearNodo(10);
    A->der = crearNodo(20);
    A->der->der = crearNodo(30);

    printf("Estructura:\n");
    imprimirArbol(A, 0, '*');

    printf("\nMaximos esperados: 10, 20, 30\n");

    int vec[TOP], n = 0;
    generaV(A, vec, &n);

    printf("\nVector generado: ");
    imprimirVector(vec, n);

    printf("\nVerificacion:\n");
    printf("  vec[0]=%d, Esperado=10 %s\n", vec[0], (vec[0]==10) ? "OK":"FALLO");
    printf("  vec[1]=%d, Esperado=20 %s\n", vec[1], (vec[1]==20) ? "OK":"FALLO");
    printf("  vec[2]=%d, Esperado=30 %s\n", vec[2], (vec[2]==30) ? "OK":"FALLO");

    liberarArbol(A);
}

void prueba5() {
    printf("\n==========================================\n");
    printf("PRUEBA 5: Arbol profundo\n");
    printf("==========================================\n");

    /*
        Bosque:
            Arbol1
              10
              |
              20
              |
              30
              |
              40  <- maximo
              |
              35

        Maximo: 40
    */

    Arbol A = crearNodo(10);
    A->izq = crearNodo(20);
    A->izq->izq = crearNodo(30);
    A->izq->izq->izq = crearNodo(40);
    A->izq->izq->izq->izq = crearNodo(35);

    printf("Estructura:\n");
    imprimirArbol(A, 0, '*');

    int maxEsperado = 40;
    printf("\nMaximo esperado: %d\n", maxEsperado);

    int vec[TOP], n = 0;
    generaV(A, vec, &n);

    printf("\nVector generado: ");
    imprimirVector(vec, n);

    printf("Resultado: vec[0]=%d, Esperado=%d %s\n",
           vec[0], maxEsperado, (vec[0] == maxEsperado) ? "OK" : "FALLO");

    liberarArbol(A);
}

void prueba6() {
    printf("\n==========================================\n");
    printf("PRUEBA 6: Valores negativos\n");
    printf("==========================================\n");

    /*
        Bosque:
            Arbol1      Arbol2
              -5          -20
             / \            |
           -10  -3        -15

        Maximos: -3, -15
    */

    Arbol A = crearNodo(-5);
    A->izq = crearNodo(-10);
    A->izq->der = crearNodo(-3);

    A->der = crearNodo(-20);
    A->der->izq = crearNodo(-15);

    printf("Estructura:\n");
    imprimirArbol(A, 0, '*');

    printf("\nMaximos esperados: -3, -15\n");

    int vec[TOP], n = 0;
    generaV(A, vec, &n);

    printf("\nVector generado: ");
    imprimirVector(vec, n);

    printf("\nVerificacion:\n");
    printf("  vec[0]=%d, Esperado=-3 %s\n", vec[0], (vec[0]==-3) ? "OK":"FALLO");
    printf("  vec[1]=%d, Esperado=-15 %s\n", vec[1], (vec[1]==-15) ? "OK":"FALLO");

    liberarArbol(A);
}

void prueba7() {
    printf("\n==========================================\n");
    printf("PRUEBA 7: Bosque vacio\n");
    printf("==========================================\n");

    Arbol A = NULL;

    printf("Estructura: NULL (bosque vacio)\n");

    int vec[TOP], n = 0;
    generaV(A, vec, &n);

    printf("\nVector generado: ");
    imprimirVector(vec, n);

    printf("Cantidad de elementos: %d, Esperado=0 %s\n",
           n, (n==0) ? "OK":"FALLO");
}

int main() {
    printf("========================================\n");
    printf("  PROGRAMA DE PRUEBA - EJERCICIO 21b\n");
    printf("  Maximos de cada arbol del bosque\n");
    printf("========================================\n");

    prueba1();
    prueba2();
    prueba3();
    prueba4();
    prueba5();
    prueba6();
    prueba7();

    printf("\n========================================\n");
    printf("RESUMEN\n");
    printf("========================================\n");
    printf("Si todos los casos muestran 'OK', tu algoritmo funciona correctamente.\n");
    printf("Si algun caso muestra 'FALLO', revisa la logica.\n");
    printf("\nTu observacion es correcta: no puedes pasar A completo a maxClave\n");
    printf("porque A->der es el siguiente arbol del bosque, no parte del arbol actual.\n");
    /*
    Arbol A;
    //cargarA(&A);
    int k = 2, cond = 1;
    verificar(A, k, &cond);
    if(cond)
        printf("Se verifica que todos los �rboles contengan al menos un nodo de grado K");
    */
    return 0;
}
