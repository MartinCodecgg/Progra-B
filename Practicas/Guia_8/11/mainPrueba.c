#include <stdio.h>
#define N 50

// ============================================
// IMPLEMENTACIONES SIMPLIFICADAS DE PILA Y COLA
// ============================================

// PILA
typedef struct {
    int datos[N];
    int tope;
} TPila;

void IniciaP(TPila *p) {
    p->tope = -1;
}

int VaciaP(TPila p) {
    return p.tope == -1;
}

void poneP(TPila *p, int valor) {
    if(p->tope < N-1) {
        p->tope++;
        p->datos[p->tope] = valor;
    }
}

int consultaP(TPila p) {
    if(!VaciaP(p))
        return p.datos[p.tope];
    return -1;
}

void sacaP(TPila *p, int valor) {  // Nota: el parámetro 'valor' no se usa aquí
    if(!VaciaP(*p))
        p->tope--;
}

// COLA
typedef struct {
    int datos[N];
    int frente;
    int final;
    int cantidad;
} TCola;

void iniciaC(TCola *c) {
    c->frente = 0;
    c->final = -1;
    c->cantidad = 0;
}

int VaciaC(TCola c) {
    return c.cantidad == 0;
}

void poneC(TCola *c, int valor) {
    if(c->cantidad < N) {
        c->final = (c->final + 1) % N;
        c->datos[c->final] = valor;
        c->cantidad++;
    }
}

void sacaC(TCola *c, int *valor) {
    if(!VaciaC(*c)) {
        *valor = c->datos[c->frente];
        c->frente = (c->frente + 1) % N;
        c->cantidad--;
    }
}

// ============================================
// TUS FUNCIONES (SIN MODIFICAR)
// ============================================

//funcion auxiliar
int verifVisitados(int visitados[], int n) {
    int i = 0;
    while(i < n && visitados[i] != 0)
        i++;
    //return visitados[i]; //acceso fuera de rango cuando el vector esta todo lleno
    return i == n;
}

//inciso a) (conexos y no conexos)
//a la matriz la supongo cuadrada
/*
void muestraProfundidad(int mat[][N],int n, int ini) {
    int j, VV[N], vertice;
    TPila P;

    IniciaP(&P);
    for(j = 0; j < n; j++)
        VV[j] = 0; //en un parcial N no coincide con n asi que no puedo hacer simplemente VV[n] = {0};
    poneP(&P, ini);
    VV[ini] = 1;
    printf("%d",ini);

    while(!VaciaP(P)) {
        vertice = consultaP(P);
        j = 0;
        while(j < n && (mat[vertice][j] == 0 || VV[j] == 1))
            j++;
        if(j < n) { //preguntar solo por el valor de j, porque si j llega a ser n y accedo a la matriz hago un acceso fuera de indice
            poneP(&P,j);
            printf("%d",j);
            VV[j] = 1;
        }
        else
            sacaP(&P,vertice); //este saca sucede cuando el vertice actual no tiene ningun adyacente entonces debo desapilar y volver a buscar en los anteriores siempre que el vector tengo algun 0
    }
}
*/ 
//optimizada para solo para grafos conexos
void muestraProfundidad(int mat[][N],int n, int ini) {
    int j, VV[N], vertice, cantVis = 0;
    TPila P;

    IniciaP(&P);
    for(j = 0; j < n; j++)
        VV[j] = 0; //en un parcial N no coincide con n asi que no puedo hacer simplemente VV[n] = {0};
    poneP(&P, ini);
    VV[ini] = 1;
    cantVis = 1;
    printf("%d",ini);

    while(cantVis < n) { //Si el grafo es conexo, esta condicion es mejor, ahora si el grafo puede ser no conexo usar directamente VaciaP() unicamente
        vertice = consultaP(P);
        j = 0;
        while(j < n && (mat[vertice][j] == 0 || VV[j] == 1))
            j++;
        if(j < n) { //preguntar solo por el valor de j, porque si j llega a ser n y accedo a la matriz hago un acceso fuera de indice
            poneP(&P,j);
            printf("%d",j);
            VV[j] = 1;
            cantVis++;
        }
        else
            sacaP(&P,vertice); //este saca sucede cuando el vertice actual no tiene ningun adyacente entonces debo desapilar y volver a buscar en los anteriores siempre que el vector tengo algun 0
    }
}

