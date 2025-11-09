#include <stdio.h>
#include <string.h>
#define N 50


int verif(Arbol AG, Pos p, int nivel, int k) { //verificado
    int subCumple = 1 , tieneMin = 0, tieneMax = 0, grValido = 0;
    char pDato[N], actDato[N];
    Pos c;

    if(Nulo(p) || nivel > k)
        return 1;
    else {
        c = hijoMasIzq(p, AG);
        if(Nulo(c))
            return 1;
        else {
            strcpy(pDato,Info(p, AG));
            if(hnoDer(c, AG))
                grValido  = 1;

            while(!Nulo(c) && subCumple) {
                strcpy(actDato, Info(c, AG));

                if(!tieneMin && strcmp(actDato, pDato) < 0)
                    tieneMin = 1;
                else
                    if(!tieneMax && strcmp(actDato, pDato) > 0)
                        tieneMax = 1;
                
                subCumple = verif(AG, c, nivel + 1, k);
                c = hnoDer(c, AG);
            }
        }
        return subCumple && (!grValido || nivel != k || tieneMin && tieneMax);
    }
}   

int main() {
    int k;
    Arbol AG;
    cargaAG(&AG);
    printf("Ingrese k\n");
    scanf("%d",&k);
    verif(AG, Raiz(AG),1, k) ? printf("Cumple\n") : printf("No cumple\n");
    return 0;
}