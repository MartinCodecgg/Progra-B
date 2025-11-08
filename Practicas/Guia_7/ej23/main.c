#include <stdio.h>
//#include "TDArbolNArio"

int cantN(ArbolG A, Pos p) {
    Pos c;
    unsigned int cont = 0;

    if(!Nulo(p)) { //no considerar unicamente la cabeza y sus hijos inmediatos, analizar al menos para los 3 primeros niveles.
        c = HijoMasIzq(p,A);
        while(!Nulo(c)) {
            cont += cantN(A, c);
            c = HnoDer(c,A);
        }
        return cont + 1; // + 1 para contar el nodo actual
    }
    else
        return 0;
}

void porcentaje(ArbolG A, Pos p, int *contNodos, int *contPares) {
    Pos c;
    if(!Nulo(p)) {
        *contNodos += 1;
        if(Info(p) % 2 == 0)
            *contPares += 1;
        c = HijoMasIzq(p, A);
        while(!Nulo(c)) {
            porcentaje(A, c, contNodos, contPares);
            c = HnoDer(c, A);
        }
    }
}

void hallaGrado(ArbolG A, Pos p, int *gradoMax) {
    Pos c;
    unsigned int gr = 0;
    if(!Nulo(p)) {
        c = HijoMasIzq(p, A);
        while(!Nulo(c)) {
            gr++;
            hallaGrado(A, c, gradoMax);
            c = HnoDer(c,A);
        }
        if(gr > *gradoMax)
            *gradoMax = gr;
    }
}
 //Solucion usando INT (es mejor asi), enves de usar el parametro de salida se usan dos variables mas
/*
int gradoArbol (arbol a, pos p) {
  int grado = 0, max = 0, aux;
  pos c;
  if (!nulo (p) ) {
    c = hijoMasIzq(p,a);
    while (!nulo(c)) {
      grado++;
      aux = gradoArbol(c,a);
      if (aux > max)
        max = aux;
      c = hermanoDer(c,a);
    }
  }
  return (grado>max) ?�grado�:�max;
}
*/

int cantNImpar(ArbolG A, Pos p, int nivel) {
    Pos c;
    int tot = 0, gr = 0;
    nivel++;
    if(!Nulo(p)) {
        c = HijoMasIzq(p, A);
        while(!Nulo(c)) {
            gr++;
            tot += cantNImpar(A, c, nivel);
            c = HnoDer(c,A);
        }
        if(gr % 2 != 0 && nivel % 2 != 0)
            tot++;
    }
    return tot; //gr se inicializa en cero cosa que cumple la condicion de no ser nulo y de ser nivel impar
}   //[PREGUNTAR SI ESTA BIEN USAR EL TERNARIO O DEBERIA DE USAR UN IF CON DOS RETURN PARA NO PONER EL : 0 QUE ESTA DE MAS]

int verifInt(ArbolG A, Pos p) {
    Pos c;
    int contHijos = 0, HijoCumple = 1, esHoja = 0;
    if(!Nulo(p)) { //no es necesario un else ya que siempre llamo a la funcion siendo esta valida
        c = HijoMasIzq(p, A);
        if(Nulo(c))
            esHoja = 1;
        while(!Nulo(c) && HijoCumple) {
            contHijos++;
            HijoCumple = verifInt(A, c);
            c = HnoDer(c, A); //esta linea debe evaluarse SIEMPRE, si pongo alguna condicion aqui, el ciclo entrara en un bucle infinito
        }
        if(esHoja)
            return 1; //si es hoja retorna 1
        else
            return (HijoCumple && contHijos == Info(p, A)); //La condicion de cierre es que el hijo no cumpla o no coincida en la cantidad, primero verificando que no sea una hoja
    }
    //else
        //return 1; ES NECESARIO?
}

void verifVoid(ArbolG A, Pos p, int *cond) {
    Pos c;
    int contHijos = 0, esHoja = 0;
    if(!Nulo(p)) {
        c = HijoMasIzq(p, A);
        if(Nulo(c))
            esHoja = 1;
        while(!Nulo(c) && *cond) {
            contHijos++;
            verifVoid(A, c, cond);
            c = HnoDer(c, A);
        }
        if(!esHoja && contHijos != Info(p,A))
            *cond = 0;
    }
}
//int cond = 1;
//Llamado main: verifVoid(A, Raiz(A), &cond)

void promedio(ArbolG A, Pos p, int k, int nivel, int *acum, int *cont) { //Funciona correctamente
    Pos c;
    nivel++;
                //La logica de esta solucion, es no analizar el nivel K, solo hasta el nivel k-1
    if(!Nulo(p)) {
        if(k == 1 && nivel == 1) {
            *acum = Info(p, A);
            *cont = 1;
        }
        else {
            c = HijoMasIzq(p, A);
            while(!Nulo(c)) {
                if(nivel == k - 1) {
                    (*cont)++;
                    *acum += Info(c, A);
                }
                if(nivel <=  k - 1)
                    promedio(A, c, k, nivel, acum, cont);
                c = HnoDer(c, A);
            }
        }
    }
}
//Llamado main:
//promedio(A, Raiz(A), k, 1, &acum, &cont);
//printf("El promedio es acum/cont\n");

//En cambio si analizace el nivel k tambien, podria ir acumulando simplemente desde el nivel actual, resultando:

void promedio(ArbolG A, Pos p, int k, int nivel, int *acum, int *cont) { //IA (es una mejor solucion aunque analiza un nivel mas, pero el codigo es mas claro y corto)
    Pos c; //Funciona correctamente

    if(!Nulo(p)) {
        if(nivel == k) {         // Si estamos en el nivel k, acumulamos
            *acum += Info(p, A);
            (*cont)++;
        }
        if(nivel < k) { // Solo seguir explorando si no hemos pasado el nivel k
            c = HijoMasIzq(p, A);
            while(!Nulo(c)) {
                promedio(A, c, k, nivel + 1, acum, cont);
                c = HnoDer(c, A);
            }
        }
    }
}

//CONCLUSION: Si quiero obtener un promedio o hacer alguna operacion solo de algun nivel k, me conviene recorrer el nivel k estando parado en el y no analizar los hijos del padre de nivel k -1

int main() {
    ArbolG A;
    int gradoMax = -1, cond = 1, contNodos = 0, contPares = 0, k, acum = 0, cont = 0;

    printf("cantidad de nodos %d\n",cantN(A, Raiz(A)));
    porcentaje(A, Raiz(A), &contNodos, &contPares);
    printf("El porcentaje es: %f\n", (float) contPares/contNodos * 100);
    hallaGrado(A, Raiz(A), &gradoMax);
    printf("Grado mal es %d", gradoMax);
    printf("cantidad de nodos de grado impar que hay en niveles impares %d\n",cantNImpar(A, Raiz(A), 0));
    verifVoid(A, Raiz(A), &cond);
    if(verifInt(A, Raiz(A)))
        printf("Cumple\n");
    else
        printf("No cumple\n");

    printf("Ingrese K\n");
    scanf(" %d", &k);
    promedio(A, Raiz(A), k, 0, &acum, &cont);
    printf("El promedio es: %f\n", (float) acum/cont); //recordar castear al hallar promedios y porcentajes, y usar %f si casteo a float
    return 0;
}
