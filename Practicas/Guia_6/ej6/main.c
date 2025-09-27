#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
6. Se tiene una lista con equipos de fútbol (nombre y puntaje en el torneo), la cual está ordenada
descendentemente por puntaje (los equipos con el mismo puntaje están ordenados
alfabéticamente). Cada equipo cuenta con una sublista de jugadores (nombre y edad, estado
([A]ctivo, [S]uspendido)).
a) Listar para todos los clubes los jugadores cuyo nombre comienza con la letra K (dato). Al
finalizar mostrar cantidad de jugadores listados y el club que tiene más jugadores que
cumplan el criterio solicitado.
b) Listar los clubes que tienen un mínimo de X (dato) puntos junto con todos sus jugadores,
mostrando edad promedio de cada equipo.
c) Verificar si el equipo E (dato) tiene P (dato) puntos.
d) Eliminar los jugadores que se encuentren en estado inactivo en todos los equipos.
*/

#define TOP_NOMBRE 30
#define CANT_DATOS 3

typedef char Tnombre[TOP_NOMBRE];

typedef struct nodito {
    Tnombre nombre;
    int edad;
    char estado;
    struct nodito * sig; } nodito;

typedef nodito * sublista;

typedef struct nodo {
    char nomClub[TOP_NOMBRE];
    int puntaje;
    sublista sub; //Sublista directamente porque sublista esta definido con typedef, ademas es el struct mismo, no un puntero a sublista
    struct nodo * sig; } nodo;

typedef nodo * TLista;

void generaL(TLista *L);
void insertaOrd(TLista * L,char nomClub[],int puntaje,Tnombre nombres[],int edades[],char estados[]);
void Listado(TLista L,char k);
void ListadoClubes(TLista L, int x);
int verificar(TLista L,char E[], int P);
void eliminaJugadores(TLista L);
void muestraL(TLista L);

int main(){

    TLista L = NULL;
    char k, E[TOP_NOMBRE]; //recordar siempre al definir arreglos poner la dimension.
    int x, p;

    generaL(&L);

    printf("\nIngrese K\n");
    scanf(" %c",&k);
    Listado(L,k);
    printf("Ingrese X para el inciso B\n");
    scanf("%d",&x);
    printf("Listado de clubes\n");
    ListadoClubes(L,x);
    printf("Ingrese E y P\n");
    scanf(" %s",E);
    scanf(" %d",&p);

    if(verificar(L,E,p))
        printf("El equipo tiene la cantidad de puntos ingresados\n");
    else
        printf("El equipo NO tiene la cantidad de puntos ingresados");

    eliminaJugadores(L);
    printf("\nMostrando Jugadores\n");
    muestraL(L);
    return 0;
}

void generaL(TLista *L) {

    char nom1[] = "Boca",nom2[] = "Racing" ,nom3[] = "Barca";
    int puntaje1 = 5,puntaje2 = 7, puntaje3 = 7;
    Tnombre nombres1[] = {"lucas","renzo","mauro"}; //recordar para definir arrays de string, ya no va el char, si defino mi propio tipo
    Tnombre nombres2[] = {"kasino","kukardo","blberto"};
    Tnombre nombres3[] = {"valentino","bmi","aaaa"};

    int edades1[] = {19,20,21};
    int edades2[] = {17,25,29};
    int edades3[] = {19,50,21};

    char estados1[] = {'A','A','A'};
    char estados2[] = {'S','S','S'};
    char estados3[] = {'A','A','A'};

    printf("\nMostrando Lista 1\n");
    insertaOrd(L,nom1,puntaje1,nombres1,edades1,estados1);
    printf("\nMostrando Lista 2\n");
    insertaOrd(L,nom2,puntaje2,nombres2,edades2,estados2);
    printf("\nMostrando Lista 3\n");
    insertaOrd(L,nom3,puntaje3,nombres3,edades3,estados3);
}
//RECORDAR si tira error de passing arguments es porque no coincide con la implementacion
void insertaOrd(TLista * L,char nomClub[],int puntaje,Tnombre nombres[],int edades[],char estados[]) {

    TLista aux, act, ant;
    sublista auxSub = NULL, antSub;
    int i;

    //Defino la lista que voy a insertar
    aux = (TLista) malloc(sizeof(nodo));
    strcpy(aux->nomClub,nomClub);
    printf("%s\t",aux->nomClub);
    aux->puntaje = puntaje;
    printf("%d\t",aux->puntaje);

    //SubLista
    for(i=0; i<CANT_DATOS; ++i) {
        antSub = auxSub;
        auxSub = (sublista) malloc(sizeof(nodito));
        strcpy(auxSub->nombre,nombres[i]);
        printf("%s\t",auxSub->nombre);
        auxSub->edad = edades[i];
        printf("%d\t",auxSub->edad);
        auxSub->estado = estados[i];
        printf("%c\t",auxSub->estado);

        if(antSub == NULL)
            aux->sub = auxSub;
        else
            antSub->sig = auxSub;

        antSub = auxSub;
    }
    auxSub->sig = NULL;

    //Lista
    if(*L == NULL || puntaje > (*L)->puntaje || (puntaje == (*L)->puntaje && strcmp(nomClub, (*L)->nomClub) < 0)){
        aux->sig = *L; //El problema es tambien aqui debo verificar que si son iguales, en caso de serlos
        *L = aux;       //tengo que desempatar por el orden de abecedario, si es menor se inserta aqui y es mayor en la rama del else
    }
    else {
        ant = NULL;
        act = *L;
        while(act != NULL && puntaje < act->puntaje) {
            ant = act;
            act = act->sig;
        }
        while(act != NULL && puntaje == act->puntaje && strcmp(nomClub,act->nomClub) > 0) { //el puntaje debe seguir siendo el mismo.
            ant = act;
            act = act->sig;
        }
        ant->sig = aux; //Debemos verificar siempre que ant no llegue siendo NULL aqui, si llega a ser null crashea al intentar acceder a sig
        aux->sig = act; //recordar que debo usar 3 variables aqui, act, ant y aux, y la que estoy insertando es aux
    }
}

