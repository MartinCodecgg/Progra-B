
// a) La dimension seria de 6 x 6, por tener 6 vertices

// b)
#include <stdio.h>
#define N 6
#define M {{0,0,1,0,1,0},{1,0,0,1,0,0},{0,0,0,0,1,0},{0,0,0,0,0,0},{0,0,0,0,0,1},{0,0,0,0,0,0}}

void warshall(int mat[][N], int n, int R[][N]) {
    int i, j, k;

    //Inicializaciones
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(i == j)
                R[i][j] = 1;
            else
                if(mat[i][j] != 0)
                    R[i][j] = 1;
                else
                    R[i][j] = 0;

    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(R[i][k] == 1 && R[k][j] == 1)
                    R[i][j] = 1;
}




// === CODIGO IA === :
void imprimirMatriz(int mat[][N], int n, char vertices[]) {
    printf("\n    ");
    for(int j = 0; j < n; j++)
        printf("%c ", vertices[j]);
    printf("\n");

    for(int i = 0; i < n; i++) {
        printf("%c | ", vertices[i]);
        for(int j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

int main() {
    int adyacencia[][N] = M;
    int alcance[N][N];
    int n = 6; // A, B, C, D, E, F
    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    // Índices: A=0, B=1, C=2, D=3, E=4, F=5
    // Construyendo el grafo de tu imagen:

    printf("Matriz de Adyacencia:");
    imprimirMatriz(adyacencia, n, vertices);

    warshall(adyacencia, n, alcance);

    printf("\n\nMatriz de Alcance R:");
    imprimirMatriz(alcance, n, vertices);

    printf("\n\nInterpretacion:");
    printf("\nDesde A se puede alcanzar: ");
    for(int j = 0; j < n; j++)
        if(alcance[0][j]) printf("%c ", vertices[j]);

    return 0;
}
