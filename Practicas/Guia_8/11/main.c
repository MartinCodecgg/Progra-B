#include <stdio.h>
#include "colas.h"

/*
void recorreAmplitud(int mat[][N], int n, int inicial) {
    int visitados[N] = {0};
    TCola Cola;
    int j, vertice;

    poneC(&Cola, inicial);
    visitados[inicial] = 1;

    while(!Vacia(Cola)) {
        sacaC(&Cola, &vertice);
        printf("%d\n",inicial); //siempre imprimo cuando saco de la cola
        for(j = 0; j < n; j++) {
            if(mat[vertice][j] != 0 && visitados[j] != 1) {
                poneC(&Cola,j); //tanto en el vector como en la cola pongo posiciones/indices y no los valores de los vertices(claves)
                visitados[j] = 1;
            }
        }
    }
}
*/

//inciso b
void recorreAmplitud(int mat[][N], int n, int inicial) {
    int visitados[N] = {0}, j, vertice;
    TCola Cola;
    iniciaC(&Cola);

    poneC(&Cola, inicial);
    visitados[inicial] = 1;

    while(!VaciaC(Cola)) { //preguntar si verificar que no quede vacia la cola o recorrer al arreglo
        sacaC(&Cola, &vertice);
        printf("%d\n",j); //conviene imprimir aqui porque sino debere imprimir el vertice inicial
        //printf("%d\n",inicial); //siempre imprimo cuando saco de la cola (En el video dice que hay que marcar al poner en la cola)
        for(j = 0; j < n; j++)
            if(mat[vertice][j] != 0 && visitados[j] != 1) {
                poneC(&Cola,j); //tanto en el vector como en la cola pongo posiciones/indices y no los valores de los vertices(claves)
                visitados[j] = 1;
            }
    }
}

//inciso c

int verifVisitados(int visitados[], int n) {
    int i = 0;
    while(i < n && visitados[i] != 0)
        i++;
    //return visitados[i]; //acceso fuera de rango cuando el vector esta todo lleno
    return i == n;
}

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