void Listado(TLista L, char k) {

    TLista aux = L;

    sublista actS;
    int cont = 0,contMax, max = -9999;
    Tnombre clubMax;

    while(aux != NULL) {
        actS = aux->sub;
        contMax = 0;
        while(actS != NULL) {
                if((actS->nombre)[0] == k) {
                    printf("%s\n",actS->nombre);
                    ++contMax;
                }
                actS=actS->sig;
        }
        cont += contMax;
        if(contMax > max) {
            max = contMax;
            strcpy(clubMax,aux->nomClub);
        }
        aux = aux->sig;
    }
    printf("La cantidad de jugadores mostrados es: %d\n",cont);
    printf("El club con la mayor cantidad de jugadores que cumplen la condicion es: %s\n",clubMax);
}

void ListadoClubes(TLista L, int x) {

    TLista aux = L;
    sublista actS;
    float edadProm;
    int contJugadores;

    while(aux != NULL) {
        if(aux->puntaje > x) {
            printf("%s\n",aux->nomClub);
            actS = aux->sub;
            while(actS != NULL) {
                printf("%s\n",actS->nombre);
                edadProm += actS->edad;
                contJugadores++;
                actS = actS->sig;
            }
            edadProm /= contJugadores;
            printf("La edad promedio de sus jugadores es: %3.2f\n",edadProm);
        }
        aux = aux->sig;
    }
}

int verificar(TLista L,char E[], int P) {

    TLista aux = L;

    while(aux != NULL && strcmp(E,aux->nomClub) != 0) {
        aux = aux->sig;
    }
    if(aux != NULL && strcmp(E,aux->nomClub) == 0 && aux->puntaje == P)
        return 1;
    else
        return 0;
}

void eliminaJugadores(TLista L) {

    TLista aux = L;
    sublista actS, antS, elim;

    while(aux != NULL) {
        actS = aux->sub;
        while(actS != NULL) {
            if(actS == aux->sub) {
                if(aux->sub->estado == 'S') { //caso de la cabecera
                    elim = aux->sub;
                    aux->sub = aux->sub->sig;
                    actS = actS->sig;
                    free(elim);
                }
                else {
                    antS=actS;
                    actS=actS->sig;
                }
            }
            else {
                if(actS->estado == 'S') {
                    antS->sig = actS->sig;
                    elim = actS;
                    actS = actS->sig;
                    free(elim);
                }
                else {
                    antS=actS;
                    actS = actS->sig;
                }
            }
        }
        aux = aux->sig;
    }
}

// Inciso e optimizado (Sonnet 4)
void eliminaJugadores_v2(TLista L) {
    TLista aux = L;
    sublista actS, antS, elim;

    while(aux != NULL) {

        antS = NULL;
        actS = aux->sub;
        while(actS != NULL) {
            if(actS->estado == 'S') {
                elim = actS;

                if(antS == NULL) { // Es el primer nodo
                    aux->sub = actS->sig;
                    actS = aux->sub;
                } else { // No es el primer nodo
                    antS->sig = actS->sig;
                    actS = actS->sig;
                }

                free(elim);
            } else {
                antS = actS;
                actS = actS->sig;
            }
        }
        aux = aux->sig;
    }
}
//Lo que hace esta forma es inicializar el antS en NULL, para luego preguntar si es NULL o no y asi ver si es la cabecera o no
//Ademas cuando se determina que un nodo hay que eliminarse, se lo guarda en elim, luego se hace una logica u otra
//dependiendo si es la cabecera o no, y por ultimo se le hace al free al nodo a eliminar
//Por el else del 1er if simplemenete avanza y asigna el actual al anterior

void muestraL(TLista L) {
    TLista aux = L;
    sublista actS;
    while(aux != NULL) {
        printf("%s %d\n\n",aux->nomClub,aux->puntaje);
        actS = aux->sub;
        while(actS != NULL) {
            printf("%s %d %c\n",actS->nombre,actS->edad,actS->estado);
            actS = actS->sig;
        }
        aux = aux->sig;
    }
}
