#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
using namespace std;
int dart;
float resultado=0;

void dartboard(){
    float x,y,raiz,c;
    for(int i=0;i<dart;i++){
        float ran1_1=0-((float)(rand()) / ((float)(RAND_MAX/(1 - 0))));
        float ran1_2=0-((float)(rand()) / ((float)(RAND_MAX/(1 - 0))));
        x= ran1_1;
        y=ran1_2;
        raiz=sqrt((x*x)+(y*y));
        if(raiz <=1.0){
            c=c+1.0;   
        }
    }  
    resultado=(float)(4.0*(c/dart));
    printf("%f\n", resultado);
}


int main(int argc, char*argv[]){
    srand (time(NULL));

    struct timeval inicio;
    struct timeval fin;
    double milisegundosFinal;
    long segundos, milisegundos;
    dart = strtol(argv[1], NULL, 10);

    gettimeofday(&inicio, 0);

    gettimeofday(&fin, 0);

    segundos = fin.tv_sec - inicio.tv_sec;
    milisegundos = fin.tv_usec - inicio.tv_usec;
    milisegundosFinal = ((segundos)*1000 + milisegundos / 1000.0);

    printf("Tiempo de ejecucion:\t");
    printf("%.16g milisegundos\n", milisegundosFinal);
    dartboard();
    return 0;
}