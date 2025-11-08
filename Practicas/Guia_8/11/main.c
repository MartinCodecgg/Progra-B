#include <stdio.h>
#define N 50
#include "colas.h"
#include "pilas.h"

//funcion auxiliar
int verifVisitados(int visitados[], int n) {
    int i = 0;
    while(i < n && visitados[i] != 0)
        i++;
    //return visitados[i]; //acceso fuera de rango cuando el vector esta todo lleno
    return i == n;
}

//Version optimizada, no conviene llamar a !todosVisitados, conviene usar un n que contenga la dimension de VV

//inciso a) (solo para grafos conexos)
//a la matriz la supongo cuadrada
void muestraProfundidad(int mat[][N],int n, int ini) {
    int j, VV[N], vertice;
    TPila P;

    IniciaP(&P);
    for(j = 0; j < n; j++)
        VV[j] = 0; //en un parcial N no coincide con n asi que no puedo hacer simplemente VV[n] = {0};
    poneP(&P, ini);
    VV[ini] = 1;
    printf("%d",ini);

    while(!verifVisitados(VV, n)) { //mientras no todos visitados
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
//llamada main: muestraProfundidad(mat, n, 3); //o cualquier vertice para iniciar

//inciso b
void recorreAmplitud(int mat[][N], int n, int inicial) {
    int visitados[N] = {0}, j, vertice;
    TCola Cola;
    iniciaC(&Cola);

    poneC(&Cola, inicial);
    visitados[inicial] = 1;

    while(!VaciaC(Cola)) { //preguntar si verificar que no quede vacia la cola o recorrer al arreglo , //mientras no todos visitados
        sacaC(&Cola, &vertice);
        printf("%d\n",vertice); //conviene imprimir aqui porque sino debere imprimir el vertice inicial
        //printf("%d\n",inicial); //siempre imprimo cuando saco de la cola (En el video dice que hay que marcar al imprimir en la cola)
        for(j = 0; j < n; j++)
            if(mat[vertice][j] != 0 && visitados[j] != 1) {
                poneC(&Cola,j); //tanto en el vector como en la cola pongo posiciones/indices y no los valores de los vertices(claves)
                visitados[j] = 1;
            }
    }
}

//inciso c

void cantCompConexas(int mat[][N], int n, int *conexas) {
    int visitados[N] = {0}, j, vertice, todosVisitados;
    TCola Cola;
    iniciaC(&Cola);
    *conexas = 0; //tambien puedo desreferenciar e inicializar aqui

    //visitados[inicial] = 1; No debe ir para este algoritmo, ya que empezare por el primer vertice no visitado que encuentre, hallado en el 2do while(visitados ...

    todosVisitados = verifVisitados(visitados, n);
    while(!todosVisitados) {
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
        todosVisitados = verifVisitados(visitados, n);
    }
}

int main() {
    return 0;
}
