#include <stdio.h>

void prim(int mat[][N],int n, int ini, int arbolGen[][N]) {
    int u[N], nu = 0, j,k, vertice, VV[N], pesoMin;

    for(j = 0; j < n; j++)
        VV[j] = 0;
    u[nu] = ini;
    nu++;
    VV[ini] = 1; //vector ordenado por cantidad de visitados

    while(nu < n-1) {
        pesoMin = 99999;
        for(k = 0; k < nu; k++) { //recorre nu[] (vector con todos los vertices)
            for(j = 0; j < n; j++) {
                if(mat[nu[k]][j] != 0 && VV[j] != 1 && mat[nu[k]][j] < pesoMin) {
                    pesoMin = mat[nu[k]][j];
                    Vmin = nu[k];
                    adyMin = j;
                }
                if(j < n) {//es decir si encontre un adyacente valido
                    u[nu] = adyMin;
                    nu++;
                    VV[adyMin] = 1; //marco el nuevo vertice como visitado
                    arbolGen[Vmin][adyMin] = pesoMin;
                    arbolGen[adyMin][Vmin] = pesoMin;
                }
            }
    }
}
//llamado main: prim(mat,n,3,arbolGen);

int main() {





    return 0;
}
