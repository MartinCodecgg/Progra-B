// Función para cargar la lista circular LC con datos de coches
void cargaLC(TListaC *LC) {
    TListaC nuevo, ultimo;

    // Inicializar la lista circular (nodo fantasma)
    *LC = (TListaC) malloc(sizeof(nodoC));
    (*LC)->sig = *LC;  // Apunta a sí mismo
    ultimo = *LC;

    printf("=== CARGA DE COCHES (AUTOMÁTICA) ===\n");

    // Coche 1
    nuevo = (TListaC) malloc(sizeof(nodoC));
    strcpy(nuevo->patente, "ABC123");
    nuevo->vip = 'S';
    strcpy(nuevo->radio, "U");
    nuevo->cantP = 4;
    nuevo->libre = 'S';
    nuevo->sig = *LC;
    ultimo->sig = nuevo;
    ultimo = nuevo;
    printf("Cargado: %s - VIP:%c - Radio:%s - Pas:%d - Libre:%c\n",
           nuevo->patente, nuevo->vip, nuevo->radio, nuevo->cantP, nuevo->libre);

    // Coche 2
    nuevo = (TListaC) malloc(sizeof(nodoC));
    strcpy(nuevo->patente, "DEF456");
    nuevo->vip = 'N';
    strcpy(nuevo->radio, "R");
    nuevo->cantP = 3;
    nuevo->libre = 'S';
    nuevo->sig = *LC;
    ultimo->sig = nuevo;
    ultimo = nuevo;
    printf("Cargado: %s - VIP:%c - Radio:%s - Pas:%d - Libre:%c\n",
           nuevo->patente, nuevo->vip, nuevo->radio, nuevo->cantP, nuevo->libre);

    // Coche 3
    nuevo = (TListaC) malloc(sizeof(nodoC));
    strcpy(nuevo->patente, "GHI789");
    nuevo->vip = 'S';
    strcpy(nuevo->radio, "I");
    nuevo->cantP = 2;
    nuevo->libre = 'S';
    nuevo->sig = *LC;
    ultimo->sig = nuevo;
    ultimo = nuevo;
    printf("Cargado: %s - VIP:%c - Radio:%s - Pas:%d - Libre:%c\n",
           nuevo->patente, nuevo->vip, nuevo->radio, nuevo->cantP, nuevo->libre);

    // Coche 4
    nuevo = (TListaC) malloc(sizeof(nodoC));
    strcpy(nuevo->patente, "JKL012");
    nuevo->vip = 'N';
    strcpy(nuevo->radio, "U");
    nuevo->cantP = 4;
    nuevo->libre = 'S';
    nuevo->sig = *LC;
    ultimo->sig = nuevo;
    ultimo = nuevo;
    printf("Cargado: %s - VIP:%c - Radio:%s - Pas:%d - Libre:%c\n",
           nuevo->patente, nuevo->vip, nuevo->radio, nuevo->cantP, nuevo->libre);

    // Coche 5
    nuevo = (TListaC) malloc(sizeof(nodoC));
    strcpy(nuevo->patente, "MNO345");
    nuevo->vip = 'S';
    strcpy(nuevo->radio, "R");
    nuevo->cantP = 3;
    nuevo->libre = 'S';
    nuevo->sig = *LC;
    ultimo->sig = nuevo;
    ultimo = nuevo;
    printf("Cargado: %s - VIP:%c - Radio:%s - Pas:%d - Libre:%c\n",
           nuevo->patente, nuevo->vip, nuevo->radio, nuevo->cantP, nuevo->libre);

    printf("\nLista de coches cargada exitosamente.\n\n");
}

// Función para mostrar la lista circular LC
void muestraLC(TListaC LC) {
    TListaC act;
    int cont = 0;

    if(LC == NULL || LC->sig == LC) {
        printf("La lista de coches está vacía.\n");
        return;
    }

    printf("\n=== LISTA DE COCHES (CIRCULAR) ===\n");
    printf("%-10s %-5s %-8s %-10s %-8s\n", "Patente", "VIP", "Radio", "Pasajeros", "Libre");
    printf("---------------------------------------------------\n");

    act = LC->sig;
    while(act != LC) {
        printf("%-10s %-5c %-8s %-10d %-8c\n",
               act->patente,
               act->vip,
               act->radio,
               act->cantP,
               act->libre);
        cont++;
        act = act->sig;
    }

    printf("---------------------------------------------------\n");
    printf("Total de coches: %d\n\n", cont);
}

// Función para mostrar la lista simple enlazada L
void muestraL(TListaL L) {
    TListaL act;
    TElementoC viaje;
    int contCoches = 0, contViajes;

    if(L == NULL) {
        printf("La lista de viajes asignados está vacía.\n");
        return;
    }

    printf("\n=== LISTA DE VIAJES ASIGNADOS ===\n");

    act = L;
    while(act != NULL) {
        printf("\n--- Coche: %s ---\n", act->patente);

        if(VaciaC(act->C)) {
            printf("  Sin viajes asignados.\n");
        } else {
            printf("  %-5s %-8s %-10s\n", "VIP", "Radio", "Pasajeros");
            printf("  ------------------------------\n");

            contViajes = 0;
            // Recorrer la cola sin destruirla
            TCola tempC;
            IniciaC(&tempC);

            while(!VaciaC(act->C)) {
                sacaC(&(act->C), &viaje);
                printf("  %-5c %-8s %-10d\n",
                       viaje.vip,
                       viaje.radio,
                       viaje.cantP);
                poneC(&tempC, viaje);
                contViajes++;
            }

            // Restaurar la cola original
            while(!VaciaC(tempC)) {
                sacaC(&tempC, &viaje);
                poneC(&(act->C), viaje);
            }

            printf("  Total viajes: %d\n", contViajes);
        }

        contCoches++;
        act = act->sig;
    }

    printf("\n-----------------------------------\n");
    printf("Total de coches con viajes: %d\n\n", contCoches);
}

