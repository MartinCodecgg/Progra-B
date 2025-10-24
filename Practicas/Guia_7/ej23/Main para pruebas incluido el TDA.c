#include <stdio.h>
#include <stdlib.h>

// ==================== DEFINICIONES DEL TDA ====================

typedef struct Nodo {
    int info;
    struct Nodo *hijoIzq;    // Primer hijo
    struct Nodo *hnoDer;      // Hermano derecho
} Nodo;

typedef Nodo* Pos;
typedef Nodo* ArbolG;

// ==================== PRIMITIVAS DEL TDA ====================

int Nulo(Pos p) {
    return p == NULL;
}

Pos Raiz(ArbolG A) {
    return A;
}

int Info(Pos p, ArbolG A) {
    if (p != NULL)
        return p->info;
    return -1; // Error
}

Pos HijoMasIzq(Pos p, ArbolG A) {
    if (p != NULL)
        return p->hijoIzq;
    return NULL;
}

Pos HnoDer(Pos p, ArbolG A) {
    if (p != NULL)
        return p->hnoDer;
    return NULL;
}

// ==================== FUNCIONES AUXILIARES ====================

Pos crearNodo(int valor) {
    Pos nuevo = (Pos)malloc(sizeof(Nodo));
    nuevo->info = valor;
    nuevo->hijoIzq = NULL;
    nuevo->hnoDer = NULL;
    return nuevo;
}

void agregarHijo(Pos padre, Pos hijo) {
    if (padre->hijoIzq == NULL) {
        padre->hijoIzq = hijo;
    } else {
        Pos temp = padre->hijoIzq;
        while (temp->hnoDer != NULL) {
            temp = temp->hnoDer;
        }
        temp->hnoDer = hijo;
    }
}

// Crear el árbol del ejercicio 22
ArbolG crearArbolEjemplo() {
    // Nivel 1
    Pos B = crearNodo(2);

    // Nivel 2
    Pos C = crearNodo(3);
    Pos D = crearNodo(5);

    // Nivel 3
    Pos E = crearNodo(7);
    Pos F = crearNodo(3);
    Pos G = crearNodo(11);
    Pos H = crearNodo(1);
    Pos L = crearNodo(13);

    // Nivel 4
    Pos I = crearNodo(17);
    Pos J = crearNodo(19);
    Pos K = crearNodo(23);
    Pos M = crearNodo(29);

    // Construir el árbol
    agregarHijo(B, C);
    agregarHijo(B, D);

    agregarHijo(D, E);
    agregarHijo(D, F);
    agregarHijo(D, G);
    agregarHijo(D, H);
    agregarHijo(D, L);

    agregarHijo(F, I);
    agregarHijo(F, J);
    agregarHijo(F, K);

    agregarHijo(H, M);

    return B;
}

void liberarArbol(Pos p) {
    if (!Nulo(p)) {
        liberarArbol(p->hijoIzq);
        liberarArbol(p->hnoDer);
        free(p);
    }
}

// ==================== FUNCIONES DEL EJERCICIO 23 ====================

int cantN(ArbolG A, Pos p) {
    Pos c;
    unsigned int cont = 0;

    if(!Nulo(p)) {
        c = HijoMasIzq(p, A);
        while(!Nulo(c)) {
            cont += cantN(A, c);
            c = HnoDer(c, A);
        }
        return cont + 1;
    }
    else
        return 0;
}

