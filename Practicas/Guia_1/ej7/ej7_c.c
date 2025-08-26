#include <stdio.h>

int main() {

char w;
/* leer w = 2.5 */

//parece ser que cuando leemos reales tenemos aun mas problemas con el scanF
//Entonces la unica forma de hacer este ejercicio es simplemente estar comentanto todo el codigo, no dejando scanf consecutivos activos
/*
scanf("%d", &w);
printf("%d\n",w); //Lo trunca y devuelve 2, devuelve un int

scanf("%c",&w);

scanf("%f", &w);
printf("%f\n",w); //devuelve 0.0000 es decir un ocurre un error

scanf("%c",&w);
*/
scanf("%c", &w);    //tambien lo trunca y devuelve un char
printf("%c\n",w);

//scanf("%c",&x);

return 0;
}
