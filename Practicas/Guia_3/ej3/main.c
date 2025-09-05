#include <stdio.h>
#define N 4

float promedio(int A[],int n);

int main() {
    int A[] = {1,2,3,4};
    printf("El promedio de los elementos del vector es: %3.2f",promedio(A,N-1)/N);

    return 0;
}

float promedio(int A[],int n) {
    if (n == 0)
        return A[0];
    else
        return A[n] + promedio(A,n-1);
}
