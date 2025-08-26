#include <stdio.h>

int main() {
int a;
/* leer a = 3 */

scanf("%d", &a); //en el scanf debemos usar el & para acceder a la ubicacion de memoria
printf("%d \n",a); //esta todo correcto aqui y imprime 3

scanf("%c",&a); //limpia el enter

scanf("%f", &a);
printf("%f \n",a); //nos muestra la direccion de memoria

scanf("%c",&a); //limpia el enter

scanf("%c", &a); //imprime el caracter 3
printf("%c \n",a); //si usase d imprimiria el codigo ascii de 3 creo

}

//Para no tener problemas con el enter podemos ir comentando y no usar multiples scanF o tambien podemos usar scanF intermedios
//como los que dicen "limpia el enter", para asi limpiar el enter
