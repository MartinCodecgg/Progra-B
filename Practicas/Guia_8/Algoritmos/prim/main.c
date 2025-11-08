#include <stdio.h>
#define N 50
//(ignorar, algoritmo ineficiente)
void prim(int ady[][N], int T[][N], int limN) {
    int i, imin, j, jmin, min, u[N] = {0}, disp = limN - 1;

    scanf("%d",&i);
    u[i-1] = 1;
    while(disp) { 
        min = 9999;
        for(i = 0; i < limN; i++)
            if(u[i]) 
                for(j = 0; j < limN; j++)
                    if(ady[i][j] != 0 && ady[i][j] < min && u[j]) {
                        min = ady[i][j];
                        imin = i;
                        jmin = j;
                    }
        u[jmin] = 1;
        T[imin][jmin] = T[jmin][imin] =  min;
        disp--;
    }
}