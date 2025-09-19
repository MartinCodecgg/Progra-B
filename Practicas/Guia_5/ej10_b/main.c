#include <stdio.h>
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\TDA Pila Dinamica\pilas.h"
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\TDA Pila Dinamica\pilas.c"

void cargaYvalidaP(TPila *P);

int main() {

    TPila P;
    IniciaP(&P);

    cargaYvalidaP(&P);

    return 0;
}

void cargaYvalidaP(TPila *P) {

    FILE* arch = fopen("expresion.txt","rt");
    int OK = 1;

    if(arch == NULL)
        printf("Error al abrir el archivo");
    else {
        printf("Archivo abierto correctamente\n");
        TElementoP elem,aux;

        fscanf(arch," %c",&elem); //los espacios no dan problemas cuando leo caracteres (no cadena de caracteres)

        while(elem != '.' && OK) {
            //printf("%c\n",elem); PARA COMPROBAR QUE LEA BIEN LOS DATOS
            if(elem == '(' || elem == ')' || elem == '[' || elem == ']' || elem == '{' || elem == '}') {
                if(elem == '(' || elem == '[' || elem == '{')
                   poneP(P,elem);
                else {
                    sacaP(P,&aux);
                    if(!((aux == '(' && elem == ')') || //recordar que los && tienen mas presedencia que || por ello debo usar parentesis aqui
                       (aux == '[' && elem == ']') ||
                       (aux == '{' && elem == '}') ) )
                            OK = 0;
                }
            }
            fscanf(arch,"%c",&elem);
        }
        if(OK && VaciaP(*P)) //la condicion de estar balanceado es que la cola este vacia y que este OK en 1
            printf("Esta balanceado\n");
        else
            printf("NO esta balanceado\n");
    }
}
