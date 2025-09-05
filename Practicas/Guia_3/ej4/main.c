#include <stdio.h>
#define TOP 50
#define M 3
#define N 3

void cuentaVoid(float A[][TOP],float x,int* cont,int i,int j,int m);
int cuentaFunc(float A[][TOP],float x,int i,int j,int m);


int main() {

    float A[][TOP] = {{1,2,3},{2,3,4},{3,4,5}};
    float x;
    int cont = 0;

    printf("Ingrese X\n");
    scanf("%f",&x);
    cuentaVoid(A,x,&cont,N-1,M-1,M-1);
    printf("La cantidad de componentes que coinciden con ese valor en la matriz es: %d\n",cont);
    printf("La cantidad de componentes que coinciden con ese valor en la matriz es: %d\n",cuentaFunc(A,x,N-1,M-1,M-1));

    return 0;
}

void cuentaVoid(float A[][TOP],float x,int* cont,int i,int j,int m) {

    if(i > -1) {
        if(A[i][j] == x)
            *cont +=1;

        (j>0) ? cuentaVoid(A,x,cont,i,j-1,m)
              : cuentaVoid(A,x,cont,i-1,m,m);
    }

}

int cuentaFunc(float A[][TOP],float x,int i,int j,int m) {
    if(i<0)
        return 0;
    else {

    if (j>0)
        return (A[i][j] == x) + cuentaFunc(A,x,i,j-1,m);
    else
        return (A[i][j] == x) + cuentaFunc(A,x,i-1,m,m);
    }
}
