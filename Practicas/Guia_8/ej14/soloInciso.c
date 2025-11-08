#include <stdio.h>
#include <stdlib.h>

void prim(int mat[][N], int n, int ini, int arbolGen[][N]) {
    int u[N], nu = 0, j, k, VV[N], pesoMin, fila, col;
    int Vmin, adyMin;

    for(j = 0; j < n; j++)
        VV[j] = 0;
    u[nu] = ini;
    nu++;
    VV[ini] = 1;

    while(nu < n) { //u debe tener la misma cantidad de vertices del grafo, es decir n
        pesoMin = 99999;
        for(k = 0; k < nu; k++)
            for(j = 0; j < n; j++) {

                if(u[k] < j) { //triangulo superior
                    fila = u[k];
                    col = j;
                }
                else { //estoy en el triangulo inferior ahora y paso a recorrer la columna del vertice actual
                    fila = j;
                    col = u[k];
                }

                if(mat[fila][col] != 0 && VV[col] == 0 && mat[fila][col] < pesoMin) {
                    pesoMin = mat[fila][col];
                    Vmin = fila;
                    adyMin = col;
                }
            }
        if(pesoMin != 99999) {
            u[nu] = adyMin;
            nu++;
            VV[adyMin] = 1;
            arbolGen[Vmin][adyMin] = pesoMin;
            arbolGen[adyMin][Vmin] = pesoMin;
        }
    }
}
// Llamado: prim(mat, n, 3, arbolGen);

int main() {

    return 0;
}
