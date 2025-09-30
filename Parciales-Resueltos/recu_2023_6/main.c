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

// Función para cargar la lista circular LC con datos de coches
void cargaLC(TListaC *LC) { // IA
    TListaC nuevo, ultimo;

    // Inicializar la lista circular (nodo fantasma)
    *LC = (TListaC) malloc(sizeof(nodoC));
    (*LC)->sig = *LC;  // Apunta a sí mismo
    ultimo = *LC;

    printf("=== CARGA DE COCHES (AUTOMÁTICA) ===\n");

    // Coche 1
    nuevo = (TListaC) malloc(sizeof(nodoC));
    strcpy(nuevo->patente, "ABC123");
    nuevo->vip = 'S';
    strcpy(nuevo->radio, "U");
    nuevo->cantP = 4;
    nuevo->libre = 'S';
    nuevo->sig = *LC;
    ultimo->sig = nuevo;
    ultimo = nuevo;
    printf("Cargado: %s - VIP:%c - Radio:%s - Pas:%d - Libre:%c\n",
           nuevo->patente, nuevo->vip, nuevo->radio, nuevo->cantP, nuevo->libre);

    // Coche 2
    nuevo = (TListaC) malloc(sizeof(nodoC));
    strcpy(nuevo->patente, "DEF456");
    nuevo->vip = 'N';
    strcpy(nuevo->radio, "R");
    nuevo->cantP = 3;
    nuevo->libre = 'S';
    nuevo->sig = *LC;
    ultimo->sig = nuevo;
    ultimo = nuevo;
    printf("Cargado: %s - VIP:%c - Radio:%s - Pas:%d - Libre:%c\n",
           nuevo->patente, nuevo->vip, nuevo->radio, nuevo->cantP, nuevo->libre);

    // Coche 3
    nuevo = (TListaC) malloc(sizeof(nodoC));
    strcpy(nuevo->patente, "GHI789");
    nuevo->vip = 'S';
    strcpy(nuevo->radio, "I");
    nuevo->cantP = 2;
    nuevo->libre = 'S';
    nuevo->sig = *LC;
    ultimo->sig = nuevo;
    ultimo = nuevo;
    printf("Cargado: %s - VIP:%c - Radio:%s - Pas:%d - Libre:%c\n",
           nuevo->patente, nuevo->vip, nuevo->radio, nuevo->cantP, nuevo->libre);

    // Coche 4
    nuevo = (TListaC) malloc(sizeof(nodoC));
    strcpy(nuevo->patente, "JKL012");
    nuevo->vip = 'N';
    strcpy(nuevo->radio, "U");
    nuevo->cantP = 4;
    nuevo->libre = 'S';
    nuevo->sig = *LC;
    ultimo->sig = nuevo;
    ultimo = nuevo;
    printf("Cargado: %s - VIP:%c - Radio:%s - Pas:%d - Libre:%c\n",
           nuevo->patente, nuevo->vip, nuevo->radio, nuevo->cantP, nuevo->libre);

    // Coche 5
    nuevo = (TListaC) malloc(sizeof(nodoC));
    strcpy(nuevo->patente, "MNO345");
    nuevo->vip = 'S';
    strcpy(nuevo->radio, "URI");
    nuevo->cantP = 10;
    nuevo->libre = 'S';
    nuevo->sig = *LC;
    ultimo->sig = nuevo;
    ultimo = nuevo;
    printf("Cargado: %s - VIP:%c - Radio:%s - Pas:%d - Libre:%c\n",
           nuevo->patente, nuevo->vip, nuevo->radio, nuevo->cantP, nuevo->libre);

    printf("\nLista de coches cargada exitosamente.\n\n");
}

// Función para mostrar la lista circular LC
void muestraLC(TListaC LC) { // IA
    TListaC act;
    int cont = 0;

    if(LC == NULL || LC->sig == LC) {
        printf("La lista de coches está vacía.\n");
        return;
    }

    printf("\n=== LISTA DE COCHES (CIRCULAR) ===\n");
    printf("%-10s %-5s %-8s %-10s %-8s\n", "Patente", "VIP", "Radio", "Pasajeros", "Libre");
    printf("---------------------------------------------------\n");

    act = LC->sig;
    while(act != LC) {
        printf("%-10s %-5c %-8s %-10d %-8c\n",
               act->patente,
               act->vip,
               act->radio,
               act->cantP,
               act->libre);
        cont++;
        act = act->sig;
    }

    printf("---------------------------------------------------\n");
    printf("Total de coches: %d\n\n", cont);
}

