#include <stdio.h>
#define N 4
#define M 4

int valida(int mat[][M],int i, int j, int m,int sum,int sumAnt);

int main() {

    int mat[][M] = {{9,8,7,6},{5,4,3,2},{1,1,1,1},{0,0,0,0}};

    if(valida(mat,N-1,M-1,M-1,0,-1))
        printf("La matriz cumple la condicion");
    else
        printf("La matriz no cumple la condicion");

    return 0;
}

int valida(int mat[][M],int i, int j, int m,int sum,int sumAnt) {
    if(i<0){
        if (sum % 2 == 0)
            return 1;
        else
            return 0;
    }
    else {
        sum += mat[i][j];
        if(j>0)
            return valida(mat,i,j-1,m,sum,sumAnt);
        else
            return (sum > sumAnt) ? valida(mat,i-1,m,m,0,sum)
                                : 0;
    }
}
