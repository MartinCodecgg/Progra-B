/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilas.h"
#define ST40 41
#define ST19 20
#define ST5 6

typedef struct nodoC{
    char razon[ST40], prov[ST6];
    float porc;
    struct nodoC * sig;} nodoC;
typedef nodoC * TListaC;

typedef struct {
    char razon[ST40];
    float reBruta, reNeta;} TResumen;

void hallaCoef(TPila *P, char cod[], float *coef) {
    TElementoP elem;
    if(!VaciaP(*P)) {
        sacaP(P,&elem);
        if(strcmp(elem.cod,cod) != 0)
            hallaCoef(P,cod,coef);

        else
            *coef = elem.coef;
        poneP(P,elem);
    }
}

void insertaLC(TListaC *LC, char razon[], char prov[]) {
    TListaC actC, new;
    if(*LC) {
        actC = (*LC)->sig;
        while(actC != *LC && strcmp(actC->razon,razon) != 0) {
            actC = actC->sig;
        }
        if(strcmp(razon,actC->razon) != 0) {
            new = (TListaC) malloc(sizeof(nodoC));
            strcpy(new->razon, razon);
            strcpy(new->prov, prov);
            new->porc = 0.045;
            new->sig = (*LC)->sig;
            (*LC)->sig = new;
            *LC = new;
        }
    }
}

void elimina(TListaC *LC, char prov[]) {
    TListaC actC, antC, elim;
    if(*LC) {
        antC = *LC; actC = (*LC)->sig;
        do {
            if(strcmp(prov,actC->prov) == 0) {
                elim = actC;
                if(*LC == (*LC)->sig)
                    *LC = NULL;
                else {
                    antC->sig = actC->sig;
                    if(actC == *LC)
                        *LC = antC;
                    actC = actC->sig;
                }
                free(elim);
            }
            else {
                antC = actC;
                actC = actC->sig;
            }
        }while(*LC && actC != (*LC)->sig);
    }
}

void procesaVentas(TListaC *LC, TPila *P) {
    FILE *archT = fopen("VENTAS.txt", "rt"),
         *archB = fopen("COMXCC202505.dat","ab"); //como pide que vaya guardando al final debo usar la a

    TResumen reg;
    char razon[ST40], prov[ST6], cod[ST6], fecha[ST19], cuit[ST5], actRazon[ST40];
    float imp, coef;

    if(!archT || !archB)
        printf("Error al abrir/crear los archivos\n");
    else {
        fscanf(archT,"%s %s %s %s %s %f", razon,prov,cod,fecha,cuit,&imp);
        while(!feof(archT)) {
            if(razon[38] == 'A' && razon[39] == 'R' //mejor llamar a una funcion que valide el call center
               && fecha[4] =='5' && fecha[6] =='2' && fecha[7] =='0' && fecha[8] =='2' && fecha[9] =='5') {
                    strcpy(actRazon, razon);
                    strcpy(reg.razon, razon); reg.reNeta = 0;
                    reg.reBruta = 0; insertaLC(LC,razon,prov);
                    hallaCoef(P,cod,&coef);
                    while(!feof(archT) && strcmp(razon,actRazon) == 0) {
                        reg.reBruta += imp;
                        fscanf(archT,"%s %s %s %s %s %f", razon,prov,cod,fecha,cuit,&imp);
                    }
                    if(coef != -1) {
                        reg.reNeta = reg.reBruta * (1-coef);
                        fwrite(&reg, sizeof(TResumen), 1, archB);
                    }
                    else
                        fscanf(archT,"%s %s %s %s %s %f", razon,prov,cod,fecha,cuit,&imp);
               }
               fclose(archT); fclose(archB);
        }
    }
}

int main() {
    TListaC LC;             char prov[ST6];
    TPila P;
    //cargaP(&P); cargaLC(&LC); //lo comento para que compile pero en el parcial no debe de ir comentado
    procesaVentas(&LC, &P);
    printf("Ingrese la provincia en que la empresa dejara de operar\n");
    scanf(" %s",prov);
    elimina(&LC,prov);
    return 0;
}

*/
