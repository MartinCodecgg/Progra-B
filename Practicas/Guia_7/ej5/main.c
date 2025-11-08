#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    int dato;
    struct nodo *izq, *der;
} nodo;

typedef nodo * Arbol;

// Nuevo tipo de árbol con cadenas
typedef struct nodoCAD {
    char dato[50];
    struct nodoCAD *izq, *der;
} nodoCAD;

typedef nodoCAD * ArbolCAD;

//------------------------- PROTOTIPOS -------------------------
void profundidad(Arbol A, int *maxProfun, int cont);
int profundidadInt(Arbol A);
void profundidad2(Arbol A, int *maxProfun, int cont); //optimizado
void longPalMasLarga(ArbolCAD A2, int *maxLong);
int longPalMasLargaInt(ArbolCAD A2);
void cantHijosDerechos(Arbol A, int *cant);

void addnodo(Arbol* A, int e);
void addnodoCAD(ArbolCAD *A2, const char *cad);
void cargaArbolINT(Arbol *A);
void cargaArbolCAD(ArbolCAD *A2);

//------------------------- FUNCIONES PRINCIPALES -------------------------
int main() {
    Arbol A;
    ArbolCAD A2;
    int maxProfun = -1, maxLong = 0, cantHijosDer = 0; //para hallar la longitud maxima comparar con cero y no con -1, [PREGUNTAR]

    cargaArbolINT(&A);
    cargaArbolCAD(&A2);

    profundidad(A, &maxProfun, -1); // -1 → así raíz cuenta como nivel 0
    printf("La maxima profundidad del arbol en cuestion es: %d\n", maxProfun);

    profundidad2(A, &maxProfun, -1); // -1 → así raíz cuenta como nivel 0
    printf("(PROFUNDIDAD2)La maxima profundidad del arbol en cuestion es: %d\n", maxProfun);

    printf("(PROFUNDIDADINT)La maxima profundidad del arbol en cuestion es: %d\n", profundidadInt(A));

    longPalMasLarga(A2, &maxLong);
    printf("La longitud de la palabra mas larga del arbol es: %d\n", maxLong);
    printf("La longitud de la palabra mas larga del arbol es: %d\n",longPalMasLargaInt(A2));

    cantHijosDerechos(A, &cantHijosDer);
    printf("La cantidad de hijos derechos del arbol es cuestion es %d", cantHijosDer);
    return 0;
}

//------------------------- ARBOL DE ENTEROS -------------------------
void addnodo(Arbol* A, int e) {
    *A = (Arbol)malloc(sizeof(nodo));
    (*A)->dato = e;
    (*A)->izq = NULL;
    (*A)->der = NULL;
}

void cargaArbolINT(Arbol *A) {
    addnodo(A, 5); // raíz
    addnodo(&(*A)->izq, 8);
    addnodo(&(*A)->der, 4);
    addnodo(&(*A)->izq->izq, 3);
    addnodo(&(*A)->izq->der, 6);
    addnodo(&(*A)->der->izq, 1);
    addnodo(&(*A)->der->izq->der, 2);

    /* Arbol en cuestion
           5
         /   \
        8     4
       / \   /
      3   6 1
             \
              2
    */
}

void profundidad(Arbol A, int *maxProfun, int cont) {
    if (A) {
        cont++;
        if (cont > *maxProfun)
            *maxProfun = cont;
        profundidad(A->izq, maxProfun, cont);
        profundidad(A->der, maxProfun, cont);
    }
}

//version int

int profundidadInt(Arbol A) {
    int profunIzq, profunDer;

    if(A == NULL)
        return -1;
    else {
        profunIzq = profundidadInt(A->izq);
        profunDer = profundidadInt(A->der);
        return 1 + (profunIzq > profunDer ? profunIzq : profunDer); //no sumar parametro adicional para ir sumando en cada iteracion, poner un +1 en el return
    }   //poner parentesis a los ternarios si los uso junto a otras operaciones como aqui que estoy sumando un uno, en otro caso no necesitan parentesis
}
//llamada main: profunidad(A); //en la convencion de que la raiz tiene altura 0, se toma entonces que una hoja tiene altura 0 tambien y que el vacio tiene altura -1, en otro caso no funciona
//el otro enfoque es que la raiz tiene altura 1, entonces las hojas tambien y por elde el vacio tiene altura 0
void profundidad2(Arbol A, int *maxProfun, int cont) { //algoritmo optimizado
    if (A) {
        cont++;
        if(A->izq == NULL && A->der == NULL && cont > *maxProfun) //actualiza el maximo solo si esta parado en una hoja y no pregunta o hace asignaciones en todos los nodos
                *maxProfun = cont;
        else {
            if(A->izq) //conviene verificar que no sea NULL antes de llamar, sino llamare al dope
                profundidad(A->izq, maxProfun, cont);
            if(A->der)
                profundidad(A->der, maxProfun, cont);
        }
    }
}

//------------------------- ARBOL DE CADENAS -------------------------
void addnodoCAD(ArbolCAD *A2, const char *cad) {
    *A2 = (ArbolCAD)malloc(sizeof(nodoCAD));
    strcpy((*A2)->dato, cad);
    (*A2)->izq = NULL;
    (*A2)->der = NULL;
}

void cargaArbolCAD(ArbolCAD *A2) {
    addnodoCAD(A2, "casa");
    addnodoCAD(&(*A2)->izq, "ventana");
    addnodoCAD(&(*A2)->der, "sol");
    addnodoCAD(&(*A2)->izq->izq, "estrella");
    addnodoCAD(&(*A2)->izq->der, "flor");

    /* ArbolCAD en cuestion:
             casa
            /    \
        ventana   sol
         /   \
    estrella  flor
    */
}

void longPalMasLarga(ArbolCAD A2, int *maxLong) {
    if (A2) {
        if (strlen(A2->dato) > *maxLong)
            *maxLong = strlen(A2->dato);

        longPalMasLarga(A2->izq, maxLong);
        longPalMasLarga(A2->der, maxLong);
    }
}

int longPalMasLargaInt(ArbolCAD A2) {
    int resIzq, resDer, aux;
    if (A2) {
        resIzq = longPalMasLargaInt(A2->izq);
        resDer = longPalMasLargaInt(A2->der);

        aux = strlen(A2->dato);
        if (resIzq > aux)
            aux = resIzq;
        if (resDer > aux)
            aux = resDer;

        return aux;
    }
    else
        return 0;
}

void cantHijosDerechos(Arbol A, int *cant) {
    if(A) {
        if(A->der != NULL)
            (*cant)++;
        cantHijosDerechos(A->izq,cant);
        cantHijosDerechos(A->der, cant);
    }
}

int cantDer(Arbol A) {
    if(A == NULL)
        return 0;
    else {
        if(A->der)
            return 1 + cantDer(A->der) + cantDer(A->izq);
        else
            return cantDer(A->izq);
    }
}
