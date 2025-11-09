#include <stdio.h>
#include <ctype.h>
#define N 50

typedef struct nodo {
    char pal[N];
    struct nodo *izq, *der;} nodo;

typedef nodo * Arbol;

//inciso a //verif con sonnet 4.5 y renzo
int grado(Arbol AB) {
    int gr = 0;
    while(AB) {
        gr++;
        AB = AB->der;
    }
    return gr;
}

int esConsonante(char car) {
    char aux = tolower(car);
    return aux >= 'b' && aux <= 'z' && aux != 'e' && aux != 'i' && aux != 'o' && aux != 'u';
}

int verif(Arbol AB) {
    Arbol raiz;
    int cumple = 1, gr;

    raiz = AB;
    while(raiz && cumple) {
        gr = grado(raiz->izq);
        cumple = esConsonante(raiz->pal[0]) && gr != 0 && gr % 2 == 0 || arbolCumple(raiz->izq);
        raiz = raiz->der;
    }
    return cumple;
}

int arbolCumple(Arbol AB) {
    int gr;

    if(AB == NULL || AB->izq == NULL && AB->der == NULL)
        return 0;
    else {
        gr = grado(AB);
        return gr % 2 == 0 && esConsonante(AB->pal[0]) || arbolCumple(AB->izq) || arbolCumple(AB->der);
    }
}

//inciso B
int cuenta(ArbolG AG, Pos p, int nivel, int k) { //verif con sonnet 4.5
    Pos c;
    int cont = 0, cumple = 1, val;
    if(Nulo(p) || nivel == k)
        return 0;
    else {
        c = hijoMasIzq(p,AG);

        if(Nulo(hijoMasIzq(c)))
            val = Info(c, AG);
        else
            cumple = 0;
        while(!Nulo(c)) {
            cont += cuenta(AG,c,nivel + 1,k);
            if(cumple && Info(c,AG) % val != 0)
                cumple = 0;
            c = hnoDer(c, AG);
        }
        return cumple + cont; //el + tiene mayor precedencia que el &&
    }
}

int valida2doG(TLista vec[], int n, int v) { //verif con sonnet 4.5
    TLista act;
    int tieneBucle = 0, cont  = 0;

    act = vec[v];
    while(act) {
        if(act->v == v && act->peso != 0) {
            tieneBucle = 1;
            cont++; //recordar que debo contar tambien el grado del bucle
        }
        else
            cont += act->peso != 0;
        
        act = act->sig;
    }
    return tieneBucle && cont % 2 != 0;
}

int rec(int mat[][N], int n, TLista vec[], int i, int j, int cont) {
    
    if(i < 0)
        return 1;
    else
        if(mat[i][i] != 0)
            return rec(mat, n, vec, i-1,n,0); 
        else {
            cont += mat[j][i] != 0;
            if(j > 0)
                return rec(mat, n, vec, i, j-1, cont);
            else
                if(cont % 2 != 0)
                    return rec(mat,n,vec,i-1,n,0);
                else
                    if(valida2doG(vec,n,i))
                        return rec(mat, n, vec, i-1, n, 0);
                    else
                        return 0;
        }
}
//...
//cargaV(vec,&n); cargaMat(man,n);
//llamada main: rec(mat,n-1,vec,n-1,n-1,0) ? printf("cumple\n") : printf("No cumple\n");