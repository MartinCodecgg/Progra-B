#ifndef TDA_CREA_MUESTRA_LISTA_H_INCLUDED
#define TDA_CREA_MUESTRA_LISTA_H_INCLUDED

typedef char TElementoL;

typedef struct nodo{
 TElementoL dato;
 struct nodo * sig;} nodo;
typedef nodo * TLista;

void creaL(TLista *L,TElementoL array[], int n);

void muestraL(TLista L);

#endif // TDA_CREA+MUESTRA_LISTA_H_INCLUDED
