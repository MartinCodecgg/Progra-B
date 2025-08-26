#include <stdio.h>

int main(){
 int c=3, d=2;
 c -= d++ * 3;
 printf(" valor de c %d\tvalor de d %d\n", c, d); //valor de c -3  valor de d 3
 return 0;
}

/*

Tener en cuenta que

d++ (post-incremento): usa el valor actual de d, luego incrementa.

++d (pre-incremento): primero incrementa, luego usa el valor.

Entonces primero el valor de d que se usa para evaluar la expresion es 2, pero luego si d termina siendo 3
/*

