#include <stdio.h>

int main() {
	int a,i,res;
	printf("Ingrese un numero para calcular su factorial, -1 para finalizar el programa \n");
	scanf("%d",&a);
	do {
        res=1;
        for(i=a;i>1;i--)
        res*=i; //las llaves son opcionales ante una sola sentencia
        printf("%d = %d \n",a,res);
        printf("Ingrese un numero para calcular su factorial, -1 para finalizar el programa \n");
        scanf("%d",&a);
        } while(a != -1);
	return 0;
}
