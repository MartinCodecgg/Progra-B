#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef struct nodo {
    int vertice;
    struct nodo *sig;
} nodo;
typedef struct nodo * TLista;

int gradoE(TLista vec[], int V) {
    unsigned int i, gr = 0;
    TLista act;

    for(i = 0; i < N; i++) {
        act = vec[i];
        while(act != NULL) {
            if(act->vertice == V)
                gr++;
            act = act->sig;
        }
    }
    return gr;
}

int gradoS(TLista vec[], int V) {
    unsigned int gr = 0;

    TLista act = vec[V];
    while(act != NULL) {
        gr++;
        act = act->sig;
    }
    return gr;
}

int gradoTot(TLista vec[], int V) {
    TLista act = vec[V];

    while(act != NULL && act->vertice != V)
        act = act->sig;
    if(act != NULL && act->vertice == V)
        return gradoE(vec, V) + gradoS(vec, V) -1;
    else
        return gradoE(vec, V) + gradoS(vec, V);
}

// Función auxiliar para agregar una arista
void agregarArista(TLista vec[], int origen, int destino) {
    TLista nuevo = (TLista)malloc(sizeof(nodo));
    nuevo->vertice = destino;
    nuevo->sig = vec[origen];
    vec[origen] = nuevo;
}

// Función para imprimir el grafo
void imprimirGrafo(TLista vec[]) {
    printf("\nLista de adyacencia:\n");
    for(int i = 0; i < N; i++) {
        if(vec[i] != NULL) {
            printf("Vertice %d -> ", i);
            TLista act = vec[i];
            while(act != NULL) {
                printf("%d ", act->vertice);
                act = act->sig;
            }
            printf("\n");
        }
    }
}

int main() {
    TLista grafo[N];

    // Inicializar todas las listas en NULL
    for(int i = 0; i < N; i++)
        grafo[i] = NULL;

    // Crear un digrafo de ejemplo:
    // 0 -> 1, 2
    // 1 -> 2, 3
    // 2 -> 0, 1
    // 3 -> 1
    // 4 -> 4 (lazo)

    agregarArista(grafo, 0, 1);
    agregarArista(grafo, 0, 2);
    agregarArista(grafo, 1, 2);
    agregarArista(grafo, 1, 3);
    agregarArista(grafo, 2, 0);
    agregarArista(grafo, 2, 1);
    agregarArista(grafo, 3, 1);
    agregarArista(grafo, 4, 4);  // Lazo en vértice 4

    // Imprimir el grafo
    imprimirGrafo(grafo);

    // Probar las funciones con diferentes vértices
    printf("\n=== ANALISIS DE GRADOS ===\n");

    for(int v = 0; v <= 4; v++) {
        printf("\nVertice %d:\n", v);
        printf("  Grado de entrada: %d\n", gradoE(grafo, v));
        printf("  Grado de salida:  %d\n", gradoS(grafo, v));
        printf("  Grado total:      %d\n", gradoTot(grafo, v));
    }

    // Caso especial: vértice con lazo
    printf("\n=== NOTA ===\n");
    printf("El vertice 4 tiene un lazo (4->4)\n");
    printf("Por eso su grado total es (1+1-1) = 1\n");

    // Liberar memoria (opcional pero buena práctica)
    for(int i = 0; i < N; i++) {
        TLista act = grafo[i];
        while(act != NULL) {
            TLista temp = act;
            act = act->sig;
            free(temp);
        }
    }

    return 0;
}

/*


## Salida esperada:

Lista de adyacencia:
Vertice 0 -> 2 1
Vertice 1 -> 3 2
Vertice 2 -> 1 0
Vertice 3 -> 1
Vertice 4 -> 4

=== ANALISIS DE GRADOS ===

Vertice 0:
  Grado de entrada: 1
  Grado de salida:  2
  Grado total:      3

Vertice 1:
  Grado de entrada: 3
  Grado de salida:  2
  Grado total:      5

Vertice 2:
  Grado de entrada: 2
  Grado de salida:  2
  Grado total:      4

Vertice 3:
  Grado de entrada: 1
  Grado de salida:  1
  Grado total:      2

Vertice 4:
  Grado de entrada: 1
  Grado de salida:  1
  Grado total:      1

=== NOTA ===
El vertice 4 tiene un lazo (4->4)
Por eso su grado total es (1+1-1) = 1

*/
