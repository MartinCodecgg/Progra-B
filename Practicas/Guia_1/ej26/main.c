#include <stdio.h>
#define LEN 20
#define MATR 10

typedef struct {
    char nombre[LEN];
    char matricula[MATR];
    float prom; } Tpersona;

void leer(Tpersona *persona);

int main() {

    Tpersona persona;

    leer(&persona);

    //Adicional muestro la estructura generada:

    printf("%s ",persona.nombre); //persona y nombre ya son arrays, por ello aqui no se usa el ampersand &

    printf("%s ",persona.matricula);

    printf("%3.2f",persona.prom);

    return 0;
}

void leer(Tpersona *persona) {

    printf("Ingrese nombre de la persona \n");
    scanf(" %s", persona->nombre); //persona y nombre ya son arrays, por ello aqui no se usa el ampersand &

    printf("Ingrese matricula de la persona \n");
    scanf(" %s", persona->matricula);

    printf("Ingrese promedio de la persona \n");
    scanf(" %f", &persona->prom); //Aqui si ya que ya prom no es puntero originalmente
}