void porcentaje(ArbolG A, Pos p, int *contNodos, int *contPares) {
    Pos c;
    if(!Nulo(p)) {
        *contNodos += 1;
        if(Info(p, A) % 2 == 0)
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
    unsigned gr = 0;
    if(!Nulo(p)) {
        c = HijoMasIzq(p, A);
        while(!Nulo(c)) {
            gr++;
            hallaGrado(A, c, gradoMax);
            c = HnoDer(c, A);
        }
        if(gr > *gradoMax)
            *gradoMax = gr;
    }
}

int cantNImpar(ArbolG A, Pos p, int nivel) {
    Pos c;
    int tot = 0, gr = 0;
    nivel++;
    if(!Nulo(p)) {
        c = HijoMasIzq(p, A);
        while(!Nulo(c)) {
            gr++;
            tot += cantNImpar(A, c, nivel);
            c = HnoDer(c, A);
        }
        if(gr % 2 != 0 && nivel % 2 != 0)
            tot++;
    }
    return tot;
}

int verifInt(ArbolG A, Pos p) {
    Pos c;
    int contHijos = 0, HijoCumple = 1, esHoja = 0;
    if(!Nulo(p)) {
        c = HijoMasIzq(p, A);
        if(Nulo(c))
            esHoja = 1;
        while(!Nulo(c) && HijoCumple) {
            contHijos++;
            HijoCumple = verifInt(A, c);
            c = HnoDer(c, A);
        }
        if(esHoja)
            return 1;
        else
            return (HijoCumple && contHijos == Info(p, A));
    }
    return 1;
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
        if(!esHoja && contHijos != Info(p, A))
            *cond = 0;
    }
}

void promedio(ArbolG A, Pos p, int k, int nivel, int *acum, int *cont) {
    Pos c;

    if(!Nulo(p)) {
        if(nivel == k) {
            *acum += Info(p, A);
            (*cont)++;
        }
        if(nivel < k) {
            c = HijoMasIzq(p, A);
            while(!Nulo(c)) {
                promedio(A, c, k, nivel + 1, acum, cont);
                c = HnoDer(c, A);
            }
        }
    }
}

// ==================== FUNCIÓN MAIN ====================

int main() {
    ArbolG A;
    int gradoMax = 0, cond = 1, contNodos = 0, contPares = 0, k, acum = 0, cont = 0;

    printf("=== CREANDO ÁRBOL DE EJEMPLO ===\n");
    printf("Estructura del árbol:\n");
    printf("        B(2)\n");
    printf("       /   \\\n");
    printf("     C(3)  D(5)\n");
    printf("          /|||||\\\n");
    printf("        E F G H L\n");
    printf("         /||\\\n");
    printf("        I J K\n");
    printf("             |\n");
    printf("             M\n\n");

    A = crearArbolEjemplo();

    // a) Cantidad de nodos
    printf("a) Cantidad de nodos: %d\n", cantN(A, Raiz(A)));

    // b) Porcentaje de pares
    porcentaje(A, Raiz(A), &contNodos, &contPares);
    if(contNodos > 0)
        printf("b) Porcentaje de claves pares: %.2f%%\n", (float)contPares/contNodos * 100);

    // c) Grado del árbol
    hallaGrado(A, Raiz(A), &gradoMax);
    printf("c) Grado del árbol: %d\n", gradoMax);

    // d) Nodos de grado impar en niveles impares
    printf("d) Nodos de grado impar en niveles impares: %d\n", cantNImpar(A, Raiz(A), 0));

    // e) Verificar propiedad (versión int)
    if(verifInt(A, Raiz(A)))
        printf("e) Cumple la propiedad (verifInt)\n");
    else
        printf("e) NO cumple la propiedad (verifInt)\n");

    // e) Verificar propiedad (versión void)
    cond = 1;
    verifVoid(A, Raiz(A), &cond);
    if(cond)
        printf("   Cumple la propiedad (verifVoid)\n");
    else
        printf("   NO cumple la propiedad (verifVoid)\n");

    // f) Promedio del nivel k
    printf("\nf) Ingrese el nivel K para calcular el promedio: ");
    scanf("%d", &k);
    acum = 0;
    cont = 0;
    promedio(A, Raiz(A), k, 1, &acum, &cont);
    if(cont > 0)
        printf("   El promedio del nivel %d es: %.2f\n", k, (float)acum/cont);
    else
        printf("   No hay nodos en el nivel %d\n", k);

    // Liberar memoria
    liberarArbol(A);

    return 0;
}
