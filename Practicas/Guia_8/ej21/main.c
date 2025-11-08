#include <stdio.h>
#define N 3
#define M {{0,1,1},{0,0,1},{0,0,1}}

int masAlcanzado(int A[][N], int i, int j, int n, int cont, int max, int vMax) {
    if(j < 0)
        return vMax;
    else {
        if(A[i][j] != 0)
            cont++;
        if(i > 0)
            return masAlcanzado(A,i-1,j,n, cont, max, vMax);
        else {
            if(cont > max) {
                max = cont;
                vMax = j;
            }
            return masAlcanzado(A,n,j-1,n, 0, max, vMax);
        }
    }
}

int main() {
    int mat[][N] = M, n = N;
    printf("El vertice mas alcanzable es: %d",masAlcanzado(mat,n-1,n-1,n-1,0,-1,-1));
    return 0;
}
