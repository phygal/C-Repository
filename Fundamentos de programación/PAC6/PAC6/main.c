/*
** File: main.c
** Author: Daniel Galeano Sancho
** Date: 03-04-2019
** Description: PAC6
*/

/* System header files */
#include <stdio.h>
#include <string.h>

/* Constants */
#define MAX_LENGTH 15

/* User defined types */
typedef enum {COMMERCIAL, PRIVATE, GOVERNMENTAL, MILITAR, EXPERIMENTAL, OTHERS} tUtility;
typedef enum {FALSE,TRUE} bool;
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

/* Exercise A. Action (void function) for reading information of a plane */
void planeRead(tPlane *plane){
	
    printf("Identifier for the plane (integer): >> ");
    scanf("%d",&(plane->id));
    printf("Model for the plane (string): >> ");
    //getchar();
	//gets(plane->model);
	scanf("%s",plane->model);
    printf("Year for the plane (integer):  >> ");
    scanf("%d",&(plane->year));
    printf("Utility for the plane (enter a number being 0=COMMERCIAL, 1=PRIVATE, 2=GOVERNMENTAL, 3=MILITAR, 4=EXPERIMENTAL, 5=OTHERS): >> ");
    scanf("%u",&(plane->utility));
    printf("Weight for the plane (Tons): >> ");
    scanf("%f",&(plane->weight));
    printf("Max speed for the plane (Km/h): >> ");
    scanf("%f",&(plane->maxSpeed));
    printf("Max height for the plane (metres): >> ");
    scanf("%d",&(plane->maxHeight));
    printf("Number of motors for the plane (integer): >> ");
    scanf("%d",&(plane->motors));
    printf("Number of seats for the plane (integer): >> ");
    scanf("%d",&(plane->seats));
    printf("Is the plane active? (0 for FALSE, 1 for TRUE): >> ");
    scanf("%u",&(plane->isActive));	

}

/* Exercise B. Action (void function) for writing information of a plane */
void planeWrite(tPlane plane){
	
	printf("\nIdentifier: %d\n",plane.id);
	printf("Model: %s\n",plane.model);
	printf("Year: %d\n",plane.year);	
	printf("Utility (0 for COMMERCIAL, 1 for PRIVATE, 2 for GOVERNMENTAL, 3 for MILITAR, 4 for EXPERIMENTAL, 5 for OTHERS): %u\n",plane.utility);
	printf("Weight (Tons): %.2f\n",plane.weight);
	printf("Max speed (Km/h): %.2f\n",plane.maxSpeed);
	printf("Max height (metres): %d\n",plane.maxHeight);
	printf("Number of motors: %d\n",plane.motors);
	printf("Number of seats: %d\n",plane.seats);
	printf("Is the plane active? (0 for FALSE, 1 for TRUE): %u\n",plane.isActive);
}

/* Exercise C. Action (void function) for copying information of a plane into another plane */
void planeCopy(tPlane planeIn, tPlane *planeOut){
    
    planeOut->id = planeIn.id;
    strcpy(planeOut->model,planeIn.model);
    planeOut->year = planeIn.year;
    planeOut->utility = planeIn.utility;
    planeOut->weight = planeIn.weight;
    planeOut->maxSpeed = planeIn.maxSpeed;
    planeOut->maxHeight = planeIn.maxHeight;
    planeOut->motors = planeIn.motors;
    planeOut->seats = planeIn.seats;
    planeOut->isActive = planeIn.isActive;

}

/* Exercise D. Function for comparing features between two planes */
int planeAnalise(tPlane plane1, tPlane plane2){
    
    int res;
    
    if (plane1.maxSpeed == plane2.maxSpeed) {
        if (plane1.maxHeight == plane2.maxHeight) {
            res = 0;
        }else{
            if (plane1.maxHeight > plane2.maxHeight) {
                res = 1;
            }else{
                res = 2;
            }
        }
    }else{
        if (plane1.maxSpeed > plane2.maxSpeed) {
            res = 1;
        }else{
            res = 2;
        }
    }
    return res;
}

/* Main function */
int main(int argc, char **argv){
			
	/* Variables */
	tPlane plane1;
	tPlane plane2;
    tPlane planeMilitar;
	int analise;
	
    /* Input information for plane 1 */
	printf("Plane 1:\n");
	planeRead(&plane1);
	printf("\n");
    
	/* Input information for plane 2 */
	printf("Plane 2:\n");
	planeRead(&plane2);	
	printf("\n");
	
	/* Storing result of planeAnalise */
	analise = planeAnalise(plane1,plane2);
	
	if (plane1.utility == MILITAR) {
		if (plane2.utility == MILITAR) {
			printf("Better plane: \n");
			if (analise == 1) {
				planeWrite(plane1);
			}else{
				if (analise == 2) {
					planeWrite(plane2);
				}else{
					printf("Both planes have the same maximum speed and height.\n");
				}
			}
		}else{
			printf("Plane 1 is militar.\n");
			planeCopy(plane1,&planeMilitar);
			planeWrite(planeMilitar);
		}
	}else{
		if (plane2.utility == MILITAR) {
			printf("Plane 2 is militar.\n");
			planeCopy(plane2,&planeMilitar);
			planeWrite(planeMilitar);
		}else{
			printf("None of the planes are militar.\n");
		}
	}

	return 0;
}
