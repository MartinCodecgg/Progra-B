#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colas.h"
#define ST7 8
#define ST5 6
#define ST30 31
#define MES 7

typedef struct nodito{
    char pat[ST7], hora[ST5];
    unsigned int fecha, taHoras, taMin, trHoras, trMin;
    struct nodito *sig;
} nodito;

typedef nodito * SubLista;

typedef struct nodoD {
    char cod[ST5], nom[ST30], apel[ST30], estudiante;
    struct nodoD * sig, *ant;
    SubLista sub;
} nodoD;

typedef nodoD * Pnodo;

typedef struct {
    Pnodo pri, ult;
} TListaD;

typedef struct{
    char pat[ST7], hora[ST5];
    unsigned int fecha;
} TRmulta;

// ==================== FUNCIONES DEL CÓDIGO ORIGINAL ====================

Pnodo buscaAgente(TListaD LD, char cod[ST5]) {
    Pnodo actD = LD.pri;
    while(actD != NULL && strcmp(cod,actD->cod) < 0) //si busco por < o > debo preguntar luego si realmente lo encontre
        actD = actD->sig;
    return (actD != NULL && strcmp(actD->cod,cod) == 0) ? actD : NULL;
}

unsigned int hallaMes(unsigned int fecha) {
    unsigned int array[] = {31,28,31,30,31,30,31,31,30,31,30,31}, i = 0, acum = array[0];
    while(i<11 && fecha > acum) { //debe ser mayor, al igual que la busqueda ordenada
        acum += array[i];           //acum debe empezar con 31, sino hago una iteracion de mas, ademas devolvera avanzara cuando no tiene que avanzar
        i++;
    }
    return i+1; //siendo i+1 el mes en cuestion
}

void insertaMulta(TListaD LD, TElementoC elem) {
    Pnodo Pagente;
    SubLista actS,antS = NULL, new;
    new = (SubLista) malloc(sizeof(nodito));
    strcpy(new->pat,elem.pat);
    new->fecha = elem.fecha;
    strcpy(new->hora, elem.hora);
    new->taHoras = elem.tp / 60;
    new->taMin = elem.tp % 60;
    new->trHoras = elem.tr / 60;
    new->trMin = elem.tr % 60;
    Pagente = buscaAgente(LD,elem.cod);
    if(Pagente != NULL) {
        actS = Pagente->sub;
        while(actS != NULL && strcmp(elem.pat,actS->pat) > 0) {
            antS = actS;
            actS = actS->sig;
        }
        new->sig = actS;
        if(actS == Pagente->sub)
            Pagente->sub = new;
        else
            antS->sig = new;
    }
}

void generaMultas(TListaD LD, char AG[ST5], unsigned int k) {
    FILE *arch = fopen("MULTAS.dat","wb");
    Pnodo Pagente;
    unsigned int contMultas = 0;
    SubLista actS;
    TRmulta reg;

    if(arch == NULL)
        printf("Error al crear el archivo");
    else {
        Pagente = buscaAgente(LD,AG);
        if(Pagente) {
            actS = Pagente->sub;
            while(actS != NULL) {
                contMultas++;
                if(hallaMes(actS->fecha) % 2 == 0 && (strcmp(actS->hora,"12:00") < 0 || strcmp(actS->hora,"18:00") > 0)) {
                    strcpy(reg.pat,actS->pat);
                    strcpy(reg.hora,actS->hora);
                    reg.fecha = actS->fecha;
                    fwrite(&reg,sizeof(TRmulta),1,arch);
                }
                actS = actS->sig;
            }
            fclose(arch);
            if(contMultas > k && Pagente->estudiante == 'S')
                printf("Al agente le corresponde la bonificacion del 15%%\n");
        }
    }
}

