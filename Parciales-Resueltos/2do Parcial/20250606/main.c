#include <stdio.h>
//#include "TDANARIO"

//ejercicios probados mediante prueba de escritorio de IA

typedef struct nodo {
    unsigned int num;
    char cad;
    struct nodo *izq, *der} nodo;

typedef nodo * Arbol;

typedef struct nodoL {
    int v, peso;
    struct nodoL *sig;} nodoL;

typedef nodoL * TLista;

void cantN(Arbol AB, int *contNoDigit, int *cont2Digit) {
    if(AB) {
        if(AB->izq != NULL && AB->der == NULL || AB->izq == NULL && AB->der == NULL)
            if(AB->cad < '0' || AB->cad > '9')
                (*contNoDigit)++;
        if(AB->num >= 10  && AB->num <= 100)
            (*cont2Digit)++;
        
        cantN(AB->izq, contNoDigit, cont2Digit);
        cantN(AB->der, contNoDigit, cont2Digit);
    }
}

int determinar(ArbolG A, Pos p, int nivel, int k) {
    ArbolG c;
    int hijoCumple = 1, acum = 0, gr = 0, dato = info(p,A);
    if(Nulo(p))
        return 1;
    else {
        nivel++;
        if(dato > 0) {
            c = hijoMasIzq(p,A);
            if(!Nulo(c)) {
                while(!Nulo(c) && hijoCumple) {
                    gr++;
                    acum += info(c,A);
                    if(nivel < k) // recordar < k y no < k - 1
                        hijoCumple = determinar(A, c, nivel, k);
                    c = hnoDer(c,A);
                }
                if(gr % 2 == 0)
                    return (float) acum / gr >= 2 * dato && hijoCumple;
                else
                    return 1;
            }
        }
        return 1;
    }
}

void cantV(TLista vec[], int n,int * contV) {
    int i, tieneArista, pesoBucle, min;
    TLista act, ant, elim, antElim;

    for(i = 0; i < n; i++) {
        act = vec[i]; tieneArista = 0; pesoBucle = -1; min = 9999;
        while(act && !tieneArista) {
            if(act->v == i)
                pesoBucle = act->peso;
            else
                if(act->peso < min) {
                    min = act->peso;
                    antElim = ant;
                    elim = act;
            }

            if(pesoBucle != -1 && min < pesoBucle)
                tieneArista = 1;

            ant = act;
            act = act->sig;
        }
        if(tieneArista) { //es mejor hacer la eliminacion afuera del ciclo while si solo debe hacerse una vez, me ahorro verificar if(!tieneArista) antes de avanzar en act y aux
            (*contV)++;
            if(vec[i] == elim)
                vec[i] = vec[i]->sig;
            else
                antElim->sig = elim->sig;
            free(elim);
        }
    }
}

int main() {
    Arbol AB;
    unsigned int contNoDigit = 0, cont2Digit = 0;
    cargaA(&AB);
    cantN(AB, &contNoDigit, &cont2Digit);
    printf("La cantidad de nodos de grado 0 o 1 donde el caracter no es digito: %d," //RECORDAR USAR CONCATENACION AUTOMATICA AL PROGRAMAR EN PAPEL SI NO ME ENTRA TODO EL RENGLON
          "cant. de nodos donde el numero entero es de 2 digitos: %d",contNoDigit, cont2Digit);

    if(determinar(AB,Raiz(AB),0));
    
    return 0;
}