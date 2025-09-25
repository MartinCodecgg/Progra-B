#include <stdio.h>
#include "../TDA CREA_LISTA/Crea_Listas.h"
#include "../TDA CREA_LISTA/Crea_Listas.c"

typedef struct nodo{
 char dato;
 struct nodo * sig;} nodo;
typedef nodo * TLista; //Ya que los nodos se crean siempre de forma dinamica usando malloc, y malloc devuelve un puntero a nodo, justmamente un TLista

void muestraL(TLista L); //Si no voy a modificar entonces solo espero una copia.
void contVocal(TLista L);
void estaOrdenada(TLista L);
void Elimina(TLista *L, int pos);

int main() {
    TLista L;
    char array[] = {'a','e','i','o','u'};
    //char array[] = {'a'};
    int n = 5;

    creaL(&L,array,n); //Como voy a modificar el puntero, entonces lo paso el puntero como referencia.
    muestraL(L);
    //contVocal(L);
    //estaOrdenada(L);
    Elimina(&L,3);
    printf("Muestra luego de la eliminacion\n"); //recordar en cualquier printf poner \n por costumbre
    muestraL(L);

    return 0;
}
void muestraL(TLista L) {
    TLista aux = L;

    while(aux != NULL) {
        printf("%c\n",aux->dato);
        aux = aux->sig;
    }
}

void contVocal(TLista L) {
    TLista aux = L;
    int cont = 0;

    while(aux != NULL) {
        if (aux->dato == 'a' ||
            aux->dato == 'e' ||
            aux->dato == 'i' ||
            aux->dato == 'o' ||
            aux->dato == 'u'
        )
            ++cont;

            aux = aux->sig;
    }
    printf("La cantidad de vocales encontradas es: %d\n",cont);
}

void estaOrdenada(TLista L) { //No empezar comparando con valores basura, mejor hacer que aux sea el 2do elemento y ant el 1ro, asi nos ahorramos iteraciones.

    if(L == NULL) //Recordar que estos printF de tipo tecnicos no van, directamente validar. (al menos en el parcial)
        printf("Lista Vacia\n"); //Siempre debo comparar que la estructura no venga vacia
    else {                      //En este caso como luego uso ant en la comparacion, debo preguntar antes que L no sea NULL
        TLista aux, ant;        //Si solo pregunto en el while aux!=NULL el if de L == NULL no es necesario.
        ant = L;
        aux = L->sig;

        while(aux != NULL && aux->dato >= ant->dato) {
                ant = aux;
                aux = aux->sig;
        }
        if (aux == NULL)
            printf("La lista esta ordenada\n"); //NO hay que preguntar aux->dato >= ant->dato aqui ya que hacemos una comparacion con un NULO y eso un error.
        else                                    //Si aux es NULL entoncs es porque todas las comparaciones fueron validas.
            printf("La lista no esta ordenada\n");
    }
}       //IMPORTANTE: en estos ejercicios debemos ver como se desenvuelve el algoritmo si hay 0 o 1 o mas elementos validos
        //Si hay un solo elemento valido (el primero), el algoritmo funciona, no entra al while directamente.

void Elimina(TLista *L, int pos) {
    TLista aux = *L, ant;
    int step = 0;

    if((*L) != NULL) {
        if(pos == 0) {
            *L = aux->sig;
            free(aux);
        }
        else {
            while(step != pos) {
                ant = aux;
                aux = aux->sig;
                ++step;
            }
            ant->sig = aux->sig;
            free(aux);
        }
    }
}
