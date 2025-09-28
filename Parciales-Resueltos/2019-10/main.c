#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\IMPL_COLAESTATICACIRCULAR\colas.h"
#include "C:\Users\defin\Documents\Archivos Github\Progra-B\Practicas\Guia_5\IMPL_COLAESTATICACIRCULAR\colas.c"
#define TOP 50
#define STR8 9
#define FILA 20
#define COL 50

typedef struct Empresa {

    int numE;
    char fecha[STR8];
    char rec;
    struct Empresa * sig;} Empresa;

typedef Empresa * SubListaE;

typedef struct Norma {

    int norma,cantE;
    char nombre[STR8];
    SubListaE sub;
    struct Norma * sig;} Norma;

typedef Norma * TListaN;

void empresaQueCert(TListaN L, int n) {

    TListaN actN;
    int numE, max, eMax,i;
    int contE[TOP], numerosE[TOP];
    SubListaE actE;

    for(i=0; i<n; i++) {
        printf("Ingrese un numero de empresa (0-49)\n");
        scanf(" %d",&numE); //recordar poner adelante un espacio del scanf siempre
        numerosE[i] = numE;
        contE[i] = 0;
    }
    actN = L;
    while(actN != NULL) {
        actE = actN->sub;
                    //hay que comparar cada empresa con todos los numeros los numeros ingresados
        while(actE != NULL) { //&& actE->numE <= numerosE[n-1]  MAL el usuario no ingresa los numeros de forma ordenada
            for(i = 0; i < n; i++) {
                if(numerosE[i] == actE -> numE)
                    contE[i]++;
            }
            actE = actE->sig;
        }
        actN = actN->sig;
    }
    max = -999;
    for(i=0; i<n; i++) {
        printf("La empresa n° %d, certifico %d normas\n",numerosE[i], contE[i]);
        if(contE[i] > max) {
            max = contE[i];
            eMax = numerosE[i];
        }
    }
    printf("La empresa que mas normas certifico es: %d\n",eMax);
}

void generaM(char M[][COL], TListaN L) {
    TListaN actN;
    SubListaE actE; //Convenia inicializar toda la matriz con N y luego reemplazar por S, el codigo quedaria mas claro, y mas eficiente
    int i = 0, j;       //para reemplazar por S solo recorro las sublitas y voy rellenando la fila con el numero empresa
    if(L != NULL) {
        actN = L;
        while(actN != NULL && i < FILA){
            actE = actN->sub;
            for(j=0; j<COL; j++) {
                if(actE != NULL && actE->numE == j) {
                    M[i][j] = 'S';
                    actE = actE->sig;
                }
                else
                    M[i][j] = 'N';
            }
            actN = actN->sig;
            i++;
        }
        for(i; i < FILA; i++) //terminar con for desde i hasta 19
            for(j=0; j<COL; j++) //usar COL y no 50, no usar valores hardcodeados
                M[i][j] = 'N';
    }
}

void validaRec(char M[][COL], int x, TCola *C, int i, int j, int n, int cont, int *cont2) { //PREGUNTAR, hay ligero error
    if(j>=0) {
        cont += M[i][j] == 'S';
        if(i > 0)
            validaRec(M,x,C,i-1,j,n,cont,cont2);
        else {
            if(cont >= x) {
                poneC(C,j);
                ++*cont2; //Primero desreferencia y luego aumenta contador, valido porque el ++ a la derecha se despues
            }
            validaRec(M,x,C,n,j-1,n,0,cont2);
        }
    }
}

void Elimina(TListaN *L, TCola *C, int E){

    TElementoC elem; TListaN actN;
    SubListaE actE, antE;
    int cent = 9999, aux = 0;
    poneC(C,cent);
    sacaC(C,&elem); //cuando uso la tecnica del centinela debo poner y sacar sino entra al while sin elem teniendo un valor
    while(elem != cent) {
        if(elem == E)
            aux = 1;    // la logica va antes del pone/saca interno
        poneC(C,elem);
        sacaC(C,&elem); //siempre se debe sacar el centinela como ultimo
    }
    if(aux) {
        actN = *L;
        while(actN != NULL) {

            if(actN->sub->numE == E || actN->sub->rec == 'N'){
                actE=actN->sub;
                actN->sub = actN->sub->sig;
                free(actE);
            }
            else {
                actE = actN->sub;
                while(actE != NULL && (actE->numE != E || actE->rec != 'N')) {
                    antE = actE;
                    actE = actE->sig;
                }
                if(actE != NULL && (actE->numE == E || actE->rec == 'N')) {
                    antE->sig = actE->sig;
                    free(actE);
                }
            }
            actN = actN->sig;
        }
    }
}