// Función para mostrar la lista simple enlazada L
void muestraL(TListaL L) { // IA
    TListaL act;
    TElementoC viaje;
    int contCoches = 0, contViajes;

    if(L == NULL) {
        printf("La lista de viajes asignados está vacía.\n");
        printf("Puede mostrar vacia si esta linea esta comentada actC->libre = 'N'; en procesaArch() (comentada para probar mayorElim)\n");
        return;
    }

    printf("\n=== LISTA DE VIAJES ASIGNADOS ===\n");

    act = L;
    while(act != NULL) {
        printf("\n--- Coche: %s ---\n", act->patente);

        if(VaciaC(act->C)) {
            printf("  Sin viajes asignados.\n");
        } else {
            printf("  %-5s %-8s %-10s\n", "VIP", "Radio", "Pasajeros");
            printf("  ------------------------------\n");

            contViajes = 0;
            // Recorrer la cola sin destruirla
            TCola tempC;
            IniciaC(&tempC);

            while(!VaciaC(act->C)) {
                sacaC(&(act->C), &viaje);
                printf("  %-5c %-8s %-10d\n",
                       viaje.vip,
                       viaje.radio,
                       viaje.cantP);
                poneC(&tempC, viaje);
                contViajes++;
            }

            // Restaurar la cola original
            while(!VaciaC(tempC)) {
                sacaC(&tempC, &viaje);
                poneC(&(act->C), viaje);
            }

            printf("  Total viajes: %d\n", contViajes);
        }

        contCoches++;
        act = act->sig;
    }

    printf("\n-----------------------------------\n");
    printf("Total de coches con viajes: %d\n\n", contCoches);
}

// Función auxiliar para mostrar ambas listas
void muestraAmbas(TListaC LC, TListaL L) { // IA
    muestraLC(LC);
    muestraL(L);
}

// Función para mostrar el contenido del archivo Viajes.dat
void muestraArchivo() { // IA
    FILE *arch = fopen("Viajes.dat", "rb");
    TViaje viaje;
    int cont = 0;

    if(arch == NULL) {
        printf("Error: No se pudo abrir el archivo Viajes.dat\n");
        return;
    }

    printf("\n=== CONTENIDO DEL ARCHIVO VIAJES.DAT ===\n");
    printf("%-8s %-8s %-10s %-12s\n", "Num", "VIP", "Radio", "Pasajeros");
    printf("------------------------------------------\n");

    while(fread(&viaje, sizeof(TViaje), 1, arch) == 1) {
        cont++;
        printf("%-8d %-8c %-10s %-12d", cont, viaje.vip, viaje.radio, viaje.cantP);

        if(viaje.cantP == 0) {
            printf(" <-- ELIMINACIÓN");
        }
        printf("\n");
    }

    printf("------------------------------------------\n");
    printf("Total de viajes en archivo: %d\n\n", cont);

    fclose(arch);
}

