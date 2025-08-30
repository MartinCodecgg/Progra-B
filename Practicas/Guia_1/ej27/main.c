#include <stdio.h>
#define TOP 20

typedef struct {
    unsigned short fila, col;
    int val;
} Tinfo;

void obtieneArray(int mat[][TOP], unsigned short n, unsigned short m, Tinfo array[],unsigned short *nArray);
//debo usar un "procedimiento" o usar malloc y devolver un puntero, no puedo devolver un array como tal porque es un puntero
int main() {

    unsigned short n = 3, m=3, nArray = 0;
    Tinfo array[TOP];

    int mat[][TOP] = {
                     {1,1,1},
                     {1,1,6},
                     {1,1,36} };

    obtieneArray(mat,n,m,array,&nArray);

    //Adicional muestro el array

    unsigned short i;
    for(i = 0; i < nArray; ++i) {
        printf("fila %hu \n",array[i].fila +1); //le sumo uno porque se cuenta desde el cero
        printf("columna %hu \n",array[i].col +1);
        printf("valor %d \n",array[i].val);
    }
    return 0;
}

void obtieneArray(int mat[][TOP], unsigned short n, unsigned short m, Tinfo array[],unsigned short *nArray) {

    unsigned short i,j;
    Tinfo auxStruct;

    for(i = 0; i<n; ++i)
        for(j = 0; j<m; ++j)
            if (mat[i][j] % (n+m) == 0) {

                auxStruct.fila = i;
                auxStruct.col = j;
                auxStruct.val = mat[i][j];

                array[*nArray] = auxStruct;

                *nArray +=1;
            }
}
