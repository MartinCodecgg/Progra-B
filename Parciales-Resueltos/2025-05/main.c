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

// ============= FUNCIONES DE CARGA DE DATOS DE PRUEBA (INTELIGENCIA ARTIFICIAL) =============

void cargaLS(TLista *LS) {
    // Inicializar la lista vacía
    *LS = NULL;

    // Productos de prueba ordenados por código
    TLista prod1, prod2, prod3, prod4, prod5;

    // Producto 1: A001
    prod1 = (TLista)malloc(sizeof(nodo));
    strcpy(prod1->cod, "A001");
    prod1->precio = 150.75;
    prod1->stock = 50.0;
    prod1->margen = 0.5;
    prod1->sub = NULL;

    // Agregar compras a la sublista de A001
    SubLista sub1 = (SubLista)malloc(sizeof(nodito));
    strcpy(sub1->fecha, "2025/01/15");
    sub1->cant = 30.0;
    sub1->precio = 100.50;
    sub1->sig = NULL;
    prod1->sub = sub1;

    SubLista sub2 = (SubLista)malloc(sizeof(nodito));
    strcpy(sub2->fecha, "2025/01/10");
    sub2->cant = 20.0;
    sub2->precio = 95.00;
    sub2->sig = prod1->sub;
    prod1->sub = sub2;

    // Producto 2: B123
    prod2 = (TLista)malloc(sizeof(nodo));
    strcpy(prod2->cod, "B123");
    prod2->precio = 225.00;
    prod2->stock = -10.0;  // Stock negativo para prueba
    prod2->margen = 0.5;
    prod2->sub = NULL;

    SubLista sub3 = (SubLista)malloc(sizeof(nodito));
    strcpy(sub3->fecha, "2025/01/20");
    sub3->cant = 15.0;
    sub3->precio = 150.00;
    sub3->sig = NULL;
    prod2->sub = sub3;

    // Producto 3: C456
    prod3 = (TLista)malloc(sizeof(nodo));
    strcpy(prod3->cod, "C456");
    prod3->precio = 89.99;
    prod3->stock = 100.0;
    prod3->margen = 0.5;
    prod3->sub = NULL;

    SubLista sub4 = (SubLista)malloc(sizeof(nodito));
    strcpy(sub4->fecha, "2025/01/18");
    sub4->cant = 100.0;
    sub4->precio = 59.99;
    sub4->sig = NULL;
    prod3->sub = sub4;

    // Producto 4: D789
    prod4 = (TLista)malloc(sizeof(nodo));
    strcpy(prod4->cod, "D789");
    prod4->precio = 450.00;
    prod4->stock = -5.0;  // Stock negativo
    prod4->margen = 0.5;
    prod4->sub = NULL;

    // Producto 5: E999
    prod5 = (TLista)malloc(sizeof(nodo));
    strcpy(prod5->cod, "E999");
    prod5->precio = 75.50;
    prod5->stock = 200.0;
    prod5->margen = 0.5;
    prod5->sub = NULL;

    // Enlazar la lista simple ordenada
    *LS = prod1;
    prod1->sig = prod2;
    prod2->sig = prod3;
    prod3->sig = prod4;
    prod4->sig = prod5;
    prod5->sig = NULL;
}

void cargaLD(TListaD *LD) {
    // Inicializar lista doble vacía
    LD->pri = LD->ult = NULL;

    // Agregar productos con stock negativo
    PnodoD nodo1, nodo2;

    // Producto B123 con stock negativo
    nodo1 = (PnodoD)malloc(sizeof(nodoD));
    strcpy(nodo1->cod, "B123");
    nodo1->stock = -10.0;
    nodo1->sig = NULL;
    nodo1->ant = NULL;

    // Producto D789 con stock negativo
    nodo2 = (PnodoD)malloc(sizeof(nodoD));
    strcpy(nodo2->cod, "D789");
    nodo2->stock = -5.0;
    nodo2->sig = NULL;
    nodo2->ant = nodo1;

    // Enlazar
    nodo1->sig = nodo2;

    LD->pri = nodo1;
    LD->ult = nodo2;
}

