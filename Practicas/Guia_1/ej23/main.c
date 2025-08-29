#include <stdio.h>
#include <string.h>

/*
23. Corregir el siguiente código para que asigne el contenido de la cadena cad1 a cad3, solamente
si cad1 y cad2 son distintas.
char cad1[20], cad2[20], cad3[20];
gets(cad1); gets(cad2);
if(cad1 != cad2)
 cad3 = cad1;
*/


int main() {

    char cad1[20], cad2[20], cad3[20];

    gets(cad1);

    gets(cad2);

    if (strcmp(cad1,cad2) != 0) {
        strcpy(cad3,cad1);
        printf("%s",cad3);
    }

    else
        printf("cad1 es igual a cad2");



    return 0;
}
