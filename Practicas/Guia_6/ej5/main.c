#include <stdio.h>
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\TDA Pila Dinamica\pilas.h"
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\TDA Pila Dinamica\pilas.c"
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\IMPL_COLAESTATICACIRCULAR\colas.h"
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\IMPL_COLAESTATICACIRCULAR\colas.c"

#define TOP 30

typedef struct nodo {
TCola C;
struct nodo * sig; } nodo;
typedef nodo * TLista;

void generaL(TLista *L);
void generaP(TPila *P, TLista L);
void muestraP(TPila *P);

int main() {
    TLista L = NULL;
    TPila P;
    IniciaP(&P);
    generaL(&L);
    generaP(&P,L);
    printf("\n\nMostrando pila generada\n");
    muestraP(&P);
    return 0;
}

void muestraP(TPila *P) {

    TElemento elem;
    while(!VaciaP(*P)) {
        sacaP(P,&elem);
        printf("%d\n",elem);
    }
}

void generaP(TPila *P, TLista L) {

    TLista aux = L;
    TElemento elem;
    int cent = 9999,max;

    while(aux != NULL) {
        max = -9999;
        poneC(&(aux->C),cent);
        sacaC(&(aux->C),&elem);
        while(elem != cent) {
            poneC(&(aux->C),elem);
            sacaC(&(aux->C),&elem);
            if(elem != cent && elem > max)
                max = elem;
        }
        poneP(P,max);
        aux = aux->sig;
    }
}

void generaL(TLista *L) {

    /* forma de cargar si el orden importase (incompleto)
    TLista aux,act,ant;
    TElementoC elemC;

    int array1[] = {1,2,3,4,5};
    int array2[] = {2,4,6,8,10};
    int n = 5, i, k, cantL = 3; //Una lista de 4 nodos (3 + el primer nodo)

    //Caso del 1er elemento
    aux = (TLista) malloc(sizeof(nodo));
    IniciaC(&(aux->C));
    poneC(&(aux->C),array1[0]);
    aux->sig = NULL;
    *L = aux;


    //Caso de los demas elementos
    for(k=0; k<cantL; ++k )
        for(i=0; i<n; ++i) {
            ant = aux;
            aux = (TLista) malloc(sizeof(nodo));
            IniciaC(&(aux->C));
            if (n % 2 != 0)
                poneC(&(aux->C),array2[i]);
            else
                poneC(&(aux->C),array1[i]);

            ant->sig = aux;
        }
        aux->sig = NULL;
    */

    //Dado que el orden no importa al hallar el maximo de cada cola, hacemos de forma invertida

    TLista aux;

    int array1[] = {1,2,3,4,5};
    int array2[] = {2,4,6,8,10};
    int n = 5, i, j, cantL = 4; //Una lista de 4 nodos

    printf("Carga de la lista\n");
    for(i=0; i<cantL; ++i) {
        printf("\nnodo %d\n",i+1);
        aux = (TLista) malloc(sizeof(nodo));
        IniciaC(&(aux->C));
        for(j=0; j<n; ++j) //no hacen falta llaves ya que el if con el else son una sola sentencia
            if(j%2 != 0 && i%2 != 0) { //esta condicion es para guardar datos diferentes en cada cola
                poneC(&(aux->C),array2[j]);
                printf("%d\t",array2[j]);
            }
            else {
                poneC(&(aux->C),array1[j]);
                printf("%d\t",array1[j]);
            }
        aux->sig = *L;
        *L = aux;
    }
}
