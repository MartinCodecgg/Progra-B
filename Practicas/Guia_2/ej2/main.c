#include <stdio.h>

void ordenadas(int *x, int *y);

int main() {
 int a = 30, b = 20;
 ordenadas(&a, &b);
 printf(" valor de a %d\t valor de b %d \n", a, b);
 return 0;
}

void ordenadas(int *x, int *y){
 int aux;//recordar que enteros y punteros no son compatibles, para hacer aux = x, debo definir a aux como puntero
            //(en realidad no es lo que hay que hacer en este caso pero)

 if (x > y) { //Como defini a x y a y como punteros, luego debo trabajar con estos punteros siempre con *
                //para trabajar con los valores de las variables, ya que sino trabajare con las direcciones de memoria
                // y nunca debo trabajar con las direcciones de memoria
 aux = *x;
 *x = *y;
 *y = aux;
 }
}
