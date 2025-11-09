#include <stdio.h>
//#include "TDANARIO.h"
#define N 50

typedef struct nodo {
    int num;
    struct nodo *izq, *der;} nodo;

typedef nodo * Arbol;

/*
Dado un ABB de enteros, determinar mediante una funcion int si todos los datos positivos en nodos no hoja, verifican tener la misma paridad que sus hijos (o hijo).
*/

/*/ multiples errores: No analizo a der cuando es < 0, analizo a la vuelta, cuando deberia hacerse a la IDA
int determinar(Arbol ABB) { //verif
    int paridad, resIzq, resDer; // 
    
    if(ABB == NULL)
            return -1; //sigo analizando
    else
        if(ABB->num < 0)
            return determinar(ABB->der); //aprovechando que es ABB, no sigo buscando por la rama izquierda, solo busco por su rama derecha
        else {
            paridad = ABB->num % 2;
            if(ABB->izq == NULL && ABB->der == NULL)
                return paridad;
            else  {
                resIzq = determinar(ABB->izq);
                resDer = determinar(ABB->der);
            
                if(resIzq == -2 || resDer == -2)
                    return -2; //-2 es el caso para parar de analizar
                else
                    if(resIzq != -1 && paridad != resIzq ||
                        resDer != -1 && paridad != resDer)
                            return -2;
                    else
                        return paridad;
            }
        }
}
*/

//Inciso a) Corregido
//verif con renzo
int verif(Arbol ABB) {
    int condIzq, condDer;

    if(ABB == NULL || ABB->izq == NULL && ABB->der == NULL)
        return 1;
    else
        if(ABB->num < 0)
            return verif(ABB->der);
    else {
        if(ABB->izq == NULL).
            condIzq = 1;
        else
            condIzq = ABB->izq->dato % 2 == ABB->dato % 2;
            
        if(ABB->der == NULL)
                condDer = 1;
        else
                condDer = ABB->der->dato % 2 == ABB->dato % 2;
        if(condIzq && condDer)
            return verif(ABB->izq) && verif(ABB->der);
        else
            return 0;
    }
}
//verif con sonnet 4.5
void mayores2(ArbolG AG, int *clave1, int *clave2, Pos p, int nivel) { //verif
    Pos c;
    int aux;
    if(!Nulo(p)) {
        aux = Info(p,AG);
        if(nivel % 2 != 0) {
            if(aux > *clave1) {
                *clave2 = *clave1;
                *clave1 = aux;
            }
            else
                if(aux > *clave2)
                    *clave2 = aux;
        }
        c = hijoMasIzq(p,AG);
        while(!Nulo(c)) {
            mayores2(AG, clave1, clave2, c, nivel + 1);
            c = hnoDer(c, AG);
        }
    }
}

/*Mal planteado, al ser aristas no necesito comparar con su simetrico, solo necesito ir sumando la cantidad,
total no encotrare aristas duplicadas a trabajar con solo un lado de la matriz
void costoAAM(int k[][N], int *acum, int *contAX, int x, int i, int j, int n) { //verif
    if(i >= 0) {
        if(i > j) { //triangulo inferior
            *acum += k[j][i]; //analizo en el triangulo superior(para ello invierto indices)
            if((j == x || i == x) && k[j][i] != 0)
                (*contAX)++;
        }
        else { //triangulo superior
            *acum += k[i][j]; //analizo en el triangulo superior
            if((j == x || i == x) && k[i][j] != 0)
                (*contAX)++;
        }
        if(j > 0)
            costoAAM(k, acum, contAX, x, i, j-1, n);
        else
            costoAAM(k, acum, contAX, x, i-1,n,n);
    }
}
*/
//verif con renzo
void rec(int k[][N], int *costoAAM, int *contX, int i, int j, int n, int x, int nAristas) {
    if(i >= 0 && nAristas < n-1) { //En kruscal, si ya analize las n-1 aristas no me interesa seguir analizando.
        costoAAM += k[i][j];
        nAristas++;
        contX += (i == x || j == x) && k[i][j] != 0;
        if(j > i + 1)
            rec(k, costoAAM, contX, i, j-1, n,x, nAristas);
        else
            rec(k, costoAAM, contX, i-1, n,n,x, nAristas); 
    }
}

int main() {
    Arbol ABB;
    int clave1 = -9999, clave2 = -9999, x, acum = 0, contAX = 0, n, K[N][N];
    cargaA(&ABB); cargaK(&k);
    (determinar(ABB) != -2) ? printf("ABB cumple\n")
                            : printf("ABB No Cumple\n");
    mayores2(AG,&clave1, &clave2, Raiz(AG),0);
    printf("Ingrese x\n");
    scanf("%d",&x);
    costoAAX(K, &acum, &contAAX, x, n-1, n-1, n-1);
    printf("El costo del AAM y la cantidad de aristas que enlazan a %d"
            " a el vertice %d es %d %d respectivamente",
            x, acum,contAX);
    return 0;
}