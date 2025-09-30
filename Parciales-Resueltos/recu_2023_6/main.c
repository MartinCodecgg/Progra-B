#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "colas.h"
#define ST7 8
#define ST3 4
#define TOP 50
#define RADIOS 3

typedef struct nodoC{
    char patente[ST7], vip, radio[ST3], libre;
    int cantP;
    struct nodoC * sig;} nodoC;
typedef nodoC * TListaC;

typedef struct{
    int cantP;
    char vip, radio[ST3];} TViaje;

typedef struct nodo{
    char patente[ST7];
    TCola C;
    struct nodo * sig; } nodo;

typedef nodo * TListaL;

typedef struct{
    int cantV, cantP;} TRvec;

void buscaPat(TListaL L, char pat[ST7], TListaL *p) {
    TListaL act;
    if(L != NULL) {
        act = L;
        while(act != NULL && strcmp(pat,act->patente) > 0)
            act = act->sig;
        if(act != NULL && strcmp(pat,act->patente) == 0)
            *p = act;
        else
            *p = NULL;
    }
}

void procesaArch(TListaC LC, TListaL *L){
    TListaC actC;
    TElementoC reg;
    TListaL actL,antL, pL, new; //Mejor usar Pl y no pL, la catedra indica que es un puntero con la P mayuscula
    FILE * arch = fopen("Viajes.dat","rb");

    if (arch == NULL)
            printf("Error al abrir el archivo");
    else {
        while(fread(&reg,sizeof(TViaje),1,arch) == 1) {
            actC = LC->sig;
            while(actC != LC){
                if(actC->libre = 'S') {
                    if(reg.cantP <= actC->cantP &&
                       !(reg.vip == 'S' && actC->vip == 'N') && strcmp(reg.radio,actC->radio) <= 0) {
                            actC->libre = 'N';
                            buscaPat(*L,actC->patente,&pL);
                            if(pL == NULL) {
                                new = (TListaL) malloc(sizeof(nodo));
                                strcpy(new->patente,actC->patente);
                                IniciaC(&(new->C));
                            }
                            poneC(&(pL->C),reg);
                       }
                       printf("No se puedo asignar el viaje a la patente %s",actC->patente);
                }
                actC = actC->sig;
            }
            printf("Ningun coche puede aceptar el viaje solicitado");
        }
        fclose(arch);
    }
}

void mayorElim(TListaL L) {
    TListaL act;
    TElementoC elem;
    char actP[ST7];
    if(L != NULL) {
        act = L;
        while(act != NULL) {
            actP = act->patente;
            cont = 0;
            while(act->patente == actP) {
                if(!VaciaC(act->C)) {
                    sacaC(&(act->C),&elem);
                    poneC(&(act->C),elem);
                    if(elem.cantP == 0);
                        cont++;
                }
                act = act->sig;
            }
            if(cont >= max) {
                max = cont;
                maxP = act->patente;
            }
        }
        printf("El coche que tuvo la mayor cantidad de eliminaciones fue: %s",maxP);
    }
}

void eliminaPat(TListaC *LC, TListaL *L, char pat[]) {
    TListaC actC,antC;
    TListaL actL,antL;
    TRvec reg, vec[RADIOS];
    int i;

    actC = LC->sig;
    while(actC != LC && strcmp(act->patente,pat) != 0) {
        antC = actC;
        actC = actC->sig;
    }
    if(act == LC) {
        antC->sig = actC->sig;
        LC = antC;
    }
    else
        ant->sig = act->sig;
    free(act);

    for(i = 0; i<RADIOS; i++){
        vec[i].cantP = 0;
        vec[i].cantV = 0;
    }

    actL = L;
    while(strcmp(pat,actL->patente) != 0) {
        antL = actL;
        actL = actL->sig;
    }
    actualL = actL;
    while(actual == actL) {
        if(!VaciaC(actL->C)) {
            sacaC(&(actL->C),&reg);
            vec[strlen(reg->radio) -1].cantP += reg->cantP;
            vec[strlen(reg->radio) -1].cantV++;
        }
    }
    if(actL == *L)
        *L = (*L)->sig;
    else
        antL->sig = act->sig;
    free(actL);
}

int main() {

    TListaC LC = NULL;
    TListaL L = NULL;
    char p[ST7];
    //cargaLC(&LC);
    procesaArch(LC,&L);
    printf("Ingrese la patente p que desea eliminar\n");
    scanf("%s", p);
    //eliminaPat(&LC,&L,p);
    return 0;
}
