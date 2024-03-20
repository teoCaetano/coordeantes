#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct
{
int x;
int y;
} pointCarteseano;

typedef struct 
{
	float grad;
	float rad;
} pointPolar;

const int HEIGHT = 20;
const int WIDTH = 20;
const int ARRAYSIZE = HEIGHT * WIDTH;

int iniSumadorFila ;
int endSumadorFila ;
int iniSumadoColumna ;
int endSumadoColumna ;

bool flagFilaImpar ;
bool flagColumnaImpar ;

int sumadoColumna ;
int sumadoFila ;

pointCarteseano *mapaCarteseano; 

pointPolar *mapaPolar;

int main()
{
    // Abrir el archivo para escritura
    FILE *archivo = fopen("puntosCarteseanos.txt", "w");

    // Verificar si el archivo se abrió correctamente
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo.");
        return 1;
    }

    FILE *archivo1 = fopen("puntosPolares.txt", "w");

    // Verificar si el archivo se abrió correctamente
    if (archivo1 == NULL)
    {
        printf("Error al abrir el archivo.");
        return 1;
    }

	if ((HEIGHT % 2) == 1)
	{
		flagColumnaImpar = true;
		iniSumadoColumna = (HEIGHT/2) ;
		sumadoColumna = iniSumadoColumna;
		endSumadoColumna = iniSumadoColumna * -1;
	}
	else{

		flagColumnaImpar = false;
		iniSumadoColumna = (HEIGHT/2);
		sumadoColumna = iniSumadoColumna;
		endSumadoColumna = iniSumadoColumna * -1;

	}

	if ((WIDTH % 2) == 1)
	{
		flagFilaImpar = true;
		iniSumadorFila = -(WIDTH/2) ;
		sumadoFila = iniSumadorFila;
		endSumadorFila = iniSumadorFila * -1;
	}
	else{

		flagFilaImpar = false;
		iniSumadorFila = -(WIDTH/2);
		sumadoFila = iniSumadorFila;
		endSumadorFila = iniSumadorFila * -1;

	}

// Asignar memoria para el array
	mapaCarteseano = (pointCarteseano*)malloc(ARRAYSIZE * sizeof(pointCarteseano));
	if (mapaCarteseano == NULL) {
		printf("Error: No se pudo asignar memoria para el array.\n");
		return 1;
	}

	mapaPolar = (pointPolar*)malloc(ARRAYSIZE * sizeof(pointPolar));
	if (mapaPolar == NULL)
	{
		printf("Error: No se pudo asignar memoria para el array\n");
		return 1;
	}


// Asignar valores a los puntos en el mapa
	for (int i = 0; i < ARRAYSIZE; ++i)
	{   
		mapaCarteseano[i].x=sumadoFila;
		mapaCarteseano[i].y=sumadoColumna;
		
		sumadoFila++;
		if (((i + 1) % WIDTH) == 0)
		{
			sumadoColumna--;
		}

		if (sumadoFila>endSumadorFila)
		{
			sumadoFila = iniSumadorFila;
		}
		
		if (flagFilaImpar == false)
		{
			if (sumadoFila == 0)
			{
				sumadoFila++;
			}
		}
		if (flagColumnaImpar == false)
		{
			if (sumadoColumna == 0)
			{
				sumadoColumna--;
			}
		}

		int valueX = mapaCarteseano[i].x;
		int valueY = mapaCarteseano[i].y;

		float valueRad = valueX*valueX + valueY*valueY;
		valueRad = sqrt(valueRad);

		float valueGrad = atan2(valueY, valueX);
		valueGrad = valueGrad * 180/3.1416;
		if (valueGrad<0)
		{
			valueGrad = valueGrad + 360;
		}

		mapaPolar[i].rad = valueRad;
		mapaPolar[i].grad = valueGrad;


	}



// Imprimir los valores de los puntos
	fprintf(archivo, "arrayOutput = {\n");
	for (int i = 0; i < ARRAYSIZE; ++i)
	{
		fprintf(archivo, "{%d, %d}",mapaCarteseano[i].x, mapaCarteseano[i].y);
		if (i != ARRAYSIZE-1)
		{
			fprintf(archivo, ",");
		}
		if (((i+1)%WIDTH)==0)
		{
			fprintf(archivo, "\n");
		}
	}
	fprintf(archivo, "}");

	fclose(archivo);

// Imprimir los valores de los puntos
	fprintf(archivo1, "arrayOutput1 = {\n");
	for (int i = 0; i < ARRAYSIZE; ++i)
	{
		fprintf(archivo1, " %.2f",mapaPolar[i].rad);
		if (i != ARRAYSIZE-1)
		{
			fprintf(archivo1, ",");
		}
		if (((i+1)%WIDTH)==0)
		{
			fprintf(archivo1, "\n");
		}
	}
	fprintf(archivo1, "}");
	fprintf(archivo1, "\n\n\n");

	fprintf(archivo1, "arrayOutput2 = {\n");
	for (int i = 0; i < ARRAYSIZE; ++i)
	{
		fprintf(archivo1, " %.2f",mapaPolar[i].grad);
		if (i != ARRAYSIZE-1)
		{
			fprintf(archivo1, ",");
		}
		if (((i+1)%WIDTH)==0)
		{
			fprintf(archivo1, "\n");
		}
	}
	fprintf(archivo1, "}");

	fclose(archivo1);	

// Liberar la memoria asignada
	free(mapaCarteseano);

	return 0;
}
