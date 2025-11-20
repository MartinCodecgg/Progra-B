#include <stdio.h>

void obtiene(Arbol ABB, char *maxClave, int *maxNivel, int nivel) {
    if(ABB != NULL) {
        obtiene(ABB->izq, maxClave, maxNivel, nivel + 1);
        obtiene(ABB->der, maxClave, maxNivel, nivel + 1);
        if(nivel > *maxNivel && ABB->izq && ABB->der) {
            *maxClave = ABB->clave;
            *maxNivel = nivel;
        }
    }
}

typedef struct nodo {
    char clave;
    struct nodo *izq, *der; } nodo;

typedef nodo * Arbol;

int main() {
    char maxClave = ' ';
    Arbol ABB;
    int maxNivel = -1;
    cargaA(&ABB);
    obtiene(ABB, &maxClave, &maxNivel, 0);
    if(maxClave != ' ') 
        printf("La clave encontrada es %c", maxClave);
    else
        printf("No se encontro ninguna clave valida");
    
    return 0;
}