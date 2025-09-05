#include <stdio.h>
#define N 3

short valida(int mat[][N],int i,int j,int n);

int main() {

    int mat[][N] = {{1,0,0},{0,1,0},{0,0,1}};

    if(valida(mat,N-1,N-2,N-1) == 1)
        printf("La matriz cumple la condicion");

    else
        printf("La matriz no cumple la condicion");

    return 0;
}

short valida(int mat[][N],int i,int j,int n){

    if(i<1) //mayor que 1 porque por la manera en la cual estoy analizando la matriz, analizo solo hasta la fila con i=1
       return 1; //si i es igual a 0 ya no tengo que analizar
    else {
        if (mat[i][j] == mat[j][i])
            return (j>0) ? valida(mat,i,j-1,n) : valida(mat,i-1,i-2,n);
        else
            return 0;

    }

}
