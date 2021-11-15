#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
using namespace std;
int dart;
int canthilos;
int contador=0;
float vector_c[50];
float resultado=0;

void *dartboard(void *arg){
    float x,y,raiz,c;
    for(int i=contador*(dart/canthilos);i<(dart/canthilos)*(contador+1);i++){
        float ran1_1=0-((float)(rand()) / ((float)(RAND_MAX/(1 - 0))));
        float ran1_2=0-((float)(rand()) / ((float)(RAND_MAX/(1 - 0))));
        x= ran1_1;
        y=ran1_2;
        raiz=sqrt((x*x)+(y*y));
        if(raiz <=1.0){
            c=c+1.0;   
        }
    }  
    vector_c[contador]=c;
    contador=contador+1;
}


int main(int argc, char*argv[]){
    
    pthread_t h;
    srand (time(NULL));
    //dartboard(dart);
    canthilos = strtol(argv[2], NULL, 10);
    dart = strtol(argv[1], NULL, 10);

    struct timeval inicio;
    struct timeval fin;
    double milisegundosFinal;
    long segundos, milisegundos;

    gettimeofday(&inicio, 0);

    
    for (int i = 0 ; i < canthilos ; i++ ) {
        pthread_create (&h , NULL , &dartboard , NULL) ;
        pthread_join (h , NULL );
    }
    for(int i=0; i< canthilos;i++){
        resultado=vector_c[i]+resultado;
    }

    gettimeofday(&fin, 0);

    segundos = fin.tv_sec - inicio.tv_sec;
    milisegundos = fin.tv_usec - inicio.tv_usec;
    milisegundosFinal = ((segundos)*1000 + milisegundos / 1000.0);

    printf("Tiempo de ejecucion:\t");
    printf("%.16g milisegundos\n", milisegundosFinal);

    resultado=(float)(4.0*(resultado/dart));
    printf("%f\n", resultado);
    
    return 0;
}