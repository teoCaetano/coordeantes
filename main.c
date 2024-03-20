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

const float limitRad14 = 14.15;
const float limitRad13 = 13.46;
const float limitRad12 = 12.22;
const float limitRad11 = 11.42;
const float limitRad10 = 10.82;
const float limitRad9 = 9.85;
const float limitRad8 = 8.95;
const float limitRad7 = 7.63;
const float limitRad6 = 6.72;
const float limitRad5 = 5.40;
const float limitRad4 = 4.48;
const float limitRad3 = 3.62;
const float limitRad2 = 2.25;
const float limitRad1 = 1.42;


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

int *mapaGradMap;

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

	mapaGradMap = (int*)malloc(ARRAYSIZE * sizeof(int));
	if (mapaGradMap == NULL)
	{
		printf("Error: No se pudo asignar memoria para el array\n");
		return 1;
	}

// Asignar valores a los puntos en el mapa
	for (int i = 0; i < ARRAYSIZE; ++i)
	{   

		/*
			writes to the cartesian array
		*/
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
		/*
			writes to the polar array
		*/

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

		int valueRadMap;

		if ((valueRad<=limitRad14)&&(valueRad>limitRad13))
		{
			valueRadMap = 14;
		}
		if ((valueRad<=limitRad13)&&(valueRad>limitRad12))
		{
			valueRadMap = 13;
		}
		if ((valueRad<=limitRad12)&&(valueRad>limitRad11))
		{
			valueRadMap = 12;
		}
		if ((valueRad<=limitRad11)&&(valueRad>limitRad10))
		{
			valueRadMap = 11;
		}
		if ((valueRad<=limitRad10)&&(valueRad>limitRad9))
		{
			valueRadMap = 10;
		}
		if ((valueRad<=limitRad9)&&(valueRad>limitRad8))
		{
			valueRadMap = 9;
		}
		if ((valueRad<=limitRad8)&&(valueRad>limitRad7))
		{
			valueRadMap = 8;
		}
		if ((valueRad<=limitRad7)&&(valueRad>limitRad6))
		{
			valueRadMap = 7;
		}
		if ((valueRad<=limitRad6)&&(valueRad>limitRad5))
		{
			valueRadMap = 6;
		}
		if ((valueRad<=limitRad5)&&(valueRad>limitRad4))
		{
			valueRadMap = 5;
		}
		if ((valueRad<=limitRad4)&&(valueRad>limitRad3))
		{
			valueRadMap = 4;
		}		
		if ((valueRad<=limitRad3)&&(valueRad>limitRad2))
		{
			valueRadMap = 3;
		}		
		if ((valueRad<=limitRad2)&&(valueRad>limitRad1))
		{
			valueRadMap = 2;
		}
		if (valueRad<=limitRad1)
		{
			valueRadMap = 1;
		}

		mapaGradMap[i] = valueRadMap;
	}

	/*
		writes to the cartesian array to a file
	*/
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

	/*
		writes to the rad values of the polar array to a file
	*/
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
	/*
		writes to the grad values of the polar array to a file
	*/
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

	fprintf(archivo1, "\n\n\n");

	fprintf(archivo1, "arrayOutput3 = {\n");
	for (int i = 0; i < ARRAYSIZE; ++i)
	{
		fprintf(archivo1, "%d ",mapaGradMap[i]);
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
	free(mapaGradMap);
	free(mapaCarteseano);
	free(mapaPolar);
	return 0;
}
