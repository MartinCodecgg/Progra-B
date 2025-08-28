#include <stdio.h>

void print_hms(long long total_segundos) {

    long long horas = total_segundos / 3600;
    long long resto = total_segundos % 3600; //el operador % siempre devuelve un resto entero, no podria devolver algo con coma
    printf("%lld \n", resto);                //cosa que este algoritmo es completamente valido
    int minutos = resto / 60;
    int segundos = resto % 60;

    printf("%lld:%02d:%02d\n", horas, minutos, segundos);
}

int main(void) {
    print_hms(3661);   // salida: 1:01:0
    print_hms(59);     // salida: 0:00:59
    return 0;
}
