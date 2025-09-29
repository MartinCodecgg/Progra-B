#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOP 50
typedef struct nodo {
    int cant;
    char palabra[15];
    struct nodo * sig;
} nodo;
typedef nodo * TListaC;

// Función para crear y cargar la lista circular con palabras
// LC apunta al mayor elemento (última palabra alfabéticamente)
TListaC crearListaPalabrasCargada() {
    TListaC LC = NULL;

    // Datos para cargar (palabras ordenadas alfabéticamente con sus cantidades)
    struct {
        char palabra[15];
        int cant;
    } datos[] = {
        {"casa", 1},
        {"gato", 2},
        {"libro", 5},
        {"mesa", 1},
        {"perro", 4},
        {"ventana", 2}
    };

    int cantidad = 6;

    // Crear los nodos y cargar los datos
    for (int i = 0; i < cantidad; i++) {
        nodo *nuevo = (nodo*)malloc(sizeof(nodo));
        strcpy(nuevo->palabra, datos[i].palabra);
        nuevo->cant = datos[i].cant;

        if (LC == NULL) {
            // Primer nodo: apunta a sí mismo
            nuevo->sig = nuevo;
            LC = nuevo;
        } else {
            // Insertar al final y actualizar LC para que apunte al último (mayor)
            nuevo->sig = LC->sig;  // El nuevo apunta al primero
            LC->sig = nuevo;       // El último actual apunta al nuevo
            LC = nuevo;           // LC apunta al nuevo nodo (que es el último/mayor)
        }
    }

    return LC;
}


// Función para mostrar la lista circular de palabras
void mostrarListaPalabras(TListaC LC) {
    if (LC == NULL) {
        printf("Lista vacía\n");
        return;
    }

    nodo *actual = LC->sig; // Empezar desde el primer elemento
    printf("Lista de palabras (ordenada alfabéticamente):\n");
    printf("Palabra\t\tCantidad\n");
    printf("------------------------\n");

    do {
        printf("%-12s\t%d\n", actual->palabra, actual->cant);
        actual = actual->sig;
    } while (actual != LC->sig);
}

void elimina(TListaC *LC,char pal[]) { //[PREGUNTAR POR EFICIENCIA]
    TListaC act, ant;

    ant = NULL;
    if(*LC != NULL) {
        act = (*LC)->sig;
        while(act != *LC && strcmp(pal,act->palabra) > 0) {
            ant = act;
            act = act->sig;
        }
        if(strcmp(pal,act->palabra) == 0)
            --act->cant;
        if(act->cant == 0) { //ant == NULL && <- Esta condicion es innecesaria aqui, ya que se cumple tanto para el caso del primer elemento y el unico, debo poner condiciones unicas en cada if, y las condiciones en comun ir tirandolas hacia abajo como es el caso actual
            if(act == act->sig) //caso del unico elemento en la lista
                *LC = NULL;
            else // no poner else if() , poner el else y el if debajo
                if(ant == NULL) //primer elemento
                    (*LC)->sig = act->sig;
            else {  //otro
                ant->sig = act->sig;
                if(act == *LC) //cabecera
                    *LC = ant;
            }
            free(act);
        }
    }
}
/*
void elimina(TListaC *LC, char pal[]) { //hecho por chat (ignorar)
    TListaC act, ant;

    if (*LC == NULL) {
        ant = NULL;
        act = (*LC)->sig,
        while (act != *LC && strcmp(pal, act->palabra) > 0) {
            ant = act;
            act = act->sig;
        }
        if (strcmp(pal, act->palabra) == 0 && --act->cant == 0) { //PREGUNTAR por esto: --act->cant == 0
            if (act == act->sig)           // Único elemento
                *LC = NULL;
            else if (ant == NULL)          // Primer elemento
                (*LC)->sig = act->sig;
            else {                         // Otro elemento
                ant->sig = act->sig;
                if (act == *LC) *LC = ant; // cabecera
            }
            free(act);
        }
    }
}
*/
int main() {
    TListaC LC;
    char pal[TOP];

    // ===Crear la lista ya cargada con palabras===
    LC = crearListaPalabrasCargada();
    printf("Lista circular de palabras creada y cargada:\n");
    printf("(LC apunta a la palabra mayor alfabéticamente: '%s')\n\n", LC->palabra);
    mostrarListaPalabras(LC);

    // ===CODIGO EJERCICIO===
    printf("Ingrese la palabra a reducir su aparicion\n");
    scanf("%s",pal);
    elimina(&LC,pal);
    mostrarListaPalabras(LC);

    return 0;
}