void procesaC(TListaD LD, TCola *C) {
    TElementoC elem, cent;
    strcpy(cent.cod,"ZZZZZ");
    poneC(C,cent);
    sacaC(C,&elem);
    while(strcmp(elem.cod,cent.cod) != 0) {
        if(elem.tp < elem.tr && hallaMes(elem.fecha) == MES)
            insertaMulta(LD,elem);
            //printf("aa");
        else
            poneC(C,elem);
        sacaC(C,&elem);
        printf("itera\n");
    }
}

void elimina(TListaD *LD, char x[]) {
    Pnodo Pagente;
    SubLista antS = NULL, actS, elim;
    Pagente = buscaAgente(*LD, x);
    if(Pagente != NULL) {
        actS = Pagente->sub;
        while(actS != NULL && strcmp(actS->pat,"AF") < 0) {
            antS = actS;
            actS = actS->sig;
        } //aqui un while porque puede venir mas de una
        while(actS != NULL && actS->pat[0] == 'A' && actS->pat[1] == 'F') { //Nada afirma que al menos tiene una multa, asi que mejor preguntar que actS != NULL en el while sino puede ocurrir SEGMENTATION FAULT
            elim = actS;
            if(actS == Pagente->sub)
                Pagente->sub = Pagente->sub->sig; //Si el unico queda apuntando a NULL, si es la cabeza y no es el unico sub queda apuntando al siguiente
            else
                antS->sig = actS->sig;
            actS = actS->sig;
            free(elim);
        }
        if(Pagente->sub == NULL) {
            if(LD->pri == LD->ult)
                LD->pri = LD->ult = NULL;
            else {
                if(Pagente == LD->pri) {
                    Pagente->sig->ant = NULL;
                    LD->pri = Pagente->sig;
                }
                else
                    if(Pagente == LD->ult) {
                        Pagente->ant->sig = NULL;
                        LD->ult = Pagente->ant;
                    }
                    else {
                        Pagente->ant->sig = Pagente->sig;
                        Pagente->sig->ant = Pagente->ant;
                    }
            }
            free(Pagente);
        }
    }
    else
        printf("El agente ingresado no existe");
}

// OLD MAIN (para checkear)
/*
int main() {
    TListaD LD;
    unsigned int k;
    TCola C;
    char AG[ST5], x[ST5];
    //cargaC(&C), cargaLD(&LD);
    procesaC(LD,&C);
    printf("Ingrese k y AG\n");
    scanf(" %d %s",&k,AG);
    generaMultas(LD,AG,k);
    printf("Ingrese X");
    scanf(" %s",x);
    elimina(&LD,x);
    return 0;
}
*/

// ==================== FUNCIONES AUXILIARES DE CARGA Y VISUALIZACIÓN ====================

void inicializaLD(TListaD *LD) {
    LD->pri = LD->ult = NULL;
}

//void insertaAgenteOrdenado(TListaD *LD, char cod[ST5], char nom[ST30], char apel[ST30], char estudiante) {
void insertaAgenteOrdenado(TListaD *LD, char cod[], char nom[], char apel[], char estudiante) {
    Pnodo nuevo = (Pnodo)malloc(sizeof(nodoD));
    strncpy(nuevo->cod, cod, ST5-1);
    nuevo->cod[ST5-1] = '\0';
    strcpy(nuevo->nom, nom);
    strcpy(nuevo->apel, apel);
    nuevo->estudiante = estudiante;
    nuevo->sub = NULL;
    nuevo->sig = nuevo->ant = NULL;

    if(LD->pri == NULL) {
        LD->pri = LD->ult = nuevo;
    } else {
        Pnodo act = LD->pri, ant = NULL;
        // Lista DESCENDENTE: avanzar mientras cod < act->cod
        while(act != NULL && strcmp(cod, act->cod) < 0) {
            ant = act;
            act = act->sig;
        }
        if(ant == NULL) { // Insertar al principio
            nuevo->sig = LD->pri;
            LD->pri->ant = nuevo;
            LD->pri = nuevo;
        } else if(act == NULL) { // Insertar al final
            ant->sig = nuevo;
            nuevo->ant = ant;
            LD->ult = nuevo;
        } else { // Insertar en medio
            nuevo->sig = act;
            nuevo->ant = ant;
            ant->sig = nuevo;
            act->ant = nuevo;
        }
    }
}

