#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colas.h"
#define ST10 11
#define ST5 6

typedef struct nodito{
    char fecha[ST10];
    float precio,cant;
    struct nodito * sig;} nodito;

typedef nodito * SubLista;

typedef struct {
    char cod[ST5];
    float cant;} TRcompra;

typedef struct nodo{
    char cod[ST5];
    float precio, stock, margen;
    SubLista sub;
    struct nodo * sig;} nodo;

typedef struct nodo* TLista;

typedef struct nodoD{
    char cod[ST5];
    float stock;
    struct nodoD *sig,*ant;} nodoD;

typedef nodoD * PnodoD;

typedef struct {
    PnodoD pri,ult;} TListaD;

void eliminaLD(TListaD *LD, char cod[]) {
    PnodoD actD, elim;
    actD = LD->pri;
    while(actD != NULL && strcmp(cod,actD->cod) != 0)
        actD = actD->sig;

    if(LD->pri->sig == NULL) {
        LD->pri = LD->ult = NULL;
        free(actD);
    }
    else {
        if(actD == LD->pri) {
            elim = actD;
            LD->pri->sig->ant = NULL;
            LD->pri = LD->pri->sig;
        }
        else {
            if(actD == LD->ult) {
                elim = actD;
                LD->ult->ant = NULL;
                LD->ult = LD->ult->ant;
            }
            else {
                elim = actD;
                actD->ant->sig = actD->sig;
                actD->sig->ant = actD->ant;
            }
            free(elim);
        }
    }
}

void insertaSublista(TLista *p, char fecha[], int cant, float precio) {
    SubLista new;
    new = (SubLista) malloc(sizeof(nodito));
    strcpy(new->fecha,fecha);
    new->cant = cant;
    new->precio = precio;
    new->sig = (*p)->sub;
    (*p)->sub = new; //si esta vacia *p es NULL //p es un puntero a un TLista entonces p es un puntero doble, ademas debemos asignarle sub si estamos creando una subLista
}

void actualizaLS(TLista *LS, TListaD *LD, char cod[], float cant, float precio, char fecha[]) {
    TLista actL, antL, new;
    int tieneStockNegativo = 0;

    actL = *LS;
    while(actL != NULL && strcmp(cod,actL->cod) > 0) {
        antL = actL;
        actL = actL->sig;
    }
    if(actL != NULL) {
        if(actL->stock < 0)
            tieneStockNegativo = 1;
        actL->stock += cant;
        actL->precio = precio * actL->margen;
        insertaSublista(&actL,fecha,cant,precio);
        if(actL->stock > 0 && tieneStockNegativo)
            eliminaLD(LD,cod);
    }
    else {
        new = (TLista) malloc(sizeof(nodo));
        strcpy(new->cod,cod);
        new->stock = cant;
        new->precio = precio * 1.5;
        insertaSublista(&new,fecha,cant,precio);
        if(*LS == NULL || strcmp(cod,(*LS)->cod) < 0) {
            new->sig = *LS;
            *LS = new;
        }
        else {
            antL->sig = new;
            new->sig = actL;
        }
    }
}

void actualizaYbusca(TLista LS, TElementoC elem, float * precio, TListaD *LD) {
    TLista actL;
    PnodoD new;
    actL = LS;
    while(strcmp(elem.cod,actL->cod) > 0) //elem es un struct y por ello elem.cod
        actL = actL->sig;
    actL->stock -= elem.cant;
    *precio = actL->precio;
    if(actL->stock < 0) {
        new = (PnodoD) malloc(sizeof(nodoD));
        strcpy(new->cod,elem.cod);
        new->stock = actL->stock;
        if(LD->pri == NULL) {
            LD->pri = LD->ult = new;
            new->sig = new->ant = NULL;
        }
        else {
            LD->ult->sig = new;
            new->sig = NULL;
            new->ant = LD->ult;
            LD->ult = new;
        }
    }
}

void procesaArch(TLista *LS, TListaD *LD) {
    FILE * arch = fopen("PROVEEN.txt","rt");
    char fecha[ST10], cod[ST5];
    float cant,precio;

    if(arch == NULL)
        printf("Ocurrio uun error al intentar abrir el archivo");
    else {
        while(fscanf(arch,"%s%s%f%f",fecha,cod,&cant,&precio) == 4)
            if(fecha[2] == 2 && fecha[3] == 5 && fecha[6] == 4)
                actualizaLS(LS,LD,cod,cant,precio,fecha);
        fclose(arch);
    }
}

void procesaC(TCola *C, TLista LS, TListaD *LD) {
                        float acum = 0, precio;
    TElementoC elem;    unsigned int cont = 0;

    while(!VaciaC(*C)) {
        sacaC(C,&elem);
        actualizaYbusca(LS,elem,&precio,LD);
        cont++;
        acum += elem.cant * precio;
}
    if(cont)
        printf("El importe total de la compra es %8.2f y el importe total promedio por producto es %8.2f\n", acum, acum/cont);
}

int main() {
    TLista LS;
    TListaD LD;
    TCola C;
    //cargaC(&C); cargaLS(&LS); cargaLD(&LD);
    procesaC(&C, LS, &LD);
    procesaArch(&LS,&LD);
    return 0;
}

