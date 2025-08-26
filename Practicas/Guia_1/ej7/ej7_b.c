#include <stdio.h>

int main() {

char x;
/* leer x = 3 */

scanf("%d", &x);    //querer mostrar un char de esta forma no esta bien, depende de la suerte que nos muestre una cosa u otra
printf("%d \n",x);

scanf("%c",&x);

scanf("%f", &x);    //querer mostrar un char de esta forma no esta bien, depende de la suerte que nos muestre una cosa u otra
printf("%f \n",x);

scanf("%c",&x);

scanf("%c", &x);    //forma correcta, x es char y muestro con %c
printf("%c \n",x);

/*
scanf("%d", &a); //
printf("%d \n",a); //

scanf("%c",&a); //limpia el enter
*/

return 0;
}
