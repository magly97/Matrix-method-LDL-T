// ConsoleApplication6.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//
#pragma warning (disable: 4996)
#include "stdafx.h"
#include <stdlib.h>
#include<stdio.h>
#include <math.h>
FILE *fd;

double sumX(double **LT, double *x, int i, int n);
double sumZ(double **L, double *z, int i);
double sumD(double **L, double **D, int j);
double sumA(double **L, double **D, int i, int j);

int main()
{
	double **A,**D,**L,*B,**LT,*x,*z,*y;
	int  n;
//=====================================================WCZYTYWANIE PLIKOW===============================================
	if (!(fd = fopen("dane.txt", "r")))
	{
		printf("Blad wczytywania danych");
		exit(0);
	}

//================================================WCZYTANIE WYMIAROW MACIERZY ORAZ WEKTORA==============================
	fscanf(fd, "%d", &n); 
	
//==============================================WCZYTYWANIE TABLIC ORAZ ALOKACJA MIEJSC================================
	A= malloc(n * sizeof(double));
	D = malloc(n * sizeof(double));
	for (int i = 0; i < n; i++)
	{
		D[i] = malloc(n * sizeof(double));
		for (int j = 0; j < n; j++)
		{
			D[i][j] = 0;
		}
	}
	printf("Macierz A:\n");
	for (int i = 0; i < n;i++)
	{
		
	A[i] = malloc(n * sizeof(double));
		for (int j = 0;j < n;j++)
		{
			fscanf(fd, "%lf", &A[i][j]);
		printf("%lf  ", A[i][j]);
		}
		printf("\n");

	}

	printf("\nWektor B:\n");
	
	B = malloc(n * sizeof(double));
	for (int i = 0; i < n;i++)
	{

		fscanf(fd, "%lf", &B[i]);
		printf("%lf ", B[i]);

	}
	z= malloc(n * sizeof(double));
	for (int i = 0; i < n;i++)
	{

		z[i] = 0;


	}
	y = malloc(n * sizeof(double));
	for (int i = 0; i < n;i++)
	{

		y[i] = 0;


	}
	x = malloc(n * sizeof(double));
	for (int i = 0; i < n;i++)
	{

		x[i] = 0;


	}   
	L= malloc(n * sizeof(double));
	for (int i = 0; i < n;i++)
	{

		L[i] = malloc(n * sizeof(double));
		for (int j = 0;j < n;j++)
		{
				L[i][j] = 0;			
		}
		printf("\n");
	}


	LT= malloc(n * sizeof(double));

	for (int i = 0; i < n;i++)
	{

		LT[i] = malloc(n * sizeof(double));
		for (int j = 0;j < n;j++)
		{

				L[i][j] = 0;
			
		}

	}

//=============================================OBLICZANIE WARTOSCI LDLT===================================================

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n;j++)
		{
			
			D[j][j] = A[j][j] - sumD(L, D, j);
			if (i >= j)
				L[i][j] =  (A[i][j] - sumA(L, D, i, j))/ D[j][j] ;
		}
	}
//=====================================TRANSPONOWANIE MACIERZY L==========================================================
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			LT[i][j] = L[j][i];
		}
	}
//=========================================WYPIS  LDLT==============================================================
	printf("\nRozklad  macierzy A metoda LDL^T\nL:\n");
		for (int i = 0;i < n;i++)
		{
			for (int j = 0; j < n;j++)
			{
				printf("%lf ", L[i][j]);
			}
			printf("\n");
		}
		printf("D:\n");
		for (int i = 0;i < n;i++)
		{
			for (int j = 0; j < n;j++)
			{
			
					printf("%lf ", D[i][j]);
				
			}
			printf("\n");
		}
		printf("L^T:\n");
		for (int i = 0;i < n;i++)
		{
			for (int j = 0; j < n;j++)
			{
				printf("%lf ", LT[i][j]);
			}
			printf("\n");
		}
//=============================================FINALNE OBLICZENIA=========================================================
		for (int i = 0;i < n;i++)
		{
			z[i] = B[i] - sumZ(L, z, i);
		}
		for (int i = 0;i < n;i++)
		{
			y[i] = z[i] / D[i][i];
		}
		for (int i = n-1; i >= 0; i--)
		{
			x[i] = y[i] - sumX(LT, x, i,n);
		}
		
//=============================================WYPIS FIALNY===============================================================
		printf("\nSzukany wektor X ma wymiary: \n");
		for (int i = 0; i < n;i++)
		{
			printf(" %lf ",x[i]);
		}
		printf("\n");
//=================================================KONIEC MAINA ===============================================================
    return 0;
}

//================================================OBLICZANIE SUMY X========================================================
double sumX(double **LT, double *x, int i, int n)
{
	double suma = 0;
	for (int k = i+1; k<n;k++)
	{
		suma += LT[i][k] * x[k];
	}
	return suma;
}
//===================================================OBLICZANIE SUMY Z===================================================
double sumZ(double **L, double *z, int i)
{
	double suma = 0;
	for (int k = 0; k < i;k++)
	{
		suma += L[i][k] * z[k];
	}
	return suma;
}
//=============================================OBLICZANIE SUMY DLA D==========================================================
double sumD(double **L, double **D, int j)
{
	double suma = 0;
	for (int k = 0; k < j;k++)
	{
		suma += L[j][k] * L[j][k] * D[k][k];
	}
	return suma;
}
//==============================================OBLICZANIE SUMY DLA L=========================================================
double sumA(double **L, double **D, int i, int j)
{
	double suma = 0;
	for (int k = 0; k < j; k++)
	{
		suma += L[i][k] * L[j][k] * D[k][k];
	}
	return suma;
}