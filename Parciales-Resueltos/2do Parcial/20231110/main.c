#include <stdio.h>

int calcular(Arbol AB, int k1, int k2) {
    Arbol act;
    int cont = 0;
    act = AB;
    while(act) {
        cont += tieneClaveNeg(AB->izq,1,k1,k2);
        act = act->der;
    }
    return cont;
}

int tieneClaveNeg(Arbol AB, int nivel, int k1, int k2) {
    arbol act;
    
    if(AB == NULL)
        return 0;
    else
        if(nivel >= k1 && nivel <= k2 && AB->num > 0)
            return 1;
        else
            if(nivel < k2)
                return tieneClaveNeg(AB->izq, nivel+1,k1,k2) || tieneClaveNeg(AB->der, nivel,k1,k2);
}

void minYmax(ArbolG AG, int *min, int *max, int k, Pos p, int nivel) {
    int gr = 0;
    Pos c;

    if(!Nulo(p)) {
        c = hijoMasIzq(p, AG);
        while(!Nulo(c)) {
            gr++;
            if(nivel < k)
                minYmax(AG, min, max, k, c, nivel+1);
            c = hnoDer(c, AG);
        }
        if(nivel == k)
            if(gr < *min)
                *min = gr;
            else
                if(gr > *max)
                    *max = gr;
    }
}

int esSub(int mat[][N], int n) {
    int i, Gcumple = 1, Hcumple = 1, j;

    i = n;
    while(i >= 1 && (Gcumple || Hcumple)) {
        j = i-1;
        while(j > 0 && (Gcumple || Hcumple)) {
            if(mat[i][j] && mat[j][i] == 0)
                Gcumple = 0;
            if(mat[j][i] == 1 && mat[i][j] == 0)
                Hcumple = 0;
            j--;
        }
        i--;
    }

    if(Gcumple && Hcumple)
        printf("Ambos son subgrafos entre si\n");
    else
        if(Gcumple)
            printf("G es subgrafo de G´");
        else
            if(Hcumple)
                printf("G´ es subgrafo de G");
            else
               printf("Ningun grafo cumple la condicion\n");
}