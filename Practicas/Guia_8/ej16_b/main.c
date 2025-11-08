#include <stdio.h>
#define N 4
#define INFINITO 9999
#define M {{0,30,0,13},{22,0,10,12},{0,25,0,0},{13,6,0,0}}

void floydYcaminosMinimos(int mat[][N], int n, int distancias[][N]) {
    int k, i, j, sig[N][N], siguiente;

    //Inicializaciones
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(i == j) {
                distancias[i][j] = 0; //la distancia de un elemento a si mismo es siempre cero
                sig[i][j] = -1; //porque 0 podria ser un vertice
            }
            else
                if(mat[i][j] != 0) {
                    distancias[i][j] = mat[i][j];
                    sig[i][j] = j;
                }
                else {
                    distancias[i][j] = INFINITO;
                    sig[i][j] = -1;
                }

    //armar matriz de distancias y matriz de siguientes para mostrar luego los caminos minimos
    for(k = 0; k < n; k++)  // k = intermediario
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(distancias[i][k] + distancias[k][j] < distancias[i][j]) {//si [i][k] o [k][j] son INFINITO entonces no cumplira la condicion
                    distancias[i][j]  = distancias[i][k] + distancias[k][j];
                    sig[i][j] = sig[i][k];
                }

    //Armar y mostrar caminos minimos
    for(i = 0; i < n; i++) //i = origen
        for(j = 0; j < n; j++) {// j = destino
            siguiente = sig[i][j];
            printf("\n Camino minimo entre %d y %d \n",i,j);
            printf("%d\t",i);
            while(siguiente != j && siguiente != -1) {
                printf("%d\t",siguiente);
                siguiente = sig[siguiente][j];
            }
            if(siguiente != -1)
                printf("%d\t distancia = %d",siguiente, distancias[i][j]);
            else
                printf("%d\t distancia = %d",j, distancias[i][j]);
        }
}

int main() {
    int mat[][N] = M, n = N, distancias[N][N];
    floydYcaminosMinimos(mat, n, distancias);
    return 0;
}