// Función para crear archivo de prueba con viajes
void creaArchivoPrueba() { // IA
    FILE *arch = fopen("Viajes.dat", "wb");
    TViaje viajes[10];
    int i;

    if(arch == NULL) {
        printf("Error al crear archivo de prueba\n");
        return;
    }

    // Viaje 1 - Compatible con ABC123 (VIP, U, 3 pas)
    viajes[0].cantP = 3;
    viajes[0].vip = 'S';
    strcpy(viajes[0].radio, "U");

    // Viaje 2 - Compatible con DEF456 (No VIP, R, 2 pas)
    viajes[1].cantP = 2;
    viajes[1].vip = 'N';
    strcpy(viajes[1].radio, "R");

    // Viaje 3 - Compatible con GHI789 (VIP, I, 2 pas)
    viajes[2].cantP = 2;
    viajes[2].vip = 'S';
    strcpy(viajes[2].radio, "I");

    // Viaje 4 - Compatible con JKL012 (No VIP, U, 4 pas)
    viajes[3].cantP = 4;
    viajes[3].vip = 'N';
    strcpy(viajes[3].radio, "U");

    // Viaje 5 - Compatible con MNO345 (VIP, R, 1 pas)
    viajes[4].cantP = 1;
    viajes[4].vip = 'S';
    strcpy(viajes[4].radio, "R");

    // Viaje 6 - Eliminación: 0 pasajeros
    viajes[5].cantP = 0;
    viajes[5].vip = 'N';
    strcpy(viajes[5].radio, "U");

    // Viaje 7 - Otro viaje normal
    viajes[6].cantP = 3;
    viajes[6].vip = 'N';
    strcpy(viajes[6].radio, "R");

    // Viaje 8 - Eliminación: 0 pasajeros
    viajes[7].cantP = 0;
    viajes[7].vip = 'S';
    strcpy(viajes[7].radio, "I");

    // Viaje 9 - Viaje normal
    viajes[8].cantP = 2;
    viajes[8].vip = 'N';
    strcpy(viajes[8].radio, "U");

    // Viaje 10 - Eliminación: 0 pasajeros
    viajes[9].cantP = 0;
    viajes[9].vip = 'N';
    strcpy(viajes[9].radio, "R");

    for(i = 0; i < 10; i++) {
        fwrite(&viajes[i], sizeof(TViaje), 1, arch);
    }

    fclose(arch);
    printf("Archivo Viajes.dat creado con 10 viajes de prueba.\n\n");
}

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
    TElementoC reg;     //inicializar siempre estos puntos en NULL, porque la funcion de busqueda busca mientras L no sea NULL
    TListaL antL,actL,pL = NULL, new; //Mejor usar Pl y no pL, la catedra indica que es un puntero con la P mayuscula
    FILE * arch = fopen("Viajes.dat","rb");
    int OK; //variable que controla que no siga buscando si ya encontro un coche libre

    if (arch == NULL)
            printf("Error al abrir el archivo\n");
    else {
        while(fread(&reg,sizeof(TElementoC),1,arch) == 1) {
            OK = 0;
            actC = LC->sig;
            while(actC != LC && !OK){
                if(actC->libre == 'S') {
                    if(reg.cantP <= actC->cantP &&
                       !(reg.vip == 'S' && actC->vip == 'N') && strcmp(reg.radio,actC->radio) <= 0) {
                            OK = 1;
                            actC->libre = 'N'; //COMENTO ESTO PARA PROBAR EL PROGRAMA (probar funcion mayorElim)
                            //if(pL != NULL) //me ahorro un llamado innecesario a la funcion [PREGUNTAR SI HACERLO O NO]
                                buscaPat(*L,actC->patente,&pL);
                            if(pL == NULL) {
                                new = (TListaL) malloc(sizeof(nodo));
                                strcpy(new->patente,actC->patente);
                                IniciaC(&(new->C));
                                pL = new; // recordar en el caso de crear si pL es NULL debo al final asignarle el nodo creado, sino hace poneC con pL = NULL
                                if(*L == NULL || strcmp(new->patente,(*L)->patente) < 0) { //tener en cuenta que tanto L == NULL o *L == NULL son validos pero siempre debo preguntar por el nodo y no por el puntero al nodo
                                    new->sig = *L; //Recordar siempre cuando creo el nodo le asigno el siguiente NULL si es el primero
                                    *L = new;
                                }
                                else {
                                    actL = *L;
                                    while(actL != NULL && strcmp(actC->patente,actL->patente) > 0) {
                                        antL = actL;
                                        actL = actL->sig;
                                    }
                                    antL->sig = new; //En la insercion ordenada no debo preguntar nada fuera del while
                                    new->sig = actL;
                                }
                            }
                            poneC(&(pL->C),reg);
                       }
                       else //[PREGUNTAR SOBRE COMO INFORMAR]
                            printf("No se puedo asignar el viaje a la patente %s\n",actC->patente);
                }
                actC = actC->sig;
            }
            if(actC == LC)
                printf("Ningun coche puede aceptar el viaje solicitado\n");
        }
        fclose(arch);
    }
}

