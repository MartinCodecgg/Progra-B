#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pilas.h"
#define ST40 41
#define ST10 11
#define ST8 9
#define ST30 31
#define ST13 14
#define DEFAULT_DESC 0.045

typedef struct nodoC{
    char razon[ST40], prov[ST30];
    float porc;
    struct nodoC * sig;
} nodoC;

typedef nodoC * TListaC;

typedef struct {
    char razon[ST40];
    float reBruta, reNeta;
} TResumen;

// === FUNCIONES DEL PARCIAL ===

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

TListaC buscaCall(TListaC LC, char razon[]) {
    TListaC aux;
    if(LC) {
        aux = LC->sig;
        while(aux != LC && strcmp(razon, aux->razon) != 0)
            aux = aux->sig;
        return(strcmp(razon,aux->razon) == 0) ? aux : NULL;
    }
    else
        return NULL;
}

void insertaLC(TListaC *LC, char razon[], char prov[]) {
    TListaC new;

    new = (TListaC) malloc(sizeof(nodoC));
    strcpy(new->razon, razon);
    strcpy(new->prov, prov);
    new->porc = DEFAULT_DESC;

    if(*LC == NULL)
        new->sig = new;
    else {
        new->sig = (*LC)->sig;
        (*LC)->sig = new;
    }
    *LC = new;
}

/*
void insertaLC(TListaC *LC, char razon[], char prov[]) {
    TListaC actC, new;

    new = (TListaC) malloc(sizeof(nodoC));
    strcpy(new->razon, razon);
    strcpy(new->prov, prov);
    new->porc = 0.045;

    if(*LC) {
        actC = (*LC)->sig;
        while(actC != *LC && strcmp(actC->razon,razon) != 0) {
            actC = actC->sig;
        }
        if(strcmp(razon,actC->razon) != 0) {
            new->sig = (*LC)->sig;
            (*LC)->sig = new;
            *LC = new;
        }
    }
    else {
        new->sig = new;
        *LC = new;
    }
}
*/

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
         *archB = fopen("COMXCC202505.dat","ab");
    TResumen reg;
    char razon[ST40], prov[ST30], cod[ST10], fecha[ST10], hora[ST8], cuit[ST13], actRazon[ST40];
    TListaC Pcall;
    float imp, coefPago, coefGanancia;
    unsigned int len;
    if(archT) {
        if(archB) {
            fscanf(archT,"%s %s %s %s %s %s %f",razon,prov,cod,fecha,hora,cuit,&imp);
            while(!feof(archT)) {
                len = strlen(razon);
                if(razon[len - 2] == 'A' && razon[len - 1] == 'R'
                && fecha[4] =='5' && fecha[6] =='2' && fecha[7] =='0' && fecha[8] =='2' && fecha[9] =='5') {
                        strcpy(actRazon, razon);
                        strcpy(reg.razon, razon);
                        reg.reBruta = 0;
                        Pcall = buscaCall(*LC,razon);
                        if(!Pcall) {
                            insertaLC(LC,razon,prov);
                            coefGanancia = DEFAULT_DESC;
                        }
                        else
                            coefGanancia = Pcall->porc;
                        coefPago = -1;
                        hallaCoef(P,cod,&coefPago);
                        while(!feof(archT) && strcmp(razon,actRazon) == 0 && coefPago != -1) {
                            reg.reBruta += imp;
                            fscanf(archT,"%s %s %s %s %s %s %f",razon,prov,cod,fecha,hora,cuit,&imp);
                        }
                        if(coefPago != -1) {
                            reg.reNeta = reg.reBruta * (1 - fabs(coefGanancia - coefPago)); //fbs() es la funcion abs para numeros reales, viene con math.h
                            fwrite(&reg, sizeof(TResumen), 1, archB);
                        }
                }
                else
                    fscanf(archT,"%s %s %s %s %s %s %f",razon,prov,cod,fecha,hora,cuit,&imp);
            }
            fclose(archB);
        }
        fclose(archT);
    }
}

// ========== FUNCIONES DE PRUEBA ==========

void cargaP(TPila *P) {
    TElementoP elem;

    IniciaP(P);

    strcpy(elem.cod, "COD01");
    elem.coef = 0.15;
    poneP(P, elem);

    strcpy(elem.cod, "COD02");
    elem.coef = 0.20;
    poneP(P, elem);

    strcpy(elem.cod, "COD03");
    elem.coef = 0.10;
    poneP(P, elem);

    strcpy(elem.cod, "COD04");
    elem.coef = 0.25;
    poneP(P, elem);

    strcpy(elem.cod, "COD05");
    elem.coef = 0.18;
    poneP(P, elem);

    printf("+ Pila de medios de pago cargada (5 codigos)\n");
}

void creaArchivoVentas() {
    FILE *arch = fopen("VENTAS.txt", "wt");
    if(!arch) {
        printf("Error al crear VENTAS.txt\n");
        return;
    }

    // CORREGIDO: Formato dd/mm/aaaa hh:mm:ss
    // Formato: razon prov cod fecha hora cuit importe
    fprintf(arch, "CallCenterSolutionsBuenosAiresAR BSAS COD01 15/05/2025 10:30:00 12345 1500.50\n");
    fprintf(arch, "CallCenterSolutionsBuenosAiresAR BSAS COD01 16/05/2025 11:45:00 12345 2000.00\n");
    fprintf(arch, "CallCenterSolutionsBuenosAiresAR BSAS COD02 17/05/2025 14:20:00 12345 1000.00\n");
    fprintf(arch, "TelecomServicesCordobaCiudadAR CBA COD01 10/05/2025 09:15:00 67890 3000.00\n");
    fprintf(arch, "TelecomServicesCordobaCiudadAR CBA COD03 11/05/2025 16:30:00 67890 2500.00\n");
    fprintf(arch, "ContactCenterMendozaRegionAR MDZ COD02 20/05/2025 12:00:00 11111 1800.00\n");

    // Ventas invalidas (no terminan en AR o no son de mayo 2025)
    fprintf(arch, "EmpresaSinCallCenterBuenosAires BSAS COD01 15/05/2025 10:00:00 22222 1000.00\n");
    fprintf(arch, "CallCenterSolutionsBuenosAiresAR BSAS COD01 15/06/2025 10:00:00 12345 500.00\n");
    fprintf(arch, "CallCenterSolutionsBuenosAiresAR BSAS COD01 15/05/2024 10:00:00 12345 500.00\n");

    fclose(arch);
    printf("+ Archivo VENTAS.txt creado exitosamente\n");
}

