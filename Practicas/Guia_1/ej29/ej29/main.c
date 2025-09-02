#include <stdio.h>

void generaBinario(float temp1, float temp2, float temp3);

void leerBinario();

int main() {

    float temp1 = 25.2, temp2 = 30.0, temp3 = 50.1;

    generaBinario(temp1,temp2,temp3); //En ambos procedimientos se verifica que se hallan abierto bien los archivos
    leerBinario();                    //Entonces no debo preguntar aqui si se creo correctamente para abrirlo

    return 0;
}

void generaBinario(float temp1, float temp2, float temp3) {

    FILE* arch = fopen("temperaturas.dat","wb");

    if (arch == NULL)
        printf("Error al crear el archivo");

    else {
        fwrite(&temp1,sizeof(float),1,arch);
        fwrite(&temp2,sizeof(float),1,arch);
        fwrite(&temp3,sizeof(float),1,arch);
    }
    fclose(arch);
}

void leerBinario() {

    FILE* arch = fopen("temperaturas.dat","rb");
    float temp, acum = 0, min = 9999, max = -9999;
    unsigned int cont = 0;

    if (arch == NULL)
        printf("Error al crear el archivo \n");

    else {
        printf("Archivo abierto correctamente \n");

        while ( fread(&temp,sizeof(float),1,arch) == 1 ) {

                printf("%3.2f\n",temp);

                acum += temp;

                if (temp > max)
                    max = temp;

                if (temp < min)
                    min = temp;

                cont++;
        }
            printf("La temperatura minima fue de: %3.2f \n",min);
            printf("La temperatura maxima fue de: %3.2f \n",max);
            printf("La temperatura promedio fue de: %3.2f \n",acum/cont);
    }
    fclose(arch);
}
