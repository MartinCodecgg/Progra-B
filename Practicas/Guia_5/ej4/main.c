#include <stdio.h>
#include "colas.h"

int main() {

    TCola C;

    TElementoC elem;

    IniciaC(&C);

    cargaC(&C);

    //muestraEnteros(&C); //DESCOMENTAR PARA PROBAR EL EJERCICIO A, porque destruye la informacion necesaria para el c

    muestraManteniendo(&C);



    return 0;
}