//inciso b (para grafos conexos y no conexos)
void recorreAmplitud(int mat[][N], int n, int inicial) {
    int visitados[N] = {0}, j, vertice;
    TCola Cola;
    iniciaC(&Cola);

    poneC(&Cola, inicial);
    visitados[inicial] = 1;

    while(!VaciaC(Cola)) { //no conviene usar ni !todosvisitados() ni el i < n en este caso
        sacaC(&Cola, &vertice);
        printf("%d\n",vertice); //conviene imprimir aqui porque sino debere imprimir el vertice inicial
        //printf("%d\n",inicial); //siempre imprimo cuando saco de la cola (En el video dice que hay que marcar al poner en la cola)
        for(j = 0; j < n; j++)
            if(mat[vertice][j] != 0 && visitados[j] != 1) {
                poneC(&Cola,j); //tanto en el vector como en la cola pongo posiciones/indices y no los valores de los vertices(claves)
                visitados[j] = 1;
            }
    }
}

/* (no funciona usando !verifVisitados() [PREGUNTAR])
//inciso b (para grafos conexos y no conexos)
void recorreAmplitud(int mat[][N], int n, int inicial) {
    int visitados[N] = {0}, j, vertice;
    TCola Cola;
    iniciaC(&Cola);

    poneC(&Cola, inicial);
    visitados[inicial] = 1;

    while(!verifVisitados(visitados,n)) { //no conviene usar ni !todosvisitados() ni el i < n en este caso
        sacaC(&Cola, &vertice);
        printf("%d\n",vertice); //conviene imprimir aqui porque sino debere imprimir el vertice inicial
        //printf("%d\n",inicial); //siempre imprimo cuando saco de la cola (En el video dice que hay que marcar al poner en la cola)
        for(j = 0; j < n; j++)
            if(mat[vertice][j] != 0 && visitados[j] != 1) {
                poneC(&Cola,j); //tanto en el vector como en la cola pongo posiciones/indices y no los valores de los vertices(claves)
                visitados[j] = 1;
            }
    }
}
*/
/*
//v2 optimizada (SOLO GRAFOS CONEXOS)
void recorreAmplitud(int mat[][N], int n, int inicial) {
    int visitados[N] = {0}, j, vertice, cantVis = 0;
    TCola Cola;
    iniciaC(&Cola);

    poneC(&Cola, inicial);
    visitados[inicial] = 1;
    cantVis++;

    while(cantVis < n) { //si es seguro que el grafo es conexo es mejor usar una variable cantVis y cortar cuando cantVis == N, si puede ser no conexo, usar directamente vaciaC
        sacaC(&Cola, &vertice);
        cantVis++;
        printf("%d\n",vertice); //conviene imprimir aqui porque sino debere imprimir el vertice inicial
        //printf("%d\n",inicial); //siempre imprimo cuando saco de la cola (En el video dice que hay que marcar al poner en la cola)
        for(j = 0; j < n; j++)
            if(mat[vertice][j] != 0 && visitados[j] != 1) {
                poneC(&Cola,j); //tanto en el vector como en la cola pongo posiciones/indices y no los valores de los vertices(claves)
                visitados[j] = 1;
            }
    }
}
*/
//inciso c
void cantCompConexas(int mat[][N], int n, int *conexas) {
    int visitados[N] = {0}, j, vertice;
    TCola Cola;
    iniciaC(&Cola);
    *conexas = 0; //tambien puedo desreferenciar e inicializar aqui

    //visitados[inicial] = 1; No debe ir para este algoritmo, ya que empezare por el primer vertice no visitado que encuentre, hallado en el 2do while(visitados ...

    while(!verifVisitados(visitados, n)) {
        j = 0;
        while(visitados[j])
            j++;
        visitados[j] = 1; //importante para marcar como visitado el primer vertice de cada componente conexa
        poneC(&Cola,j);
        while(!VaciaC(Cola)) {
            sacaC(&Cola, &vertice);
            for(j = 0; j < n; j++)
                if(mat[vertice][j] != 0 && visitados[j] != 1) {
                    poneC(&Cola,j);
                    visitados[j] = 1;
                }
        }
        (*conexas)++; //aumento las conexas una vez se vacia la cola
    }
}

// ============================================
// PROGRAMA DE PRUEBA
// ============================================

