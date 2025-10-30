#include <stdio.h>
#define N 10

void generaV(int mat[][N],int vec[], int i, int j, int n, int gr) {
    if(i >= 0) {
        gr += mat[i][j];
        if(j > 0)
            generaV(mat,vec,i,j-1,n,gr);
        else {
            vec[i] = gr;
            generaV(mat, vec, i-1, n, n,0);
        }
    }
}
//llamada main: generaV(mat, vec, N-1,N-1,N-1,0);

int verticeMax(int mat[][N], int i, int j, int n, int gr, int maxGr, int Vmax) {
    if(j < 0)
        return Vmax;
    else {
        gr += mat[i][j];
        if(i > 0)
            return verticeMax(mat,i-1,j,n,gr,maxGr, Vmax);
        else {
            if(gr > maxGr) {
                maxGr = gr;
                Vmax = j;
            }
            return verticeMax(mat,n,j-1,n, 0, maxGr, Vmax);
        }
    }
}
//llamada main: printf("El vertice con mayor grado es: %d",verticeMax(mat, N-1, N-1, N-1, 0,-1,-1); //el Vmax no importa el valor con que se pasa en realidad


/*
//funcion auxiliar de determinar (inciso c)
int recorreFila(int mat[][N], int j, int indiceV, int x) {
    if(j < indiceV)
        return 0;
    else {
        if(mat[indiceV][j] > x)
            return 1;
        else
            return recorreFila(mat, j-1, indiceV, x);
    }
}

int determinar(int mat[][N], int i, int j, int x) {
    if(j < 0)
        return 1;
    else {
        if(mat[i][j] <= x){  //si no encuentro ninguno que sea mayor entonces sigo buscando
            if(i > 0)
                return determinar(mat, i-1, j, x);
            else
                if(recorreFila(mat, N-1, j, x) != 1)
                    return 0;
                else
                    return determinar(mat, j-2, j-1, x);
        }
        else
            return determinar(mat, j-2, j-1, x);
    }
}
*/

int recorreFila(int mat[][N], int j, int indiceV, int x) {
    if(j <= indiceV) // = para no verificar la diagonal dos veces
        return 0;
    else {
        if(mat[indiceV][j] > x)
            return 1;
        else
            return recorreFila(mat, j-1, indiceV, x);
    }
}

int recorreColumna(int mat[][N], int i, int indiceV, int x) {
    if(i < 0)
        return 0;
    else {
        if(mat[i][indiceV] > x)
            return 1;
        else
            return recorreColumna(mat, i-1, indiceV, x);
    }
}

int determinar(int mat[][N], int vertices, int x) {
    if(vertices < 0)
        return 1;
    else {
        if(recorreColumna(mat, vertices-1, vertices, x) == 1 || recorreFila(mat, N-1, vertices, x) == 1)
            return determinar(mat,vertices-1,x);
        else
            return 0;
    }
}

//LLamada Main:
//int resultado = determinar(mat, N-1, 4);  // Empieza desde vértice N-1
//printf("Resultado: %d\n", resultado);  // 1 = TODOS cumplen

void generaVgrMayorA3(mat[][N], Tvec vec[],int *nvec, int i, int j, int n, int gr) {
    if(i >= 0) {
        gr += mat[i][j];
        if(j > 0)
            generaVgrMayorA3(mat, vec, nvec,i,j-1,n,gr);
        else {
            if(gr > 3) {
                vec[*nvec].vertice = i;
                vec[*nvec].grado = gr;
                (*nvec)++;
            }
            generaVgrMayorA3(mat,vec,nvec,i-1,n,n,0);
        }
    }
}

//llamada inicial: int nvec = 0;
//generaVgrMayorA3(mat, vec, &nvec, N-1, N-1, N-1, 0);
