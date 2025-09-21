#define MAXELEM 100

typedef int TElementoP;
typedef struct{
    int datos[MAXELEM];
    int tope;
} TPila;

void iniciaP(TPila *);
void poneP(TPila *, TElementoP);
void sacaP(TPila *, TElementoP *);
TElementoP consultaP(TPila);
int vaciaP(TPila);
