#include <iostream>
#include <random>
#include <math.h>

using namespace std;



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


Needle crearNeedle(float L, Floor floor){
    float x = ((float)(rand()) / ((float)(RAND_MAX/(1 - 0))))*floor.separacion;
    float o = ((float)(rand()) / ((float)(RAND_MAX/(1 - 0))))*M_PI;

    return Needle{x,o,L};
}


bool interseptan(Needle needle, Floor floor){
    float xDerecha = needle.x + needle.L / 2 * sin(needle.o);
    float xIzquierda = needle.x - needle.L / 2 * sin(needle.o);

    return xDerecha > floor.separacion || xIzquierda < 0.0;
}


float probabilidad(long long int iteraciones, Floor floor, float L){

    long long int dentro = 0;
    for(long long int i = 0; i < iteraciones; i++){
        Needle needle = crearNeedle(L, floor);
        if (interseptan(needle, floor)){
            dentro = dentro + 1;
        } 
    }

    return float(dentro)/float(iteraciones);
}

int main(int argc, char *argv[])
{
    Floor floor{2};

    struct timeval inicio;
    struct timeval fin;
    double milisegundosFinal;
    long segundos, milisegundos;
    int iteraciones = strtol(argv[1], NULL, 10);;

    gettimeofday(&inicio, 0);

    float resultado = probabilidad(iteraciones, floor, 1.0);

    gettimeofday(&fin, 0);

    segundos = fin.tv_sec - inicio.tv_sec;
    milisegundos = fin.tv_usec - inicio.tv_usec;
    milisegundosFinal = ((segundos)*1000 + milisegundos / 1000.0);

    printf("Tiempo de ejecucion:\t");
    printf("%.16g milisegundos\n", milisegundosFinal);

    //cout<<1.0/resultado;


    FILE *archivo;
    archivo = fopen("documento.txt", "a");
    fprintf(archivo, "%d\n", iteraciones);
    fprintf(archivo, "%.16g\n", milisegundosFinal);
    
    return 0;
}