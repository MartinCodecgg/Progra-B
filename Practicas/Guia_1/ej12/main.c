#include <stdio.h>

int main() {
    int sum = 0, num;

    do {
        printf("Ingrese un numero, 0 para terminar \n");
        scanf(" %d", &num); //no debo meter espacios luego del %d porque genera bugs
        sum += num;

    } while (num != 0);

    printf("La suma es igual a %d",sum);

return 0;
}
