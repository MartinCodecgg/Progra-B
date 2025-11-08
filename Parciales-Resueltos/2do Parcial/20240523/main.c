#include <stdio.h>
#define N 50

//Inciso A

typedef struct nodo{
    int dato;
    struct nodo *der, *izq; } nodo;

typedef nodo * Arbol;

int determinar(Arbol AB) {
    int Gcumple = 1,gr;
    Arbol bosque, a;

    if(AB == NULL)
        return 0;
    else {
        bosque = AB;
        while(bosque && Gcumple) {
            a = bosque->izq;
            gr = 0;
            while(a) {
                gr++;
                a = a->der;
            }
            Gcumple = arbolCumple(AB, gr);
            a = a->der;
        }
        return Gcumple;
    }
}

int arbolCumple(Arbol AB, int grRaiz) {
    int gr = 0;
    Arbol act;
    
    if(AB == NULL || AB->izq == NULL && AB->der == NULL)
        return 1;
    else {
        act = AB;
        while(act && gr <= grRaiz) {
            gr++;
            act = act->der;
        }
        if(gr <= grRaiz)
            return arbolCumple(AB->izq, grRaiz) && arbolCumple(AB->der,grRaiz);
        else
            return 0;
    }
}

int main () {
    Arbol AB;
    cargaA(&AB);
    determinar(AB) ? printf("Cumple\n") : printf("No Cumple\n");
    return 0;
}


//Inciso b)
int grado(ArbolG AG, Pos p) {
    int gr = 0;
    Pos c = hijoMasIzq(p, AG);
    while(!Nulo(c)) {
        gr++;
        c = hnoDer(c, AG);
    }
    return gr;
}

int determinar(ArbolG AG, Pos p) {
    int grAct, antGr = -9999, subCumple = 0, actCumple = 1;
    Pos c;

    if(Nulo(p))
        return 0;
    else {
        c = hijoMasIzq(p,AG);
        if(Nulo(c))
            return 0;
        else {
            while(!Nulo(c) && !subCumple) {
                grAct = grado(AG,c);
                if(grAct < antGr)
                    actCumple = 0;
                antGr = grAct;
                subCumple = determinar(AG, c);
                c = hnoDer(c,AG);
            }
            return subCumple || actCumple;
        }
    }
}

//inciso C

int cantN(int mat[][N], int i, int j, int n, int cantI, int cantj) {
    if(i < 0)
        return 0;
    else
        if(mat[i][j] == 1)
            return cantN(mat, i-1,n,n,0,0);
        else {
            cantI += mat[i][j];
            cantj += mat[j][i];

            if(j > 0)
                return cantN(mat, i, j-1, n, cantI, cantj);
            else
                if(cantI == cantj)
                    return 1 + cantN(mat, i-1,n,n,0,0);
                else
                    return cantN(mat, i-1,n,n,0,0);
        }
}

