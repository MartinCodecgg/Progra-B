#include <stdio.h>
#define N 10

void grafoSubyacente(int mat[][N) {
    unsigned int i,j;

    for(i = 0; i < N - 1; i++)
        for(j = i+1; j < N; j++)
            if(mat[i][j] == 0 && mat[j][i] == 1)
                mat[i][j] = 1;
            else
                if(mat[i][j] == 1 && mat[j][i] == 0)
                    mat[j][i] = 1;
}

//V2 (Hace mas asignaciones aunque no sea necesario) [PREGUNTAR cual es mejor]

void grafoSubyacente(int mat[][N]) {
    unsigned int i, j;

    for(i = 0; i < N; i++)
        for(j = i + 1; j < N; j++)
            if(mat[i][j] == 1 || mat[j][i] == 1) {
                mat[i][j] = 1;
                mat[j][i] = 1;
            }
}

int main() {
    return 0;
}
