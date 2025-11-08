#include <stdio.h>
#define N 50
#define MAX_VAL 99999

int todosVisitados(int VV[], int n) {
    int i = 0;
    while(i < n && VV[i] == 1)
        i++;
    return i == n;
}

int djikstra(int mat[][N], int n, int origen, int destino) {
    int D[N],S[N], ns = 0, j, v, min, pesoMin, VV[N]; // v = vertice
    
    //inicializaciones
    for(j = 0; j < n; j++) {
        D[j] = MAX_VAL;
        VV[j] = 0;
    }
    D[origen] = 0;
    S[ns] = origen;
    ns++;
    VV[origen] = 1;
    v = origen;

    while(!todosVisitados(VV, n) && v != destino) {
        pesoMin = MAX_VAL;
        for(j = 0; j < n; j++) {
            if(mat[v][j] != 0 && VV[j] == 0 && mat[v][j] + D[v] < D[j]) {
                D[j] = mat[v][j] + D[v];
            }
            if(VV[j] == 0 && D[j] < pesoMin) {
                min = j;
                pesoMin = D[j];
            }
        }
        if(pesoMin != MAX_VAL) {
            S[ns] = min;
            ns++;
            VV[min] = 1; //marco como "en S" una vez que hallado el vertice a S recien
            v = min;
        }
    }
    return pesoMin;
}

int main() {
    int mat[N][N], origen, destino, n, S[N], longCamino;
    //cargaMat(mat,&n;)
    printf("Ingrese origen y destino\n");
    scanf("%d %d",origen, destino);
    printf("Peso camino minimo: %d",djikstra(mat,n,origen,destino, &longCamino));
    return 0;
}
