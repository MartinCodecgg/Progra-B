#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
 char dato;
 struct nodo * sig;} nodo;
typedef nodo * TLista;

typedef struct nodoD{
    char dato;
    struct nodoD *sig, *ant; } nodoD;
typedef nodoD * Pnodo;

typedef struct {
    Pnodo pri, ult;} TListaD;

void creaL(TLista *L, int array[], int n) {
    TLista aux,ant;
    int i;
    if(n <= 0)
        printf("Cantidad de elementos del arreglo invalida\n");
    else {
        aux = (TLista) malloc(sizeof(nodo));
        aux->dato = array[0];
        aux->sig = NULL;
        *L = aux;
        for(i=1; i<n; ++i) {
            ant = aux;
            aux = (TLista) malloc(sizeof(nodo));
            aux->dato = array[i];
            ant->sig = aux;
        }
        aux->sig = NULL;
    }
}

void muestraL(TLista L) {
    TLista aux = L;

    while(aux != NULL) {
        printf("%d ",aux->dato);
        aux = aux->sig;
    }
    printf("\n");
}

void muestraLD(TListaD LD) {
    Pnodo act;
    if(LD.pri != NULL) { //LD es simplemente un struct con dos campos, asi que accedo con .pri y no con flecha
        act = LD.pri;       //Si pasase como referencia a LD si usaria flecha
        while(act != NULL) {
            printf("%d ", act->dato);
            act = act->sig;
        }
        printf("\n");
    }
}

void copiaLD(TLista L, TListaD *LD){
    TLista actL;
    Pnodo new, antLD;

    if(L != NULL){ //INNECESARIO, Lo que no debo hacer es acceder a campos pudiendo ser la variable NULL
        actL = L;           //de todas formas lo dejo por la ultima sentencia
        while(actL != NULL){
            new = (Pnodo) malloc(sizeof(nodoD));
            //new->sig = actL->sig; ASIGNACION NO VALIDA, no enlazar con tipos de nodos diferentes
            new->dato = actL->dato;
            if(LD->pri == NULL) {//primer nodo a crear
                new->ant = NULL; //RECORDAR que debo asignar pri y ult en el caso del primer y ultimo nodo
                LD->pri = new;
            }
            else {
                new->ant = antLD; //no el primer nodo
                antLD->sig = new;
            }
            antLD = new;
            actL = actL->sig;
        }
        new->sig = NULL; //2 lineas para el caso del ultimo nodo
        LD->ult = new;
    }
}

int main() {
    TLista L;
    TListaD LD;
    // Inicializar la lista vacía SIEMPRE Debemos inicializar antes de crear listas dobles
    LD.pri = NULL;
    LD.ult = NULL;

    int array[] = {1,2,3,4};
    int n = 4;
    creaL(&L,array,n);
    muestraL(L);
    copiaLD(L,&LD);
    muestraLD(LD);
    return 0;
}
