#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* === ALGORITMOS DE LISTA SIMPLEMENTE ENLAZADA === */

void muestraL(TLista L) { //verif
    while(L) {
        printf("%c ",L->dato);
        L = L->sig;
    }
}

/*
Nada que aclarar
*/

TListaL buscaL(TLista L, char pal[]) { //verif
    while(L && strcmp(pal,L->pal) > 0)
        L = L->sig;
    return (L && strcmp(pal,L->pal) == 0) ? L : NULL;
}

/*
Nada que aclarar
*/

void elimina(TLista *L, char pal[]) { //verif
    TLista actL, antL;
    actL = *L;
    while(actL && strcmp(pal,actL->pal) != 0) {
        antL = actL;
        actL = actL->sig;
    }
    if(actL && strcmp(pal,actL->pal) == 0) {
        if(actL == *L) //unico o cabeza
            *L = (*L)->sig;
        else
            antL->sig = actL->sig; //otro
        free(actL);
    }
}

/*
Los casos particulares a considerar son el unico/cabeza y otro
*/

void eliminaPos(TLista *L, unsigned int pos) { //verif
    TLista actL, antL;
    unsigned int aux = 0;
    actL = *L;
    while(actL && aux != pos) {
        antL = actL;
        actL = actL->sig;
        aux++;
    }
    if(actL && aux == pos) {
        if(actL == *L)
            *L = (*L)->sig;
        else
            antL->sig = actL->sig;
        free(actL);
    }
}

void eliminacionSucesiva(TLista *L, char pal[]) { //verif
    TLista actL, antL, elim;
    actL = *L;
    while(actL) {
        if(strcmp(pal,actL->pal) == 0) {
            elim = actL;
            if(actL == *L) //Unico o cabeza
                (*L) = (*L)->sig;
            else
                antL->sig = actL->sig; //otro
            actL = actL->sig;
            free(elim);
        }
        else {
            antL = actL; //actualizar antL solo si no elimine nada
            actL = actL->sig;
        }
    }
}

/*
Como es eliminacion sucesiva necesito la variable elim
Si debo eliminar le asigno act al principio
Si no elimino solo avanzo
Si elimino, antes de eliminar avanzo y uso un solo free(elim) para todos los casos
Los casos particulares a considerar son Unico/Cabeza y otro antes de la cabezay otro
*/

void insertaOrd(TLista *L, char pal[]) { //veri
    TLista actL, antL, new;
    new = (TLista) malloc(sizeof(nodo)); //(si corresponde)
    //asignar datos
    actL = *L;
    while(actL && strcmp(pal,actL->pal) > 0) {
        antL = actL;
        actL = actL->sig;
    }
    new->sig = actL;
    if(actL == *L)
        *L = new;
    else
        antL->sig = new;
}

/*
Siempre lo primero que hago es asignarle el actual al siguiente del nuevo
Si cabeza asigno el nuevo a L
Si no es cabeza desenlazo el nodo solamente
Los casos particulares a considerar son Lista Vacia/insercion antes de la cabezay otro
*/

/* === ALGORITMOS DE LISTA DOBLEMENTE ENLAZADA === */

void muestraLD(TListaD LD) { //verif
    Pnodo aux = LD.pri;
    while(aux) {
        printf("%c ", aux->dato);
        aux = aux->sig;
    }
}

Pnodo busca(TListaD LD, char pal[]) { //verif
    Pnodo actD = LD.pri;
    while(actD && strcmp(pal,actD->pal) > 0)
        actD = actD->sig;
    return (actD && strcmp(pal,actD->pal) == 0) ? actD : NULL;
}

//Aqui necesito una variable auxiliar no puedo recorrer con LD.pri directamente

void eliminaLD(TListaD *LD, char pal[]) { //verif
    Pnodo aux = LD->pri;
    while(aux && strcmp(pal,aux->pal) > 0)
        aux = aux->sig;
    if(aux && strcmp(pal,aux->pal) == 0) {
        if(LD->pri == LD->ult) //unico
            LD->pri = LD->ult = NULL;
        else
            if(aux == LD->pri) {
                LD->pri->sig->ant = NULL; //cabeza pri
                LD->pri = LD->pri->sig;
            }
        else
            if(aux == LD->ult) {
                LD->ult->ant->sig = NULL; //cabeza ult
                LD->ult = LD->ult->ant;
            }
        else {
            aux->ant->sig = aux->sig; //otro
            aux->sig->ant = aux->ant;
        }
        free(aux);
    }
}

/*
En este caso como no es sucesiva solo necesito free(aux)
Los casos particulares son Unico, Cabeza Pri, Cabeza Ult, Otro
*/

void eliminaSucesiva(TListaD *LD) { //verif
    Pnodo act, elim;
        act = LD->pri;
        while(act != NULL) {
            if(act->cantDias == 0) {
                elim = act;
                if(LD->pri == LD->ult) {
                    LD->pri = NULL;
                    LD->ult = NULL;
                }
                else
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
                act = act->sig;
                free(elim);
            }
            else
                act = act->sig;
        }
}

/*
En este caso como al ser sucesiva necesito elim
Si pasa el if de que cumple la condicion para eliminar, ahi ya hago elim = act
Si no tengo que eliminar va el else y solo hace aux = aux->sig;
Luego de pasar todos los casos avanzo en aux y luego hago free (si corresponde eliminar)
Los casos particulares son Unico, Cabeza Pri, Cabeza Ult, Otro
*/

