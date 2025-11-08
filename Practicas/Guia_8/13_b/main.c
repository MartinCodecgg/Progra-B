#include <stdio.h>
#define N 50

/*estos algoritmos de prim y kruscal no validan que que el grafo sea NO conexo, ya que no tiene sentido aplicar estos algoritmos en grafos no conexos*/

void prim(int mat[][N], int n, int ini, int arbolGen[][N]) { //verificado
    int u[N], nu = 0, j, k, vertice, VV[N], pesoMin;
    int Vmin, adyMin;

    for(j = 0; j < n; j++)
        VV[j] = 0;
    u[nu] = ini;
    nu++;
    VV[ini] = 1;

    while(nu < n) { //si n es la cantidad de vertices entonces la condicion es nu < n es decir hasta que nu = n
        pesoMin = 99999;
        for(k = 0; k < nu; k++) //recorre u[] (vector con todos los vertices)
            for(j = 0; j < n; j++)
                if(mat[u[k]][j] != 0 && VV[j] == 0 && mat[u[k]][j] < pesoMin) {  // == 0 es mas claro que != 1
                    pesoMin = mat[u[k]][j];
                    Vmin = u[k];
                    adyMin = j;
                }
                if(pesoMin != 99999) {//es decir si encontre un adyacente valido
                    u[nu] = adyMin;
                    nu++;
                    VV[adyMin] = 1; //marco el nuevo vertice como visitado
                    arbolGen[Vmin][adyMin] = pesoMin;
                    arbolGen[adyMin][Vmin] = pesoMin;
                }
    }
}
// Llamado: prim(mat, n, 3, arbolGen);

// FUNCIONES DE PRUEBA
void inicializarMatriz(int mat[][N], int n) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            mat[i][j] = 0;
}

void imprimirMatriz(int mat[][N], int n, const char* titulo) {
    printf("\n%s\n", titulo);
    printf("   ");
    for(int i = 0; i < n; i++)
        printf("%3d", i);
    printf("\n");

    for(int i = 0; i < n; i++) {
        printf("%2d:", i);
        for(int j = 0; j < n; j++) {
            if(mat[i][j] == 0)
                printf("  -");
            else
                printf("%3d", mat[i][j]);
        }
        printf("\n");
    }
}

void imprimirArbol(int arbolGen[][N], int n) {
    printf("\n========================================\n");
    printf("  ARBOL GENERADO (Prim)\n");
    printf("========================================\n");

    int pesoTotal = 0;
    int aristasEncontradas = 0;

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arbolGen[i][j] != 0) {
                aristasEncontradas++;
                printf("  Arista %d: %d ---- %d (peso: %2d)\n",
                       aristasEncontradas, i, j, arbolGen[i][j]);
                pesoTotal += arbolGen[i][j];
            }
        }
    }

    printf("========================================\n");
    printf("  Total aristas: %d\n", aristasEncontradas);
    printf("  PESO TOTAL: %d\n", pesoTotal);
    printf("========================================\n");
}

void visualizarArbol(int arbolGen[][N], int n) {
    printf("\nConexiones del arbol:\n");
    for(int i = 0; i < n; i++) {
        printf("Nodo %d conectado con: ", i);
        int tiene = 0;
        for(int j = 0; j < n; j++) {
            if(arbolGen[i][j] != 0) {
                printf("%d(peso:%d) ", j, arbolGen[i][j]);
                tiene = 1;
            }
        }
        if(!tiene) printf("(ninguno)");
        printf("\n");
    }
}

