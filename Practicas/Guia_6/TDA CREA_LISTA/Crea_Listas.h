#ifndef CREA_LISTAS_H_INCLUDED
#define CREA_LISTAS_H_INCLUDED

typedef char TElementoL;

typedef struct nodo{
 TElementoL dato;
 struct nodo * sig;} nodo;
typedef nodo * TLista;

void creaL(TLista *L,TElementoL array[], int n);

#endif // CREA_LISTAS_H_INCLUDED

