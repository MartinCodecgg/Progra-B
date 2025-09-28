#include <stdio.h>
#include <stdlib.h>

void lc_eliminaelem(TLISTAC *pult, TELEMENTOLC elem, int *eliminado) { //nombre de funcion invalido, no puede comenzar con numero
 TLISTAC ant, act = *pult->sig;
 eliminado = 0;
 if (pult = NULL) {
 do{
 ant = act;
 act->sig = act;
 }while ( *pult != act && elem < act.dato);
 if (elem = act->dato){
 if (*pult != (*pult)->sig)
 *pult= NULL;
 else {
 act->sig = ant->sig;
 if (act == *pult)
 pult = *ant;
 }
 free (ant);
 eliminado = 1;
 }
 }
}


int main() {



    return 0;
}