void cargaLC(TListaC *LC) {
    *LC = NULL;
    insertaLC(LC, "CallCenterInicialAR", "CABA");
    printf("+ Lista circular inicializada\n");
}

void muestraLC(TListaC LC) {
    TListaC act;
    int count = 0;

    printf("\n=== CONTENIDO LISTA CIRCULAR ===\n");
    if(!LC) {
        printf("Lista vacia\n");
        return;
    }

    act = LC->sig;
    do {
        count++;
        printf("%d. Razon: %s | Prov: %s | Porc: %.3f\n",
               count, act->razon, act->prov, act->porc);
        act = act->sig;
    } while(act != LC->sig);
    printf("Total empresas: %d\n", count);
}

void muestraArchivoBinario() {
    FILE *arch = fopen("COMXCC202505.dat", "rb");
    TResumen reg;
    int count = 0;

    printf("\n=== CONTENIDO ARCHIVO BINARIO COMXCC202505.dat ===\n");
    if(!arch) {
        printf("El archivo no existe o no se puede abrir\n");
        return;
    }

    while(fread(&reg, sizeof(TResumen), 1, arch) == 1) {
        count++;
        printf("%d. Razon: %s\n", count, reg.razon);
        printf("   Recaudacion Bruta: $%.2f\n", reg.reBruta);
        printf("   Recaudacion Neta: $%.2f\n", reg.reNeta);
        printf("   ---\n");
    }

    if(count == 0)
        printf("Archivo vacio\n");
    else
        printf("Total registros: %d\n", count);

    fclose(arch);
}

void limpiaArchivoBinario() {
    FILE *arch = fopen("COMXCC202505.dat", "wb");
    if(arch) {
        fclose(arch);
        printf("+ Archivo binario limpiado\n");
    }
}

void muestraResultadosEsperados() {
    printf("\n");
    printf("================================================================\n");
    printf("           RESULTADOS ESPERADOS DEL PROCESAMIENTO              \n");
    printf("================================================================\n");
    printf("\n");
    printf("ARCHIVO BINARIO (COMXCC202505.dat):\n");
    printf("   Deberia contener 3 registros:\n\n");
    printf("   1. CallCenterSolutionsBuenosAiresAR\n");
    printf("      Rec. Bruta: $4500.50\n");
    printf("      Formula: |0.045 - coef_promedio| aplicado a suma de importes\n\n");
    printf("   2. TelecomServicesCordobaCiudadAR\n");
    printf("      Rec. Bruta: $5500.00\n");
    printf("      Formula: |0.045 - coef_promedio| aplicado a suma de importes\n\n");
    printf("   3. ContactCenterMendozaRegionAR\n");
    printf("      Rec. Bruta: $1800.00\n");
    printf("      Formula: |0.045 - coef| aplicado\n\n");
    printf("LISTA CIRCULAR:\n");
    printf("   Deberia contener 4 empresas (inicial + 3 procesadas)\n\n");
    printf("DESPUES DE ELIMINAR PROVINCIA:\n");
    printf("   Si eliminas 'BSAS': quedara sin CallCenterSolutions\n");
    printf("   Si eliminas 'CBA': quedara sin TelecomServices\n");
    printf("   Si eliminas 'MDZ': quedara sin ContactCenter\n\n");
}

int main() {
    TListaC LC;
    TPila P;
    char prov[ST30];

    printf("\n");
    printf("================================================================\n");
    printf("        PROGRAMA DE PRUEBA - PROCESAMIENTO DE VENTAS           \n");
    printf("================================================================\n");
    printf("\n");

    printf("PASO 1: Creando archivos de prueba...\n");
    printf("----------------------------------------\n");
    creaArchivoVentas();
    limpiaArchivoBinario();

    printf("\nPASO 2: Inicializando estructuras...\n");
    printf("----------------------------------------\n");
    cargaLC(&LC);
    cargaP(&P);

    muestraResultadosEsperados();

    printf("\nPASO 3: Procesando ventas...\n");
    printf("----------------------------------------\n");
    procesaVentas(&LC, &P);
    printf("+ Procesamiento completado\n");

    printf("\n");
    printf("================================================================\n");
    printf("                    RESULTADOS REALES                           \n");
    printf("================================================================\n");

    muestraArchivoBinario();
    muestraLC(LC);

    printf("\n");
    printf("================================================================\n");
    printf("                 PRUEBA DE ELIMINACION                          \n");
    printf("================================================================\n");
    printf("\nIngrese la provincia a eliminar (BSAS, CBA, MDZ, etc.): ");
    scanf("%s", prov);

    printf("\nEliminando empresas de provincia: %s\n", prov);
    elimina(&LC, prov);

    printf("\n--- Lista despues de eliminar ---\n");
    muestraLC(LC);

    printf("\n");
    printf("================================================================\n");
    printf("                   PRUEBA FINALIZADA                            \n");
    printf("================================================================\n");
    printf("\n");
    printf("Programa funcionando correctamente\n");

    return 0;
}
