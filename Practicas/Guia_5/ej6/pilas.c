#include <stdio.h>
#include "pilas.h"


void poneP(TPila *P, TElementoP x) {
 if ( ((*P).tope)!= MAX-1)
 (*P).datos[++((*P).tope)] = x;
}

void sacaP(TPila *P, TElementoP* x) {
 if (((*P).tope) != -1) //if (P->tope != 1)
 *x = (*P).datos[(*P).tope--]; // *x = P->datos[P->tope--]
}

TElementoP consultaP(TPila P) {
 if (P.tope != -1)
 return P.datos[P.tope];
}

int VaciaP(TPila P) {
 return (P.tope == -1);
}

void IniciaP (TPila *P) {
(*P).tope=-1;
}

void cargaP(TPila *P) {

    TElementoP elem;

    FILE* arch = fopen("enteros.txt","rt");

    while (fscanf(arch,"%d\n",&elem) == 1)
        poneP(P,elem);
}

void cuentaCeros(TPila *P) {

    TElementoP elem;
    int count;
    while(!VaciaP(*P)) {

        sacaP(P,&elem);

        if (elem == 0)
            count += 1;
    }

    printf("La cantidad de ceros que contiene la pila es %d\n",count);

}

void promedio(TPila *P) {

    TPila Paux;
    IniciaP(&Paux);
    TElementoP elem;
    int count=0;
    float acum=0;

    while(!VaciaP(*P)) {

        sacaP(P,&elem);
        poneP(&Paux,elem);

        acum += elem;
        count += 1;
    }

    //printf("acum y count son %f %d\n",acum,count);
    acum /= count;

    while(!VaciaP(Paux)) {
        sacaP(&Paux,&elem);
        poneP(P,elem);
    }

    printf("El promedio de los elementos de la pila es %3.2f\n",acum);
}

void maxYmin(TPila *P) {

    TPila Paux;
    IniciaP(&Paux);
    TElementoP elem;
    int max=-99999, min=99999;

    while(!VaciaP(*P)) {

        sacaP(P,&elem);
        poneP(&Paux,elem);

        if (elem < min)
            min = elem;

        if (elem > max)
            max = elem;
    }

    printf("El valor maximo de la pila es %d\n",max);
    printf("El valor minimo de la pila es %d\n",min);

    while(!VaciaP(Paux)) {
        sacaP(&Paux,&elem);
        poneP(P,elem);
    }

}

void quitaUlt(TPila *P) {

    TPila Paux;
    IniciaP(&Paux);
    TElementoP elem,tope;
    sacaP(P,&tope); //suponiendo que la Pila es valida o tiene al menos un valor

    while(!VaciaP(*P)) {

        sacaP(P,&elem);

        if (elem <= tope)
            poneP(&Paux,elem);
    }

    while(!VaciaP(Paux)) {
        sacaP(&Paux,&elem);
        poneP(P,elem);
        printf("%d\n",elem);
    }
    poneP(P,tope);
    printf("%d\n",tope);

}
