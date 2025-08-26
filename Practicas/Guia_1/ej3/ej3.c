#include <stdio.h>

#include <conio.h>

int main() {

//a

char A;
A = 'a';
printf(" %c ", A); //a
printf(" %d ", A); //como usamos d, imprime como numero entero, esto en C imprime 97 el numero asociado al caracter
// a o A es igual a 97, entonces al aplicar la suma se convierte en 107, equivalente al caracter (k)
A = 'a' + 10;
printf(" %c ", A); //k
printf(" %d ", A); //107

//b

int B;
B = 5;
printf(" %d ", B); //5
printf(" %c ", B); //err o en realidad indefinido pues el caracter asociado al codigo 5 no es imprimible
B = 5 + 'A'; //codigo ascii 70
printf(" %d ", B); //70
printf(" %c ", B); //F

//c

#define num 15

printf(" %d ", num); //imprime 15
printf(" %c ", num); //el codigo ASCII 15 es no legible, no imprime nada

//d

#define num 15
num = 5 + 'A'; //err la constante no puede cambiar de valor , aunque el codigo se ejecuta igual
printf(" %d ", num);
printf(" %c ", num);














}
