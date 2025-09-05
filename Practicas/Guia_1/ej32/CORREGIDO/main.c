#include <stdio.h>
#include <string.h>
#define TOP 21

#pragma pack(push,1)
typedef struct {
    char ciudad[TOP];
    unsigned short dia;
    float tempMax,tempMin;
} Treg;
#pragma pack(pop)

int main() {

    //Binario creado => Comienza ejercicio

    FILE * binario = fopen("temperaturas8_2.dat","rb");

    if(binario == NULL)
        printf("Ocurrio un error al abrir el binario");
    else {

    Treg reg;
    unsigned short diaMin;
    float tempMin,Gmin,tempMax;
    char ciudadMin[TOP],actCiudad[TOP];
    //Si tenemos que hacer un corte de control o enfrentamiento ya la forma alternativa de lectura no nos sirve

        printf("Archivo binario abierto de forma exitosa\n");
        Gmin = 99999;
        fread(&reg,sizeof(Treg),1,binario);
        while(!feof(binario)) {
            printf("Lectura: %20s %hu %3.2f %3.2f\n",reg.ciudad, reg.dia, reg.tempMax,reg.tempMin);
            strcpy(actCiudad,reg.ciudad);
            tempMin = 9999;
            tempMax = -9999;
            while(!feof(binario) && strcmp(reg.ciudad,actCiudad) == 0) { //No hacer reg.ciudad == actCiudad, para comparar debo usar strcmp
                                                                //Con strcmp si son iguales devuelve cero
                if (reg.tempMin < tempMin)
                    tempMin = reg.tempMin;

                if (reg.tempMax > tempMax)
                    tempMax = reg.tempMax;

                if (reg.tempMin < Gmin) {
                    Gmin = reg.tempMin;
                    strcpy(ciudadMin,reg.ciudad);
                    diaMin = reg.dia;
                }

                fread(&reg,sizeof(Treg),1,binario);
            }
            printf("De la ciudad %s, el dia la menor temperatura registrada fue de: %3.2f y la mayor registrada fue de %3.2f\n",actCiudad,tempMin,tempMax);
        }
        printf("La ciudad con menor temperatura en el mes fue %20s en el dia %hu \n",ciudadMin,diaMin);
    }
    return 0;
}
