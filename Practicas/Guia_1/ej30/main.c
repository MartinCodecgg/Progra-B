#include <stdio.h>

int main() {

    FILE * arch = fopen("radar.txt","rt");
    FILE * binario = fopen("multas.dat","wb");
    char pat[8]; //añadir un byte mas para el caracter nulo
    char fecha[17];
    unsigned short int vel,max,generados = 0, cont = 0;

    if (arch == NULL || binario == NULL)
        printf("Error al abrir el archivo");

    else {
        printf("archivos abiertos/creados correctamente \n");
        while (fscanf(arch,"%7s %hu %hu %[^\n]\n",pat,&vel,&max,fecha) == 4) {
                if (vel > 1.2 * max) {
                    fwrite(pat,7 * sizeof(char),1, binario); //pat ya es un puntero, no hace falta usar &
                    fwrite(&vel,sizeof(unsigned short),1, binario);
                    fwrite(&max,sizeof(unsigned short),1, binario);
                    fwrite(fecha,16 * sizeof(char),1, binario);
                    generados++;
                }
                cont++;
        }
        printf("La cantidad de registros generados es: %hu \n",generados);
        printf("La cantidad de mediciones procesadas es: %hu \n",cont);

        fclose(arch);
        fclose(binario);
    }

    //Adicional muestro el binario generado

    binario = fopen("multas.dat","rb");

    if (binario == NULL)
        printf("Error al abrir el binario para lectura");

    else {
        printf("Binario abierto correctamente para lectura \n");
        while (fread(pat,7 * sizeof(char),1, binario) == 1) {

                    fread(&vel,sizeof(unsigned short),1, binario);
                    fread(&max,sizeof(unsigned short),1, binario);
                    fread(fecha,16 * sizeof(char),1, binario);

                    printf("%7s %hu %hu %s\n",pat,vel,max,fecha);
        }
    }
    return 0;
}
