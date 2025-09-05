#include <stdio.h>
#define TOP 30
#define N 4
#define N2 3
#define M 3
int suma(int A[],int n);
void muestra(int A[],int n);
void muestraInverso(int A[],int n);
int buscaLineal(int A[],int n,int x);
int buscaBinaria(int A[],int pri,int ult, int x);
int minimo(int mat[][M],int i, int j, int m);
void maximos(int mat[][M],int i,int j,int m, int vmax[]);

int main() {
    int A[] = {1,2,3,4}, n=N, aux, x;
    printf("La suma de los elementos del vector es :%d \n",suma(A,n-1));
    muestra(A,n-1);
    printf("\n");
    muestraInverso(A,n-1);
    printf("\nIngrese X\n"); scanf("%d",&x);

    aux = buscaLineal(A,n-1,x);

    if (aux != -1)
        printf("La posicion del valor buscado es %d\n",aux);
    else
        printf("El valor ingresado no existe en el vector\n");

    printf("Busqueda Binaria\n");

    aux = buscaBinaria(A,0,n-1,x);

    if (aux != -1)
        printf("La posicion del valor buscado es: %d\n",aux);
    else
        printf("La posicion del valor buscado no existe\n");

    int mat[][M] = {{1,2,3},{2,3,4},{5,6,7}};

    printf("El minimo de la matriz es: %d\n",minimo(mat,N2-1,M-1,M-1));

    printf("Maximos de la matriz\n");

    int vmax[N2] = {0};
    maximos(mat,N2-1,M-1,M-1,vmax); //Aqui siempre pasar N-1 o M-1 , ya que si incluyo el N2/N/M luego

    //mostrar el vector con los maximos generados
    int i;
    for(i=0; i < N2; ++i) //para mostrar el vector i=0 y luego i<N2 , ya que incluyo el N2/N
       printf("%d ",vmax[i]);

    return 0;
}
int suma(int A[],int n) {
     if (n<0)
        return 0;
     else
        return A[n] + suma(A,n-1);
}

void muestra(int A[],int n) {
    if (n>-1) {
        muestra(A,n-1);
        printf("%d ",A[n]);
    }
}

void muestraInverso(int A[],int n) {
    if (n>-1) {
        printf("%d ",A[n]);
        muestraInverso(A,n-1);
    }
}

int buscaLineal(int A[],int n,int x){
    if (n<0)
        return -1;
    else {
        if (A[n] == x)
            return n;
        else
            return buscaLineal(A,n-1,x);
    }
}

int buscaBinaria(int A[],int pri,int ult, int x) {
    if (pri > ult)
        return -1;
    else {
        int medio = (pri+ult)/2;
        if (x > A[medio])
            return buscaBinaria(A,medio+1,ult,x);
        else if (x < A[medio])
            return buscaBinaria(A,pri,medio-1,x);

        else
            return medio;
    }
}

int minimo(int mat[][M],int i, int j, int m) {
    int aux;
    if (i<0)
        return 9999;
    else {
        if (j>0)
            aux = minimo(mat,i,j-1,m);
        else
            aux = minimo(mat,i-1,m,m);

        if (mat[i][j] < aux)
            return mat[i][j];
        else
            return aux;
    }
}

void maximos(int mat[][M],int i,int j,int m, int vmax[]){

    if (i>=0){
        if (mat[i][j]>vmax[i])
            vmax[i] = mat[i][j];

        (j>0) ? maximos(mat,i,j-1,m,vmax)
              : maximos(mat,i-1,m,m,vmax);
    }
}


