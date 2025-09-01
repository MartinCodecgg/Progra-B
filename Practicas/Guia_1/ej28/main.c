#include <stdio.h>

/*
28. Rehacer el ejercicio 12 suponiendo que los números se encuentran en un archivo de texto,
todos en la misma línea. ¿Como modificaría la lectura, si hubiera un valor por línea?

12. Desarrollar un programa que muestre la suma de un conjunto de números naturales ingresados
por teclado. La serie finaliza al ingresar el número 0.

*/

int main() {

    FILE* arch;
    int sum, num;

    arch = fopen ("numeros.txt", "rt"); //recordar que los nombres y los modos de los archivos van entre comillas

    if (arch == NULL)
        printf("archivo de numeros no existe");

    else {
        printf("archivo abierto correctamente");
        sum = 0;
        while( fscanf(arch,"%d",&num) == 1 ) //debo siempre verificar que devuelva 1 si uso el metodo alternativo ya que cuando llega al
            sum += num;                      //fin de archivo puede devolver numeros negativos y estos se evaluan como true para el while
    }

    printf("La suma de los numeros del archivo es %d",sum);

    return 0;
}
