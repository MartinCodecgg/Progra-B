/*
Corregir los errores en la siguiente función void, la cual genera un arreglo de caracteres con los
nodos de grado 2 de un árbol binario.
*/

void arrgrado2(arbol a, char v[N], int dimv) { //el N de v[N] no es necesario //dimV debio ser pasado como referencia
 if (a != NULL) {
    if(a->izq != NULL && a->der == NULL) {/* grado 2 */ //segun la catedra los grados de un nodo son solo contando sus hijos, osea que para que sea de grado 2 tendria que tener tanto su izq o der no nulos
        (*dimv)++; //deberia incrementarse despues, ya que la posicion cero queda sin valor
        v[dimv] = a->dato;
    } else //faltan llaves para el else
        arrgrado2(a->izq, v[], dimv);
        arrgrado2(a->der, v[], dimv);
    }
}  //[PREGUNTAR] si para el grado de un nodo se considera la arista del padre o no
