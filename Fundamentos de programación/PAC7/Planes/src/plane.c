/*
** File: plane.c
** Author: Daniel Galeano Sancho
** Date: 10-04-2019
** Description: PAC7
*/

/* System header files */
#include <stdio.h>
#include <string.h>
#include "plane.h"

/* Read information of a plane */
void planeRead(tPlane *plane){
	
    printf("Identifier for the plane (integer): >> ");
    scanf("%d",&(plane->id));
    printf("Model for the plane (string): >> ");
	scanf("%s",plane->model);
    printf("Year for the plane (integer):  >> ");
    scanf("%d",&(plane->year));
    printf("Utility for the plane (enter a number being 0=COMMERCIAL, 1=PRIVATE, 2=GOVERNMENTAL, 3=MILITAR, 4=EXPERIMENTAL, 5=OTHERS): >> ");
    scanf("%u",&(plane->utility));
    printf("First class percent occupation for the plane: >> ");
    scanf("%f",&(plane->percentOccupationFirstclass));
    printf("Business class percent occupation for the plane: >> ");
    scanf("%f",&(plane->percentOccupationBusiness));
    printf("Tourist class percent occupation for the plane: >> ");
    scanf("%f",&(plane->percentOccupationTurist));
    printf("Is the plane active? (0 for FALSE, 1 for TRUE): >> ");
    scanf("%u",&(plane->isActive));	

}

/* Write information of a plane */
void planeWrite(tPlane plane){
	
	printf("Identifier: %d\n",plane.id);
	printf("Model: %s\n",plane.model);
	printf("Year: %d\n",plane.year);	
	printf("Utility (0 for COMMERCIAL, 1 for PRIVATE, 2 for GOVERNMENTAL, 3 for MILITAR, 4 for EXPERIMENTAL, 5 for OTHERS): %u\n",plane.utility);
    printf("First class percent occupation: %.2f\n",plane.percentOccupationFirstclass);
    printf("Business class percent occupation: %.2f\n",plane.percentOccupationBusiness);
	printf("First class percent occupation: %.2f\n",plane.percentOccupationTurist);
	printf("Is the plane active? (0 for FALSE, 1 for TRUE): %u\n",plane.isActive);
}

/* Copy information of a plane, planeIn, into another plane, planeOut */
void planeCopy(tPlane planeIn, tPlane *planeOut){
    
    planeOut->id = planeIn.id;
    strcpy(planeOut->model,planeIn.model);
    planeOut->year = planeIn.year;
    planeOut->utility = planeIn.utility;
    planeOut->percentOccupationFirstclass = planeIn.percentOccupationFirstclass;
    planeOut->percentOccupationBusiness = planeIn.percentOccupationBusiness;
    planeOut->percentOccupationTurist = planeIn.percentOccupationTurist;
    planeOut->isActive = planeIn.isActive;

}

/* Exercise A */
bool isFirstPlane(tPlane plane1, tPlane plane2){
    
    float totalOccupation1, totalOccupation2;
    bool firstPlane;
        
    totalOccupation1 = (plane1.percentOccupationFirstclass  + plane1.percentOccupationBusiness + plane1.percentOccupationTurist)/NUM_CLASSES;
    totalOccupation2 = (plane2.percentOccupationFirstclass  + plane2.percentOccupationBusiness + plane2.percentOccupationTurist)/NUM_CLASSES;

    if (totalOccupation1 > totalOccupation2) {
        firstPlane = TRUE;
    }else{
        if (totalOccupation1 < totalOccupation2) {
            firstPlane = FALSE;
        }else{
            if (plane1.percentOccupationFirstclass > plane2.percentOccupationFirstclass) {
                firstPlane = TRUE;
            }else{
                if (plane1.percentOccupationFirstclass < plane2.percentOccupationFirstclass) {
                    firstPlane = FALSE;
                }else{
                    if (plane1. percentOccupationBusiness > plane2. percentOccupationBusiness) {
                        firstPlane = TRUE;
                    }else{
                        if (plane1. percentOccupationBusiness < plane2. percentOccupationBusiness) {
                            firstPlane = FALSE;
                        }else{
                            if (plane1. percentOccupationTurist > plane2. percentOccupationTurist) {
                                firstPlane = TRUE;
                            }else{
                                if (plane1. percentOccupationTurist < plane2. percentOccupationTurist) {
                                    firstPlane = FALSE;
                                }else{
                                    firstPlane = TRUE;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
	return firstPlane;
}

/* Exercise B */
void planePriorized(tPlane plane1, tPlane plane2, tPlane *planePriority){

    if (isFirstPlane(plane1,plane2)) {
        planeCopy(plane1, planePriority);
    }else{
        planeCopy(plane2, planePriority);
    }
}

