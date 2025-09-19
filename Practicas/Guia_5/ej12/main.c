#include <stdio.h>
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\TDA Pila Dinamica\pilas.h"
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\TDA Pila Dinamica\pilas.c"

void calcular(char expresion[]);

int main() {
    char expresion[] = "5 1 3 + *";
    calcular(expresion);
    return 0;
}

void calcular(char expresion[]) {

    TPila P;
    IniciaP(&P);
    int i,n1,n2;
    char cad;

    i = 0;
    while(expresion[i]) {

        if(expresion[i] != '*' && expresion[i]!= '/' && expresion[i]!= '-' && expresion[i]!= '+')
            poneP(&P,expresion[i]);
        else {
            sacaP(&P,&cad);
            n1 = cad - '0';
            sacaP(&P,&cad);
            n2 = cad - '0';

            switch (expresion[i]) {
            case '*': poneP(&P,n1*n2);
            break;
            case '/': poneP(&P,n1/n2);
            break;
            case '+': poneP(&P,n1+n2);
            break;
            case '-': poneP(&P,n1-n2);
            break;
            }
        }
      i++;
    }
    sacaP(&P,&cad);
    printf("%d",cad - '0');
}
