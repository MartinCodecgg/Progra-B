#include <stdio.h>
#define N 50

void muestraCamino(int P[], int v) { //suponiendo que el predecesor del origen es -1
    int caminoInv[N], i, tam;

    tam = 0;
    while(v != -1) {
        caminoInv[tam] = v;
        v = P[v];
        tam++;
    }

    for(i = tam-1; i >= 0; i--)
        printf("%d\t",caminoInv[i]);

}

int main() {
    int P[] = {-1,0,1,2}, v = 3;
    muestraCamino(P,v);
    return 0;
}