void insertaOrd(TListaD *LD, char pal[]) { //verif
    Pnodo new, aux;
    new = (Pnodo) malloc(sizeof(nodoD));
    //asignarle los datos
    aux = LD->pri;
    while(aux && strcmp(pal,aux->pal) > 0)
        aux = aux->sig;
    if(LD->pri == NULL) { //Lista vacia //no es valida la comparacion multiple en C
        new->sig = new->ant = NULL;
        LD->pri = LD->ult = new;
    }
    else
        if(strcmp(pal,LD->pri->pal) < 0) { //cabeza pri
            new->ant = NULL;
            new->sig = LD->pri;
            LD->pri->ant = new;
            LD->pri = new;
        }
        else
            if(strcmp(pal,LD->ult->pal) > 0) { //cabeza ult
                new->sig = NULL;
                new->ant = LD->ult;
                LD->ult->sig = new;
                LD->ult = new;
        }
        else { //otro
            new->sig = aux; //siempre tratar el nodo nuevo, y sus enlaces y luego recien los demas, aunque en este caso da igual, en otros casos el orden si importa y el orden correcto general es siempre tratar el nuevo primero
            new->ant = aux->ant;
            aux->ant->sig = new;
            aux->ant = new;
        }
}

/*
La diferencia entre la insercion y la eliminacion en listas circulares y dobles (porque en la simple da igual), es que la insercion debemos preguntar si es mayor o menor a la cabeza y no si es igual (como en la eliminacion)
Los casos particulares son Lista Vacia, menor que cabeza pri, mayor que cabeza ult, otro
*/

/* === ALGORITMOS DE LISTA CIRCULAR === */

void muestraLC(TListaC LC) { //verif
    TListaC aux;
    if(LC) {
        aux = LC->sig;
        do {
            printf("%d", aux->dato);
            aux = aux->sig;
        } while(aux != LC->sig);
    }
}

/*
Recordar que para mostrar en la lista circular conviene usar el do while
Muestro
Avanzo
Condicion del while
*/

TListaC busca(TListaC LC, char pal[]) { //verif
    TListaC aux;
    if(LC) {
        aux = LC->sig;
        while(aux != LC && strcmp(pal,aux->pal) != 0)
            aux = aux->sig;
        return (strcmp(pal, aux->pal) == 0) ? aux : NULL;
    }
    else
        return NULL;
}

//En la busqueda de la lista circular como debo preguntar por LC al princpio tambien debo poner un else con un return NULL para cubrir todas las ramas

void insertaLC(TListaC *LC, char pal[]) { //verif
    TListaC actC, antC, new;
    new = (TListaC) malloc(sizeof(nodoC)); //(si corresponde)
    //copiar parametro a new
    if(*LC) {
        antC = (*LC);
        actC = (*LC)->sig;
        while(actC != *LC && strcmp(pal,actC->pal) > 0) {
            antC = actC;
            actC = actC->sig;
        }
        //new->sig = actC;
        if(strcmp(pal,(*LC)->pal) > 0) {//tengo que insertar en la cabeza
            new->sig = (*LC)->sig;
            (*LC)->sig = new;
             *LC = new;
        }
        else { //otro
            antC->sig = new;
            new->sig = actC;
        }
    }
    else { //vacia
        *LC = new;
        new->sig = new;
    }
}

/*
En la insercion en lista circular, tambien en la eliminacion, el anterior lo hago ult y el act lo hago el primero
Dado que debo preguntar si LC es valido, si no se cumple va el else con el caso particular de que la lista venga vacia
Los casos particulares son: Lista Vacia, Mayor a cabeza y Otro
*/

void elimina(TListaC *LC, char pal[]) { //verif
    TListaC actC, antC;
    if(*LC) {
        antC = (*LC);
        actC = (*LC)->sig;
        while(actC != *LC && strcmp(pal, actC->pal) != 0) {
            antC = actC;
            actC = actC->sig;
        }
        if(strcmp(pal,actC->pal) == 0) {
            if(*LC == (*LC)->sig) //unico
                *LC = NULL;
            else {
                antC->sig = actC->sig; //otro
                if(actC == *LC) //cabeza
                    *LC = antC;
            }
            free(actC);
        }
    }
}

/*
Muy similar a la insercion
Los casos particulares son: Unico, cabeza y otro
*/

void eliminaSucesiva(TListaC *LC, char pal[]) { //verif
    TListaC antC, actC, elim;
    if(*LC) {
        antC = (*LC);
        actC = (*LC)->sig;
        do {
            if(strcmp(pal, actC->pal) == 0) {
                elim = actC;
                if(*LC == (*LC)->sig)   // unico nodo
                    *LC = NULL;
                else {
                    antC->sig = actC->sig; //otro
                    if(actC == *LC)  // cabeza
                        *LC = antC;
                    actC = actC->sig;
                }
                free(elim);
            }
            else { //si no hay que eliminar nada
                antC = actC;
                actC = actC->sig;
            }
        } while(*LC && actC != (*LC)->sig);  // Termina cuando vuelve a ser el 1ero,
    }
}
//La ventaja del do while es q permite no repetir logica para el caso de la cabeza

/*
En la eliminacion multiple en la lista circular conviene usar do while para no repetir mucha logica
El orden es:
Empiezo por pri
Pregunto si debo eliminar
Si debo eliminar:
-elim = act;
-Casos particulares
-Free
La condicion del while es mientras LC sea valido y mientras actC sea distinto del primer elemento

Los casos particulares son: unico, cabeza y otro
*/

int main() {
    TLista L;
    TListaD LD;
    TListaC LC;
    L = LD = LC = NULL;

    printf("Hello world!\n");
    return 0;
}

