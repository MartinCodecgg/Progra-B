#include <stdio.h>
#include <stdlib.h>

typedef struct nodoD{
    char dato;
    struct nodoD *sig, *ant; } nodoD;
typedef nodoD * Pnodo;

typedef struct {
    Pnodo pri, ult;} TListaD;

void creaLD(TListaD *LD, char array[], int n) {
    Pnodo aux;
    int i;

    // Inicializar la lista vacía
    LD->pri = NULL;
    LD->ult = NULL;

    if(n <= 0) {
        printf("Cantidad de elementos del arreglo invalida\n");
        return;
    }

    // Crear el primer nodo
    aux = (Pnodo) malloc(sizeof(nodoD));
    aux->dato = array[0];
    aux->sig = NULL;
    aux->ant = NULL;

    // Establecer primer y último nodo (por ahora es el mismo)
    LD->pri = aux;
    LD->ult = aux;

    // Crear el resto de nodos
    for(i = 1; i < n; ++i) {
        aux = (Pnodo) malloc(sizeof(nodoD));
        aux->dato = array[i];
        aux->sig = NULL;
        aux->ant = LD->ult;  // El anterior es el último actual

        // Enlazar el último nodo actual con el nuevo
        LD->ult->sig = aux;

        // Actualizar el último nodo
        LD->ult = aux;
    }
}

int validaPalindroma(TListaD LD){ //RECORDAR que si LD es por copia no usar la flecha
    Pnodo pri,ult,antPri;

    if(LD.pri == NULL || LD.pri->sig == NULL) //unico caracter o lista vacia
        return 1;
    else{
        pri = LD.pri;
        ult = LD.ult;
        while (pri->dato == ult->dato && ult != pri && antPri != ult){
            antPri = pri;
            pri = pri->sig;
            ult = ult->ant;
        }
        return (ult == pri || antPri == ult); //Al mismo tiempo que se valida que los datos sean iguales:
    }//Si tienen la misma direccion de memoria es porque es palindroma, estan parados en la mitad de la palabra
}   //De otro modo si la direccion del anterior de pri es igual a ult significa que se superaron y es palindroma por esto

int main(){
    TListaD LD;
    char array[] = {'r','a','d','a','r'};
    int n = 5;
    creaLD(&LD,array,n);
    if(validaPalindroma(LD))
        printf("Es Palindroma");
    else
        printf("No es Palindroma");


    return 0;
}
