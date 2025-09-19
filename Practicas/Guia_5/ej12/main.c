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
    int i,n1,n2,OK = 1;

    i = 0;
    while(expresion[i]) {

        if(expresion[i] != '*' && expresion[i]!= '/' && expresion[i]!= '-' && expresion[i]!= '+' && expresion[i] != ' ')
            poneP(&P,expresion[i] - '0');
        else {
            if (expresion[i] != ' ') {

                if (!VaciaP(P)) {
                    sacaP(&P,&n1);
                     if (!VaciaP(P))
                        sacaP(&P,&n2);
                     else
                        OK = 0; //IMPRIMIR UNA SOLA VEZ AL FINAL ANTE UN ERROR
                }
                else
                    OK = 0;

                if(OK) {
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
            }
        }
      i++;
    }
    if(!VaciaP(P) && OK) {
        sacaP(&P,&n1);
        if(VaciaP(P)) //Este si que nose si es necesario realmente, pero validar mejor es aconsejable ponerlo, por las dudas
            printf("El resultado de la operacion es: %d",n1);
        else
            printf("Error: La expresion no es valida");
    }
    else
        printf("Error: La expresion no es valida");
}
