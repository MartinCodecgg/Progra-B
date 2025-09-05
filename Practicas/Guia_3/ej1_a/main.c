#include <stdio.h>

int calculaProducto(int n1,int n2);

int main() {

    int n1,n2;
    printf("Ingrese dos numeros\n");
    scanf("%d %d",&n1,&n2);
    printf("El resultado del producto es: %d",calculaProducto(n1,n2));

    return 0;
}

int calculaProducto(int n1,int n2) {
    if (n2 == 1)
        return  n1;
    else {
        return n1 + calculaProducto(n1,n2-1);
    }
}
