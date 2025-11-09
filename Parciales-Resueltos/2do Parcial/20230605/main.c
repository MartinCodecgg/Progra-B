//ejercicio 2) b
//verif con sonnet 4.5
int existe(ArbolG AG, Pos p, int G, int acum) {
    int gr = 0, dato;
    Pos c;
    if(Nulo(p))
        return 0;
    else {
        dato = Info(p, AG);
        c = hijoMasIzq(p,AG);
        while(!Nulo(c) && acum <= 1) {
            gr++;
            acum = existe(AG, c, G, acum); //esta es otra forma de sumar el acum, paso el mismo por parametro
            c = hnoDer(c, AG); // y devuelvo el acum incrementado si alguno de los nodos inferiores cumplio, de hacer en el 
        }                           // while acum += estaria sumando dos veces el mismo nodo que cumplia la condicion, 
        acum += gr == G && dato % 2 != 0 && dato < 0; // ya con el propio return estoy sumando una vez

        return acum;
    }
}
//llamada main: existe(AG, Raiz(AG), G, 0) == 1 ? printf("Cumple\n"); : printf("No cumple\n");

