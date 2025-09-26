#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para los libros
typedef struct libro {
    char titulo[50];
    char autor[30];
    int anio;
    struct libro * sig;} libro;
typedef libro * TListaLibros;

// Estructura para los autores
typedef struct autor {
    char nombre[30];
    struct autor * sig;
    TListaLibros sublista; } autor; // Sublista de libros del autor
typedef autor * TListaAutores;

// Estructura para los socios
typedef struct socio {
    char nombre[30];
    int numero;
    struct socio * sig;
    TListaLibros prestados; } socio;  // Sublista de libros prestados

typedef socio * TListaSocios;

// Procedimiento para insertar libro ordenado por título en la sublista de un autor
void insertarLibroOrdenado(TListaLibros *lista, char* titulo, char* autorNombre, int anio) {
    TListaLibros nuevo, actual, ant;

    nuevo = (TListaLibros)malloc(sizeof(libro));
    strcpy(nuevo->titulo, titulo);
    strcpy(nuevo->autor, autorNombre);
    nuevo->anio = anio;
    nuevo->sig = NULL;

    if (*lista == NULL || strcmp(nuevo->titulo, (*lista)->titulo) < 0) {
        nuevo->sig = *lista;
        *lista = nuevo;
    } else {
        ant = NULL;
        actual = *lista;
        while (actual != NULL && strcmp(nuevo->titulo, actual->titulo) > 0) {
            ant = actual;
            actual = actual->sig;
        }
        nuevo->sig = actual;
        ant->sig = nuevo;
    }
}

// Procedimiento para insertar autor ordenado alfabéticamente
void insertarAutorOrdenado(TListaAutores *lista, char* nombre) {
    TListaAutores nuevo, actual, ant;

    nuevo = (TListaAutores)malloc(sizeof(autor));
    strcpy(nuevo->nombre, nombre);
    nuevo->sig = NULL;
    nuevo->sublista = NULL;

    if (*lista == NULL || strcmp(nuevo->nombre, (*lista)->nombre) < 0) {
        nuevo->sig = *lista;
        *lista = nuevo;
    } else {
        ant = NULL;
        actual = *lista;
        while (actual != NULL && strcmp(nuevo->nombre, actual->nombre) > 0) {
            ant = actual;
            actual = actual->sig;
        }
        nuevo->sig = actual;
        ant->sig = nuevo;
    }
}

// Procedimiento para insertar socio
void insertarSocio(TListaSocios *lista, char* nombre, int numero) {
    TListaSocios nuevo;

    nuevo = (TListaSocios)malloc(sizeof(socio));
    strcpy(nuevo->nombre, nombre);
    nuevo->numero = numero;
    nuevo->prestados = NULL;
    nuevo->sig = *lista;
    *lista = nuevo;
}

// Procedimiento para buscar autor en una lista
TListaAutores buscarAutor(TListaAutores lista, char* nombre) {
    TListaAutores actual;

    actual = lista;
    while (actual != NULL && strcmp(actual->nombre, nombre) != 0) {
        actual = actual->sig;
    }
    return actual;
}

// Procedimiento para mostrar libros de una sublista
void mostrarLibros(TListaLibros lista) {
    TListaLibros actual;

    actual = lista;
    while (actual != NULL) {
        printf("      - %s (%d)\n", actual->titulo, actual->anio);
        actual = actual->sig;
    }
}

// Procedimiento para mostrar autores de una lista
void mostrarAutores(TListaAutores lista) {
    TListaAutores actual;

    actual = lista;
    while (actual != NULL) {
        printf("  %s:\n", actual->nombre);
        mostrarLibros(actual->sublista);
        actual = actual->sig;
    }
}

// Procedimiento para mostrar socios
void mostrarSocios(TListaSocios lista) {
    TListaSocios actual;

    actual = lista;
    while (actual != NULL) {
        printf("Socio %d - %s:\n", actual->numero, actual->nombre);
        if (actual->prestados != NULL) {
            printf("  Libros prestados:\n");
            mostrarLibros(actual->prestados);
        } else {
            printf("  No tiene libros prestados\n");
        }
        printf("\n");
        actual = actual->sig;
    }
}

// Procedimiento para inicializar biblioteca
void inicializarBiblioteca(TListaAutores biblioteca[26]) {
    int i;
    for (i = 0; i < 26; i++) {
        biblioteca[i] = NULL;
    }
}

