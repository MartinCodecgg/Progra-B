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
    struct nodoC * sig;
} nodoC;

typedef nodoC * TListaC;

typedef struct {
    char razon[ST40];
    float reBruta, reNeta;
} TResumen;

// TUS FUNCIONES ORIGINALES (sin modificar)

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
    char razon[ST40], prov[ST6], cod[ST6], fecha[ST19], cuit[ST5], actRazon[ST40];
    float imp, coef = 0;
    unsigned int len;
    if(!archT || !archB)
        printf("Error al abrir/crear los archivos\n");
    else {
        fscanf(archT,"%s %s %s %s %s %f", razon,prov,cod,fecha,cuit,&imp);
        while(!feof(archT)) {
            len = strlen(razon);
            if(razon[len - 1] == 'A' && razon[len -2] == 'R'
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
               }
                else
                    fscanf(archT,"%s %s %s %s %s %f", razon,prov,cod,fecha,cuit,&imp);
        }
        fclose(archT); fclose(archB);
    }
}

// ========== FUNCIONES DE PRUEBA ==========

void cargaP(TPila *P) {
    TElementoP elem;

    // Inicializar pila vacia
    IniciaP(P);

    // Cargar medios de pago con sus coeficientes de comision
    // Segun enunciado: CodigoMP (ANU 10) y coeficiente de comision (0.2 representa 20%)

    strcpy(elem.cod, "COD01");
    elem.coef = 0.15;  // 15% de comision
    poneP(P, elem);

    strcpy(elem.cod, "COD02");
    elem.coef = 0.20;  // 20% de comision
    poneP(P, elem);

    strcpy(elem.cod, "COD03");
    elem.coef = 0.10;  // 10% de comision
    poneP(P, elem);

    strcpy(elem.cod, "COD04");
    elem.coef = 0.25;  // 25% de comision
    poneP(P, elem);

    strcpy(elem.cod, "COD05");
    elem.coef = 0.18;  // 18% de comision
    poneP(P, elem);

    printf("+ Pila de medios de pago cargada (5 codigos)\n");
}

void creaArchivoVentas() {
    FILE *arch = fopen("VENTAS.txt", "wt");
    if(!arch) {
        printf("Error al crear VENTAS.txt\n");
        return;
    }

    // Ventas validas (razon termina en AR, fecha mayo 2025)
    fprintf(arch, "CallCenterSolutionsBuenosAiresAR BSAS COD01 2025-05-15 12345 1500.50\n");
    fprintf(arch, "CallCenterSolutionsBuenosAiresAR BSAS COD01 2025-05-16 12345 2000.00\n");
    fprintf(arch, "CallCenterSolutionsBuenosAiresAR BSAS COD02 2025-05-17 12345 1000.00\n");
    fprintf(arch, "TelecomServicesCordobaCiudadAR CBA COD01 2025-05-10 67890 3000.00\n");
    fprintf(arch, "TelecomServicesCordobaCiudadAR CBA COD03 2025-05-11 67890 2500.00\n");
    fprintf(arch, "ContactCenterMendozaRegionAR MDZ COD02 2025-05-20 11111 1800.00\n");

    // Ventas invalidas (no terminan en AR o no son de mayo 2025)
    fprintf(arch, "EmpresaSinCallCenterBuenosAires BSAS COD01 2025-05-15 22222 1000.00\n");
    fprintf(arch, "CallCenterSolutionsBuenosAiresAR BSAS COD01 2025-06-15 12345 500.00\n");
    fprintf(arch, "CallCenterSolutionsBuenosAiresAR BSAS COD01 2024-05-15 12345 500.00\n");

    fclose(arch);
    printf("+ Archivo VENTAS.txt creado exitosamente\n");
}

void cargaLC(TListaC *LC) {
    TListaC nuevo;
    *LC = NULL;

    // Crear primer nodo
    nuevo = (TListaC)malloc(sizeof(nodoC));
    strcpy(nuevo->razon, "CallCenterInicialAR");
    strcpy(nuevo->prov, "CABA");
    nuevo->porc = 0.045;
    nuevo->sig = nuevo;
    *LC = nuevo;

    printf("+ Lista circular inicializada\n");
}

void muestraLC(TListaC LC) {
    TListaC act;
    int count = 0;

    printf("\n=== CONTENIDO LISTA CIRCULAR ===\n");
    if(!LC) {
        printf("Lista vacía\n");
        return;
    }

    act = LC->sig;
    do {
        count++;
        printf("%d. Razón: %s | Prov: %s | Porc: %.3f\n",
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
        printf("%d. Razón: %s\n", count, reg.razon);
        printf("   Recaudación Bruta: $%.2f\n", reg.reBruta);
        printf("   Recaudación Neta: $%.2f\n", reg.reNeta);
        printf("   ---\n");
    }

    if(count == 0)
        printf("Archivo vacío\n");
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
    printf("      Rec. Bruta: $4500.50 (1500.50 + 2000.00 + 1000.00)\n");
    printf("      Rec. Neta: $3615.40 (85%% de 4500.50, usando coef 0.15 y 0.20)\n\n");
    printf("   2. TelecomServicesCordobaCiudadAR\n");
    printf("      Rec. Bruta: $5500.00 (3000.00 + 2500.00)\n");
    printf("      Rec. Neta: $4812.50 (usando coef 0.15 y 0.10)\n\n");
    printf("   3. ContactCenterMendozaRegionAR\n");
    printf("      Rec. Bruta: $1800.00\n");
    printf("      Rec. Neta: $1440.00 (80%% de 1800.00, usando coef 0.20)\n\n");
    printf("LISTA CIRCULAR:\n");
    printf("   Deberia contener las 3 empresas anteriores\n");
    printf("   (mas el nodo inicial si no fue eliminado)\n\n");
    printf("DESPUES DE ELIMINAR PROVINCIA:\n");
    printf("   Si eliminas 'BSAS': quedara sin CallCenterSolutions...\n");
    printf("   Si eliminas 'CBA': quedara sin TelecomServices...\n");
    printf("   Si eliminas 'MDZ': quedara sin ContactCenter...\n\n");
}

// ========== PROGRAMA PRINCIPAL DE PRUEBA ==========

int main() {
    TListaC LC;
    TPila P;
    char prov[ST6];

    printf("\n");
    printf("================================================================\n");
    printf("        PROGRAMA DE PRUEBA - PROCESAMIENTO DE VENTAS           \n");
    printf("================================================================\n");
    printf("\n");

    // Paso 1: Crear archivos y estructuras
    printf("PASO 1: Creando archivos de prueba...\n");
    printf("----------------------------------------\n");
    creaArchivoVentas();
    limpiaArchivoBinario();

    // Paso 2: Inicializar estructuras
    printf("\nPASO 2: Inicializando estructuras...\n");
    printf("----------------------------------------\n");
    cargaLC(&LC);
    cargaP(&P);  // Ahora si cargamos la pila

    // Paso 3: Mostrar resultados esperados
    muestraResultadosEsperados();

    // Paso 4: Procesar ventas
    printf("\nPASO 3: Procesando ventas...\n");
    printf("----------------------------------------\n");
    procesaVentas(&LC, &P);
    printf("+ Procesamiento completado\n");

    // Paso 5: Mostrar resultados reales
    printf("\n");
    printf("================================================================\n");
    printf("                    RESULTADOS REALES                           \n");
    printf("================================================================\n");

    muestraArchivoBinario();
    muestraLC(LC);

    // Paso 6: Probar eliminacion
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

    return 0;
}
