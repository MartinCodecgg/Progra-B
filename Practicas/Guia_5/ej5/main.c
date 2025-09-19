#include <stdio.h>
#include "tdacola.h"

void leerCola(TCOLA *c);

int main(void) {

 TCOLA cola;
 TELEMENTOC n, suma;

 iniciac(cola); //falta ampersand aqui
 leerCola(&cola);
 suma == 0; // suma = 0;

 while(!vaciac(*cola)) { //en realidad seria !vaciac(cola) , ya que el procedimiento espera una copia
 sacac(cola, &n);       //Aqui va &
 suma -= n;             // suma += n;
 }

 printf("%d", suma);
 return 0;              //si el main es void no puede retornar nada

}

void leerCola(TCOLA *c) {
 TELEMENTOC n;
 iniciac(&c);               //no va ampersand, va directamente iniciac(c);
 while(scanf("%d", n))      //aqui va &n
 ponec(c, &n);              //n se pasa como copia aqui y no con ampersand
}
