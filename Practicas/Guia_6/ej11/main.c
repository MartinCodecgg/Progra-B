#include <stdio.h>
#include <stdlib.h>
/*
11. Corregir los errores de la siguiente función, que elimina el nodo de una lista circular que
contiene un valor pasado como parámetro (elem)
*/

void lc_eliminaelem(TLISTAC *pult, TELEMENTOLC elem, int *eliminado) { //nombre de funcion invalido, no puede comenzar con numero
 TLISTAC ant, act = *pult->sig;     //incorrecta inicializacion, debio ser *(pult)->sig;
 eliminado = 0; //debio ser *eliminado = 0
 if (pult = NULL) { //debio ser *pult
 do{
 ant = act;
 act->sig = act; //no tiene sentido esto
 }while ( *pult != act && elem < act.dato); //debio ser act->dato, elem<act.dato tampoco esta bien porque no afirma que esta ordenada
 if (elem = act->dato){
 if (*pult != (*pult)->sig) //si no es el caso del ultimo elemento
 *pult= NULL; //pone en null pero no hace free, tampoco asigna elim para luego eliminar
 else {
 act->sig = ant->sig; //no deberia ir esto aqui, ya que la logica de abajo puede ejecutarse igual
 if (act == *pult) //se refiere al caso de la cabecera
 pult = *ant;   //ant ya es un puntero, esto no esta bien
 }
 free (ant);
 eliminado = 1; //*eliminado = 1; a lo sumo
 }
 }
}


int main() {

    return 0;
}
