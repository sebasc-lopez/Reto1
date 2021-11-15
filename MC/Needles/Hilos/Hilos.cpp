#include <iostream>
#include <random>
#include <math.h>
#include <pthread.h>
#include <time.h>

using namespace std;

float piso=2.0;
long long int iteraciones;
float L=1.0;
int canthilos;
float x;
float o;
int dentro = 0;
int contador=0;
int vector_dentro[30];
float resultado=0;

float crearNeedle(){
    x = ((float)(rand()) / ((float)(RAND_MAX/(1 - 0))))*piso;
    o = ((float)(rand()) / ((float)(RAND_MAX/(1 - 0))))*M_PI;   
}


bool interseptan(){
    float xDerecha = x + L / 2 * sin(o);
    float xIzquierda = x - L / 2 * sin(o);

    return xDerecha > piso|| xIzquierda < 0.0;
}


void *probabilidad(void *arg){   
    for(int i=contador*(iteraciones/canthilos) ; i<(iteraciones/canthilos)*(contador+1); i++){
        crearNeedle();
        if (interseptan()){
            dentro = dentro + 1;
        } 
    }
    contador=contador+1;
    vector_dentro[contador]=dentro;


    //return (float)dentro/iteraciones;
}

int main(int argc, char *argv[])
{
    pthread_t h;
    srand (time(NULL));
    //dartboard(dart);

    struct timeval inicio;
    struct timeval fin;
    double milisegundosFinal;
    long segundos, milisegundos;
    iteraciones = strtol(argv[1], NULL, 10);
    canthilos = strtol(argv[2], NULL, 10);

    gettimeofday(&inicio, 0);

    for (int i = 0 ; i < canthilos; i++ ) {
        pthread_create (&h , NULL , &probabilidad , NULL) ;
        pthread_join (h , NULL );
    }

    gettimeofday(&fin, 0);

    segundos = fin.tv_sec - inicio.tv_sec;
    milisegundos = fin.tv_usec - inicio.tv_usec;
    milisegundosFinal = ((segundos)*1000 + milisegundos / 1000.0);

    printf("Tiempo de ejecucion:\t");
    printf("%.16g milisegundos\n", milisegundosFinal);


    FILE *archivo;
    archivo = fopen("documento.txt", "a");
    fprintf(archivo, "%d\n", iteraciones);
    fprintf(archivo, "%.16g\n", milisegundosFinal);


    /*for (int i=0; i<canthilos;i++){
        resultado=resultado+vector_dentro[i];
    }
    resultado=(float)dentro/iteraciones;
    printf("%f", 1/resultado);*/
 
    return 0;
}