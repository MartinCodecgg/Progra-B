#include <stdio.h>
//#include "TDANARIO.h"

int cuenta(Arbol AG, Pos p, int k1, int k2, int nivel) {
    Pos c;
    int grValido = 0, datoPriHijo, datoUltHijo, tot = 0;

    if(Nulo(p) || nivel > k2)
        return 0;
    else {
        c = hijoMasIzq(p, AG);
        if(Nulo(c))
            return 0;
        else {
            datoPriHijo = Info(c, AG);
            if(!Nulo(hnoDer(c)))
                grValido = 1;
            
            while(!Nulo(hnoDer(c))) {
                tot += cuenta(AG, c, k1, k2, nivel + 1);
                c = hnoDer(c, AG);
            }
            datoUltHijo = Info(c, AG);
            tot += cuenta(AG, c, k1, k2, nivel + 1);
            if(nivel >= k1 && nivel <= k2 && grValido && datoPriHijo > nivel && datoUltHijo > nivel)
                tot++;
            
            return tot;
        }
    }
}

int main() {
    Arbol AG;
    int k1, k2;
    cargaAG(&AG);
    printf("Ingrese K1 y K2\n");
    scanf("%d %d", &k1, &k2);
    printf("La cantidad de nodos de que cumplen con la condicion es %d", cuenta(AG, Raiz(AG), k1, k2, 0));
    return 0;
}