void generaL(TListaN *L){
    TListaN antN,aux;
    int norma,cantE,i,numE;
    SubListaE auxE, antE, actE;
    char nombreN[STR8], fecha[STR8], rec;
    FILE * arch = fopen("CARGACTUAL.txt","rt");

    if(arch == NULL)
        printf("Error al abrir el archivo\n");
    else {
        while(fscanf(arch,"%d%s%d",&norma,nombreN,&cantE) == 3) {
            aux = (TListaN) malloc(sizeof(Norma));
            aux->norma = norma;
            strcpy(aux->nombre, nombreN);
            aux->cantE = cantE; aux->sub = NULL;
            //antN = NULL; //Si voy a hacer este algoritmo de la lectura ordenada no debo inicializar a antN en cada iteracion
            if(*L == NULL)//cabecera
                *L = antN = aux;
            else {
                antN->sig = aux; //La lectuta cambia al estar ordenado el archivo
                antN = aux;
            }
            aux->sig = NULL;
            for(i=0; i<cantE; i++) {
                fscanf(arch,"%d%s %c",&numE,fecha,&rec);
                auxE = (SubListaE) malloc(sizeof(Empresa));
                auxE->numE = numE;
                auxE->rec = rec;
                strcpy(auxE->fecha,fecha);
                antE = NULL;
                if(aux->sub == NULL || numE < aux->sub->numE) { //Nunca comparar con el aux porque aux es el que estoy creando
                    auxE->sig = aux->sub;
                    aux->sub = auxE;
                }
                else {
                    actE = aux->sub;
                    while(actE != NULL && numE > aux->sub->numE) {
                        antE = actE;
                        actE = actE->sig;
                    }
                    if(antE != NULL) {
                        antE->sig = auxE;
                        auxE->sig = actE;
                    }
                }
            }
        }
        fclose(arch);
    }
}

void mostrarLista(TListaN L) { //IA
    TListaN actN;
    SubListaE actE;
    int contNormas = 0, contEmpresas;

    if(L == NULL) {
        printf("\n=== LISTA VACIA ===\n");
        return;
    }

    printf("\n=============== LISTA COMPLETA ===============\n");

    actN = L;
    while(actN != NULL) {
        contNormas++;
        printf("\nNORMA #%d:\n", contNormas);
        printf("  Codigo: %d\n", actN->norma);
        printf("  Nombre: %s\n", actN->nombre);
        printf("  Cantidad declarada: %d\n", actN->cantE);

        if(actN->sub == NULL) {
            printf("  *** SUBLISTA VACIA ***\n");
        } else {
            printf("  Empresas certificadas:\n");
            actE = actN->sub;
            contEmpresas = 0;

            while(actE != NULL) {
                contEmpresas++;
                printf("    [%d] Empresa: %d, Fecha: %s, Recertificada: %c\n",
                       contEmpresas, actE->numE, actE->fecha, actE->rec);
                actE = actE->sig;
            }
            printf("  Total empresas en sublista: %d\n", contEmpresas);
        }
        printf("  ----------------------------------------\n");

        actN = actN->sig;
    }

    printf("\nRESUMEN: %d normas en total\n", contNormas);
    printf("============================================\n\n");
}

void mostrarCola(TCola *C) { //IA
    TCola tempC;
    TElementoC elem;
    int cont = 0;

    printf("\n======= CONTENIDO DE LA COLA =======\n");

    if(VaciaC(*C)) {
        printf("Cola vacia\n");
        printf("===================================\n\n");
        return;
    }

    IniciaC(&tempC);

    printf("Empresas en la cola: ");
    while(!VaciaC(*C)) {
        sacaC(C, &elem);
        printf("%d ", elem);
        poneC(&tempC, elem);
        cont++;
    }

    // Restaurar cola original
    while(!VaciaC(tempC)) {
        sacaC(&tempC, &elem);
        poneC(C, elem);
    }

    printf("\nTotal elementos: %d\n", cont);
    printf("===================================\n\n");
}

int main() {

    TListaN L = NULL;
    char M[FILA][COL];
    TCola C;
    int n, x, cont2 = 0, E;

    generaL(&L);
    if(L != NULL) { //validar que cargo bien la lista antes de hacer todo lo otro (en caso de lectura)
        printf("Ingrese N\n");
        scanf(" %d",&n);
        empresaQueCert(L,n);
        generaM(M,L);

        //Mostrando matriz generada (ADICIONAL)
        int i,j;
        for(i = 0; i<20; i++) {
            for(j=0; j<50; j++)
                printf("%c ",M[i][j]);
            printf("\n");
        }

        printf("Ingrese X\n");
        scanf(" %d",&x);
        IniciaC(&C);
        validaRec(M,x,&C,FILA-1,COL-1,FILA-1,0,&cont2);
        printf("La cantidad de empresas que cumplen con la condicion es: %d\n",cont2);
        printf("Ingrese E\n");
        scanf(" %d",&E);
        Elimina(&L,&C,E);
        mostrarCola(&C); //IA
        mostrarLista(L); //IA
    }
    return 0;
}
