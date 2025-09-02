#include <stdio.h>
#include <string.h>
#define TOP 20

void busca(unsigned int pos);

int main() {

    //Genero archivo binario desde txt

    FILE * arch = fopen("ranking.txt","rt");
    char apelYnom[TOP], nacio[TOP];
    float punt;

    if (arch == NULL)
        printf("Error al abrir el archivo de texto");

    else { //este else debe englobar todo el codigo, ya que no tiene sentido seguir ejecutando si no genere el binario
        printf("Archivo de texto abierto correctamente \n");
        FILE * binario = fopen("ranking.dat","wb");

        if (binario == NULL)
            printf("Error al crear archivo binario");

        else {
            printf("archivo binario abierto correctamente \n");
        /*
        while( fscanf(arch,"%[^\n]%s\n%f\n",apelYnom,nacio,&punt) == 3) { //No se puede leer con scanf usando [^\n] intermedio, solo al final es valido
            fwrite(apelYnom,TOP * sizeof(char),1,binario);
            fwrite(nacio,TOP * sizeof(char),1,binario);
            fwrite(&punt,sizeof(float),1,binario);
        }
        */

        while( fgets(apelYnom,TOP,arch) != NULL ) {
            fgets(nacio, TOP, arch);
            fscanf(arch, "%f\n", &punt);

            // Quitar salto de línea
            apelYnom[strcspn(apelYnom, "\n")] = '\0';
            nacio[strcspn(nacio, "\n")] = '\0';

            fwrite(apelYnom,TOP * sizeof(char),1,binario);
            fwrite(nacio,TOP * sizeof(char),1,binario);
            fwrite(&punt,sizeof(float),1,binario);
        }
        fclose(binario);
        fclose(arch);


    //Una vez generado el archivo binario para el ejercicio

    unsigned int pos;

    printf("Ingrese la posicion a buscar en el archivo binario \n");
    scanf("%u",&pos);

    busca(pos);
    }
    }

    return 0;
}

void busca(unsigned int pos) {

    FILE * binario = fopen("ranking.dat","rb");
    char apelYnom[TOP], nacio[TOP];
    float punt;

    if (binario == NULL)
        printf("Error al crear el binario");

    else {
        printf("Binario abierto para lectura correctamente \n");

        fseek(binario, pos * (2*TOP + sizeof(float)), SEEK_SET); //RECORDAR que el fseek() funciona con bytes, es decir le
        fread(apelYnom,TOP * sizeof(char), 1, binario);          //debemos pasar los bytes que debe desplazarse,
        fread(nacio,TOP * sizeof(char), 1, binario);    //y todos los registros tienen la misma cantidad de datos reservada
        fread(&punt,sizeof(float), 1, binario);         //2* TOP por las dos cadenas + el dato tipo float

        printf("%s %s %3.2f",apelYnom,nacio,punt);

        fclose(binario);
    }
}
