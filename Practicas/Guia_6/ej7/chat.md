Usando funciones lo que tendria que hacer es que la funcion de busqueda me retorne el nodo, luego una funcion que desenlace y la otra que enlace (o inserte) ?,  lo que haria ahora seria que creaLibro realmente cree el nodo usando malloc, luego que insertaOrdL lo inserte al nodo, asi tambien puedo reutilizar el insertaOrd para el caso de prestamo y extraccion?, y no haria falta una funcion que desenlance o si?, porque son 4 lineas por ahi, lo puedo hacer facil
ChatGPT Plus

Exacto 👌, lo pensaste bien. Te lo desarmo paso a paso:

1. Separar responsabilidades

Hoy tu insertaOrdL está creando el nodo y lo está insertando.
Lo más limpio es:

crearLibro() → hace el malloc, copia los datos (titulo, autor, anio) y devuelve un Sublista ya listo, pero sin enlazar.

insertaOrdL(L, nodo) → recibe un Sublista ya creado y lo inserta en orden en la lista L.

De esa forma podés reutilizar insertaOrdL tanto cuando agregás un libro nuevo como cuando movés un libro entre listas.

2. Desenlazar

No hace falta hacer una función aparte si no querés, porque son 3–4 líneas (recorrer con ant y act, actualizar punteros). Pero si lo usás mucho, una desenlazaNodo(L, titulo) que te devuelva el Sublista extraído puede venir bien:

Sublista desenlazaNodo(TListaP L, const char *titulo) {
    Sublista ant = NULL, act = L->sub;

    while (act != NULL && strcmp(act->titulo, titulo) != 0) {
        ant = act;
        act = act->sig;
    }
    if (act == NULL) return NULL; // no encontrado

    if (ant == NULL)
        L->sub = act->sig;
    else
        ant->sig = act->sig;

    act->sig = NULL; // lo dejo limpio
    return act;      // lo retorno para reinsertarlo
}

3. Insertar en destino

Con eso, tu prestamo o devolucion quedaría re simple:

void prestamo(TListaP array[], TListaP socios, char autor[], char socio[], char titulo[]) {
    TListaP pAutor, pSocio;
    buscaProp(array[toupper(autor[0]) - 'A'], autor, &pAutor);
    buscaProp(socios, socio, &pSocio);
    if (pSocio == NULL) creaProp(&socios, socio, &pSocio);

    Sublista libro = desenlazaNodo(pAutor, titulo);
    if (libro != NULL) {
        insertaOrdL(pSocio, libro);
    }
}

🔑 Ventajas de este esquema

crearLibro solo crea nodos → una sola responsabilidad.

insertaOrdL solo inserta ordenado → lo podés usar en altas nuevas y en préstamos/devoluciones.

desenlazaNodo es opcional, pero te da simetría y hace más legible el código.

👉 Pregunta: ¿querés que te reescriba tu insertaOrdL y agregaLibro con esta separación (crearLibro + insertaOrdL), para que quede prolijo y reutilizable?


***


Básicamente lo que no hay que hacer en el ejercicio, es hacer malloc cuando quiera mover un nodo, tampoco hay que hacer free en ninguna parte del ejercicio

Para desenlazar nodo simplemente

ant->sig = act->sig;

La variable act como tal la mando a otra función

Para enlazar:

ant->sig = aux;
aux->sig = act;

La función creaProp debería hacer el malloc
Y que la función insertOrd sea la que haga el enlace