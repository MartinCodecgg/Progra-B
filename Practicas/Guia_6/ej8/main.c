#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    char dato;
    struct nodo * sig, *ant; } nodo;

typedef nodo * Pnodo;

typedef struct {
    Pnodo pri, ult;} TListaD; //La D hace referencia a lista doble //Pnodo ya es un puntero asi que pri y ult no van con *

void creaL(TListaD *L, char array[], int n) {
    Pnodo aux;
    int i;

    // Inicializar la lista vacía
    L->pri = NULL;
    L->ult = NULL;

    if(n <= 0) {
        printf("Cantidad de elementos del arreglo invalida\n");
        return;
    }

    // Crear el primer nodo
    aux = (Pnodo) malloc(sizeof(nodo));
    aux->dato = array[0];
    aux->sig = NULL;
    aux->ant = NULL;

    // Establecer primer y último nodo (por ahora es el mismo)
    L->pri = aux;
    L->ult = aux;

    // Crear el resto de nodos
    for(i = 1; i < n; ++i) {
        aux = (Pnodo) malloc(sizeof(nodo));
        aux->dato = array[i];
        aux->sig = NULL;
        aux->ant = L->ult;  // El anterior es el último actual

        // Enlazar el último nodo actual con el nuevo
        L->ult->sig = aux;

        // Actualizar el último nodo
        L->ult = aux;
    }
}

void muestraL(TListaD LD) {
    Pnodo act;
    if(LD.pri != NULL) { //LD es simplemente un struct con dos campos, asi que accedo con .pri y no con flecha
        act = LD.pri;       //Si pasase como referencia a LD si usaria flecha
        while(act != NULL) {
            printf("%c ", act->dato);
            act = act->sig;
        }
        printf("\n");
    }
}

void contVocales(TListaD LD) {
    Pnodo act;
    int cont = 0;
    if(LD.pri != NULL) {
        act = LD.pri;
        while(act != NULL) {
            if(act->dato == 'a' || act->dato == 'e' || act->dato == 'i' || act->dato == 'o' || act->dato == 'u')
                ++cont;
            act = act->sig;
        }
        printf("La cantidad de nodos que contienen vocales es de: %d\n",cont);
    }
}

int estaOrd(TListaD LD) {
    Pnodo act;
    if(LD.pri == NULL || LD.pri->sig == NULL)
        return 1;
    else {
        act = LD.pri->sig;
        while(act != NULL && act->dato > act->ant->dato)
            act = act->sig;
        return (act == NULL);
    }
}

void eliminaPos(TListaD *LD, int p) {
    Pnodo act,elim;
    int aux;

    if(LD->pri != NULL) {
        if(p == 0) { //si elimino desde la primer posicion
            elim = LD->pri;
            LD->pri = LD->pri->sig;
            if(LD->pri == NULL) //si era un unico elemento
                LD->ult = NULL;
            else
                LD->pri->ant = NULL; //si elimino el primer elemento, debo modificar su siguiente SIEMPRE
            free(elim);
        }
        else {
            act = LD->pri;
            aux = 0;
            while(act != NULL && aux != p) {
                act = act->sig;
                aux++;
            }
            if(act != NULL && aux == p) { //Nadie afirma que el dato existe
                elim = act;
                act->ant->sig = act->sig; //engancha el anterior con el siguiente
                if(act->sig != NULL)
                    act->sig->ant = act->ant; // engancha el siguiente con el anterior
                else
                    LD->ult = act->ant; //modifico el puntero al ultimo
                free(elim);
            }//RECORDAR que al trabajar con listas dobles
        } //debo modificar tanto el anterior como el siguiente SIEMPRE a no ser que sea el primer elemento o el ultimo
    }   //si es el primero modifica solo el siguiente, si es el ultimo solo el anterior , ademas de modificar el LD
}

int main() {
    TListaD LD;
    char array[] = {'a','b','e','f'};
    int n = 4, p;
    creaL(&LD,array,n);
    muestraL(LD);
    contVocales(LD);
    if(estaOrd(LD))
        printf("Esta ordenado\n");
    else
        printf("No esta ordenado\n");
    printf("Ingrese P\n");
    scanf("%d",&p);
    eliminaPos(&LD, p);
    muestraL(LD);
    return 0;+
}