//void insertaMultaEnAgente(Pnodo agente, char pat[ST7], unsigned int fecha, char hora[ST5]
                        //unsigned int taHoras, unsigned int taMin, unsigned int trHoras, unsigned int trMin) {
void insertaMultaEnAgente(Pnodo agente, char pat[], unsigned int fecha, char hora[],
                          unsigned int taHoras, unsigned int taMin, unsigned int trHoras, unsigned int trMin) {
    SubLista nuevo = (SubLista)malloc(sizeof(nodito));
    strcpy(nuevo->pat, pat);
    nuevo->fecha = fecha;
    strcpy(nuevo->hora, hora);
    nuevo->taHoras = taHoras;
    nuevo->taMin = taMin;
    nuevo->trHoras = trHoras;
    nuevo->trMin = trMin;
    nuevo->sig = NULL;

    if(agente->sub == NULL) {
        agente->sub = nuevo;
    } else {
        SubLista act = agente->sub, ant = NULL;
        while(act != NULL && strcmp(pat, act->pat) > 0) {
            ant = act;
            act = act->sig;
        }
        if(ant == NULL) { // Insertar al principio
            nuevo->sig = agente->sub;
            agente->sub = nuevo;
        } else { // Insertar después de ant
            nuevo->sig = act;
            ant->sig = nuevo;
        }
    }
}

void cargaDatosC(TCola *C) {
    TElementoC elem;
    IniciaC(C);

    // Elemento 1: SÍ se debe insertar (tp < tr y mes == 7)
    strcpy(elem.cod, "A0001");
    strcpy(elem.pat, "XY1234");
    elem.fecha = 200;  // Julio
    strcpy(elem.hora, "15:00");
    elem.tp = 60;
    elem.tr = 90;
    poneC(C, elem);

    // Elemento 2: NO se debe insertar (tp >= tr, no cumple primera condición)
    strcpy(elem.cod, "A0002");
    strcpy(elem.pat, "ZZ9999");
    elem.fecha = 210;  // Julio
    strcpy(elem.hora, "16:00");
    elem.tp = 120;
    elem.tr = 90;
    poneC(C, elem);

    // Elemento 3: NO se debe insertar (mes != 7, aunque tp < tr)
    strcpy(elem.cod, "A0003");
    strcpy(elem.pat, "WW5555");
    elem.fecha = 150;  // Mayo
    strcpy(elem.hora, "11:00");
    elem.tp = 45;
    elem.tr = 80;
    poneC(C, elem);

    // Elemento 4: SÍ se debe insertar (tp < tr y mes == 7)
    strcpy(elem.cod, "A0001");
    strcpy(elem.pat, "BB8888");
    elem.fecha = 195;  // Julio
    strcpy(elem.hora, "10:00");
    elem.tp = 30;
    elem.tr = 45;
    poneC(C, elem);

    /*
    // Centinela
    TElementoC cent;
    strcpy(cent.cod, "ZZZZZ");
    poneC(C, cent);
    */
}