void mayorElim(TListaL L) {
    TListaL act;
    TElementoC elem, cent;
    cent.cantP = -1;
    char maxP[ST7];
    int cont, max = -1;
    if(L != NULL) {
        act = L;
        while(act != NULL) {
            cont = 0;
            poneC(&(act->C),cent);
            sacaC(&(act->C),&elem);
            while(elem.cantP != cent.cantP) {
                poneC(&(act->C),elem);
                sacaC(&(act->C),&elem);
                if(elem.cantP == 0)
                    cont++;
            }
            if(cont != 0 && cont >= max) { //descartar coches q no tengan eliminaciones, caso de que ninguno tenga
                max = cont;
                strcpy(maxP,act->patente);
            }
            act = act->sig;
        }
        if(max != -1)
            printf("El coche que tuvo la mayor cantidad de eliminaciones fue: %s con %d eliminaciones\n",maxP,cont); //muestra ABC... lo cual es correcto
        else
            printf("No hubo coches con viajes cancelados, PARA PROBAR LA FUNCION COMENTAR ESTA LINEA actC->libre = 'N'; en procesaArch()");
    }
}

void eliminaPat(TListaC *LC, TListaL *L, char pat[], TRvec vec[]) {
    TListaC actC,antC;
    TListaL actL,antL;
    TElementoC reg;
    int i;
    //ELIMINAR DE LA LISTA CIRCULAR
    antC = *LC; //recordar siempre para eliminar de la lista simple empiezo por el primero y ant es el ultimo
    actC = (*LC)->sig;
    while(actC != *LC && strcmp(actC->patente,pat) != 0) {
        antC = actC;
        actC = actC->sig;
    }
    if(*LC == (*LC)->sig) {//un solo nodo
        *LC = NULL;
        free(actC); //valido al no ser eliminacion sucesiva , free(*LC); mal porque termina apuntando a NULL
    }
    else {
        if(actC == *LC) {
            antC->sig = actC->sig;
            *LC = antC;
        }
        else
            antC->sig = actC->sig;
        free(actC);
    }

    for(i = 0; i<RADIOS; i++){
        vec[i].cantP = 0;
        vec[i].cantV = 0;
    }
    //ELIMINAR DE LA LISTA SIMPLE
    actL = *L;
    while(strcmp(pat,actL->patente) != 0) {
        antL = actL;
        actL = actL->sig;
    }
    while(!VaciaC(actL->C)) {
        sacaC(&(actL->C),&reg);
        vec[strlen(reg.radio) -1].cantP += reg.cantP;
        vec[strlen(reg.radio) -1].cantV++;
    }
    if(actL == *L)
        *L = (*L)->sig; //valido para el primero y el unico, porque es el primero le asigno NULL
    else
        antL->sig = actL->sig;
    free(actL);
}

int main() {
    TListaC LC = NULL;
    TListaL L = NULL;
    char p[ST7];
    TRvec vec[RADIOS];

    // === CODIGO IA PARA PROBAR ===

    // Cargar datos
    cargaLC(&LC);
    creaArchivoPrueba();
    muestraArchivo();

    // Validar carga
    if(LC == NULL || LC->sig == LC) {
        printf("Error: LC está vacía\n");
        return 1;
    }

    // Procesar archivo
    procesaArch(LC, &L);

    // Mostrar resultados
    printf("\n--- ESTADO DESPUÉS DEL PROCESAMIENTO ---\n");
    muestraAmbas(LC, L);

    // Probar mayorElim solo si L no es NULL
    if(L != NULL) {
        printf("\n--- BÚSQUEDA DE MAYOR ELIMINACIÓN ---\n");
        mayorElim(L);

        // Probar eliminaPat
        printf("\n\n--- ELIMINACIÓN DE PATENTE ---\n");
        printf("Ingrese la patente que desea eliminar\n");
        scanf(" %s", p);
        eliminaPat(&LC, &L, p,vec);

        printf("\n--- ESTADO FINAL ---\n");
        muestraAmbas(LC, L);
    } else {
        printf("L es NULL - No hay viajes asignados\n");
    }

    return 0;
}
