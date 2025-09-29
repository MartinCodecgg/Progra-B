#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ST8 9

typedef struct nodoD {
    char cod[ST8];
    int cantDias;
    float totalVentas;
    struct nodoD *sig,*ant;} nodoD;
typedef struct nodoD * Pnodo;

typedef struct{
    Pnodo pri,ult;} TListaD;

void elimina(TListaD *LD){
    Pnodo act, elim;
    if(LD->pri != NULL) { //como LD es un puntero puedo usar -> flechita directamente
        if(LD->pri->cantDias == 0 && LD->pri != NULL && LD->pri == LD->ult) { //unico elemento
            LD->pri = NULL;
            LD->ult = NULL;
            free(LD->pri);
        }
        else {}
        if(LD->pri != NULL && LD->pri->cantDias == 0 || LD->ult->cantDias == 0){
            if(LD->pri->cantDias == 0) {
                elim = LD->pri;
                LD->pri->sig->ant = NULL;
                LD->pri = LD->pri->sig;
                free(elim);
            }
            if (LD->pri != NULL && LD->ult->cantDias == 0) {
                elim = LD->ult;
                LD->ult->ant->sig = NULL;
                LD->ult = LD->ult->ant;
                free(elim);
            }
        }
        printf("asa");
        act = LD->pri;
        while(act != NULL){
            if(act->cantDias == 0) {
                elim = act;
                act->ant->sig = act->sig;
                act->sig->ant = act->ant;
                act = act->sig;
                free(elim);
            }
            else
                act = act->sig;
        }
    }
}

void elimina2(TListaD *LD) {
    Pnodo act, elim;

    if(LD->pri != NULL) {
        act = LD->pri;
        while(act != NULL) {
            if(act->cantDias == 0) {
                if(act == act->sig) {
                    LD->pri = NULL;
                    LD->ult = NULL;
                    free(act);
                }
                else {
                    if(act == LD->pri) {
                        elim = act;
                        LD->pri->sig->ant = NULL;
                        LD->pri = LD->pri->sig;
                    }
                    else
                        if(act == LD->ult) {
                            elim = act;
                            LD->ult->ant->sig = NULL;
                            LD->ult = LD->ult->ant;
                        }
                    else {
                        elim = act;
                        act->ant->sig = act->sig;
                        act->sig->ant = act->ant;
                    }
                    act = act->sig;
                    free(elim);
                }
            }
            else
                act = act->sig;
        }
    }
}
// Función auxiliar para crear un nodo
Pnodo crearNodo(const char* cod, int cantDias, float totalVentas) {
    Pnodo nuevo = (Pnodo)malloc(sizeof(nodoD));
    if(nuevo != NULL) {
        strcpy(nuevo->cod, cod);
        nuevo->cantDias = cantDias;
        nuevo->totalVentas = totalVentas;
        nuevo->sig = NULL;
        nuevo->ant = NULL;
    }
    return nuevo;
}

// Función para insertar al final
void insertarFinal(TListaD *LD, const char* cod, int cantDias, float totalVentas) {
    Pnodo nuevo = crearNodo(cod, cantDias, totalVentas);
    if(nuevo != NULL) {
        if(LD->pri == NULL) {
            LD->pri = LD->ult = nuevo;
        } else {
            LD->ult->sig = nuevo;
            nuevo->ant = LD->ult;
            LD->ult = nuevo;
        }
    }
}

// Función para mostrar la lista
void mostrarLista(TListaD *LD) {
    Pnodo act = LD->pri;
    printf("Lista: ");
    while(act != NULL) {
        printf("[%s:%d:%.1f] ", act->cod, act->cantDias, act->totalVentas);
        act = act->sig;
    }
    printf("\n");
}

int main(){
    TListaD lista = {NULL, NULL};

    printf("=== PRUEBA 1: Lista con varios nodos con cantDias = 0 ===\n");
    insertarFinal(&lista, "A001", 0, 100.5);
    insertarFinal(&lista, "A002", 5, 200.0);
    insertarFinal(&lista, "A003", 0, 150.0);
    insertarFinal(&lista, "A004", 0, 300.0);
    insertarFinal(&lista, "A005", 10, 400.0);
    insertarFinal(&lista, "A006", 0, 250.0);

    printf("Antes de eliminar:\n");
    mostrarLista(&lista);

    elimina2(&lista);

    printf("Después de eliminar (cantDias = 0):\n");
    mostrarLista(&lista);

    printf("\n=== PRUEBA 2: Todos los nodos tienen cantDias = 0 ===\n");
    insertarFinal(&lista, "B001", 0, 100.0);
    insertarFinal(&lista, "B002", 0, 200.0);
    insertarFinal(&lista, "B003", 0, 300.0);

    printf("Antes de eliminar:\n");
    mostrarLista(&lista);

    elimina2(&lista);

    printf("Después de eliminar (debería estar vacía):\n");
    mostrarLista(&lista);

    printf("\n=== PRUEBA 3: Solo primer y último nodo tienen cantDias = 0 ===\n");
    insertarFinal(&lista, "C001", 0, 100.0);
    insertarFinal(&lista, "C002", 5, 200.0);
    insertarFinal(&lista, "C003", 8, 300.0);
    insertarFinal(&lista, "C004", 0, 400.0);
    printf("Antes de eliminar:\n");
    mostrarLista(&lista);

    elimina2(&lista);

    printf("Después de eliminar:\n");
    mostrarLista(&lista);

    return 0;
}