void cargaDatosLD(TListaD *LD) {
    // Lista DESCENDENTE: A0003, A0002, A0001

    // Agente A0003 - Estudiante (primero en orden descendente)
    insertaAgenteOrdenado(LD, "A0003", "Carlos", "Gomez", 'S');
    Pnodo ag = LD->pri;
    insertaMultaEnAgente(ag, "AA1111", 31, "11:00", 2, 0, 1, 30);   // Enero (mes 1)
    insertaMultaEnAgente(ag, "AG2222", 200, "19:30", 1, 10, 0, 55); // Julio (mes 7)

    // Agente A0002 - No estudiante
    insertaAgenteOrdenado(LD, "A0002", "Maria", "Lopez", 'N');
    ag = LD->ult;
    insertaMultaEnAgente(ag, "AC7890", 60, "13:30", 1, 20, 2, 10);  // Febrero (mes 2)
    insertaMultaEnAgente(ag, "AF2345", 150, "16:00", 1, 45, 2, 30); // Mayo (mes 5) - EMPIEZA CON AF

    // Agente A0001 - Estudiante (último en orden descendente)
    insertaAgenteOrdenado(LD, "A0001", "Juan", "Perez", 'S');
    ag = LD->ult;
    insertaMultaEnAgente(ag, "AB1234", 45, "10:30", 1, 30, 2, 15);  // Febrero (mes 2)
    insertaMultaEnAgente(ag, "AE9999", 170, "13:00", 1, 20, 2, 0);  // Junio (mes 6) - NUEVA
    insertaMultaEnAgente(ag, "AF1111", 180, "14:00", 2, 0, 1, 45);  // Junio (mes 6) - EMPIEZA CON AF
    insertaMultaEnAgente(ag, "AF5678", 120, "09:00", 0, 45, 1, 30); // Abril (mes 4) - EMPIEZA CON AF
    insertaMultaEnAgente(ag, "AF9999", 190, "11:00", 1, 10, 1, 50); // Julio (mes 7) - EMPIEZA CON AF
    insertaMultaEnAgente(ag, "AG1234", 210, "20:00", 1, 15, 3, 0);  // Julio (mes 7)
    insertaMultaEnAgente(ag, "AI9012", 220, "15:00", 1, 30, 2, 15); // Agosto (mes 8)
}

void mostrarLD(TListaD LD) {
    printf("\n========== LISTA DE AGENTES Y MULTAS ==========\n");
    Pnodo act = LD.pri;
    if(act == NULL) {
        printf("Lista vacía\n");
        return;
    }

    while(act != NULL) {
        printf("\nCODIGO: %s | NOMBRE: %s %s | ESTUDIANTE: %c\n",
               act->cod, act->nom, act->apel, act->estudiante);
        printf("  Multas:\n");

        SubLista actS = act->sub;
        if(actS == NULL) {
            printf("    (sin multas)\n");
        } else {
            while(actS != NULL) {
                printf("    - Patente: %s | Fecha: %u | Hora: %s | TA: %u:%02u | TR: %u:%02u\n",
                       actS->pat, actS->fecha, actS->hora,
                       actS->taHoras, actS->taMin, actS->trHoras, actS->trMin);
                actS = actS->sig;
            }
        }
        act = act->sig;
    }
    printf("================================================\n");
}

