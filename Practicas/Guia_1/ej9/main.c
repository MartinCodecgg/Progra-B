#include <stdio.h>
#include <stdlib.h>

//Reescribir las siguientes sentencias utilizando la instrucción switch:

int main() {

    int x = 4, y;

    if (x == 4)
        y = 7;
    else
        if (x == 5)
            y = 9;
        else
            if(x == 9)
                y = 14;
            else
                y = 22;

    printf("%d \n",y);

    //recreando ahora usando la sentencia switch

    switch (x) {
        case 4: y=7;
            break;
        case 5: y=9;
            break;
        default: y=22;
    }
    printf("%d",y);

}
