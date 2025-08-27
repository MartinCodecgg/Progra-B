#include <stdio.h>
#include <stdlib.h>
#define valida(n1,n2)( (n1 == n2+1 || n1 == n2-1) ? 1 : 0 )

int main() {

    int a = 8,b = 6, c = 7;

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
    return 0;
}
