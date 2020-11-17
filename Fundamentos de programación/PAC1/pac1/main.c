/*
** File: main.c
** Author: Daniel Galeano Sancho
** Date: 26-02-2019
** Description: PAC1, Exercici 2
*/

/* Fitxers de capçalera */
#include <stdio.h>

int main(int argc, char **argv)
{
	/* Declaració de tipus */
	typedef enum {COMMERCIAL, PRIVATE, GOVERNMENTAL, MILITAR, EXPERIMENTAL, OTHERS} tUse; 
	typedef enum {FALSE, TRUE} bool; 
	
	/* Declaració de variables */
	int id; 
	char model;
	int manufacturingYear; 
	tUse use; 
	float weight; 
	float speed; 
	int maximumHeight; 
	int engines; 
	int seats; 	
	bool active; 

	/* Lectura de dades de l'avió */
	printf("Type the plane identification number: \n");
	scanf("%d",&id);
	printf("Type the plane model: (max 1 character) \n");
	getchar();
	scanf("%c",&model);
	printf("Type the plane manufacturing year: \n");
	scanf("%d",&manufacturingYear);
	printf("Type the plane’s use (0 for COMMERCIAL, 1 for PRIVATE, 2 for GOVERNMENTAL, 3 for MILITAR, 4 for EXPERIMENTAL, 5 for OTHERS): \n");
	scanf("%d",&use);
	printf("Type the plane weight in tons: (without passengers, gas and load) \n");
	scanf("%f",&weight);
	printf("Type the plane speed in km/h: \n");
	scanf("%f",&speed);
	printf("Type the plane maximum height in meters: \n");
	scanf("%d",&maximumHeight);
	printf("Type the plane number of engines: \n");
	scanf("%d",&engines);
	printf("Type the plane number of seats: \n");
	scanf("%d",&seats);
	printf("Type if the plane is active (0 for FALSE , 1 for TRUE): \n");
	scanf("%d",&active);

	/* Es mostren les dades de l'avió per pantalla */
	printf("\n\nID: %d\n",id);
	printf("Model: %c\n",model);
	printf("Manufacturing year: %d\n",manufacturingYear);
	printf("Use (0 for COMMERCIAL, 1 for PRIVATE, 2 for GOVERNMENTAL, 3 for MILITAR, 4 for EXPERIMENTAL, 5 for OTHERS): %d\n",use);
	printf("Weight: %.2f tons\n",weight);
	printf("Speed: %.2f km/h\n",speed);
	printf("Maximum height: %d m\n",maximumHeight);
	printf("Number of engines: %d\n",engines);
	printf("Number of seats: %d\n",seats);
	printf("Active (0 for FALSE , 1 for TRUE): %d\n",active);
	
	return 0;
}
