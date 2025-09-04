#include <stdio.h>
#include <stdlib.h>
#define TOP 20

int main() {

    int* array[TOP];
    int* ptr;
    unsigned n = 0;
    int num;
    FILE* arch = fopen("enteros.txt","rt");

    if (arch == NULL)
        printf("Error al abrir el archivo");
    else {
        printf("archivo abierto correctamente para lectura\n");

        while ( fscanf(arch,"%d\n",&num) == 1 ) {

            ptr = (int*) malloc(sizeof(int));
            *ptr = num;
            array[n] = ptr;
            n += 1;
        }

        //adicional muestro el vector generado
        unsigned int i = 0;
        for (i=0; i<n; ++i)
            printf("%d ",*array[i]);
    }

    return 0;
}
