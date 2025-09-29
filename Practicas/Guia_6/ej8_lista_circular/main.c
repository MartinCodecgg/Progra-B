#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct nodo{
    char dato;
    struct nodo * sig;
} nodo;

typedef nodo * TListaC;

// Función para crear y cargar la lista circular con datos
// LC apunta al mayor elemento (convención de cátedra)
TListaC crearListaCargada() {
    TListaC LC = NULL;
    char datos[] = {'A', 'B', 'C', 'D', 'E'}; // Datos para cargar
    int cantidad = 5;

    // Crear los nodos y cargar los datos
    for (int i = 0; i < cantidad; i++) {
        nodo *nuevo = (nodo*)malloc(sizeof(nodo));
        nuevo->dato = datos[i];

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

void muestraLC(TListaC LC) {
    TListaC act;

    if(LC != NULL) {
        act = LC->sig;
        while(act != LC) {
            printf("%c ",act->dato);
            act = act->sig;
        }
        printf("%c\n",act->dato);
    }
}

int contVocales(TListaC LC) {
    TListaC act;
    int cont = 0;
    char aux;

    if(LC != NULL) {
        act = LC->sig;
        while(act != LC) {
            act = act->sig;
            aux = toupper(act->dato);
            if(aux == 'A' || aux == 'E' || aux == 'i' || aux == 'o' || aux == 'u')
            cont++;
        }
    }
    return cont;
}

int estaOrd(TListaC LC) {
    TListaC act, ant;

    if(LC != NULL) {
        ant = LC->sig;
        act = LC->sig->sig;
        while(act != LC && act->dato > ant->dato) {
            ant = act;
            act = act->sig;
        }
        return (act == LC && act->dato > ant->dato);
    }
    else
        return 1;
}

void elimina(TListaC *LC, int p) {
    TListaC act, ant;
    int aux;

    if(*LC != NULL) {
        ant = *LC;
        act = (*LC)->sig;
        aux = 0;
        while(aux != p) {
            ant = act;
            act = act->sig;
            aux++;
        }
        if(aux == p) {
            if(act == act->sig) { //unico elemento
                *LC = NULL;
                free(LC);
            }
            else { //dado que se que para todos los casos voy a eliminar la misma variable puedos sacar factor comun
                if(act == *LC) {
                    ant->sig = act->sig;
                    *LC = ant;
                }
                else
                    ant->sig = act->sig;
                free(act);
            }
        }
    }
}

int main() {
    TListaC LC;

    // Crear la lista ya cargada con datos
    LC = crearListaCargada();
    printf("Lista circular creada y cargada (LC apunta al mayor 'E'):\n");
    muestraLC(LC);
    printf("\nUsando tu función muestraLC:\n");
    // Aquí puedes probar tu función muestraLC(LC);
    printf("\nDemostrando estructura: LC='%c' apunta al mayor, LC->sig='%c' es el primero\n",
           LC->dato, LC->sig->dato);

    // === CODIGO EJERCICIO ===

    muestraLC(LC);
    printf("La cantidad de nodos que contienen vocales es de: %d\n",contVocales(LC));
    if(estaOrd(LC))
        printf("Esta ordenada\n");
    else
        printf("No esta ordenada\n");
    elimina(&LC,4);
    muestraLC(LC);

    return 0;
}
