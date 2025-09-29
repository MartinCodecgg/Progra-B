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

// Función simple para mostrar la lista (IA)
void mostrarLista(TListaC LC) {
    if (LC == NULL) {
        printf("Lista vacía\n");
        return;
    }

    nodo *actual = LC;
    printf("Lista circular: ");
    do {
        printf("%c ", actual->dato);
        actual = actual->sig;
    } while (actual != LC);
    printf("\n");
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
            if(aux == 'A' || aux == 'E' || aux == 'iI' || aux == 'o' || aux == 'u')
            cont++;
        }
    }
    return cont;
}

int main() {
    TListaC LC;
    int vocales;

    // Crear la lista ya cargada con datos
    LC = crearListaCargada();
    printf("Lista circular creada y cargada (LC apunta al mayor 'E'):\n");
    mostrarLista(LC);
    printf("\nUsando tu función muestraLC:\n");
    // Aquí puedes probar tu función muestraLC(LC);
    printf("\nDemostrando estructura: LC='%c' apunta al mayor, LC->sig='%c' es el primero\n",
           LC->dato, LC->sig->dato);

    // === CODIGO EJERCICIO ===

    muestraLC(LC);
    vocales = contVocales(LC);
    printf("La cantidad de nodos que contienen vocales es de: %d\n",vocales);

    return 0;
}
