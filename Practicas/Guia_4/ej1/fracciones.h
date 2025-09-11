#ifndef HEADER_F3117456C0A5956B
#define HEADER_F3117456C0A5956B

#endif // header guard

typedef struct {
    int n,d;
} fraccion;

fraccion crear(int n, int d);
int numerador(fraccion f);
int denominador(fraccion f);
fraccion sumar(fraccion f1, fraccion f2);
fraccion simplificar(fraccion f);
int iguales(fraccion f1, fraccion f2);
