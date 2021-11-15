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





struct Floor
{
    float separacion;
};


struct Needle
{
    float x;
    float o;
    float L;
};

int numPro;
long long int iteraciones;
struct Floor piso = {2};
float L = 1.0;
long long int *cont;




struct Needle crearNeedle(float L){
    float x = ((float)(rand()) / ((float)(RAND_MAX/(1 - 0))))*piso.separacion;
    float o = ((float)(rand()) / ((float)(RAND_MAX/(1 - 0))))*M_PI;

    struct Needle a = {x,o,L};
    return a;
}


float interseptan(struct Needle needle){
    float xDerecha = needle.x + needle.L / 2 * sin(needle.o);
    float xIzquierda = needle.x - needle.L / 2 * sin(needle.o);

    return xDerecha > piso.separacion || xIzquierda < 0.0;
}


int probabilidad(int rank){

    int id = rank;
    for(long long int i = 0; i < ((long long int)iteraciones/(long long int)numPro); i++){
        struct Needle needle = crearNeedle(L);
        if (interseptan(needle)){
            cont[id] = cont[id] + 1;
        }
        
        
    }
    return 0;
}



int main(int argc, char *argv[])
{
    srand(time(NULL));
    pid_t pid;
    iteraciones = strtol(argv[1], NULL, 10);
    int rank;
    int status;
    numPro = strtol(argv[2], NULL, 10);

    cont = mmap(NULL, numPro * sizeof(long long int),
              PROT_READ | PROT_WRITE,
              MAP_SHARED | MAP_ANONYMOUS,
              0, 0);

    struct timeval inicio;
    struct timeval fin;
    double milisegundosFinal;
    long segundos, milisegundos;

    gettimeofday(&inicio, 0);
  
    for (rank = 0; rank < numPro; rank++){
        pid = fork();
        if(pid > 0){
            continue;
        }
        else if(pid == 0){
            exit(probabilidad(rank));
        }
    }



    for (rank = 0; rank < numPro; rank++)
    wait(&status);
    gettimeofday(&fin, 0);

    segundos = fin.tv_sec - inicio.tv_sec;
    milisegundos = fin.tv_usec - inicio.tv_usec;
    milisegundosFinal = ((segundos)*1000 + milisegundos / 1000.0);

    printf("Tiempo de ejecucion:\t");
    printf("%.16g milisegundos\n", milisegundosFinal);


    long double resultado = 1.0/((( long int)cont[0]+( long int)cont[1]+( long int)cont[2]+( long int)cont[3]+( long int)cont[4]+(long int)cont[5])/( long double)iteraciones);
 
    ILE *archivo;
    archivo = fopen("documento.txt", "a");
    fprintf(archivo, "%d\n", iteraciones);
    fprintf(archivo, "%.16g\n", milisegundosFinal);

    //printf("%2Lf\n",resultado);
    
    return 0;
}