#include <stdio.h>
#include <ctype.h>
//#include "TDANARIO.h"
#define N 500
/*
//En estos casos como no tengo que validar algo sobre los hijos de cada nodo, conviene extraer la logica de validar un nodo antes del while, ademas asi me ahorro logica adicional para la raiz
void buscaA(Arbol AG, Pos p, int vec[], int niv, int *niveles1, int *maxNiv) {
    Pos c;

    if(!Nulo(p)) {
        c = hijoMasIzq(p, AG);
        if(niv > *maxNiv)
            *maxNiv = niv;
        while(!Nulo(c)) {
            if(vec[niv + 1] != 1 && esVocal(Info(c, AG))) {
                vec[niv + 1] = 1;
                (*niveles1)++;
            }
            buscaA(AG, c, vec, niv + 1, niveles1, maxNiv);
            c = hnoDer(c, AG);
        }
    }
}

int esVocal(char car) {
    car = toupper(car);
    return car == 'A' || car == 'E' || car == 'I' || car == 'O' || car == 'U';
}

int main() {
    Arbol AG;
    int vec[N] = {0}, niveles1 = 0, maxNiv = -1; //si tomase el nivel de la raiz igual a 1, me queda la componente cero sin usar, en cambio si tomase de la componente cero seria mas facil
    carga(&AG);
    buscaA(AG, Raiz(AG), vec, 0, &niveles1, &maxNiv);
    vec[0] = esVocal(Info(Raiz(AG), AG));
    if(vec[0])
        niveles1++;
    maxNiv+1 == niveles1 ? printf("Cumple\niveles1") : printf("No cumple\niveles1");
    return 0;
}
*/
//v2 haciendo la logica fuera del while

//En estos casos como no tengo que validar algo sobre los hijos de cada nodo, conviene extraer la logica de validar un nodo antes del while, ademas asi me ahorro logica adicional para la raiz
int esVocal(char car) {
    car = toupper(car);
    return car == 'A' || car == 'E' || car == 'I' || car == 'O' || car == 'U';
}

void validar(Arbol a, Pos p, int v[], int *niveles1, int *maxNiv, int niv) {
    Pos c;
    
    if(!Nulo(p)) {
        if(v[niv] == 0 && esVocal(Info(p, a))) {
            v[niv] = 1;
            (*niveles1)++;
        }
        
        if(niv > *maxNiv)
            *maxNiv = niv;
        
        c = hijoMasIzq(p, a);
        while(!Nulo(c)) {
            validar(a, c, v, niveles1, maxNiv, niv + 1);
            c = hnoDer(c, a);
        }
    }
}

int main() {
    Arbol AG;
    int vec[N] = {0}, niveles1 = 0, maxNiv = -1;
    
    carga(&AG);
    
    validar(AG, Raiz(AG), vec, &niveles1, &maxNiv, 0);
        
    (niveles1 == maxNiv + 1) ? printf("Cumple\n") : printf("No cumple\n");
    
    return 0;
}
