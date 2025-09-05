#include <stdio.h>

void cuenta(int n1,int n2,int *cociente,int *resto);

int main() {

    int n1,n2,resto,cociente = 0;
    printf("Ingrese n1 y n2\n");
    scanf("%d %d",&n1,&n2);
    cuenta(n1,n2,&cociente,&resto);
    printf("El cociente y resto de la division entre los dos dos numeros es: %d %d\n",cociente, resto);

    return 0;
}

void cuenta(int n1,int n2,int *cociente,int *resto) {

    if (n2 < n1)
        *resto = n2;
    else {
        n2-=n1;
        *cociente +=1;
        cuenta(n1,n2,cociente,resto);
    }
}
