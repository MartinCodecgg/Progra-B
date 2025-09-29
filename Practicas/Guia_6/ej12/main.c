#include <stdio.h>
#include <stdlib.h>

typedef struct nodito{
    int num;
    struct nodito * sig;
} nodito;

typedef nodito * SubLista;

typedef struct nodo{
    float prom;
    int cant;
    struct nodo * sig;
} nodo;

typedef nodo * TLista;

typedef struct nodoD{
    int A,B;
    SubLista sub;
    struct nodoD *sig, *ant;
} nodoD;

typedef nodoD * Pnodo;

typedef struct{
    Pnodo pri,ult;
} TListaD;

// Función para inicializar la lista doble
void inicializarLD(TListaD *LD){
    LD->pri = NULL;
    LD->ult = NULL;
}

// Función para crear un nuevo nodo de sublista
SubLista crearNodoSub(int valor){
    SubLista nuevo = (SubLista)malloc(sizeof(nodito));
    if(nuevo != NULL){
        nuevo->num = valor;
        nuevo->sig = NULL;
    }
    return nuevo;
}

// Función para agregar un elemento a la sublista
void agregarASublista(SubLista *sub, int valor){
    SubLista nuevo = crearNodoSub(valor);
    if(nuevo != NULL){
        if(*sub == NULL){
            *sub = nuevo;
        } else {
            SubLista aux = *sub;
            while(aux->sig != NULL){
                aux = aux->sig;
            }
            aux->sig = nuevo;
        }
    }
}

// Función para crear un nodo de la lista doble
Pnodo crearNodoD(int A, int B){
    Pnodo nuevo = (Pnodo)malloc(sizeof(nodoD));
    if(nuevo != NULL){
        nuevo->A = A;
        nuevo->B = B;
        nuevo->sub = NULL;
        nuevo->sig = NULL;
        nuevo->ant = NULL;
    }
    return nuevo;
}

// Función para agregar un nodo al final de la lista doble
void agregarAListaD(TListaD *LD, int A, int B){
    Pnodo nuevo = crearNodoD(A, B);
    if(nuevo != NULL){
        if(LD->pri == NULL){
            LD->pri = nuevo;
            LD->ult = nuevo;
        } else {
            LD->ult->sig = nuevo;
            nuevo->ant = LD->ult;
            LD->ult = nuevo;
        }
    }
}
// Función para mostrar la lista doble (para pruebas)
void mostrarListaD(TListaD LD){
    Pnodo actual = LD.pri;
    int nodoNum = 1;

    printf("\n=== LISTA DOBLE ===\n");
    while(actual != NULL){
        printf("Nodo %d: Rango [%d,%d] - Sublista: ", nodoNum, actual->A, actual->B);

        SubLista auxSub = actual->sub;
        printf("{ ");
        while(auxSub != NULL){
            printf("%d ", auxSub->num);
            auxSub = auxSub->sig;
        }
        printf("}\n");

        actual = actual->sig;
        nodoNum++;
    }
}

// Función para mostrar la lista simple resultado
void mostrarListaL(TLista L){
    TLista actual = L;
    int nodoNum = 1;

    printf("\n=== LISTA SIMPLE RESULTADO ===\n");
    while(actual != NULL){
        printf("Nodo %d: Promedio = %.2f, Elementos fuera de rango = %d\n",
               nodoNum, actual->prom, actual->cant);
        actual = actual->sig;
        nodoNum++;
    }
}

void generaL(TListaD LD,TLista *L){
    *L = NULL;
    TLista new, antL;
    Pnodo act;
    SubLista actS;
    int cont;

    antL = NULL;
    act = LD.pri;
    while(act != NULL){
        new = (TLista) malloc(sizeof(nodo));
        new->prom = 0;
        new->cant = 0;
        if(*L == NULL)
            *L = new;
        cont = 0;
        actS = act->sub; //nunca hacer LD.pri->sub, es act->sub;
        while(actS != NULL){
            if(actS->num < act->A || actS->num > act->B)
                ++new->cant;
            new->prom += actS->num;
            cont++;
            actS = actS->sig;
        }
        if(cont) //Validar siempre posibles divisiones por Cero
            new->prom /= cont;
        if(antL != NULL)
            antL->sig = new;
        antL = new;
        act = act->sig;
    }
     antL->sig = NULL;
        //new->sig = NULL;  MAL ademas las comparaciones como new != NULL es comportamiento indefinido si new nunca tuvo valor
}

int main(){
    TListaD LD;
    TLista L;

    // === CODIGO PARA CREAR LISTA DOBLE (IA)

    // Inicializar listas
    inicializarLD(&LD);
    // Crear datos de ejemplo
    printf("Creando lista doble con datos de ejemplo...\n");
    // Primer nodo: rango [1,5]
    agregarAListaD(&LD, 1, 5);
    agregarASublista(&LD.ult->sub, 2);  // dentro del rango
    agregarASublista(&LD.ult->sub, 7);  // fuera del rango
    agregarASublista(&LD.ult->sub, 3);  // dentro del rango
    agregarASublista(&LD.ult->sub, 8);  // fuera del rango
    // Segundo nodo: rango [10,20]
    agregarAListaD(&LD, 10, 20);
    agregarASublista(&LD.ult->sub, 15); // dentro del rango
    agregarASublista(&LD.ult->sub, 5);  // fuera del rango
    agregarASublista(&LD.ult->sub, 18); // dentro del rango
    // Tercer nodo: rango [0,10]
    agregarAListaD(&LD, 0, 10);
    agregarASublista(&LD.ult->sub, 5);  // dentro del rango
    agregarASublista(&LD.ult->sub, 15); // fuera del rango
    agregarASublista(&LD.ult->sub, 2);  // dentro del rango
    agregarASublista(&LD.ult->sub, 12); // fuera del rango
    agregarASublista(&LD.ult->sub, 8);  // dentro del rango
    // Mostrar lista doble original
    mostrarListaD(LD);
    // Generar lista simple paralela
    // Mostrar lista simple resultado
    //mostrarListaL(L);
    // Verificación manual de los resultados:
    printf("\n=== VERIFICACIÓN ===\n");
    printf("Nodo 1: Sublista {2,7,3,8} - Promedio: %.2f, Fuera de [1,5]: 2 elementos (7,8)\n", (2+7+3+8)/4.0);
    printf("Nodo 2: Sublista {15,5,18} - Promedio: %.2f, Fuera de [10,20]: 1 elemento (5)\n", (15+5+18)/3.0);
    printf("Nodo 3: Sublista {5,15,2,12,8} - Promedio: %.2f, Fuera de [0,10]: 2 elementos (15,12)\n", (5+15+2+12+8)/5.0);

    // === CODIGO PARA CREAR LISTA SIMPLE (EJERCICIO)

    generaL(LD,&L);
    mostrarListaL(L);

    return 0;
}
