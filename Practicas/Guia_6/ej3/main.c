#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TOP_PALABRAS 30

/*
Escribir un programa que lea desde un archivo un texto que contiene una cantidad desconocida
de palabras (una en cada línea) y genere una lista ordenada de todas las palabras existentes en
el texto con su frecuencia de aparición.
*/

typedef struct nodo{
 char dato[TOP_PALABRAS];
 int cant;
 struct nodo * sig;} nodo;

typedef nodo * TLista;

void Leer(TLista *L);
void insertaOrd(TLista *L,char nom[]);
void muestraL(TLista L);


int main() {

    TLista L = NULL;
    Leer(&L);
    printf("\nMostrando la lista ordenada\n\n");
    muestraL(L);

    return 0;
}

void Leer(TLista *L) {

    FILE *arch = fopen("palabras.txt","rt");

    if(arch == NULL)
        printf("Error al abrir el archivo");
    else {
        char nom[TOP_PALABRAS];
        printf("Archivo abierto correctamente\n");

        while(fscanf(arch,"%[^\n]\n",nom) == 1) {
            printf("%s\n",nom);
            insertaOrd(L,nom);
        }
    }
}

void insertaOrd(TLista *L,char nom[]) {

    TLista aux, act, ant;
    //Caso del primer elemento
    if(*L == NULL || strcmp(nom,(*L)->dato) < 0) {
        aux = (TLista) malloc(sizeof(nodo));
        strcpy(aux->dato,nom);
        aux->cant = 1; //fijo el contador en 1 no en cero, porque es unico elemento
        aux->sig = *L;
        *L = aux;
    }
    else {
        act = *L;
        ant = NULL;
        while(act != NULL && strcmp(nom,act->dato) > 0)  {
            ant = act;
            act = act->sig;
        }
        if(act != NULL && strcmp(nom,(act)->dato) == 0) //Siempre que pregunto por el == debo pregunrar si el actual no es nulo
            ++act->cant;
        else {
            aux = (TLista) malloc(sizeof(nodo));
            strcpy(aux->dato,nom);
            aux->cant = 1;
            aux->sig = act; //recordar asignar al elemento a insertar el siguiente antes de asignar el anterior al elemento a insertar
            ant->sig = aux;
        }
    }
}

void muestraL(TLista L) {
    TLista aux = L;
    while(aux != NULL) {
        printf("%s %d\n",aux->dato,aux->cant);
        aux = aux->sig;
    }
}
