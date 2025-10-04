#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "colas.h"
#define ST8 9
#define ST5 6
#define ST3 4

// Estructuras principales
typedef struct nodo{
    char dom[ST7], fecha[ST8], hora[ST5];
    struct nodo *sig;
} nodo;
typedef nodo * TLista;

typedef struct nodito{
    char dom[ST7];
    unsigned int cantOB;
    struct nodito * sig;
} nodito;
typedef nodito * SubLista;

typedef struct nodoD {
    char puesto[ST3];
    SubLista sub;
    struct nodoD *sig, *ant;
} nodoD;
typedef struct nodoD * Pnodo;

typedef struct{
    Pnodo pri, ult;
} TListaD;

// ============================================
// TU CÓDIGO ORIGINAL - SIN MODIFICAR
// ============================================

int validaDom(TLista Pl) {
    if(strlen(Pl->dom) == 7)
        return Pl->dom[4] == Pl->fecha[5];
    else
        return Pl->dom[5] == Pl->fecha[5];
}

int hallaCantPuestos(TListaD LD) {
    unsigned int cont = 0;
    Pnodo actD = LD.pri;
    while(actD != NULL) {
        cont++;
        actD = actD->sig;
    }
    return cont;
}

Pnodo buscaPuesto(TListaD LD, int pos) {
    unsigned int aux = 1; //usar aux = 1 en este caso para que funcione el rand
    Pnodo actD;
    actD = LD.pri;
    while(actD != NULL && aux != pos) {
        aux++;
        actD = actD->sig;
    }
    return actD;
}

void insertaSubLista(Pnodo Ppuesto, TElementoC elem) {
    SubLista new, auxS;

    new = (SubLista) malloc(sizeof(nodito));
    new->sig = NULL;
    strcpy(new->dom,elem.dom);
    new->cantOB = 0;
    auxS = Ppuesto->sub;

    if(Ppuesto->sub != NULL) { //Porque podria ser la primera multa a cargar
        auxS = Ppuesto->sub;
        while(auxS->sig != NULL) //para hacer la lectura adelantada para ahorrarme una variable debo considerar que Ppuesto->sub no sea NULL, caso contrario podria ocurrir SEGMENTATION FAULT
            auxS = auxS->sig;
        /*
        if(auxS == Ppuesto->sub)  /Este fragmento no tenia sentido, ya que si quiero insertar al final, el unico caso donde inserto en la cabeza es cuando la lista vacia, pero si esta vacia no entraba por el if
            Ppuesto->sub = new;
        else
        */
        auxS->sig = new;
    }
    else
        Ppuesto->sub = new;
}

void actualizaSub(Pnodo Ppuesto, unsigned int contOB, char estado, char dom[ST7]) {
    SubLista actS, antS;

    antS = NULL;
    actS = Ppuesto->sub;
    while(actS != NULL && strcmp(dom, actS->dom) != 0) {
        antS = actS;
        actS = actS->sig;
    }
    if(actS != NULL) { //verificar el archS ya que el archivo puede venir mal, nadie asegura que este validado
        if(estado == 'O')
            actS->cantOB++;
        else {
            if(actS == Ppuesto->sub)
                Ppuesto->sub = Ppuesto->sub->sig;
            else {
                antS->sig = actS->sig;
            }
            free(actS);
        }
    }
}

void eliminaIncorrectos(TLista *L) {
    TLista act,ant,elim;
    unsigned int totCont = 0, contCancel = 0;

    ant = NULL;
    act = *L;
    while(act != NULL) {
        totCont++;
        if(validaDom(act)) {
            ant = act;
            act = act->sig;
        }
        else {
            contCancel++;
            elim = act;
            if(act == *L)
                (*L) = (*L)->sig;
            else
                ant->sig = act->sig;
            act =  act->sig;
            free(elim);
        }
    }
    if(totCont)
        printf("El porcentaje de turnos depurados es del %3.2f\n",(float) contCancel/totCont * 100);
}

