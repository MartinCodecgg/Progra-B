#include <stdio.h>
#include <stdlib.h>
#include "../TDA_CREA+MUESTRA_LISTA/TDA_CREA+MUESTRA_LISTA.h"
#include "../TDA_CREA+MUESTRA_LISTA/TDA_CREA+MUESTRA_LISTA.c"

typedef char TElementoL;

typedef struct nodo{
 TElementoL dato;
 struct nodo * sig;} nodo;
typedef nodo * TLista;

void creaLinvertido(TLista *L, TElementoL array[], int n);
void creaManteniendo(TLista *L,TElementoL array[], int n);
void creaOrdenado(TLista *L,TElementoL array[], int n);
void insertaLOrd(TLista *L,char x);

int main() {

    TLista L;
    char array[] = {'z','b','c','d'};
    //char array[] = {'z'};
    int n = 4;
    creaLinvertido(&L,array,n);
    muestraL(L);
    //printf("Crea Manteniendo\n");
    //creaManteniendo(&L,array,n);
    //muestraL(L);
    //printf("Crea Ordenado\n");
    //creaOrdenado(&L,array,n);
    //muestraL(L);

    return 0;
}

void creaLinvertido(TLista *L,TElementoL array[], int n) {
    TLista aux;
    int i;
    if(n <= 0)
        printf("Cantidad de elementos del arreglo invalida\n");
    else {
        //caso del primer elemento
        aux = (TLista) malloc(sizeof(nodo));
        aux->dato = array[0];
        aux->sig = NULL;
        *L = aux;
        //Caso de los demas elementos
        for(i=1; i<n; ++i) {
            aux = (TLista) malloc(sizeof(nodo)); //Vemos que al crealo invertido cada nuevo nodo se conecta siempre a la cabeza directamente
            aux->dato = array[i];                   //Como resultado no hace falta aux
            aux->sig = *L;
            *L = aux;
        }
    }
}

void creaManteniendo(TLista *L,TElementoL array[], int n) {
    TLista aux,ant;
    int i;
    if(n <= 0)
        printf("Cantidad de elementos del arreglo invalida\n");
    else {
        aux = (TLista) malloc(sizeof(nodo));
        aux->dato = array[0];
        aux->sig = NULL;
        *L = aux;
        for(i=1; i<n; ++i) { //Se podria simplificar inclusive, para no usar la variable ant, pero no es mas claro
            ant = aux;
            aux = (TLista) malloc(sizeof(nodo));
            aux->dato = array[i];
            ant->sig = aux;
        }
        aux->sig = NULL;
    }
}

void creaOrdenado(TLista *L,TElementoL array[], int n) {
    int i;
    *L = NULL;
    if(n <= 0)
        printf("Cantidad de elementos del arreglo invalida\n");
    else
        for(i=0; i<n; ++i)
            insertaLOrd(L,array[i]);
}

void insertaLOrd(TLista *L,char x) {
    TLista aux,act,ant;

    aux = (TLista) malloc(sizeof(nodo));
    aux->dato = x;

    if(*L == NULL || x < (*L)->dato) { //SIEMPRE antes de comprobar si *L == NULL *L debe estar inicializado
        aux->sig = *L;                  //En el caso de la insercion ordenada siempre debemos tener en cuenta esto.
        *L = aux;
    }
    else {
        ant = NULL;
        act = *L;
        while(act != NULL && x > act->dato ) { //recordar usar > solo y no >= porque sino lo pondra adelante
            ant = act;
            act = act->sig;
        }
        aux->sig = act; //Recordar que primero se asigna el siguiente del elemento al insertar y luego se le asigna al anterior el elemento a insertar
        ant->sig = aux;
    }
}
