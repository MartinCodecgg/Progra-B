
int busca(arbol a, int* x) { //x no se modifica, debio ser pasado como copia
 if (a != NULL) //debio ser a == NULL
    return 0;
 else
    if(x = a.dato) // debio ser a->dato ya que a es un puntero a nodo, ademas debio ser == y no  =
        return 1;
    else
        if(x < a.dato)
            return busca(a.der, *x); //debio ser izquierda
    else
        return busca(a->izq, *x); //debio ser derecha
}

//CORREGIDA

int busca(arbol a, int x) { //x no se modifica, debio ser pasado como copia
 if (a == NULL)
    return 0;
 else
    if(x == a->dato) // debio ser a->dato ya que a es un puntero a nodo, ademas debio ser == y no  =
        return 1;
    else
        if(x < a->dato)
            return busca(a->izq, x); //debio ser izquierda
    else
        return busca(a->der, x); //debio ser derecha
}
