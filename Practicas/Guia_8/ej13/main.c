
// === Kruscal trabaja con Aristas en cambio prim trabaja con vertices === 

#include <stdio.h>
#define N 50

typedef struct {
    int origen, destino, peso;
} Tarista;

void reevaluaV(int CC[], int n, int v1, int v2) {
    int i;
    for(i = 0; i<n; i++)
        if(CC[i] == v2)
            CC[i] = v1;
}

int kruscal(int mat[][N], int n, Tarista arbolGen[]) {
   int nArbolGen = 0, CC[N], i,j, costoMin, Vmin, adyMin;
   for(i = 0; i < n; i++)
        CC[i] = i;
   while(nArbolGen < n-1) { //aqui como guardo aristas es hasta n - 1, corresponde con la cantidad de aristas ideales
        costoMin = 99999;
        for(i = 0; i < n; i++) //recorro filas
                for(j = i+1; j < n; j++) //recorro columnas, (como busco aristas y la matriz es simetrica, me conviene solo buscar en el triangulo superior)
                    if(mat[i][j] != 0 && mat[i][j] < costoMin && CC[i] != CC[j]) {
                        costoMin = mat[i][j];
                        Vmin = i;
                        adyMin = j;
                    }
        reevaluaV(CC,n,CC[Vmin],CC[adyMin]);
        arbolGen[nArbolGen] = (Tarista) {Vmin, adyMin, costoMin};
        nArbolGen++;
   }
//}
// Inciso A TERMINA AQUI
//llamada main: kruscal(mat,n,arbolGen);

   // ====== CODIGO IA ======:
   // Calcular y retornar peso total
   int pesoTotal = 0;
   for(i = 0; i < nArbolGen; i++)
       pesoTotal += arbolGen[i].peso;
   return pesoTotal;
}

void reevaluaV(int CC[], int n, int v1, int v2) {
    int i;
    for(i = 0; i<n; i++)
        if(CC[i] == v2)
            CC[i] = v1;
}

int kruscal2(int mat[][N], int n, int arbolGen[][N]) {
   int CC[N], i,j, costoMin, Vmin, adyMin, aristas = 0;

   for(i = 0; i < n; i++)
        CC[i] = i;

   while(aristas < n - 1) { //aqui como guardo aristas es hasta n - 1, corresponde con la cantidad de aristas ideales
        costoMin = 99999;
        for(i = 0; i < n-1; i++)
                for(j = i+1; j < n; j++)
                    if(mat[i][j] != 0 && mat[i][j] < costoMin && CC[i] != CC[j]) {
                        costoMin = mat[i][j];
                        Vmin = i;
                        adyMin = j;
                    }
        reevaluaV(CC,n,CC[Vmin],CC[adyMin]);
        arbolGen[Vmin][adyMin] = arbolGen[adyMin][Vmin] = costoMin;
        aristas++;
   }
}

// FUNCIONES DE PRUEBA
void inicializarMatriz(int mat[][N], int n) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            mat[i][j] = 0;
}

