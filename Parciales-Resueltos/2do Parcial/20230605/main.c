//ejercicio b

int existe(ArbolG AG, Pos p, int G, int acum) {
    int gr = 0, aux;
    Pos c;
    if(!Nulo(p))
        return 0;
    else {
        c = hijoMasIzq(p,AG);
        while(!Nulo(c) && acum <= 1) {
            gr++;
            acum += existe(AG, c, G, acum);
            c = hnoDer(c, AG);
        }
        aux = Info(c, AG);
        acum += gr == G && aux % 2 == 0 && aux < 0;
        return acum == 1;
    }
}
//llamada main: existe(AG, Raiz(AG), G, 0) ? printf("Cumple\n"); : printf("No cumple\n");

