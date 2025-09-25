//NO TERMINE DE COMPROBAR LA LOGICA EL EJERCICIO
/*
4. Corregir los errores en el siguiente programa, el cual incorpora en una lista ordenada de
números los elementos de un arreglo de N números ordenados, respetando el orden de la lista.
*/

#define N 2 //1) Error falta #include <stdio.h> //

void main(){
 int i, arr[N] = {4,8,9,60};  //N esta en 2 y el array tiene 4 elementos.

 TLISTA lista=NULL, pult=NULL, act, ant, nuevo;

 cargarLista(&lista); //2) No se pasa el vector como parametro

 printf("\nLista Original\n");

 muestra(&lista); //2) esta mal pasar la lista como referencia si solo la voy a mostrar y no modificare la cabecera por elde
 act = lista;       // 3) Esta logica debe ir en una funcion aparte
 ant = NULL;
 for(i=0; i<=N; i++) { // deberia ser i<N porque asi hace una iteracion de mas
 while(act!=NULL && arr[i] <= act->n) { //deberia ser array[i] >=
 act = ant;
 act = act.sig; //deberia ser act->sig
 }
 *nuevo = (TLISTA)malloc(sizeof(NODO)); //nuevo ya es Tlista, no deberia ser *nuevo, sino mas bien solo nuevo, ya que malloc devuelve un puntero
 nuevo->n = arr[i-1]; //a que se refiere con n?, si fuese la cantidad de elementos, pero dado como esta el for esto estaria
 if(ant = NULL) { //ant == NULL
 nuevo->sig = lista;
 *lista = &nuevo;  //es simplemente lista = nuevo; porque ambos ya son punteros, ademas estamos en el main
 }                  //nose si la logica esta del todo bien
 else {
 nuevo->sig = ant;
 ant->sig = &nuevo; //nuevamente no va ampersand
 }
 act = nuevo->sig;
 }
 printf("\nLista Resultado\n");
 muestra(&lista);  //nuevamente no va &
}