void imprimirMatriz(int mat[][N], int n) {
    printf("\nMatriz de adyacencia:\n");
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

void imprimirArbol(Tarista arbolGen[], int n) {
    printf("\n========================================\n");
    printf("  ARBOL GENERADO (Kruskal)\n");
    printf("========================================\n");

    int pesoTotal = 0;
    for(int i = 0; i < n - 1; i++) {
        printf("  Arista %d: %d ---- %d (peso: %2d)\n",
               i+1, arbolGen[i].origen, arbolGen[i].destino, arbolGen[i].peso);
        pesoTotal += arbolGen[i].peso;
    }

    printf("========================================\n");
    printf("  PESO TOTAL: %d\n", pesoTotal);
    printf("========================================\n");
}

void visualizarArbol(Tarista arbolGen[], int n) {
    printf("\nConexiones del arbol:\n");
    for(int i = 0; i < n; i++) {
        printf("Nodo %d conectado con: ", i);
        int tiene = 0;
        for(int j = 0; j < n - 1; j++) {
            if(arbolGen[j].origen == i) {
                printf("%d(peso:%d) ", arbolGen[j].destino, arbolGen[j].peso);
                tiene = 1;
            }
            if(arbolGen[j].destino == i) {
                printf("%d(peso:%d) ", arbolGen[j].origen, arbolGen[j].peso);
                tiene = 1;
            }
        }
        if(!tiene) printf("(ninguno)");
        printf("\n");
    }
}

int main() {
    int mat[N][N];
    Tarista arbolGen[N];
    int n;

    printf("========================================\n");
    printf("  PRUEBA DEL ALGORITMO DE KRUSKAL\n");
    printf("========================================\n");

    // ==================== PRUEBA 1 ====================
    printf("\n\n=============== PRUEBA 1 ===============\n");
    printf("Grafo simple (5 vertices)\n");
    printf("     0 ---2--- 1\n");
    printf("     |  \\      |\n");
    printf("     6   3     5\n");
    printf("     |      \\  |\n");
    printf("     3 ---7--- 2\n");
    printf("     |         |\n");
    printf("     9         7\n");
    printf("     |         |\n");
    printf("     4 ---------\n\n");

    n = 5;
    inicializarMatriz(mat, n);

    // Aristas del grafo
    mat[0][1] = mat[1][0] = 2;
    mat[0][2] = mat[2][0] = 3;
    mat[0][3] = mat[3][0] = 6;
    mat[1][2] = mat[2][1] = 5;
    mat[2][4] = mat[4][2] = 7;
    mat[1][4] = mat[4][1] = 5;
    mat[3][4] = mat[4][3] = 9;

    imprimirMatriz(mat, n);

    printf("\nEjecutando Kruskal...\n");
    int peso1 = kruscal(mat, n, arbolGen);

    imprimirArbol(arbolGen, n);
    visualizarArbol(arbolGen, n);

    // ==================== PRUEBA 2 ====================
    printf("\n\n=============== PRUEBA 2 ===============\n");
    printf("Grafo mediano (6 vertices)\n\n");

    n = 6;
    inicializarMatriz(mat, n);

    // Grafo mas complejo
    mat[0][1] = mat[1][0] = 4;
    mat[0][2] = mat[2][0] = 2;
    mat[1][2] = mat[2][1] = 1;
    mat[1][3] = mat[3][1] = 5;
    mat[2][3] = mat[3][2] = 8;
    mat[2][4] = mat[4][2] = 10;
    mat[3][4] = mat[4][3] = 2;
    mat[3][5] = mat[5][3] = 6;
    mat[4][5] = mat[5][4] = 3;

    imprimirMatriz(mat, n);

    printf("\nEjecutando Kruskal...\n");
    int peso2 = kruscal(mat, n, arbolGen);

    imprimirArbol(arbolGen, n);
    visualizarArbol(arbolGen, n);

    // ==================== PRUEBA 3 ====================
    printf("\n\n=============== PRUEBA 3 ===============\n");
    printf("Grafo pequeno (4 vertices) - Caso simple\n\n");

    n = 4;
    inicializarMatriz(mat, n);

    mat[0][1] = mat[1][0] = 1;
    mat[0][2] = mat[2][0] = 4;
    mat[0][3] = mat[3][0] = 3;
    mat[1][3] = mat[3][1] = 2;
    mat[2][3] = mat[3][2] = 5;

    imprimirMatriz(mat, n);

    printf("\nEjecutando Kruskal...\n");
    int peso3 = kruscal(mat, n, arbolGen);

    imprimirArbol(arbolGen, n);
    visualizarArbol(arbolGen, n);

    // ==================== RESUMEN ====================
    printf("\n\n========================================\n");
    printf("         RESUMEN DE PRUEBAS\n");
    printf("========================================\n");
    printf("  Prueba 1 (5 nodos): Peso = %d\n", peso1);
    printf("  Prueba 2 (6 nodos): Peso = %d\n", peso2);
    printf("  Prueba 3 (4 nodos): Peso = %d\n", peso3);
    printf("========================================\n");

    return 0;
}