// Función auxiliar para mostrar ambas listas
void muestraAmbas(TListaC LC, TListaL L) {
    muestraLC(LC);
    muestraL(L);
}

// Función para crear archivo de prueba con viajes
void creaArchivoPrueba() {
    FILE *arch = fopen("Viajes.dat", "wb");
    TViaje viajes[10];
    int i;

    if(arch == NULL) {
        printf("Error al crear archivo de prueba\n");
        return;
    }

    // Viaje 1 - Compatible con ABC123 (VIP, U, 3 pas)
    viajes[0].cantP = 3;
    viajes[0].vip = 'S';
    strcpy(viajes[0].radio, "U");

    // Viaje 2 - Compatible con DEF456 (No VIP, R, 2 pas)
    viajes[1].cantP = 2;
    viajes[1].vip = 'N';
    strcpy(viajes[1].radio, "R");

    // Viaje 3 - Compatible con GHI789 (VIP, I, 2 pas)
    viajes[2].cantP = 2;
    viajes[2].vip = 'S';
    strcpy(viajes[2].radio, "I");

    // Viaje 4 - Compatible con JKL012 (No VIP, U, 4 pas)
    viajes[3].cantP = 4;
    viajes[3].vip = 'N';
    strcpy(viajes[3].radio, "U");

    // Viaje 5 - Compatible con MNO345 (VIP, R, 1 pas)
    viajes[4].cantP = 1;
    viajes[4].vip = 'S';
    strcpy(viajes[4].radio, "R");

    // Viaje 6 - Eliminación: 0 pasajeros
    viajes[5].cantP = 0;
    viajes[5].vip = 'N';
    strcpy(viajes[5].radio, "U");

    // Viaje 7 - Otro viaje normal
    viajes[6].cantP = 3;
    viajes[6].vip = 'N';
    strcpy(viajes[6].radio, "R");

    // Viaje 8 - Eliminación: 0 pasajeros
    viajes[7].cantP = 0;
    viajes[7].vip = 'S';
    strcpy(viajes[7].radio, "I");

    // Viaje 9 - Viaje normal
    viajes[8].cantP = 2;
    viajes[8].vip = 'N';
    strcpy(viajes[8].radio, "U");

    // Viaje 10 - Eliminación: 0 pasajeros
    viajes[9].cantP = 0;
    viajes[9].vip = 'N';
    strcpy(viajes[9].radio, "R");

    for(i = 0; i < 10; i++) {
        fwrite(&viajes[i], sizeof(TViaje), 1, arch);
    }

    fclose(arch);
    printf("Archivo Viajes.dat creado con 10 viajes de prueba.\n\n");
}

// Main de prueba completo
void testCompleto() {
    TListaC LC = NULL;
    TListaL L = NULL;
    char pat[ST7];

    printf("\n========================================\n");
    printf("INICIO DE PRUEBAS DEL SISTEMA\n");
    printf("========================================\n\n");

    // 1. Cargar lista de coches
    printf("--- PASO 1: Carga de coches ---\n");
    cargaLC(&LC);

    // 2. Crear archivo de prueba
    printf("--- PASO 2: Creación de archivo de viajes ---\n");
    creaArchivoPrueba();

    // 3. Mostrar lista de coches inicial
    printf("--- PASO 3: Estado inicial de coches ---\n");
    muestraLC(LC);

    // 4. Procesar archivo (asignar viajes)
    printf("--- PASO 4: Procesamiento de viajes ---\n");
    procesaArch(LC, &L);

    // 5. Mostrar ambas listas después del procesamiento
    printf("\n--- PASO 5: Estado después del procesamiento ---\n");
    muestraAmbas(LC, L);

    // 6. Probar función mayorElim
    printf("\n--- PASO 6: Búsqueda de coche con más eliminaciones ---\n");
    mayorElim(L);

    // 7. Probar función eliminaPat
    printf("\n\n--- PASO 7: Eliminación de patente ---\n");
    strcpy(pat, "ABC123");
    printf("Eliminando patente: %s\n", pat);
    eliminaPat(&LC, &L, pat);

    // 8. Mostrar estado final
    printf("\n--- PASO 8: Estado final ---\n");
    muestraAmbas(LC, L);

    printf("\n========================================\n");
    printf("FIN DE PRUEBAS\n");
    printf("========================================\n\n");
}

int main() {
    TListaC LC = NULL;
    TListaL L = NULL;
    char p[ST7];
    //cargaLC(&LC);
    procesaArch(LC,&L);
    printf("Ingrese la patente p que desea eliminar\n");
    scanf("%s", p);
    eliminaPat(&LC,&L,p);
    testCompleto();
    return 0;
}
