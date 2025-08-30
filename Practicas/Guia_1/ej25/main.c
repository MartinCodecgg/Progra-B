#include <stdio.h>
#include <string.h>
#define TOP 100
#define TOPNOMBRE 20

void leer(char nombres[][TOPNOMBRE], unsigned short edades[], unsigned short *n);

void listado(char nombres[][TOPNOMBRE], unsigned short edades[], unsigned short n);

int main() {

    char nombres[TOP][TOPNOMBRE]; //Los array de string se definen tal cual como una matriz y funcionan como una,
    unsigned short edades[TOP], n;  //mas bien es un arreglo bidireccional

    n = 0;

    leer(nombres, edades, &n);

    listado(nombres, edades, n);

    return 0;
}

void leer(char nombres[][TOPNOMBRE], unsigned short edades[], unsigned short *n) {

    char nom[TOPNOMBRE];
    unsigned short edad;

    printf("A continuacion ingrese el edad y nombre de las personas que desea incluir, ingrese edad como 0 para finalizar la carga \n");

    do {
        scanf(" %hu",&edad);

        if (edad) {

            //gets(nom[n]); //no se recomienda usar gets en C, da problemas internos, lo mas recomendable fgets o el scanf de abajo

            scanf(" %[^\n]", nombres[*n]);   // lee string con espacios
            //printf("%s",nombres[n]);

            strcpy(nombres[*n], nom);

            edades[*n] = edad;

            *n += 1;
        }

        } while (edad);

}

void listado(char nombres[][TOPNOMBRE], unsigned short edades[], unsigned short n) {

    unsigned short x,i,cont = 0; //recordar para contadores y acumuladores siempre inicializar al comienzo
    printf("Ingrese X \n");
    scanf(" %hu",&x);

    printf("Listado de personas con mas de %hu años \n",x);

    for (i = 0; i<n; ++i)
        if (edades[i] > x) {
            printf("%s \n", nombres[i]);
            ++cont;
        }

    if (cont)
        printf("El porcentaje de personas de mayores de edad sobre el total es: %3.2f %%", (float) cont/n *100);
    else
        printf("No hay personas mayores de edad");

    //Recordar en C si queremos realmente escribir el signo de porcentaje debemos escribir %%
}