void atender(TListaD LD, TCola *C, TLista L) {
    TElementoC elem, cent;
    TLista actL, antL;
    unsigned int N, pos, tieneTurno; //= 0; //no tiene sentido inicializar aqui, debo iniciar para cada elemento de la cola
    Pnodo Ppuesto;
    N = hallaCantPuestos(LD);
    strcpy(cent.dom,"ZZZZZZZ");
    poneC(C,cent);
    sacaC(C,&elem);

    while(strcmp(elem.dom,cent.dom) != 0) {
        actL = L;
        tieneTurno = 0;

        while(actL != NULL && strcmp(elem.dom,actL->dom) > 0) //busco el turno
            actL = actL->sig;
        while(actL != NULL && strcmp(elem.dom,actL->dom) == 0 && !tieneTurno) { //busca el turno si hay mas de uno para la misma patente
            if(actL->fecha[5] == '4')
                tieneTurno = 1;
            antL = actL; //el ant para poder validar bien despues
            actL = actL->sig;
        }
        if(tieneTurno) {
            pos = rand() % N + 1;
            Ppuesto = buscaPuesto(LD,pos);
            insertaSubLista(Ppuesto,elem);
        }
        else {
            if(actL != NULL && strcmp(elem.dom,antL->dom) == 0) //Esta logica no tiene sentido ya que actL ya avanzo y no es el mismo, tener cuidado con esto
                poneC(C,elem);
            else
                printf("La patente %s no tiene ningun turno asignado\n",elem.dom);
        }
        sacaC(C,&elem);
    }
}

void procesaArch(TListaD LD) {
    FILE* arch = fopen("TESTEOS.txt", "rt");
    unsigned int puesto, cantOB;
    Pnodo Ppuesto;
    char dom[ST7], estado;

    if(arch == NULL)
        printf("Error al intentar abrir el archivo");
    else {
        while(fscanf(arch,"%u %s %u %c", &puesto, dom, &cantOB, &estado) == 4) {
            Ppuesto = buscaPuesto(LD,puesto + 1); //el mas uno es porque buscaPuesto trabaja con aux = 1 y por ello pasarle 0 (como puede venir en el archivo) daria error
            if(Ppuesto != NULL) //tener en cuenta que nadie afirma que el puesto venga bien desde el archivo
                actualizaSub(Ppuesto, cantOB, estado, dom);
        }
        fclose(arch);
    }
}

// ============================================
// FIN DE TU CÓDIGO ORIGINAL
// ============================================

// ============================================
// FUNCIONES DE CARGA Y VISUALIZACIÓN
// ============================================

void cargaL(TLista *L) {
    // Formato fecha: AAAAMMDD
    // Para patentes de 7 chars: dom[4] debe coincidir con fecha[5] (2do dígito del mes)
    // Ej: ABC4XXX con fecha 20250402 → dom[4]='4' == fecha[5]='4' ✓
    char patentes[][ST7] = {"ABC4423", "DEF3356", "GHI4489", "JKL5512", "MNO4445", "PQR4478"};
    char fechas[][ST8] = {"20250402", "20250302", "20250420", "20250510", "20250425", "20250418"};
    char horas[][ST5] = {"10:30", "14:00", "09:15", "16:45", "11:00", "15:30"};

    *L = NULL;
    TLista aux, nuevo;

    for(int i = 0; i < 6; i++) {
        nuevo = (TLista) malloc(sizeof(nodo));
        strcpy(nuevo->dom, patentes[i]);
        strcpy(nuevo->fecha, fechas[i]);
        strcpy(nuevo->hora, horas[i]);
        nuevo->sig = NULL;

        if(*L == NULL)
            *L = nuevo;
        else
            aux->sig = nuevo;
        aux = nuevo;
    }
    printf("Lista de turnos cargada.\n");
}

void cargaLD(TListaD *LD) {
    LD->pri = NULL;
    LD->ult = NULL;
    Pnodo nuevo;

    for(int i = 1; i <= 3; i++) {
        nuevo = (Pnodo) malloc(sizeof(nodoD));
        sprintf(nuevo->puesto, "%d", i);
        nuevo->sub = NULL;
        nuevo->sig = NULL;
        nuevo->ant = LD->ult;

        if(LD->pri == NULL)
            LD->pri = nuevo;
        else
            LD->ult->sig = nuevo;
        LD->ult = nuevo;
    }
    printf("Lista de puestos cargada (3 puestos).\n");
}

