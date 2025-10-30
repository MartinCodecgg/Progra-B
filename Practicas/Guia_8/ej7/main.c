#include <stdio.h>
#include <stdlib.h>
#define N 7

// Estructura para lista de adyacencia
typedef struct nodo {
    int destino;
    struct nodo *sig;
} TNodo;

typedef TNodo *TLista;

int gradoMat(int mat[][N], int V) {
    unsigned int gr = 0, j;

    for(j = 0; j < N; j++) {
        gr += mat[V][j];
    }
    return gr;
}

int gradoListaAdyacencia(TLista vec[], int V) {
    int gr = 0;
    TLista act = vec[V];
    while(act != NULL) {
        gr++;
        act = act->sig;
    }
    return gr;
}

unsigned int gradoMediaMatriz(int mat[][N], int V) {
    unsigned int gr = 0, i,j;

    for(i = 0; i < V; i++)
        gr += mat[i][V];
    for(j = V; j < N; j++)
        gr += mat[V][j];

    return gr;
}

// Función auxiliar para agregar arista en lista de adyacencia
void agregarArista(TLista vec[], int origen, int destino) {
    // Agregar destino a la lista de origen
    TNodo *nuevo = (TNodo*)malloc(sizeof(TNodo));
    nuevo->destino = destino;
    nuevo->sig = vec[origen];
    vec[origen] = nuevo;

    // Como es grafo no dirigido, agregar también en sentido inverso
    nuevo = (TNodo*)malloc(sizeof(TNodo));
    nuevo->destino = origen;
    nuevo->sig = vec[destino];
    vec[destino] = nuevo;
}

// Función para imprimir matriz
void imprimirMatriz(int mat[][N], const char *titulo) {
    printf("\n%s:\n", titulo);
    printf("    ");
    for(int i = 0; i < N; i++) printf("%d ", i);
    printf("\n");
    for(int i = 0; i < N; i++) {
        printf("%d: ", i);
        for(int j = 0; j < N; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // ========== GRAFO DE EJEMPLO ==========
    // Usaremos el grafo del ejercicio anterior simplificado:
    // A=0, B=1, C=2, D=3, E=4, F=5, G=6
    // Aristas (sin dirección):
    // 0-3, 0-5, 1-2, 1-3, 2-5, 3-4, 3-5, 3-6, 4-3(ya está), 5-6

    // ===== 1. MATRIZ DE ADYACENCIA COMPLETA =====
    int matriz[N][N] = {0};

    // Agregar aristas (grafo no dirigido, matriz simétrica)
    matriz[0][3] = matriz[3][0] = 1;  // A-D
    matriz[0][5] = matriz[5][0] = 1;  // A-F
    matriz[1][2] = matriz[2][1] = 1;  // B-C
    matriz[1][3] = matriz[3][1] = 1;  // B-D
    matriz[2][5] = matriz[5][2] = 1;  // C-F
    matriz[3][4] = matriz[4][3] = 1;  // D-E
    matriz[3][5] = matriz[5][3] = 1;  // D-F
    matriz[3][6] = matriz[6][3] = 1;  // D-G
    matriz[5][6] = matriz[6][5] = 1;  // F-G

    imprimirMatriz(matriz, "MATRIZ DE ADYACENCIA COMPLETA");

    printf("\n=== GRADOS CON MATRIZ COMPLETA ===\n");
    for(int v = 0; v < N; v++) {
        printf("Grado del vértice %d: %d\n", v, gradoMat(matriz, v));
    }

    // ===== 2. LISTA DE ADYACENCIA =====
    TLista listaAdyacencia[N];
    for(int i = 0; i < N; i++) {
        listaAdyacencia[i] = NULL;
    }

    // Agregar las mismas aristas
    agregarArista(listaAdyacencia, 0, 3);  // A-D
    agregarArista(listaAdyacencia, 0, 5);  // A-F
    agregarArista(listaAdyacencia, 1, 2);  // B-C
    agregarArista(listaAdyacencia, 1, 3);  // B-D
    agregarArista(listaAdyacencia, 2, 5);  // C-F
    agregarArista(listaAdyacencia, 3, 4);  // D-E
    agregarArista(listaAdyacencia, 3, 5);  // D-F
    agregarArista(listaAdyacencia, 3, 6);  // D-G
    agregarArista(listaAdyacencia, 5, 6);  // F-G

    printf("\n=== GRADOS CON LISTA DE ADYACENCIA ===\n");
    for(int v = 0; v < N; v++) {
        printf("Grado del vértice %d: %d\n", v, gradoListaAdyacencia(listaAdyacencia, v));
    }

    // ===== 3. MEDIA MATRIZ (triángulo superior) =====
    int mediaMatriz[N][N] = {0};

    // Solo llenamos el triángulo superior (j > i)
    mediaMatriz[0][3] = 1;  // A-D
    mediaMatriz[0][5] = 1;  // A-F
    mediaMatriz[1][2] = 1;  // B-C
    mediaMatriz[1][3] = 1;  // B-D
    mediaMatriz[2][5] = 1;  // C-F
    mediaMatriz[3][4] = 1;  // D-E
    mediaMatriz[3][5] = 1;  // D-F
    mediaMatriz[3][6] = 1;  // D-G
    mediaMatriz[5][6] = 1;  // F-G

    imprimirMatriz(mediaMatriz, "MEDIA MATRIZ (Triángulo Superior)");

    printf("\n=== GRADOS CON MEDIA MATRIZ ===\n");
    for(int v = 0; v < N; v++) {
        printf("Grado del vértice %d: %d\n", v, gradoMediaMatriz(mediaMatriz, v));
    }

    // Verificación: todos los métodos deben dar los mismos resultados
    printf("\n=== VERIFICACIÓN ===\n");
    int todoBien = 1;
    for(int v = 0; v < N; v++) {
        int g1 = gradoMat(matriz, v);
        int g2 = gradoListaAdyacencia(listaAdyacencia, v);
        int g3 = gradoMediaMatriz(mediaMatriz, v);

        if(g1 != g2 || g2 != g3) {
            printf("❌ ERROR en vértice %d: Mat=%d, Lista=%d, MediaMat=%d\n", v, g1, g2, g3);
            todoBien = 0;
        }
    }

    if(todoBien) {
        printf("✅ ¡Todas las funciones dan los mismos resultados!\n");
    }

    // Liberar memoria de la lista de adyacencia
    for(int i = 0; i < N; i++) {
        TLista actual = listaAdyacencia[i];
        while(actual != NULL) {
            TLista temp = actual;
            actual = actual->sig;
            free(temp);
        }
    }

    return 0;
}
/*
```

## Salida esperada:
```
MATRIZ DE ADYACENCIA COMPLETA:
    0 1 2 3 4 5 6
0: 0 0 0 1 0 1 0
1: 0 0 1 1 0 0 0
2: 0 1 0 0 0 1 0
3: 1 1 0 0 1 1 1
4: 0 0 0 1 0 0 0
5: 1 0 1 1 0 0 1
6: 0 0 0 1 0 1 0

=== GRADOS CON MATRIZ COMPLETA ===
Grado del vértice 0: 2
Grado del vértice 1: 2
Grado del vértice 2: 2
Grado del vértice 3: 5
Grado del vértice 4: 1
Grado del vértice 5: 4
Grado del vértice 6: 2

...

✅ ¡Todas las funciones dan los mismos resultados!
*/
