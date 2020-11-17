/*
** File: main.c
** Author: Daniel Galeano Sancho
** Date: 29-03-2019
** Description: PAC5
*/

/* System header file */
#include <stdio.h>

/* Constants */
#define MAX_LENGTH 15

/* User defined types */
typedef enum {COMMERCIAL, PRIVATE, GOVERNMENTAL, MILITAR, EXPERIMENTAL, OTHERS} tUtility;
typedef enum {FALSE, TRUE} bool;
typedef struct{
	int id;
	char model[MAX_LENGTH];
	int year;
	tUtility utility;
	float weight;
	float maxSpeed;
	int maxHeight;
	int motors;
	int seats;
	bool isActive;
}tPlane;

/* Main function */
int main(int argc, char **argv){
			
	/* Variables */
	tPlane plane1;
	tPlane plane2;
	int totalSeats;

	/* Inicialization of variables */
	totalSeats = 0;

	/* Reading plane 1 data */
    printf("Enter id of the plane 1: >> ");
    scanf("%d",&plane1.id);
    printf("Enter model of the plane 1: >> ");
    getchar();
	gets(plane1.model);
    printf("Enter year of manufacturing of the plane 1: >> ");
    scanf("%d",&plane1.year);
    printf("Enter the utility of the plane 1 (0 for COMMERCIAL, 1 for PRIVATE, 2 for GOVERNMENTAL, 3 for MILITAR, 4 for EXPERIMENTAL, 5 for OTHERS): >> ");
    scanf("%u",&plane1.utility);
    printf("Enter the weight of the plane 1 (in t): >> ");
    scanf("%f",&plane1.weight);
    printf("Enter the maximum speed of the plane 1 (in km/h): >> ");
    scanf("%f",&plane1.maxSpeed);
    printf("Enter the maximum height of the plane 1 (in m): >> ");
    scanf("%d",&plane1.maxHeight);
    printf("Enter the number of motors of the plane 1: >> ");
    scanf("%d",&plane1.motors);
    printf("Enter the number of seats of the plane 1: >> ");
    scanf("%d",&plane1.seats);
    printf("Enter if the plane 1 is active (0 for FALSE, 1 for TRUE): >> ");
    scanf("%u",&plane1.isActive);
	
	/* Reading plane 2 data */
    printf("\nEnter id of the plane 2: >> ");
    scanf("%d",&plane2.id);
    printf("Enter model of the plane 2: >> ");
    getchar();
	gets(plane2.model);
    printf("Enter year of manufacturing of the plane 2: >> ");
    scanf("%d",&plane2.year);
    printf("Enter the utility of the plane 2 (0 for COMMERCIAL, 1 for PRIVATE, 2 for GOVERNMENTAL, 3 for MILITAR, 4 for EXPERIMENTAL, 5 for OTHERS): >> ");
    scanf("%u",&plane2.utility);
    printf("Enter the weight of the plane 2 (in t): >> ");
    scanf("%f",&plane2.weight);
    printf("Enter the maximum speed of the plane 2 (in km/h): >> ");
    scanf("%f",&plane2.maxSpeed);
    printf("Enter the maximum height of the plane 2 (in m): >> ");
    scanf("%d",&plane2.maxHeight);
    printf("Enter the number of motors of the plane 2: >> ");
    scanf("%d",&plane2.motors);
    printf("Enter the number of seats of the plane 2: >> ");
    scanf("%d",&plane2.seats);
    printf("Enter if the plane 2 is active (0 for FALSE, 1 for TRUE): >> ");
    scanf("%u",&plane2.isActive);

    
    printf("\nID of the plane with more seats: ");

    if (plane1.isActive && (plane1.utility == COMMERCIAL) ){
        if (plane2.isActive && (plane2.utility == COMMERCIAL) ){
            if (plane1.seats >= plane2.seats) {
                printf("%d",plane1.id);
            }else{
                printf("%d",plane2.id);
			}
            totalSeats = plane1.seats + plane2.seats;
        }else{
            printf("%d",plane1.id);
            totalSeats = plane1.seats;
        }
    }else{
        if (plane2.isActive && (plane2.utility = COMMERCIAL) ){
            printf("%d",plane2.id);
            totalSeats = plane2.seats;
        }else{
            printf("No planes were found that are active and are commercial.");
        }
    }
    
    printf("\nTotal seats: %d\n",totalSeats);

	return 0;
}