void mostrarArchivoBinario() {
    FILE *arch = fopen("MULTAS.dat", "rb");
    TRmulta reg;

    printf("\n========== CONTENIDO ARCHIVO MULTAS.DAT ==========\n");
    if(arch == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    int count = 0;
    while(fread(&reg, sizeof(TRmulta), 1, arch) == 1) {
        count++;
        printf("Registro %d - Patente: %s | Fecha: %u | Hora: %s\n",
               count, reg.pat, reg.fecha, reg.hora);
    }

    if(count == 0) {
        printf("Archivo vacío\n");
    }

    fclose(arch);
    printf("==================================================\n");
}

// ==================== PROGRAMA DE PRUEBAS ====================

int main() {
    TListaD LD;
    TCola C;

    printf("\n");
    printf("==================================================================\n");
    printf("==    SISTEMA DE PRUEBAS - GESTIÓN DE MULTAS DE TRÁNSITO        ==\n");
    printf("==================================================================\n");

    // ==================== PRUEBA 1: CARGA INICIAL ====================
    printf("\n[PRUEBA 1] CARGA INICIAL DE DATOS\n");
    printf("----------------------------------\n");
    inicializaLD(&LD);
    cargaDatosLD(&LD);
    printf("Lista de agentes cargada\n");
    mostrarLD(LD);

    // ==================== PRUEBA 2: BUSCAR AGENTE ====================
    printf("\n[PRUEBA 2] BÚSQUEDA DE AGENTES\n");
    printf("-------------------------------\n");
    printf("Estado inicial: Lista con 3 agentes (A0001, A0002, A0003)\n");

    printf("\nBuscando agente 'A0002'...\n");
    Pnodo encontrado = buscaAgente(LD, "A0002");
    printf("Resultado esperado: Encontrar agente A0002 (Maria Lopez)\n");
    printf("Resultado real: %s\n",
           encontrado != NULL ? "Agente encontrado" : "Agente NO encontrado");
    if(encontrado != NULL) {
        printf("  Datos: %s %s - Código: %s\n", encontrado->nom, encontrado->apel, encontrado->cod);
    }

    printf("\nBuscando agente 'A9999' (no existe)...\n");
    encontrado = buscaAgente(LD, "A9999");
    printf("Resultado esperado: NULL (no encontrado)\n");
    printf("Resultado real: %s\n",
           encontrado == NULL ? "Correctamente NULL" : "Error: devolvió un agente");

    // ==================== PRUEBA 3: HALLAR MES ====================
    printf("\n[PRUEBA 3] CÁLCULO DE MES POR FECHA JULIANA\n");
    printf("--------------------------------------------\n");
    printf("Fecha  45 -> Esperado: mes 2 (Febrero)  | Real: mes %u %s\n",
           hallaMes(45), hallaMes(45) == 2 ? "OK" : "ERR");
    printf("Fecha 120 -> Esperado: mes 4 (Abril)    | Real: mes %u %s\n",
           hallaMes(120), hallaMes(120) == 4 ? "OK" : "ERR");
    printf("Fecha 210 -> Esperado: mes 7 (Julio)    | Real: mes %u %s\n",
           hallaMes(210), hallaMes(210) == 7 ? "OK" : "ERR");

    // ==================== PRUEBA 4: PROCESAR COLA ====================
    printf("\n[PRUEBA 4] PROCESAMIENTO DE COLA (procesaC)\n");
    printf("--------------------------------------------\n");
    printf("Estado inicial: Lista con agentes cargados\n");
    printf("Cola con 4 elementos + centinela:\n");
    printf("  1. XY1234 - A0001 - Fecha:200 (Jul) - tp:60 < tr:90   -> INSERTAR (bien)\n");
    printf("  2. ZZ9999 - A0002 - Fecha:210 (Jul) - tp:120 >= tr:90 -> NO insertar\n");
    printf("  3. WW5555 - A0003 - Fecha:150 (May) - tp:45 < tr:80   -> NO insertar (mes != 7)\n");
    printf("  4. BB8888 - A0001 - Fecha:195 (Jul) - tp:30 < tr:45   -> INSERTAR (bien)\n\n");

    printf("Condición: Insertar si tp < tr Y mes == 7 (Julio)\n");
    printf("Resultado esperado: 2 multas insertadas (XY1234 y BB8888 al agente A0001)\n\n");

    cargaDatosC(&C);
    printf("Cola cargada con datos de prueba\n");

    printf("\nAgente A0001 ANTES de procesaC:\n");
    Pnodo ag_antes = buscaAgente(LD, "A0001");
    if(ag_antes != NULL) {
        SubLista sub = ag_antes->sub;
        int count = 0;
        while(sub != NULL) {
            count++;
            printf("  %d. %s\n", count, sub->pat);
            sub = sub->sig;
        }
        printf("  Total multas: %d\n", count);
    }

    printf("\nEjecutando procesaC...\n");
    procesaC(LD, &C);

    printf("\nAgente A0001 DESPUÉS de procesaC:\n");
    Pnodo ag_despues = buscaAgente(LD, "A0001");
    if(ag_despues != NULL) {
        SubLista sub = ag_despues->sub;
        int count = 0;
        while(sub != NULL) {
            count++;
            printf("  %d. %s", count, sub->pat);
            if(strcmp(sub->pat, "XY1234") == 0 || strcmp(sub->pat, "BB8888") == 0)
                printf(" (bien) (nueva)");
            printf("\n");
            sub = sub->sig;
        }
        printf("  Total multas: %d (esperado: 6 = 4 originales + 2 nuevas)\n", count);
    }

    // ==================== PRUEBA 5: GENERAR MULTAS ====================
    printf("\n[PRUEBA 5] GENERACIÓN DE ARCHIVO MULTAS.DAT\n");
    printf("--------------------------------------------\n");
    printf("Estado inicial: Agente A0001 con 4 multas\n");
    printf("Parámetros: k=2 (si tiene más de 2 multas y es estudiante -> bonificación)\n\n");

    printf("Multas del agente A0001:\n");
    printf("  1. AB1234 - Fecha:  45 (Feb/par) - Hora: 10:30 (antes 12:00) -> INCLUIR (bien)\n");
    printf("  2. AG5678 - Fecha: 180 (Jun/par) - Hora: 14:00 (12:00-18:00) -> NO incluir\n");
    printf("  3. AI9012 - Fecha: 210 (Jul/impar)- Hora: 20:00              -> NO incluir\n");
    printf("  4. AH3456 - Fecha: 120 (Abr/par) - Hora: 09:00 (antes 12:00) -> INCLUIR (bien)\n\n");

    printf("Resultado esperado:\n");
    printf("  - Archivo con 2 registros (AB1234 y AH3456)\n");
    printf("  - Mensaje de bonificación (4 multas > k=2 y es estudiante)\n\n");

    printf("Ejecutando generaMultas...\n");
    generaMultas(LD, "A0001", 2);
    printf("\nResultado real:\n");
    mostrarArchivoBinario();

// ==================== PRUEBA 6: ELIMINAR MULTAS ====================
printf("\n[PRUEBA 6] ELIMINACIÓN DE MULTAS (patentes que empiezan con AF)\n");
printf("---------------------------------------------------------------\n");
printf("Estado inicial: Agente A0001 con varias multas\n");
printf("Resultado esperado: Eliminar AF1111, AF5678, AF9999 (quedan AB, AE, AG, AI)\n\n");

printf("Lista ANTES de eliminar:\n");
Pnodo ag = buscaAgente(LD, "A0001");
SubLista sub;
if(ag != NULL) {
    sub = ag->sub;
    while(sub != NULL) {
        printf("  - %s %s\n", sub->pat,
               (sub->pat[0] == 'A' && sub->pat[1] == 'F') ? "(AF - será eliminada)" : "");
        sub = sub->sig;
    }
}

elimina(&LD, "A0001");

printf("\nLista DESPUÉS de eliminar:\n");
ag = buscaAgente(LD, "A0001");
if(ag != NULL && ag->sub != NULL) {
    sub = ag->sub;
    int count = 0;
    while(sub != NULL) {
        count++;
        printf("  - %s %s\n", sub->pat,
               (sub->pat[0] == 'A' && sub->pat[1] == 'F') ? "ERR" : "OK");
        sub = sub->sig;
    }
    printf("Total multas restantes: %d (esperado: 6)\n", count);
} else {
    printf("  (sin multas o agente eliminado)\n");
}


    // ==================== PRUEBA 7: ELIMINAR AGENTE SIN MULTAS ====================
    printf("\n[PRUEBA 7] ELIMINACIÓN DE AGENTE SIN MULTAS\n");
    printf("--------------------------------------------\n");

    // Crear agente temporal sin multas
    insertaAgenteOrdenado(&LD,"A0004","Pedro","Martinez",'N');
    printf("Estado inicial: Agente A0004 agregado sin multas\n");
    mostrarLD(LD);

    printf("\nEliminando multas del agente A0004...\n");
    elimina(&LD, "A0004");
    printf("Resultado esperado: Agente A0004 eliminado de la lista\n\n");

    printf("Estado final de la lista:\n");
    mostrarLD(LD);

    // ==================== RESUMEN ====================
    printf("\n================================================================\n");
    printf("==                      PRUEBAS COMPLETADAS                     ==\n");
    printf("================================================================\n");

    return 0;
}
