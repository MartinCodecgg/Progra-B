#include <stdio.h>

int valida(int a,int b, int c); //poner los parametros igual al nombre las variables, esto no trae problemas

int main() {

    int a = 6,b = 7, c = 8;

    valida(a,b,c) ? printf("Consecutivos") : printf("NO Consecutivos"); //valida(a,b,c) llama a una funcion, no es una expresion, no lleva parentesis aqui

    return 0;
}

int valida(int a,int b, int c) {

    return
        ((b == a+1) && (c == b+1)) || //123
        ((b == a+1) && (c == b+1)) || //132
        ((b == a+1) && (c == b+1)) || //213
        ((b == a+1) && (c == b+1)) || //231
        ((b == a+1) && (c == b+1)) || //312
        ((b == a+1) && (c == b+1))    //321
        ;

        //no usar un if aqui, que retorne el resultado de toda la expresion, el return ya de por si
        // engloba toda la expresio  en un parentesis, por ello no hace falta hacer return ()
}
