#include <stdio.h>
#include <conio.h>

int main() {
 int c = 3, l;
 c = (c * 2 - (l = 4, -- l));
 printf(" valor de c %d\t valor de l %d\n", c, l); //valor de c 3   valor de l 3
 getch(); //para usar geth() hay que incluir la libreria conio.h pues en compiladores modernos esta funcion no esta incluida
 return 0;
}

/* Aqui se esta usando el operador coma, el operador coma es como una expresion conjunta, evalua las expresiones de izquierda a derecha y
el valor final es el de la ultima expresion, primero se evalua l=4 y luego se evalua --l ,
 por lo que l termina siendo 3 y c 3 tambien
*/