// Procedimiento para obtener índice de letra (A=0, B=1, etc.)
int obtenerIndiceletra(char letra) {
    if (letra >= 'A' && letra <= 'Z') {
        return letra - 'A';
    } else if (letra >= 'a' && letra <= 'z') {
        return letra - 'a';
    }
    return 0; // Por defecto letra A
}

// Procedimiento para agregar libro a la biblioteca
void agregarLibroABiblioteca(TListaAutores biblioteca[26], char* titulo, char* autorNombre, int anio) {
    int indice;
    TListaAutores autorEncontrado;

    indice = obtenerIndiceletra(autorNombre[0]);
    autorEncontrado = buscarAutor(biblioteca[indice], autorNombre);

    if (autorEncontrado == NULL) {
        // El autor no existe, crearlo
        insertarAutorOrdenado(&biblioteca[indice], autorNombre);
        autorEncontrado = buscarAutor(biblioteca[indice], autorNombre);
    }

    // Agregar libro a la sublista del autor
    insertarLibroOrdenado(&autorEncontrado->sublista, titulo, autorNombre, anio);
}

// Procedimiento para cargar datos de prueba
void cargarDatosPrueba(TListaAutores biblioteca[26], TListaSocios *socios) {
    // Agregar autores y libros
    agregarLibroABiblioteca(biblioteca, "Fundacion", "Asimov, Isaac", 1951);
    agregarLibroABiblioteca(biblioteca, "Yo, Robot", "Asimov, Isaac", 1950);
    agregarLibroABiblioteca(biblioteca, "El Hombre Bicentenario", "Asimov, Isaac", 1976);

    agregarLibroABiblioteca(biblioteca, "Orgullo y Prejuicio", "Austen, Jane", 1813);
    agregarLibroABiblioteca(biblioteca, "Emma", "Austen, Jane", 1815);

    agregarLibroABiblioteca(biblioteca, "El Aleph", "Borges, Jorge Luis", 1949);
    agregarLibroABiblioteca(biblioteca, "Ficciones", "Borges, Jorge Luis", 1944);

    agregarLibroABiblioteca(biblioteca, "Don Quijote de la Mancha", "Cervantes, Miguel", 1605);

    agregarLibroABiblioteca(biblioteca, "Cien Años de Soledad", "Garcia Marquez, Gabriel", 1967);
    agregarLibroABiblioteca(biblioteca, "El Amor en los Tiempos del Colera", "Garcia Marquez, Gabriel", 1985);

    agregarLibroABiblioteca(biblioteca, "1984", "Orwell, George", 1949);
    agregarLibroABiblioteca(biblioteca, "Rebelion en la Granja", "Orwell, George", 1945);

    // Crear socios
    insertarSocio(socios, "Martinez, Juan", 1);
    insertarSocio(socios, "Lopez, Maria", 2);
    insertarSocio(socios, "Gonzalez, Pedro", 3);
}

// Procedimiento para mostrar biblioteca completa
void mostrarBiblioteca(TListaAutores biblioteca[26]) {
    int i;

    printf("=== BIBLIOTECA ORGANIZADA POR LETRAS ===\n");
    for (i = 0; i < 26; i++) {
        if (biblioteca[i] != NULL) {
            printf("\nLetra %c:\n", 'A' + i);
            mostrarAutores(biblioteca[i]);
        }
    }
}

int main() {

    //=== Codigo para crear las Listas ===

    // Declarar variables
    TListaAutores biblioteca[26];
    TListaSocios socios;

    // Inicializar estructuras
    inicializarBiblioteca(biblioteca);
    socios = NULL;

    // Cargar datos de prueba
    printf("=== CREANDO DATOS DE PRUEBA ===\n\n");
    cargarDatosPrueba(biblioteca, &socios);

    // Mostrar resultados
    mostrarBiblioteca(biblioteca);

    printf("\n=== LISTA DE SOCIOS ===\n");
    mostrarSocios(socios);

    printf("=== ESTRUCTURA CREADA EXITOSAMENTE ===\n");
    printf("Ahora puedes implementar las funciones de:\n");
    printf("- Agregar libros\n");
    printf("- Registrar préstamos\n");
    printf("- Procesar devoluciones\n");

    //=== FIN Codigo para crear las Listas ===



    return 0;
}
