#include <stdio.h>
#define TOP 30

void muestraImpares(unsigned int v[], unsigned int *n);

void generaV(unsigned int v[], unsigned int *n, unsigned int *k, unsigned int v2[], unsigned int *n2);

void muestraV(unsigned int v2[], unsigned int *n2);

int buscar(unsigned int vec[], unsigned int *n, unsigned int *x);

int main() {

    unsigned int v[TOP], n;
    unsigned short opcion,i;

    printf("Ingrese la dimension del vector \n");
    scanf("%u",&n);

    printf("Ingrese las componentes del vector \n");
    for (i = 0; i < n; ++i)
        scanf(" %u",&v[i]);

    do {
    printf("Ingrese una opcion: 1): Mostrar los elementos en posiciones impares 1,3,5 2): Generar un vector con los elementos divisibles por k y mostrarlo 3) Buscar la posicion de un valor x \n");
    scanf(" %hu",&opcion);

    } while (opcion != 1 && opcion != 2 && opcion != 3);


    if (opcion == 1)
        muestraImpares(v, &n);

    else if (opcion == 2) {
        unsigned int k, n2 = 0;
        unsigned int v2[TOP];

        printf("Ingrese k \n");
        scanf(" %u",&k);
        n2 = 0;
        generaV(v,&n,&k,v2,&n2); //RECORDAR que en C no es posible definir y asignar a un vector el resultado de una funcion
        muestraV(v2,&n2);        // es decir int i[] = funcion()
    }                            //y dado que necesito tanto el v2 como n2, tengo que devolver dos cosas y seria un "procedimiento"

    else {
        int x, aux; // x puede ser negativo y aux debe devolver -1 en casos de no encontrar
        printf("\nIngrese X\n"); //recordar que si quiero solo dejar un espacio antes debo poner \n y luego el texto directamente
        scanf("%u",&x);

        aux = buscar(v,&n,&x); //usar siempre buscar y no busca para estas funciones de busqueda

        if (aux != -1)
            printf("La posicion del valor ingresado es: %u",aux);
        else
            printf("El valor ingresado no existe en el vector");

    }

    return 0;
}

void muestraImpares(unsigned int v[], unsigned int *n) {

    unsigned short int i;
    for (i = 0; i<*n; ++i) {
        if (i % 2 != 0)
            printf("%u \t",v[i]);
    }
}

void generaV(unsigned int v[], unsigned int *n, unsigned int *k, unsigned int v2[], unsigned int *n2) {

    unsigned short i;
    for (i = 0; i<*n ;++i) {   //Recordar para mostrar asignar un vector a otro con un for el proceso es
        if (v[i] % *k == 0) {   //ASIGNO => IMPRIMO => AUMENTO N y N debe estar inicializado en cero, de otro modo un bug
            v2[*n2] = v[i];
            *n2 += 1;
        }
    }
}

void muestraV(unsigned int v2[], unsigned int *n2) {

    unsigned short int i;
    for (i = 0; i<*n2; ++i) {
        printf("%u ",v2[i]);
    }
}

int buscar(unsigned int v[], unsigned int *n, unsigned int *x) { //intentar usar v siempre, de forma generica
                                                                    //no salir con return/break en for y la busqueda es siempre con while
    unsigned short i = 0;

    while (v[i] != *x && i<*n) {
            ++i;
    }

    if (i<*n)
        return i;
    else
        return -1;

}
