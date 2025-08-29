#include <stdio.h> //verif R C

int main() {

    long long unsigned int num; //para int se usa d, pero para long long unsigned se tendria que usar llu
    unsigned int n = 0, i, binario[128];

    printf("Ingrese el numero \n");
    scanf("%llu",&num);

    while (num > 0) {

        binario[n] = num % 2;
        num /= 2;
        n++;    //recordar que debo aumentar el n despues xq sino ignora la 1era componente del array
    }

    for(i=0; i<n ;++i) //Los numeros binarios se deben mostrar del ultimo al primero si los calculo del 1ero al ultimo
        printf("%d",binario[i]);

    return 0;
}
