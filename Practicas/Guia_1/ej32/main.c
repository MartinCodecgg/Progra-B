#include <stdio.h>
#include <string.h>
#define TOP 20

typedef struct {
    char ciudad[TOP];
    unsigned short dia;
    float tempMax,tempMin;
} Treg;

int main() {

    //genero binario
    FILE* arch = fopen("temperaturas.txt","rt");
    Treg reg;

    if (arch == NULL)
        printf("Error al abrir el archivo de texto\n");

    else {
        FILE* binario = fopen("temperaturas.dat","wt"); //abrir el binario solo si abrio correctamente el archivo de texto
        while( fscanf(arch,"%20s %hu %f %f", reg.ciudad, &reg.dia, &reg.tempMax,&reg.tempMin) == 4) {

            printf("%20s %hu %3.2f %3.2f\n",reg.ciudad, reg.dia, reg.tempMax,reg.tempMin);
            fwrite(&reg,sizeof(Treg),1,binario);
        }
        fclose(arch);
        fclose(binario);


    //Binario creado => Comienza ejercicio

    binario = fopen("temperaturas.dat","rt");
    unsigned short diaMin;
    float tempMin = 99999;
    char ciudadMin[TOP];

    if (binario == NULL)
        printf("Error al abrir el binario para lectura");

    else {
        printf("Archivo binario abierto de forma exitosa\n");
        while ( fread(&reg,sizeof(Treg),1,binario) == 1) {

            printf("%20s %hu %3.2f %3.2f \n",reg.ciudad, reg.dia, reg.tempMax,reg.tempMin);

            if (reg.tempMin < tempMin) {
                tempMin = reg.tempMin;
                strcpy(ciudadMin,reg.ciudad);
                diaMin = reg.dia;
            }

        }
        printf("La ciudad con menor temperatura en el mes fue %20s en el dia %hu \n",ciudadMin,diaMin);
    }
  }

    return 0;
}
