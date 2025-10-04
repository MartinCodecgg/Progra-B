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

void elimina2(TListaD *LD) {
    Pnodo act, elim;

    if(LD->pri != NULL) { //innecesario, es inncesario ya que estoy preguntando lo mismo en el while
        act = LD->pri;
        while(act != NULL) {
            if(act->cantDias == 0) {
                if(act->sig == NULL && act->ant == NULL) { ///LD->pri == LD->ult
                    //elim = act; //Se repite
                    LD->pri = NULL;
                    LD->ult = NULL;
                    //act = NULL; // SE REPITE
                    //free(elim);  //SE REPITE
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

void elimina3(TListaD *LD) {
    Pnodo act, elim;
        act = LD->pri;
        while(act != NULL) {
            if(act->cantDias == 0) {
                elim = act;
                if(LD->pri == LD->ult) {
                    LD->pri = NULL;
                    LD->ult = NULL;
                }
                else {
                    if(act == LD->pri) {
                        LD->pri->sig->ant = NULL;
                        LD->pri = LD->pri->sig;
                    }
                    else
                        if(act == LD->ult) {
                            LD->ult->ant->sig = NULL;
                            LD->ult = LD->ult->ant;
                        }
                    else {
                        act->ant->sig = act->sig;
                        act->sig->ant = act->ant;
                    }
                }
                act = act->sig;
                free(elim);
            }
            else
                act = act->sig;
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

// Función para liberar toda la lista
void liberarLista(TListaD *LD) {
    Pnodo act = LD->pri, siguiente;
    while(act != NULL) {
        siguiente = act->sig;
        free(act);
        act = siguiente;
    }
    LD->pri = LD->ult = NULL;
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

    liberarLista(&lista);

    printf("\n=== PRUEBA 2: Todos los nodos tienen cantDias = 0 ===\n");
    insertarFinal(&lista, "B001", 0, 100.0);
    insertarFinal(&lista, "B002", 0, 200.0);
    insertarFinal(&lista, "B003", 0, 300.0);

    printf("Antes de eliminar:\n");
    mostrarLista(&lista);

    elimina3(&lista);

    printf("Después de eliminar (debería estar vacía):\n");
    mostrarLista(&lista);

    liberarLista(&lista);

    printf("\n=== PRUEBA 3: Solo primer y último nodo tienen cantDias = 0 ===\n");
    insertarFinal(&lista, "C001", 0, 100.0);
    insertarFinal(&lista, "C002", 5, 200.0);
    insertarFinal(&lista, "C003", 8, 300.0);
    insertarFinal(&lista, "C004", 0, 400.0);

    printf("Antes de eliminar:\n");
    mostrarLista(&lista);

    elimina3(&lista);

    printf("Después de eliminar:\n");
    mostrarLista(&lista);

    liberarLista(&lista);

    // === CODIGO EJERCICIO ===

    /*
    elimina2(&lista);
    printf("Después de eliminar:\n");
    mostrarLista(&lista);
    */
    return 0;
}
