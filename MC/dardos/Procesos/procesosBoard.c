#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>


int dart;
int canthilos;
int contador=0;
float *vector_c;
float resultado=0;




int dartboard(int arg){
    float x,y,raiz,c=0.0;
    printf("%d\n",arg);
    for(int i=arg*(dart/canthilos);i<(dart/canthilos)*(arg+1);i++){
        float ran1_1=0-((float)(rand()) / ((float)(RAND_MAX/(1 - 0))));
        float ran1_2=0-((float)(rand()) / ((float)(RAND_MAX/(1 - 0))));
        x= ran1_1;
        y=ran1_2;
        raiz=sqrt((x*x)+(y*y));
        if(raiz <=1.0){
            printf("%f\n",c);
            c=c+1.0;   
        }
    }  
    vector_c[arg]=c;

    return 0;
}


int main(int argc, char*argv[]){
    
    int rank;
    pid_t pid;
    int status;
    srand (time(NULL));

    dart = strtol(argv[1], NULL, 10);
    canthilos = strtol(argv[2], NULL, 10);

    vector_c = mmap(NULL, canthilos * sizeof(float),
              PROT_READ | PROT_WRITE,
              MAP_SHARED | MAP_ANONYMOUS,
              0, 0);

    contador = mmap(NULL, sizeof(int),
              PROT_READ | PROT_WRITE,
              MAP_SHARED | MAP_ANONYMOUS,
              0, 0);
            
    
    struct timeval inicio;
    struct timeval fin;
    double milisegundosFinal;
    long segundos, milisegundos;

    gettimeofday(&inicio, 0);

    for (rank = 0; rank < canthilos; rank++){
        pid = fork();
        if(pid > 0){
            continue;
        }
        else if(pid == 0){
            exit(dartboard(rank));
        }
    }

    for (rank = 0; rank < canthilos; rank++)
        wait(&status);

    
    gettimeofday(&fin, 0);

    segundos = fin.tv_sec - inicio.tv_sec;
    milisegundos = fin.tv_usec - inicio.tv_usec;
    milisegundosFinal = ((segundos)*1000 + milisegundos / 1000.0);

    printf("Tiempo de ejecucion:\t");
    printf("%.16g milisegundos\n", milisegundosFinal);


    for(int i=0; i< canthilos;i++){
        printf("%f\n",vector_c[i]);
        resultado=vector_c[i]+resultado;
    }

    resultado=(float)(4.0*(resultado/dart));
    printf("%f\n", resultado);
    
    return 0;
}