void cargaC(TCola *C) {
    IniciaC(C);

    // Crear elementos de compra para la cola
    TElementoC elem;

    // Compra 1: Producto A001
    strcpy(elem.cod, "A001");
    elem.cant = 5.0;
    poneC(C, elem);

    // Compra 2: Producto C456
    strcpy(elem.cod, "C456");
    elem.cant = 10.0;
    poneC(C, elem);

    // Compra 3: Producto A001 (otra vez)
    strcpy(elem.cod, "A001");
    elem.cant = 3.0;
    poneC(C, elem);

    // Compra 4: Producto E999
    strcpy(elem.cod, "E999");
    elem.cant = 8.0;
    poneC(C, elem);

    // Compra 5: Producto C456 (otra vez)
    strcpy(elem.cod, "C456");
    elem.cant = 15.0;
    poneC(C, elem);
}

// ============= FUNCIONES DE VISUALIZACIÓN (INTELIGENCIA ARTIFICIAL) =============

void mostrarSublista(SubLista sub) {
    SubLista actual = sub;
    int num = 1;

    if (actual == NULL) {
        printf("        Sin compras registradas\n");
        return;
    }

    printf("        Historial de compras:\n");
    while (actual != NULL) {
        printf("          %d) Fecha: %s | Cant: %.2f | Precio: $%.2f\n",
               num, actual->fecha, actual->cant, actual->precio);
        actual = actual->sig;
        num++;
    }
}

void mostrarLS(TLista LS) {
    TLista actual = LS;
    int num = 1;

    printf("\n========== LISTA SIMPLE DE PRODUCTOS (LS) ==========\n");

    if (actual == NULL) {
        printf("Lista vacía\n");
        return;
    }

    while (actual != NULL) {
        printf("\n--- Producto %d ---\n", num);
        printf("  Código: %s\n", actual->cod);
        printf("  Precio venta: $%.2f\n", actual->precio);
        printf("  Stock actual: %.2f\n", actual->stock);
        printf("  Margen: %.2f\n", actual->margen);
        mostrarSublista(actual->sub);

        actual = actual->sig;
        num++;
    }
    printf("\n====================================================\n");
}

void mostrarLD(TListaD LD) {
    PnodoD actual = LD.pri;
    int num = 1;

    printf("\n========== LISTA DOBLE DE STOCK NEGATIVO (LD) ==========\n");

    if (actual == NULL) {
        printf("Lista vacía (no hay productos con stock negativo)\n");
        printf("=========================================================\n");
        return;
    }

    printf("Productos con stock negativo:\n");
    while (actual != NULL) {
        printf("  %d) Código: %s | Stock: %.2f\n", num, actual->cod, actual->stock);
        actual = actual->sig;
        num++;
    }
    printf("=========================================================\n");
}

void mostrarC(TCola C) {
    printf("\n========== COLA DE COMPRAS (C) ==========\n");

    if (VaciaC(C)) {
        printf("Cola vacía\n");
        printf("=========================================\n");
        return;
    }

    printf("Elementos en la cola:\n");
    // Nota: Esta función solo muestra si hay elementos,
    // pero no los puede mostrar sin sacarlos (ya que sacaC los elimina)
    printf("(La cola contiene elementos de compra)\n");
    printf("=========================================\n");
}

// ============= PROGRAMA DE PRUEBA (INTELIGENCIA ARTIFICIAL)=============

void crearArchivoPrueba() {
    FILE *arch = fopen("PROVEEN.txt", "wt");

    if (arch == NULL) {
        printf("Error al crear archivo de prueba\n");
        return;
    }

    // Formato: fecha(AAAA/MM/DD) codigo cantidad precio
    // Fechas válidas: mes 04 (abril), año 2025
    fprintf(arch, "2025/04/10 A001 25.00 105.00\n");
    fprintf(arch, "2025/04/15 B123 30.00 155.00\n");  // B123 tiene stock negativo, debería eliminarse de LD
    fprintf(arch, "2025/04/20 C456 50.00 62.00\n");
    fprintf(arch, "2025/04/05 F888 40.00 85.50\n");   // Producto nuevo
    fprintf(arch, "2025/01/12 A001 15.00 100.00\n");  // Fecha no válida (mes != 04)
    fprintf(arch, "2024/04/18 E999 10.00 50.00\n");   // Fecha no válida (año != 2025)

    fclose(arch);
    printf("\nArchivo PROVEEN.txt creado con datos de prueba.\n");
}

