#include <stdio.h>
#include <ctype.h>
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\TDA_PILA_DINAMICA_DECADENADECARACTERES\pilas.h"
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\TDA_PILA_DINAMICA_DECADENADECARACTERES\pilas.c"

#define TOTAL_LETRAS 27 //26 letras mas el espacio en blanco
#define TOP_NOMBRE 50 //debe concidir con el tamaño del tipo para evitar problemas

void cargaP(TPila pilas[]);
void consultaLetra(TPila pilas[]);
void IniciaPilas(TPila pilas[]);

int main() {

    TPila pilas[TOTAL_LETRAS];
    IniciaPilas(pilas);
    cargaP(pilas);
    consultaLetra(pilas);

    return 0;
}

void IniciaPilas(TPila pilas[]) {

    int i;
    for(i=0; i<TOTAL_LETRAS; i++) {
        IniciaP(&(pilas[i]));
    }
}

void cargaP(TPila pilas[]) {

    FILE* arch = fopen("personas.txt","rt");
    char nom[TOP_NOMBRE];

    if(arch == NULL)
        printf("Error en la apertura del archivo");
    else {
        printf("Mostrando lectura\n");

        while(fscanf(arch,"%[^\n]\n",nom) == 1) {
              nom[0] = tolower(nom[0]);
              printf("%s\n",nom);
              poneP(&(pilas[nom[0] - 'a']),nom); //al hacer pilas[posicion] obtengo un tipo TPila y poneP espera un puntero Tpila, por ello el &
        }
    }
}

void consultaLetra(TPila pilas[]) {
    TPila Paux;
    IniciaP(&Paux);
    char cad, nom[TOP_NOMBRE];

    do {
        printf("Ingrese una letra para consultar, @ para finalizar\n");
        scanf(" %c",&cad);
        cad = tolower(cad);

        if(cad != '@') {
            while(!VaciaP(pilas[cad - 'a'])) {
                sacaP(&(pilas[cad - 'a']),nom);
                printf("nombre: %s\n",nom);
                poneP(&Paux,nom);
            }

            while(!VaciaP(Paux)) {
                sacaP(&Paux,nom);
                poneP(&(pilas[cad - 'a']),nom);
            }
       }
    } while (cad != '@');
}


