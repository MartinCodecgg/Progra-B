#include <stdio.h>
#include <stdlib.h> //no necesario para el ejercicio pero si para la carga funcione

typedef struct nodo {
    int dato;
    struct nodo *izq, *der;
} nodo;

typedef nodo* Arbol;

// ─────────────────────────────
// Crear un nuevo nodo
// ─────────────────────────────
Arbol crearNodo(int dato) {
    Arbol nuevo = (Arbol) malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

// ─────────────────────────────
// Carga automatica del arbol
// ─────────────────────────────
// Ejemplo de arbol:
//         5
//        / \
//       8   4
//      / \   \
//     3   6   9
// ─────────────────────────────
void cargaA(Arbol *A) {
    *A = crearNodo(5);
    (*A)->izq = crearNodo(8);
    (*A)->der = crearNodo(4);
    (*A)->izq->izq = crearNodo(3);
    (*A)->izq->der = crearNodo(6);
    (*A)->der->der = crearNodo(9);
}

// ─────────────────────────────
// a) Suma de multiplos de 3
// ─────────────────────────────
int suma(Arbol A) {
    if (A) {
        if (A->dato % 3 == 0)
            return A->dato + suma(A->izq) + suma(A->der);
        else
            return suma(A->izq) + suma(A->der);
    } else
        return 0;
}

// ─────────────────────────────
// Programa principal
// ─────────────────────────────

int cantH(Arbol A) {
	if(A == NULL)
		return 0;
	else {
		if(A->izq == NULL && A->der == NULL)
			return 1;
		else
			return cantH(A->izq) + cantH(A->der);
	}
}
//La condicion para que sea hoja es que tanto su izquierdo como su derecho sean NULL

int estaX(Arbol A, int x) {
	if(A)
		return A->dato == x || estaX(A->izq,x) || estaX(A->der,x);
	else
		return 0;
}


int main() {
    Arbol A = NULL;
    int x;
    cargaA(&A);  // Carga automatica del arbol

    printf("La suma de los elementos que son múltiplos de 3 es: %d\n", suma(A));
    printf("La cantidad de hojas del arbol es %d\n", cantH(A));
    printf("Ingrese x para posteriormente verificar si existe en el Arbol\n");
    scanf(" %d",&x);

    if(estaX(A,x))
        printf("El valor ingreso existe en el arbol\n");
    else
        printf("El valor ingresado no existe en el arbol\n");

    return 0;
}