// =========== FUNCIONES PROPIAS DEL PARCIAL ===========

void eliminaLD(TListaD *LD, char cod[]) {
    PnodoD actD, elim;
    actD = LD->pri; //No pongo el if de que si es distinto de NULL porque en teoria llamo a la funcion siempre teniendo algo que eliminar
    while(actD != NULL) {
        if(strcmp(cod,actD->cod) == 0) {
            if(LD->pri->sig == NULL) {
                elim = actD;
                actD = NULL; //le doy a elim, act y luego le asigno NULL para que despues al liberar quede apuntando a memoria basura y entre al while (porque sera != NULL) y provoque comportamiento indefinido
                LD->pri = LD->ult = NULL;
                free(elim);
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
                        LD->ult->ant->sig = NULL;
                        LD->ult = LD->ult->ant;
                    }
                    else {
                        elim = actD;
                        actD->ant->sig = actD->sig;
                        actD->sig->ant = actD->ant;
                    }
                }
                actD = actD->sig;
                free(elim);
            }
        }
        else
            actD = actD->sig;
    }
}

void insertaSublista(TLista *p, char fecha[], float cant, float precio) {
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
    if(actL != NULL && strcmp(cod,actL->cod) == 0) {
        if(actL->stock < 0)
            tieneStockNegativo = 1;
        actL->stock += cant;
        actL->precio = precio * (1 + actL->margen); //el margen se guarda como decimal, ej: 0.5
        insertaSublista(&actL,fecha,cant,precio);
        if(actL->stock > 0 && tieneStockNegativo)
            eliminaLD(LD,cod);
    }
    else {
        new = (TLista) malloc(sizeof(nodo));
        strcpy(new->cod,cod);
        new->stock = cant;
        new->precio = precio * 1.5;
        new->margen = 0.5;
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
            if(fecha[0] == '2' && fecha[1] == '0' && fecha[2] == '2' && fecha[3] == '5' && fecha[6] == '4')
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

/* ORIGINAL MAIN (Para controlar)
int main() {
    TLista LS;
    TListaD LD;
    TCola C;
    //cargaC(&C); cargaLS(&LS); cargaLD(&LD);
    procesaC(&C, LS, &LD);
    procesaArch(&LS,&LD);
    return 0;
}
*/

/* ===== MAIN PARA PROBAR CODIGO (INTELIGENCIA ARTIFICIAL)  ====== */

int main() {
    TLista LS;
    TListaD LD;
    TCola C;

    printf("========== PROGRAMA DE PRUEBA ==========\n");
    printf("Cargando datos de prueba...\n\n");

    // Cargar datos de prueba
    cargaLS(&LS);
    cargaLD(&LD);
    cargaC(&C);

    // Mostrar estado inicial
    printf("\n***** ESTADO INICIAL *****\n");
    mostrarLS(LS);
    mostrarLD(LD);
    mostrarC(C);

    // Procesar la cola de compras
    printf("\n\n***** PROCESANDO COLA DE COMPRAS *****\n");
    procesaC(&C, LS, &LD);

    // Mostrar estado después de procesar la cola
    printf("\n\n***** ESTADO DESPUÉS DE PROCESAR COLA *****\n");
    mostrarLS(LS);
    mostrarLD(LD);

    // Crear y procesar archivo
    crearArchivoPrueba();
    printf("\n\n***** PROCESANDO ARCHIVO PROVEEN.TXT *****\n");
    procesaArch(&LS, &LD);

    // Mostrar estado final
    printf("\n\n***** ESTADO FINAL *****\n");
    mostrarLS(LS);
    mostrarLD(LD);

    printf("\n========== FIN DEL PROGRAMA DE PRUEBA ==========\n");

    return 0;
}
