#include <stdio.h>
#include <ctype.h>

//verif con sonnet 4.5 haciendo pruebas de escritorio
int contA(Arbol AB) {
    int cont = 0, aux;

    while(AB) {
        //aux = 0; no es necesario inicializar ya que la expesion de abajo ya devuelve 1 o 0
        aux = esVocal(AB->car) && hijosCumplen(AB->izq);
        cont += rec(AB->izq, aux);
        AB = AB->der;
    }
    return cont;
}

int esVocal(char car) {
    car = toupper(car);
    return car == 'A' || car == 'E' || car == 'I' || car == 'O' || car == 'U';
}

/*
Recordar de no usar una variable para recorrer en el while cuando podria usar la misma condicion
int hijosCumplen(Arbol AB) {
    int cumple = 1;
    if(AB == NULL)
        return 1; // 1 o 0?, medio ambiguo
    else {
        while(AB && cumple) { //recordar que si la condicion del while es lo mismo que se evalua con una variable dentro, puedo poner solo la condicion
            cumple = !esVocal(AB->car);
            AB = AB->der;
        }
        return cumple;
    }
}
*/
/*
int hijosCumplen(Arbol AB) {

    if(AB == NULL) //estoy evaluando lo mismo que el return
        return 1; // 1 o 0?, medio ambiguo
    else {
        while(AB && !esVocal(AB->car)) { //recordar que si la condicion del while es lo mismo que se evalua con una variable dentro, puedo poner solo la condicion
            AB = AB->der;
        }
        return AB == NULL;
    }
}
*/
int hijosCumplen(Arbol AB) {
    while(AB && !esVocal(AB->car))
        AB = AB->der;
    return AB == NULL;
}

int rec(Arbol AB, int cont) {

    if(AB == NULL)
        return 0;
    else {
        cont += esVocal(AB->car) && hijosCumplen(AB->izq);
        if(cont == 2)
            return 1;
        else
            return rec(AB->izq, cont) || rec(AB->der, cont);
    }
}