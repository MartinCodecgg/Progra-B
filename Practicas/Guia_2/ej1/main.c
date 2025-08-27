#include <stdio.h>
#include <stdlib.h>

int main() {

    int *p, a = 4, b = 5;

    p = &b;
    *p *= 2; //multiplca a b por 2

    printf("b=%d *p=%d\n", b, *p); // 10 2
    printf("&b=%p p=%p &p=%p\n", &b, p, &p); // direccion de memoria de b , direccion de memoria de b , direccion de memoria de p
                                                //porque recordar que los punteros tambien ocupan cierta memoria, osea que tambien se puede
                                                //obtener la direccion de memoria de un puntero
    b = *p *3; // b = 30

    printf("b=%d *p=%d\n", b, *p); // 30 30
    printf("&b=%p p=%p\n", &b, p); // direccion de memoria de b, direccion de memoria de b

    a = b;  // a == 30
    p = &a; // ahora p apunta a a
    (*p)++; // a = 31

    printf("b=%d a=%d *p=%d\n", b, a, *p); // 30 31 31
    printf("&b=%p &a=%p p=%p &p=%p\n", &b, &a, p, &p); // direccion de memoria de b, direccion de memoria de a, direccion de memoria de a, direccion de memoria de p

    return 0;
}
