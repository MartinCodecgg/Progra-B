#include <stdio.h>
#define N 50

typedef struct {
    int origen, destino, peso;
} Tarista;

void reevaluaV(int CC[], int n, int v1, int v2) {
    int i;
    for(i = 0; i<n; i++)
        if(CC[i] == v2)
            CC[i] = v1;
}

int kruscal(int mat[][N], int n, Tarista arbolGen[]) {
   int nArbolGen = 0, CC[N], i,j, costoMin, Vmin, adyMin;
   for(i = 0; i < n; i++)
        CC[i] = i;
   while(nArbolGen < n-1) {
        costoMin = 99999;
        for(i = 0; i < n-1; i++)
                for(j = i+1; j < n; j++)
                    if(mat[i][j] != 0 && mat[i][j] < costoMin && CC[i] != CC[j]) {
                        costoMin = mat[i][j];
                        Vmin = i;
                        adyMin = j;
                    }
        reevaluaV(CC,n,CC[Vmin],CC[adyMin]);
        arbolGen[nArbolGen] = (Tarista) {Vmin, adyMin, costoMin};
        nArbolGen++;
   }
}
//llamada main: kruscal(mat,n,arbolGen);

int main() {
    int mat[N][N], n;
    Tarista arbolGen[N];
    kruscal(mat, n, arbolGen);
    return 0;
}
