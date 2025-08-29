#include <stdio.h>
#define TOP 100
                    //En declaraciones de funciones las matrices siempre deben llevar su cantidad de columnass
void busca(int mat[][TOP],unsigned short *n,unsigned short *m, int *x,short *posX,short *posY);

void muestraProm(int mat[][TOP],unsigned short *n,unsigned short *m, float *prom);

void muestra2(int mat[][TOP],unsigned short *n,unsigned short *m, float *prom);

int main() {

    unsigned short n,m,i,j;
    short posX = -1,posY = -1;
    float prom; //este es el promedio de toda la matriz
    int mat[TOP][TOP], x; //Cuando defino sin asignacion debo definir las dos dimensiones

    printf("Ingrese N y M \n");
    scanf(" %hu %hu",&n,&m);

    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            scanf(" %d",&mat[i][j]);

    printf("Ingrese el valor a buscar \n");
    scanf(" %d",&x);

    busca(mat,&n,&m,&x,&posX,&posY);

    if (posX != -1 && posY != -1) //recordar que debo validar que sea distinto de -1 porque cero ahora es valido
        printf("Las posiciones del valor ingresado en la matriz son: %hd %hd \n",posX,posY);
    else
        printf("El valor no existe");

    muestraProm(mat,&n,&m,&prom);

    muestra2(mat,&n,&m,&prom);

    return 0;
}

void busca(int mat[][TOP],unsigned short *n,unsigned short *m, int *x,short *posX, short *posY) {

    short i = 0, j, cond = 0;

    while (i<*n && !cond) { //no es valido hacer !=cond ??????,  => mejor usar cond == 0:
                                // => Lo correcto en realidad hubiese sido hacer !cond ya que el ! es el que niega
        j = 0;

        while (mat[i][j] != *x && j<*n)
            ++j;

        if (mat[i][j] == *x) {
            cond = 1;
            *posX = i;
            *posY = j;
        }
        else
            ++i;
    }
}

void muestraProm(int mat[][TOP],unsigned short *n,unsigned short *m, float *prom) {

    unsigned short i,j;
    int sum = 0;

    for (j = 0; j < *m; ++j) {
        for (i = 0; i < *n; ++i)
            sum += mat[i][j];

        printf("El promedio de la columna %d es : %3.2f \n", j, (float) sum / *n); //3.2 es maximo 3 digitos antes de la coma y 2 decimales
        *prom +=sum;
        sum = 0;
    }
    *prom /= (*n) * (*m);
}

void muestra2(int mat[][TOP],unsigned short *n,unsigned short *m, float *prom) {

    printf("Inciso C \n");

    printf("promedio de la matriz es: %3.2f \n",*prom);

    unsigned short i,j,tieneCero,cont;

    for (i = 0; i < *n; ++i) {
        tieneCero = 0;
        cont = 0;
        for (j = 0; j < *m; ++j) {
            if (mat[i][j] == 0)
                tieneCero = 1;

            if (mat[i][j] > *prom)
                ++cont;                 //Recordar para contadores siempre usar ++
        }
        if (tieneCero)
            printf("La cantidad de elementos que superan el promedio de la fila %hu es: %hu\n",i,cont);
    }
}
