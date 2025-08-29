#include <stdio.h>

/* 18. Desarrollar un subprograma que duplique los elementos de un vector ubicados en las
posiciones pares. Implementar 3 veces utilizando for, while y do while */

int main() {

    int i, v[] = {1,2,3,4}, n = 4;

    for(i = 0;i < n; ++i) {
        if (i % 2 == 0)
            v[i] = v[i] * 2;
    }

    for(i = 0;i < n; ++i)
        printf("%d \t",v[i]);


    return 0;
}
//Las cadenas de caracteres son las unicas que deben llevar la componente nula