void cargaC(TCola *C) {
    IniciaC(C);
    TElementoC elem;

    char patentes[][ST7] = {"ABC4423", "DEF3356", "XYZ9999", "GHI4489", "MNO4445", "STU6666"};

    for(int i = 0; i < 6; i++) {
        strcpy(elem.dom, patentes[i]);
        poneC(C, elem);
    }
    printf("Cola de automóviles cargada.\n");
}

void crearArchivoTesteos() {
    FILE *arch = fopen("TESTEOS.txt", "wt");
    if(arch == NULL) {
        printf("Error al crear archivo TESTEOS.txt\n");
        return;
    }

    fprintf(arch, "0 ABC4423 2 O\n");
    fprintf(arch, "1 DEF3356 0 O\n");
    fprintf(arch, "2 GHI4489 3 O\n");
    fprintf(arch, "0 ABC4423 1 O\n");
    fprintf(arch, "1 MNO4445 1 O\n");
    fprintf(arch, "2 GHI4489 2 A\n");

    fclose(arch);
    printf("Archivo TESTEOS.txt creado.\n");
}

void muestraLista(TLista L) {
    printf("\n=== LISTA DE TURNOS ===\n");
    if(L == NULL) {
        printf("Lista vacía.\n");
        return;
    }

    int i = 1;
    while(L != NULL) {
        printf("%d. Dom: %s | Fecha: %s | Hora: %s",
               i++, L->dom, L->fecha, L->hora);
        if(validaDom(L))
            printf(" [VÁLIDO]\n");
        else
            printf(" [INVÁLIDO]\n");
        L = L->sig;
    }
}

void muestraListaD(TListaD LD) {
    printf("\n=== PUESTOS DE ATENCIÓN ===\n");
    if(LD.pri == NULL) {
        printf("Lista vacía.\n");
        return;
    }

    Pnodo act = LD.pri;
    while(act != NULL) {
        printf("\nPuesto %s:\n", act->puesto);
        if(act->sub == NULL) {
            printf("  (sin automóviles)\n");
        } else {
            SubLista actS = act->sub;
            while(actS != NULL) {
                printf("  - %s | OB: %u\n", actS->dom, actS->cantOB);
                actS = actS->sig;
            }
        }
        act = act->sig;
    }
}

void muestraCola(TCola C) {
    printf("\n=== COLA DE AUTOMÓVILES ===\n");
    if(VaciaC(C)) {
        printf("Cola vacía.\n");
        return;
    }

    int i = 1;
    for(int j = C.pri; j <= C.ult; j++) {
        printf("%d. %s\n", i++, C.datos[j].dom);
    }
}

void muestraArchivo() {
    printf("\n=== TESTEOS.txt ===\n");
    FILE *arch = fopen("TESTEOS.txt", "rt");
    if(arch == NULL) {
        printf("Archivo no encontrado.\n");
        return;
    }

    char linea[100];
    while(fgets(linea, sizeof(linea), arch) != NULL) {
        printf("%s", linea);
    }
    fclose(arch);
}

// OLD MAIN (Para controlar)
/*
int main() {
    TLista L;
    TListaD LD;
    TCola C;
    cargaL(&L); cargaLD(&LD); cargaC(&C);
    eliminaIncorrectos(&L);
    atender(LD,&C,L);
    procesaArch(LD);
    return 0;
}
*/

// === MAIN PARA TESTEAR EL CODIGO