int main() {
    int mat[N][N];
    int arbolGen[N][N];
    int n;

    printf("========================================\n");
    printf("  PRUEBA DEL ALGORITMO DE PRIM\n");
    printf("========================================\n");

    // ==================== PRUEBA 1 ====================
    printf("\n\n=============== PRUEBA 1 ===============\n");
    printf("Grafo simple (5 vertices)\n");
    printf("Inicio desde vertice 0\n");
    printf("     0 ---2--- 1\n");
    printf("     |         |\n");
    printf("     3         5\n");
    printf("     |         |\n");
    printf("     2 ---7--- 3\n");
    printf("               |\n");
    printf("               9\n");
    printf("               |\n");
    printf("               4\n\n");

    n = 5;
    inicializarMatriz(mat, n);
    inicializarMatriz(arbolGen, n);

    // Aristas del grafo
    mat[0][1] = mat[1][0] = 2;
    mat[0][2] = mat[2][0] = 3;
    mat[1][3] = mat[3][1] = 5;
    mat[2][3] = mat[3][2] = 7;
    mat[3][4] = mat[4][3] = 9;

    imprimirMatriz(mat, n, "Matriz de adyacencia (Grafo original):");

    printf("\nEjecutando Prim desde nodo 0...\n");
    prim(mat, n, 0, arbolGen);

    imprimirMatriz(arbolGen, n, "Matriz del arbol generado:");
    imprimirArbol(arbolGen, n);
    visualizarArbol(arbolGen, n);

    // ==================== PRUEBA 2 ====================
    printf("\n\n=============== PRUEBA 2 ===============\n");
    printf("Grafo mediano (6 vertices)\n");
    printf("Inicio desde vertice 0\n\n");

    n = 6;
    inicializarMatriz(mat, n);
    inicializarMatriz(arbolGen, n);

    // Mismo grafo que Kruskal para comparar
    mat[0][1] = mat[1][0] = 4;
    mat[0][2] = mat[2][0] = 2;
    mat[1][2] = mat[2][1] = 1;
    mat[1][3] = mat[3][1] = 5;
    mat[2][3] = mat[3][2] = 8;
    mat[2][4] = mat[4][2] = 10;
    mat[3][4] = mat[4][3] = 2;
    mat[3][5] = mat[5][3] = 6;
    mat[4][5] = mat[5][4] = 3;

    imprimirMatriz(mat, n, "Matriz de adyacencia (Grafo original):");

    printf("\nEjecutando Prim desde nodo 0...\n");
    prim(mat, n, 0, arbolGen);

    imprimirMatriz(arbolGen, n, "Matriz del arbol generado:");
    imprimirArbol(arbolGen, n);
    visualizarArbol(arbolGen, n);

    // ==================== PRUEBA 3 ====================
    printf("\n\n=============== PRUEBA 3 ===============\n");
    printf("Grafo pequeno (4 vertices)\n");
    printf("Inicio desde vertice 1\n\n");

    n = 4;
    inicializarMatriz(mat, n);
    inicializarMatriz(arbolGen, n);

    mat[0][1] = mat[1][0] = 1;
    mat[0][2] = mat[2][0] = 4;
    mat[0][3] = mat[3][0] = 3;
    mat[1][3] = mat[3][1] = 2;
    mat[2][3] = mat[3][2] = 5;

    imprimirMatriz(mat, n, "Matriz de adyacencia (Grafo original):");

    printf("\nEjecutando Prim desde nodo 1...\n");
    prim(mat, n, 1, arbolGen);

    imprimirMatriz(arbolGen, n, "Matriz del arbol generado:");
    imprimirArbol(arbolGen, n);
    visualizarArbol(arbolGen, n);

    // ==================== PRUEBA 4 ====================
    printf("\n\n=============== PRUEBA 4 ===============\n");
    printf("Mismo grafo que Prueba 1\n");
    printf("Inicio desde vertice 3 (diferente inicio)\n\n");

    n = 5;
    inicializarMatriz(mat, n);
    inicializarMatriz(arbolGen, n);

    mat[0][1] = mat[1][0] = 2;
    mat[0][2] = mat[2][0] = 3;
    mat[1][3] = mat[3][1] = 5;
    mat[2][3] = mat[3][2] = 7;
    mat[3][4] = mat[4][3] = 9;

    imprimirMatriz(mat, n, "Matriz de adyacencia (Grafo original):");

    printf("\nEjecutando Prim desde nodo 3...\n");
    prim(mat, n, 3, arbolGen);

    imprimirMatriz(arbolGen, n, "Matriz del arbol generado:");
    imprimirArbol(arbolGen, n);
    visualizarArbol(arbolGen, n);

    // ==================== RESULTADOS ESPERADOS ====================
    printf("\n\n========================================\n");
    printf("  RESULTADOS ESPERADOS (CORRECTOS)\n");
    printf("========================================\n");
    printf("Prueba 1 (5 nodos desde 0): Peso = 19\n");
    printf("  Aristas: 0-1(2), 0-2(3), 1-3(5), 3-4(9)\n\n");
    printf("Prueba 2 (6 nodos desde 0): Peso = 13\n");
    printf("  Aristas: 0-2(2), 1-2(1), 1-3(5), 3-4(2), 4-5(3)\n\n");
    printf("Prueba 3 (4 nodos desde 1): Peso = 7\n");
    printf("  Aristas: 0-1(1), 1-3(2), 0-2(4)\n\n");
    printf("Prueba 4 (5 nodos desde 3): Peso = 19\n");
    printf("  Aristas: 1-3(5), 0-1(2), 0-2(3), 3-4(9)\n");
    printf("========================================\n");

    return 0;
}
