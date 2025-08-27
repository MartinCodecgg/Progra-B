#include <stdio.h>
#include <stdlib.h>

int valida(int n1,int n2);

int main() {

    int a = 6,b = 8, c = 7;

    if (valida(a,b) == 1) {

        if (valida(a,c) == 1)
            printf("Consecutivos");

        else if (valida(b,c) == 1)
            printf("Consecutivos");

        else
            printf("No son Consecutivos");
    }
    else if (valida(b,c) == 1) {

        if (valida(a,c) == 1)
            printf("Consecutivos");
        else
            printf("No son Consecutivos");
    }
    else
        printf("No son Consecutivos");
    return 0;
}

int valida(int n1,int n2) {
    return ( (n1 == n2+1 || n1 == n2-1) ? 1 : 0 );
}