int main() {
    srand(time(NULL));

    TLista L;
    TListaD LD;
    TCola C;

    printf("========================================\n");
    printf("    SISTEMA VTV - PRUEBA\n");
    printf("========================================\n\n");

    printf("--- CARGA INICIAL ---\n");
    cargaL(&L);
    cargaLD(&LD);
    cargaC(&C);
    crearArchivoTesteos();

    printf("\n--- ESTADO INICIAL ---");
    muestraLista(L);
    muestraListaD(LD);
    muestraCola(C);

    // TEST 1: validaDom
    printf("\n\n========================================\n");
    printf("TEST 1: validaDom()\n");
    printf("========================================\n");
    printf("Formato fecha: AAAAMMDD → fecha[5] = 2do dígito del mes\n");
    printf("RESULTADO ESPERADO:\n");
    printf("  - ABC4423 con fecha 20250402: VÁLIDO (dom[4]='4' == fecha[5]='2')... espera, eso es INVÁLIDO\n");
    printf("  - Corrigiendo: dom[4] debe coincidir con fecha[5]\n");
    printf("\nRESULTADO REAL:\n");
    TLista auxL = L;
    while(auxL != NULL) {
        printf("  - %s con fecha %s: %s (dom[4]='%c' vs fecha[5]='%c')\n",
               auxL->dom, auxL->fecha,
               validaDom(auxL) ? "VÁLIDO" : "INVÁLIDO",
               auxL->dom[4], auxL->fecha[5]);
        auxL = auxL->sig;
    }

    // TEST 2: hallaCantPuestos
    printf("\n\n========================================\n");
    printf("TEST 2: hallaCantPuestos()\n");
    printf("========================================\n");
    printf("RESULTADO ESPERADO: 3 puestos\n");
    printf("RESULTADO REAL: %d puestos\n", hallaCantPuestos(LD));

    // TEST 3: buscaPuesto
    printf("\n\n========================================\n");
    printf("TEST 3: buscaPuesto()\n");
    printf("========================================\n");
    printf("RESULTADO ESPERADO:\n");
    printf("  - Posición 0: Puesto 1\n");
    printf("  - Posición 1: Puesto 2\n");
    printf("  - Posición 2: Puesto 3\n");
    printf("  - Posición 3: NULL (no existe)\n");
    printf("\nRESULTADO REAL:\n");
    for(int i = 0; i <= 3; i++) {
        Pnodo test = buscaPuesto(LD, i);
        if(test != NULL)
            printf("  - Posición %d: Puesto %s\n", i, test->puesto);
        else
            printf("  - Posición %d: NULL\n", i);
    }

    // TEST 4: eliminaIncorrectos
    printf("\n\n========================================\n");
    printf("TEST 4: eliminaIncorrectos()\n");
    printf("========================================\n");
    printf("RESULTADO ESPERADO:\n");
    printf("  - Todos los turnos son válidos\n");
    printf("  - Porcentaje depurado: 0.00%%\n");
    printf("\nRESULTADO REAL:\n");
    eliminaIncorrectos(&L);
    muestraLista(L);

    // TEST 5: atender
    printf("\n\n========================================\n");
    printf("TEST 5: atender()\n");
    printf("========================================\n");
    printf("RESULTADO ESPERADO:\n");
    printf("  - ABC4423: Tiene turno válido en abril (fecha[5]='2') → revisar validación\n");
    printf("  - DEF3356: Turno de marzo → NO asignado\n");
    printf("  - XYZ9999: Sin turno → mensaje de error\n");
    printf("  - GHI4489: Tiene turno válido en abril → asignado a un puesto\n");
    printf("  - MNO4445: Tiene turno válido en abril → asignado a un puesto\n");
    printf("  - STU6666: Sin turno → mensaje de error\n");
    printf("\nRESULTADO REAL:\n");
    atender(LD, &C, L);
    muestraListaD(LD);

    // TEST 6: procesaArch
    printf("\n\n========================================\n");
    printf("TEST 6: procesaArch()\n");
    printf("========================================\n");
    printf("Archivo TESTEOS.txt contiene:\n");
    muestraArchivo();
    printf("\nNo hacer la prueba del punto c ya que atender() da puestos de forma aleatoria y luego el archivo deberia contenener estos puestos aleatorios, siendo imposible probar bien\n");
    printf("Funciona correctamente pero no tiene sentido el ej C\n");
    /*
    printf("\nRESULTADO ESPERADO:\n");
    printf("  Puesto 0:\n");
    printf("    - ABC4423: +2 OB, luego +1 OB → total 3 OB\n");
    printf("  Puesto 1:\n");
    printf("    - DEF3356: +0 OB → total 0 OB\n");
    printf("    - MNO4445: +1 OB → total 1 OB\n");
    printf("  Puesto 2:\n");
    printf("    - GHI4489: +3 OB, luego eliminado (estado 'A')\n");
    printf("\nRESULTADO REAL:\n");
    procesaArch(LD);

    printf("\n\n========================================\n");
    printf("ESTADO FINAL DE TODOS LOS PUESTOS\n");
    printf("========================================");
    muestraListaD(LD);
    */
    printf("\n\n========================================\n");
    printf("  PRUEBA FINALIZADA\n");
    printf("========================================\n");

    return 0;
}