void imprimirMatriz(int mat[][N], int n) {
    printf("\nMatriz de adyacencia:\n");
    printf("   ");
    for(int i = 0; i < n; i++)
        printf("%2d ", i);
    printf("\n");

    for(int i = 0; i < n; i++) {
        printf("%2d: ", i);
        for(int j = 0; j < n; j++) {
            printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int mat[N][N] = {0};
    int n, conexas;

    // ===== GRAFO CONEXO DE PRUEBA (6 vértices) =====
    printf("========================================\n");
    printf("PRUEBA 1: GRAFO CONEXO\n");
    printf("========================================\n");
    n = 6;

    // Grafo conexo: 0-1-2-3, 1-4, 3-5
    mat[0][1] = mat[1][0] = 1;
    mat[1][2] = mat[2][1] = 1;
    mat[2][3] = mat[3][2] = 1;
    mat[1][4] = mat[4][1] = 1;
    mat[3][5] = mat[5][3] = 1;

    imprimirMatriz(mat, n);

    printf("\nRecorrido en PROFUNDIDAD desde vértice 0:\n");
    muestraProfundidad(mat, n, 0);

    printf("\n\nRecorrido en AMPLITUD desde vértice 0:\n");
    recorreAmplitud(mat, n, 0);

    conexas = 0;
    cantCompConexas(mat, n, &conexas);
    printf("\nCantidad de componentes conexas: %d\n", conexas);

    // Limpiar matriz
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            mat[i][j] = 0;

    // ===== GRAFO CON 3 COMPONENTES CONEXAS =====
    printf("\n\n========================================\n");
    printf("PRUEBA 2: GRAFO CON 3 COMPONENTES CONEXAS\n");
    printf("========================================\n");
    n = 8;

    // Componente 1: 0-1-2
    mat[0][1] = mat[1][0] = 1;
    mat[1][2] = mat[2][1] = 1;

    // Componente 2: 3-4
    mat[3][4] = mat[4][3] = 1;

    // Componente 3: 5-6-7
    mat[5][6] = mat[6][5] = 1;
    mat[6][7] = mat[7][6] = 1;

    imprimirMatriz(mat, n);

    printf("\nRecorrido en PROFUNDIDAD desde vértice 0:\n");
    muestraProfundidad(mat, n, 0);

    printf("\n\nRecorrido en AMPLITUD desde vértice 3:\n");
    recorreAmplitud(mat, n, 3);

    conexas = 0;
    cantCompConexas(mat, n, &conexas);
    printf("\nCantidad de componentes conexas: %d\n", conexas);

    // Limpiar matriz
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            mat[i][j] = 0;

    // ===== GRAFO CÍCLICO =====
    printf("\n\n========================================\n");
    printf("PRUEBA 3: GRAFO CÍCLICO\n");
    printf("========================================\n");
    n = 5;

    // Ciclo: 0-1-2-3-4-0
    mat[0][1] = mat[1][0] = 1;
    mat[1][2] = mat[2][1] = 1;
    mat[2][3] = mat[3][2] = 1;
    mat[3][4] = mat[4][3] = 1;
    mat[4][0] = mat[0][4] = 1;

    imprimirMatriz(mat, n);

    printf("\nRecorrido en PROFUNDIDAD desde vértice 0:\n");
    muestraProfundidad(mat, n, 0);

    printf("\n\nRecorrido en AMPLITUD desde vértice 2:\n");
    recorreAmplitud(mat, n, 2);

    conexas = 0;
    cantCompConexas(mat, n, &conexas);
    printf("\nCantidad de componentes conexas: %d\n", conexas);

    return 0;
}

/*
========================================
PRUEBA 1: GRAFO CONEXO
========================================

Matriz de adyacencia:
    0  1  2  3  4  5
 0:  0  1  0  0  0  0
 1:  1  0  1  0  1  0
 2:  0  1  0  1  0  0
 3:  0  0  1  0  0  1
 4:  0  1  0  0  0  0
 5:  0  0  0  1  0  0

Recorrido en PROFUNDIDAD desde vértice 0:
012354

Recorrido en AMPLITUD desde vértice 0:
0
1
2
4
3
5

Cantidad de componentes conexas: 1

========================================
PRUEBA 2: GRAFO CON 3 COMPONENTES CONEXAS
========================================

Matriz de adyacencia:
    0  1  2  3  4  5  6  7
 0:  0  1  0  0  0  0  0  0
 1:  1  0  1  0  0  0  0  0
 2:  0  1  0  0  0  0  0  0
 3:  0  0  0  0  1  0  0  0
 4:  0  0  0  1  0  0  0  0
 5:  0  0  0  0  0  0  1  0
 6:  0  0  0  0  0  1  0  1
 7:  0  0  0  0  0  0  1  0

Recorrido en PROFUNDIDAD desde vértice 0:
012

Recorrido en AMPLITUD desde vértice 3:
3
4

Cantidad de componentes conexas: 3

========================================
PRUEBA 3: GRAFO CÍCLICO
========================================

Matriz de adyacencia:
    0  1  2  3  4
 0:  0  1  0  0  1
 1:  1  0  1  0  0
 2:  0  1  0  1  0
 3:  0  0  1  0  1
 4:  1  0  0  1  0

Recorrido en PROFUNDIDAD desde vértice 0:
01234

Recorrido en AMPLITUD desde vértice 2:
2
1
3
0
4

Cantidad de componentes conexas: 1
*/
