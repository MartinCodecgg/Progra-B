#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TOP_NOMBRE 30
#define TOP 50
#define TOTAL_LETRAS 26 //total letras del abecedario

// Estructura para los libros
typedef struct Libro {
    char titulo[TOP], autor[TOP_NOMBRE];
    int anio;
    struct Libro * sig; } Libro;
typedef Libro * Sublista;

// Estructura genérica para autores y socios
typedef struct prop {
    char nombre[TOP_NOMBRE];
    Sublista sub;
    struct prop * sig; } prop;
typedef prop * TListaP;

// Procedimiento para insertar libro ordenado por título en sublista
void insertarLibroOrdenado(Sublista *lista, char* titulo, char* autor, int anio) {
    Sublista nuevo, actual, ant;

    nuevo = (Sublista)malloc(sizeof(Libro));
    strcpy(nuevo->titulo, titulo);
    strcpy(nuevo->autor, autor);
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

// Procedimiento para insertar al final de sublista (para libros prestados)
void insertarLibroAlFinal(Sublista *lista, char* titulo, char* autor, int anio) {
    Sublista nuevo, actual;

    nuevo = (Sublista)malloc(sizeof(Libro));
    strcpy(nuevo->titulo, titulo);
    strcpy(nuevo->autor, autor);
    nuevo->anio = anio;
    nuevo->sig = NULL;

    if (*lista == NULL) {
        *lista = nuevo;
    } else {
        actual = *lista;
        while (actual->sig != NULL) {
            actual = actual->sig;
        }
        actual->sig = nuevo;
    }
}

// Procedimiento para insertar propietario ordenado alfabéticamente
void insertarPropOrdenado(TListaP *lista, char* nombre) {
    TListaP nuevo, actual, ant;

    nuevo = (TListaP)malloc(sizeof(prop));
    strcpy(nuevo->nombre, nombre);
    nuevo->sig = NULL;
    nuevo->sub = NULL;

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

// Procedimiento para insertar socio (al inicio para simplicidad)
void insertarSocio(TListaP *lista, char* nombre) {
    TListaP nuevo;

    nuevo = (TListaP)malloc(sizeof(prop));
    strcpy(nuevo->nombre, nombre);
    nuevo->sub = NULL;
    nuevo->sig = *lista;
    *lista = nuevo;
}

// Procedimiento para buscar propietario en lista
TListaP buscarProp(TListaP lista, char* nombre) {
    TListaP actual;

    actual = lista;
    while (actual != NULL && strcmp(actual->nombre, nombre) != 0) {
        actual = actual->sig;
    }
    return actual;
}

// Procedimiento para mostrar libros de sublista
void mostrarLibros(Sublista lista) {
    Sublista actual;

    actual = lista;
    while (actual != NULL) {
        printf("      - %s (%d)\n", actual->titulo, actual->anio);
        actual = actual->sig;
    }
}

// Procedimiento para mostrar propietarios (autores o socios) y sus libros
void mostrarProps(TListaP lista, char* tipo) {
    TListaP actual;

    actual = lista;
    while (actual != NULL) {
        printf("  %s:\n", actual->nombre);
        if (actual->sub != NULL) {
            if (strcmp(tipo, "socio") == 0) {
                printf("    Libros prestados:\n");
            } else {
                printf("    Libros disponibles:\n");
            }
            mostrarLibros(actual->sub);
        } else {
            if (strcmp(tipo, "socio") == 0) {
                printf("    No tiene libros prestados\n");
            } else {
                printf("    No tiene libros disponibles\n");
            }
        }
        printf("\n");
        actual = actual->sig;
    }
}

// Procedimiento para inicializar arreglo de biblioteca
void inicializarBiblioteca(TListaP biblioteca[26]) {
    int i;
    for (i = 0; i < 26; i++) {
        biblioteca[i] = NULL;
    }
}

// Procedimiento para obtener índice de letra
int obtenerIndiceLetra(char letra) {
    char letraUpper;

    letraUpper = toupper(letra);
    if (letraUpper >= 'A' && letraUpper <= 'Z') {
        return letraUpper - 'A';
    }
    return 0; // Por defecto A
}

// Procedimiento para agregar libro a biblioteca
void agregarLibroABiblioteca(TListaP biblioteca[26], char* titulo, char* autor, int anio) {
    int indice;
    TListaP autorEncontrado;

    indice = obtenerIndiceLetra(autor[0]);
    autorEncontrado = buscarProp(biblioteca[indice], autor);

    if (autorEncontrado == NULL) {
        insertarPropOrdenado(&biblioteca[indice], autor);
        autorEncontrado = buscarProp(biblioteca[indice], autor);
    }

    insertarLibroOrdenado(&autorEncontrado->sub, titulo, autor, anio);
}

// Procedimiento para cargar datos de prueba
void cargarDatosPrueba(TListaP biblioteca[26], TListaP *socios) {
    // Cargar libros en biblioteca
    agregarLibroABiblioteca(biblioteca, "Fundacion", "Asimov, Isaac", 1951);
    agregarLibroABiblioteca(biblioteca, "Yo, Robot", "Asimov, Isaac", 1950);
    agregarLibroABiblioteca(biblioteca, "El Hombre Bicentenario", "Asimov, Isaac", 1976);

    agregarLibroABiblioteca(biblioteca, "Orgullo y Prejuicio", "Austen, Jane", 1813);
    agregarLibroABiblioteca(biblioteca, "Emma", "Austen, Jane", 1815);
    agregarLibroABiblioteca(biblioteca, "Sentido y Sensibilidad", "Austen, Jane", 1811);

    agregarLibroABiblioteca(biblioteca, "El Aleph", "Borges, Jorge Luis", 1949);
    agregarLibroABiblioteca(biblioteca, "Ficciones", "Borges, Jorge Luis", 1944);
    agregarLibroABiblioteca(biblioteca, "Laberintos", "Borges, Jorge Luis", 1962);

    agregarLibroABiblioteca(biblioteca, "Don Quijote de la Mancha", "Cervantes, Miguel", 1605);
    agregarLibroABiblioteca(biblioteca, "Novelas Ejemplares", "Cervantes, Miguel", 1613);

    agregarLibroABiblioteca(biblioteca, "Cien Años de Soledad", "Garcia Marquez, Gabriel", 1967);
    agregarLibroABiblioteca(biblioteca, "El Amor en los Tiempos del Colera", "Garcia Marquez, Gabriel", 1985);
    agregarLibroABiblioteca(biblioteca, "Cronica de una Muerte Anunciada", "Garcia Marquez, Gabriel", 1981);

    agregarLibroABiblioteca(biblioteca, "1984", "George", 1949);
    agregarLibroABiblioteca(biblioteca, "Rebelion en la Granja", "Orwell, George", 1945);
    agregarLibroABiblioteca(biblioteca, "Homenaje a Cataluña", "Orwell, George", 1938);

    // Crear socios
    insertarSocio(socios, "Martinez");
    insertarSocio(socios, "Lopez");
    insertarSocio(socios, "Gonzalez");
    insertarSocio(socios, "Rodriguez, Ana Sofia");
    insertarSocio(socios, "Fernandez, Carlos Alberto");
}

// Procedimiento para mostrar biblioteca completa
void mostrarBiblioteca(TListaP biblioteca[26]) {
    int i;

    printf("=== BIBLIOTECA ORGANIZADA POR LETRAS ===\n");
    for (i = 0; i < 26; i++) {
        if (biblioteca[i] != NULL) {
            printf("\nLetra %c:\n", 'A' + i);
            mostrarProps(biblioteca[i], "autor");
        }
    }
}

// Procedimiento para mostrar estadísticas
void mostrarEstadisticas(TListaP biblioteca[26], TListaP socios) {
    int totalLibros, totalAutores, totalSocios, librosPrestados;
    int i;
    TListaP actual;
    Sublista actualL;

    totalLibros = 0;
    totalAutores = 0;
    totalSocios = 0;
    librosPrestados = 0;

    // Contar libros y autores en biblioteca
    for (i = 0; i < 26; i++) {
        actual = biblioteca[i];
        while (actual != NULL) {
            totalAutores++;
            actualL = actual->sub;
            while (actualL != NULL) {
                totalLibros++;
                actualL = actualL->sig;
            }
            actual = actual->sig;
        }
    }

    // Contar socios y libros prestados
    actual = socios;
    while (actual != NULL) {
        totalSocios++;
        actualL = actual->sub;
        while (actualL != NULL) {
            librosPrestados++;
            actualL = actualL->sig;
        }
        actual = actual->sig;
    }

    printf("\n=== ESTADISTICAS ===\n");
    printf("Total de autores: %d\n", totalAutores);
    printf("Total de libros disponibles: %d\n", totalLibros);
    printf("Total de socios: %d\n", totalSocios);
    printf("Total de libros prestados: %d\n", librosPrestados);
}

//FUNCIONES PROPIAS DEL EJERCICIO Y NO DE LA LECTURA

void agregaLibro(TListaP array[], char autor[], char titulo[], int anio);

void buscaLib(TListaP prop, Sublista * libro, char titulo[]);

void prestamo(TListaP array[],TListaP *socios, char autor[], char socio[], char titulo[]);

void buscaProp(TListaP L,char autor[], TListaP *p);

void creaProp(TListaP *L, char autor[], TListaP *p);

void insertaOrdL(TListaP prop, char autor[], char titulo[], int anio);

void devolucion(TListaP socios, char socio[], char titulo[], TListaP array[]);

void Elimina(TListaP L, char titulo[]);

int main() {

    // === CODIGO PARA CREAR LISTAS (IA)

    // Variables principales
    TListaP array[TOTAL_LETRAS];
    TListaP socios;

    // Inicialización
    inicializarBiblioteca(array);
    socios = NULL;

    printf("=== SISTEMA DE BIBLIOTECA ===\n");
    printf("Cargando datos de prueba...\n\n");

    // Cargar datos de prueba
    cargarDatosPrueba(array, &socios);

    // Mostrar biblioteca
    mostrarBiblioteca(array);

    // Mostrar socios
    printf("\n=== LISTA DE SOCIOS ===\n");
    mostrarProps(socios, "socio");

    // Mostrar estadísticas
    mostrarEstadisticas(array, socios);

    // === CODIGO EJERCICIO (En realida se pedia mover, y lo que hago es duplicar y luego eliminar lo cual no esta bien

    char autor[TOP_NOMBRE], titulo[TOP_NOMBRE],socio[TOP_NOMBRE];
    int anio;
    //cargaAutores(&array); cargaSocios(&socios);

    printf("Ingrese autor,titulo y año del libro a insertar\n");
    scanf(" %s%s%d",autor,titulo,&anio);
    agregaLibro(array,autor,titulo,anio);
    printf("Ingrese autor,socio y titulo para pedir un prestamo\n");
    scanf(" %s%s%s",autor,socio,titulo);
    prestamo(array,&socios,autor,socio,titulo);
    printf("Ingrese socio y titulo para devolver\n");
    scanf(" %s%s",socio,titulo);
    devolucion(socios,socio,titulo,array);


    // PROBANDO CODIGO
    /*
    printf("\n=== PRUEBA: AGREGAR LIBRO ===\n");
    strcpy(autor, "Asimov, Isaac");
    strcpy(titulo, "Robots e Imperio");
    anio = 1985;
    printf("Agregando libro: %s de %s (%d)\n", titulo, autor, anio);
    agregaLibro(array, autor, titulo, anio);

    // Ejemplo de préstamo
    printf("\n=== PRUEBA: REGISTRAR PRESTAMO ===\n");
    strcpy(autor, "Asimov, Isaac");
    strcpy(socio, "Martinez, Juan Carlos");
    strcpy(titulo, "Fundacion");
    printf("Prestando %s de %s a %s\n", titulo, autor, socio);
    prestamo(array, &socios, autor, socio, titulo);

    // Ejemplo de devolución
    printf("\n=== PRUEBA: DEVOLUCION ===\n");
    strcpy(socio, "Martinez, Juan Carlos");
    strcpy(titulo, "Fundacion");
    printf("Devolviendo %s de %s\n", titulo, socio);
    devolucion(socios, socio, titulo, array);

    printf("\n=== FIN DE PRUEBAS ===\n");
    */

    return 0;
}

void agregaLibro(TListaP array[], char autor[], char titulo[], int anio) {

    TListaP L = array[toupper(autor[0])-'A'], p;

    buscaProp(L,autor,&p); //debio ser funcion que retorna puntero

    if(p == NULL)
        creaProp(&L,autor,&p);

    insertaOrdL(p,autor,titulo,anio);
}

void prestamo(TListaP array[],TListaP *socios, char autor[], char socio[], char titulo[]) {

    TListaP L = array[toupper(autor[0]) - 'A'], p, pSocio;
    Sublista plib;

    buscaProp(L,autor,&p);
    buscaLib(p,&plib,titulo);
    buscaProp(*socios,socio,&pSocio);
    if(pSocio == NULL)
        creaProp(socios,socio,&pSocio);

    insertaOrdL(pSocio,plib->autor,plib->titulo,plib->anio);
    Elimina(p,titulo);
}

void buscaProp(TListaP L,char autor[], TListaP *p) {

    TListaP act = L; //quizas falta validar que la lista no sea nula
    while(act != NULL && strcmp(autor,act->nombre) > 0)
        act = act->sig;
    if(act != NULL && strcmp(autor,act->nombre) == 0)
        *p = act;
    else
        *p = NULL;
}
//TListaP L = array
void creaProp(TListaP *L, char autor[], TListaP *p) {
    TListaP aux,ant,act;
    aux = (TListaP) malloc(sizeof(prop));
    strcpy(aux->nombre, autor);
    aux->sub = NULL; //Cuando creo un nuevo nodo, su subLista tiene que apuntar a NULL, tener en cuenta

    if(*L == NULL || strcmp(autor,(*L)->nombre) < 0) {
        aux->sig = *L;
        *L = *p = aux;
    }
    else {
        act = *L;
        while(act != NULL && strcmp(autor,act->nombre) > 0 ) {
            ant = act;
            act = act->sig;
        }
        ant->sig = aux;
        aux->sig = act;
        *p = aux; //tener cuidado con las asignacios multiples, son peligrosas, aqui no se puede hacer hasta que aux tenga su
    }                   //estructura final establecida, ademas son menos claras que las comunes.
}

void insertaOrdL(TListaP L, char autor[], char titulo[], int anio) {
    Sublista act,ant;
    Sublista aux = (Sublista) malloc(sizeof(Libro));
    strcpy(aux->titulo,titulo);
    strcpy(aux->autor,autor);
    aux->anio = anio;
    act = L->sub;

    if(act == NULL || strcmp(titulo,act->titulo) < 0) {
        aux->sig = act;
        L->sub = aux;
    }
    else {
        while(act != NULL && strcmp(titulo,act->titulo) > 0){
            ant = act;
            act = act->sig;
        }
        ant->sig = aux;
        aux->sig = act;
    }
}

void devolucion(TListaP socios, char socio[], char titulo[], TListaP array[]) {

    TListaP p, paut, L;
    Sublista pLib;
    buscaProp(socios,socio,&p);
    buscaLib(p,&pLib,titulo);
    L = array[toupper(pLib->autor[0])-'A'];
    buscaProp(L,pLib->autor,&paut);
    insertaOrdL(paut,pLib->autor,titulo,pLib->anio);
    Elimina(p,titulo);
}

void buscaLib(TListaP L, Sublista * libro, char titulo[]) { //debio ser funcion que retorna puntero
    Sublista act;
    act = L->sub;
    while(act != NULL && strcmp(titulo,act->titulo) > 0)
        act = act->sig;
    *libro = act;
}

void Elimina(TListaP L, char titulo[]) {
    Sublista act,ant;
    ant = NULL;
    if(strcmp(L->sub->titulo, titulo) == 0) {
        act = L->sub;
        L->sub = act->sig;
        free(act);
    }
    else {
        act = L->sub;
        while(act != NULL && strcmp(titulo,act->titulo) > 0) {
            ant = act;
            act = act->sig;
        }
        ant->sig = act->sig;
        free(act);
    }
}
