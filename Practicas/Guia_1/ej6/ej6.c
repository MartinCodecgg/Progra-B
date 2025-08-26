#include <stdio.h>

int main(){
 int a,b,c, d = 2;
 a=b=c=3;

 printf("%d \n ", a + b * c / d); // 7
 //primero se evalua el * luego el / por I a D y luego se le suma a

 printf("%d \n ",(a + b) * c % d); //0, el resto de dividir 18 por 2
//1ro se evalua el parentesis luego el * y luego el %

 printf("%d \n ", d < 65 && 3 == d ); //0, devuelve cero porque no existen los booleanos

 printf("%d \n ", a <= b || (3 > a) ); //1 el true en C es 1

 printf("%d \n ",(a >= d) && (2 - 14 == c + 1) );//0

 printf("%d \n ", a>b || a<c && a == c || a >= b); //

 //es equivalente a esto

 printf("%d\n", ((a > b) || ((a < c) && (a == c)) || (a >= b))); //1

 //primero se evaluan las expresiones, luego el && porque tiene mayor precedencia que el || , luego se evaluan los || de
 // izquierda a derecha

 return 0;
}
