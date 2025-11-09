#include <stdio.h>

//tomo el nivel de la raiz como cero en este caso por convencion
//verif con sonnet 4.5
int calcular(Arbol AB, int k1, int k2) {
    Arbol act;
    int cont = 0;
    act = AB;
    while(act) {
        cont += k1 == 0 && act->num < 0 || tieneClaveNeg(act->izq,1,k1,k2); //la primera condicion analiza la raiz
        act = act->der;
    }
    return cont;
}

int tieneClaveNeg(Arbol AB, int nivel, int k1, int k2) {
    Arbol act;
    
    if(AB == NULL)
        return 0;
    else
        if(nivel >= k1 && nivel <= k2 && AB->num < 0)
            return 1;
        else
            if(nivel < k2)
                return tieneClaveNeg(AB->izq, nivel + 1,k1,k2) || tieneClaveNeg(AB->der, nivel,k1,k2);
            else
                return 0; //recordar retornar algo en todos los casos
}

//verif con sonnet 4.5
void minYmax(ArbolG AG, int *min, int *max, int k, Pos p, int nivel) {
    int gr = 0;
    Pos c;

    if(!Nulo(p) && nivel <= k) {
        c = hijoMasIzq(p, AG);
        while(!Nulo(c)) {
            gr++;
            minYmax(AG, min, max, k, c, nivel + 1);
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

//vefic con prof
void esSub(int mat[][N], int n) {
    int i, Gcumple = 1, Hcumple = 1, j;

    i = n;
    while(i >= 1 && (Gcumple || Hcumple)) {
        j = i-1;
        while(j > 0 && (Gcumple || Hcumple)) {
            if(Gcumple && mat[i][j] == 1 && mat[j][i] == 0)
                Gcumple = 0;
            if(Hcumple && mat[j][i] == 1 && mat[i][j] == 0)
                Hcumple = 0;
            j--;
        }
        i--;
    }

    if(Gcumple && Hcumple)
        printf("Ambos son subgrafos entre si\n");
    else
        if(Gcumple)
            printf("G es subgrafo de G'");
        else
            if(Hcumple)
                printf("G' es subgrafo de G");
            else
               printf("Ningun grafo cumple la condicion\n");
}