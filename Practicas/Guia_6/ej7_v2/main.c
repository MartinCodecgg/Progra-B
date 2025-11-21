#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 50

typedef struct nodito {
    char titulo[N], nom[N];
    int anio;
    struct nodito * sig; } nodito;

typedef nodito * SubLista;

typedef struct nodo {
    char nom[N];
    SubLista sub;
    struct nodo * sig; } nodo;

typedef nodo * TLista;

void buscaPosAutorSocio(TLista L, TLista *act, TLista *ant, char nom[]) {
    while(*act && strcmp(nom, (*act)->nom) > 0) {  //busco pos de autor o socio
        *ant = *act;
        *act = (*act)->sig;
    }
}

void buscaPosLibro(SubLista *actS, SubLista *antS, char titulo[]) {
    while(*actS && strcmp(titulo, (*actS)->titulo) > 0) { //busco pos del libro
        *antS = *actS;
        *actS = (*actS)->sig;
    }
}

void insertaAutorSocio(TLista *L, TLista *act,TLista ant, char nom[]) {
    TLista nuevo;

    nuevo = (TLista) malloc(sizeof(nodo));
    strcpy(nuevo->nom, nom);
    nuevo->sub =  NULL;
    nuevo->sig = *act;
    if(*act == *L)
        *L = nuevo;
    else
        ant->sig = nuevo;

    *act = nuevo;
}

void agregaLibro(TLista vec[]) {
    TLista act, ant;
    SubLista actS, antS, nuevoLib;
    int aux, anio;
    char autor[N], titulo[N];

    printf("Ingrese autor, titulo y anio para crear el libro\n");
    scanf(" %s %s %d", autor, titulo, &anio);
    aux = toupper(autor[0]) - 'A';
    act = vec[aux];
    buscaPosAutorSocio(vec[aux], &act, &ant, autor);

    if(act == NULL || strcmp(act->nom,autor) != 0)
        insertaAutorSocio(&vec[aux], &act, ant, autor);

    nuevoLib = (SubLista) malloc(sizeof(nodito));
    nuevoLib->anio = anio;
    strcpy(nuevoLib->nom,autor);
    strcpy(nuevoLib->titulo, titulo);

    actS = act->sub;
    buscaPosLibro(&actS, &antS, titulo);

    nuevoLib->sig = actS;
    if(actS == act->sub)
        act->sub =  nuevoLib;
    else
        antS->sig = nuevoLib;
}

void enlazayDesenlaza(TLista *Lorigen, TLista *Ldestino, char titulo[], char nomOrigen[],char nomDestino[]) {
    TLista act, ant;
    SubLista actS, antS, libro;

    //Manejar origen
    act = *Lorigen;
    buscaPosAutorSocio(*Lorigen, &act, &ant, nomOrigen); //busco pos de autor o socio

    if(act) {
        actS = act->sub;
        buscaPosLibro(&actS, &antS, titulo); //busco pos del libro
        libro = actS; //el libro que quiero desenlanzar

        if(libro) {
            if(actS == act->sub) //desenlaza
                act->sub = act->sub->sig;
            else
                antS->sig = actS->sig;

            if(act->sub == NULL) { //eliminar autor o socio si ya no tiene libros para prestar o para devolver
                if(*Lorigen == act)
                    *Lorigen = (*Lorigen)->sig;
                else
                    ant->sig = act->sig;
                free(act);
            }

            //Manejar destino
            act = *Ldestino;
            buscaPosAutorSocio(*Ldestino, &act, &ant, nomDestino); //busco del autor o socio a insertar

            if(act == NULL ||strcmp(act->nom,nomDestino) != 0) //Si el autor o socio no existe crearlo e insertarlo (act ya apunta a la posicion a insertar)
                insertaAutorSocio(Ldestino, &act, ant, nomDestino);

            actS = act->sub;
            buscaPosLibro(&actS, &antS, titulo);

            libro->sig = actS; //enlazo (insercion)
            if(actS == act->sub)
                act->sub = libro;
            else
                antS->sig = libro;
        }
    }
}

void prestamosYdevoluciones(TLista vec[], TLista *socios) {
    char autor[N], titulo[N], socio[N], opcion;
    int aux;

    printf("Ingrese la operacion que desea realizar, prestamo(P), o devolucion(D)\n");
    scanf(" %c",&opcion);
    opcion = toupper(opcion);

    printf("Ingrese el nombre del socio\n");
    scanf(" %s",socio);

    printf("Ingrese autor, titulo del libro que desea pedir\n");
    scanf("%s %s", autor, titulo);
    aux = toupper(autor[0]) - 'A';

    if(opcion == 'P')
        enlazayDescenlaza(&vec[aux],socios, titulo, autor, socio);  //es mejor pasar el vector evaluado en la posicion de la lista que hacer aux = vec[toupper(autor[0] - 'A'], porque si luego para actualizar la posicion del vector es un bardo
    else
        enlazayDescenlaza(&vec[aux],socios, titulo, socio, autor);
}//recordar usar &vec[aux] si le paso un puntero de array de punteros

int main() {
    TLista vec[N], socios;
    char opcion;

    cargaVec(vec);
    cargaSocios(&socios);

    printf("Ingrese la opcion que desea realizar, agregar un libro (A), realizar un prestamo o devolucion (B)\n");
    scanf(" %c", &opcion); //recordar poner siempre un espacio adelante, para agarrar costumbre
    if(toupper(opcion) == 'A')
        agregaLibro(vec);
    else
        prestamosYdevoluciones(vec, &socios);
    return 0;
}
