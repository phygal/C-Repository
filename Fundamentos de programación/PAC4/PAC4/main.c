/*
** File: main.c
** Author: Daniel Galeano Sancho
** Date: 19-03-2019
** Description: PAC4
*/

/* System header file */
#include <stdio.h>
#include <string.h>

/* User defined types */
typedef enum {COMMERCIAL, PRIVATE, GOVERNMENTAL, MILITAR, EXPERIMENTAL, OTHERS} tUtility;
typedef enum {FALSE, TRUE} bool;

/* Main function */
int main(int argc, char **argv)
{
	/* Constants */
	const int MAX_PLANES = 10;
	const int MAX_LENGTH = 25+1;
		
	/* Variables */
    int idPlane[MAX_PLANES];
    char manufacturer[MAX_LENGTH];
    char model[MAX_LENGTH-10];
    int year[MAX_PLANES];
    int seats[MAX_PLANES];
    tUtility utility[MAX_PLANES];
    bool isActive[MAX_PLANES];
    int numPlanes;
    int i;
    float avgSeats;

	/* Inicialization of variables */
	numPlanes = 0;
	avgSeats = 0;

	/* Loop to keep values between conditions */
	do{
		printf("How many planes do you want to enter?: >> ");
		scanf("%d",&numPlanes);
		if((numPlanes <= 0)||(numPlanes > MAX_PLANES)){
			printf("Incorrect value. Value must be between 1 and %d.\nTry again.\n",MAX_PLANES);
		}
	}while((numPlanes <= 0)||(numPlanes > MAX_PLANES));

	/* Reading variables */
	printf("Enter the name of the manufacturer of all planes: >> ");
	scanf("%s",manufacturer);
	printf("Enter the name of the model of all planes: >> ");
	scanf("%s",model);
	
	for (i=0;i<numPlanes;i++){
		printf("\nPlane number %d\n",i+1);
		printf("Enter id of the plane: >> ");
		scanf("%d",&idPlane[i]);
		printf("Enter number of seats of the plane: >> ");
		scanf("%d",&seats[i]);
		printf("Enter year of manufacturing of the plane: >> ");
		scanf("%d",&year[i]);
		printf("Enter the utility of the plane (0 for COMMERCIAL, 1 for PRIVATE, 2 for GOVERNMENTAL, 3 for MILITAR, 4 for EXPERIMENTAL, 5 for OTHERS): >> ");
		scanf("%u",&utility[i]);
		printf("Enter if the plane is active (0 for FALSE, 1 for TRUE): >> ");
		scanf("%u",&isActive[i]);

		avgSeats += (float)seats[i];
	}

	avgSeats /= (float)numPlanes;

	/* Showing variables */
	printf("\nManufacturer of the planes: %s\n",manufacturer);
	printf("Model of the planes: %s\n",model);

	for (i=0;i<numPlanes;i++){
		printf("\nID: %d\n",idPlane[i]);
		printf("Seats: %d\n",seats[i]);
		printf("Manufacturing year: %d\n",year[i]);
		printf("Utility (0 for COMMERCIAL, 1 for PRIVATE, 2 for GOVERNMENTAL, 3 for MILITAR, 4 for EXPERIMENTAL, 5 for OTHERS): %u\n",utility[i]);
		printf("Active (0 for FALSE, 1 for TRUE): %u\n",isActive[i]);
		if (seats[i] > avgSeats){
			printf("Number of seats are greater than the average.\n");
		}
		else{
			printf("Number of seats are not greater than the average.\n");
		}
	}

	return 0;
}
