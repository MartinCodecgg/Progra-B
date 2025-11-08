#include <stdio.h>
#define N 50
#define INFINITO 9999

void convertir(int D[][N], int n, int R[][N]) {
    int i, j, k;

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(D[i][j] == INFINITO)
                R[i][j] = 0;
            else
                R[i][j] = 1;
}

int main() {
    return 0;
}
