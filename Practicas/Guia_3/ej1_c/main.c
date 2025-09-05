#include <stdio.h>
#define TOP 4

void maxVoid(int A[],int n,int*max);
int maxInt(int A[],int n);
int maxInt2(int A[],int n);

int main() {

    int A[] = {1,2,3,4}, n=4, max=-99999; //recordar siempre al hacer recursvidad en C y trabajar con arreglos, debo invocar con n-1
    maxVoid(A,n-1,&max);
    printf("El maximo del vector es: %d\n",max);
    printf("El maximo del vector es: %d\n",maxInt(A,n-1));
    printf("El maximo del vector es: %d\n",maxInt2(A,n-1));

    return 0;
}

void maxVoid(int A[],int n,int* max) {
    if (n >= 0)
        if (A[n]>*max) {
            *max = A[n];
            maxVoid(A,n-1,max);
    }
}

int maxInt(int A[],int n) {
    int aux;
    if (n<0)
        return -9999;
    else {
        aux = maxInt(A,n-1);
        return (aux > A[n]) ?  aux : A[n];
    }
}

int maxInt2(int A[],int n) {
    return (n<0) ? -99999
                 : (maxInt(A,n-1) > A[n]) ? maxInt(A,n-1)
                                          : A[n];
}
