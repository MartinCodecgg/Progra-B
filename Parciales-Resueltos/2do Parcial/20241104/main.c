#include <stdio.h>
#include <ctype.h>

int esConsonante(char car) {
    char aux = tolower(car);
    return aux >= 'b' && aux <= 'z' && aux != 'e' && aux != 'i' && aux != 'o' && aux != 'u';
}

int verif(Arbol AB) {
    Arbol act;
    int cumple = 1;

    act = AB;
    while(act && cumple) {
        cumple = esConsonante(act->pal[0]) && arbolCumple(AB->izq); //recordar que en estos de ejercicios de arbol a bosque la raiz se analiza por separado
        act = act->der;
    }
    return cumple;
}

int arbolCumple(Arbol AB) {
    Arbol act;
    int hijoCumple = 0, gr = 0;

    if(AB == NULL)
        return 0;
    else 
        if(AB->izq == NULL && AB->der == NULL || !esConsonante(act->pal[0]))
            return 0;
        else {
            act = AB;
            while(act && !hijoCumple) {
                gr++;
                hijoCumple = arbolCumple(AB->izq);
                act = act->der;
            }
            return gr % 2 == 0 || hijoCumple;
        }
}

int cuenta(ArbolG AG, Pos p, int nivel, int k) {
    Pos c;
    int esHoja = 0, cont = 0, cumple = 1, val;
    if(!Nulo(p) || nivel == k)
        return 0;
    else {
        nivel++;
        c = hijoMasIzq(p,AG);
        if(hijoMasIzq(c)) {
            esHoja = 1; val = Info(c, AG);
        }
        while(!Nulo(c)) {
            cont += cuenta(AG,c,nivel,k);
            cumple = Info(c,AG) % val != 0;
            c = hnoDer(c, AG);
        }
        return esHoja && cumple + cont;
    }
}

int valida2doG(TLista vec[], int n, int v) {
    TLista act;
    int tieneBucle = 1, cont  = 0;

    act = vec[v];
    while(act && tieneBucle) {
        if(act->v == v && act->peso == 0)
            tieneBucle = 0;
        else {
            cont += act->peso != 0;
            act = act->sig;
        }
    }
    return tieneBucle && cont % 2 != 0;
}

int rec(int mat[][N], int n, TLista vec[], int i, int j, int cont) {
    
    if(i < 0)
        return 1;
    else
        if(mat[i][j] == 1)
            return rec(mat, n, vec, i-1,n,0); 
        else {
            cont += mat[i][j] != 0;
            if(j > 0)
                return rec(mat, n, vec, i, j-1, cont);
            else
                if(cont % 2 != 0)
                    return rec(mat,n,vec,i-1,n,0);
                else
                    return 0;
        }
}
//...
//cargaV(vec,&n); cargaMat(man,n);
//llamada main: rec(mat,n-1,vec,n-1,n-1,0) ? printf("cumple\n") : printf("No cumple\n");