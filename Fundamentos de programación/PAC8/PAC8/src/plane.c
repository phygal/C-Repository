/*
** File: plane.c
** Author: Daniel Galeano Sancho
** Date: 25-04-2019
** Description: PAC8
*/

#include <stdio.h>
#include <string.h>
#include "plane.h"


void planeRead(tPlane *plane){
    
    
    printf("Identifier for plane (integer): >> ");
    scanf("%d", &plane->id);
    
    printf("Model for plane  (string): >> ");
    scanf("%s", plane->model);
       
    printf("Year for plane  (integer):  >> ");
    scanf("%d", &plane->year);
        
    printf("Utility for plane  (enter a number being 0=COMMERCIAL, 1=PRIVATE, 2=GOVERNMENTAL, 3=MILITAR, 4=EXPERIMENTAL, 5=OTHERS: >> ");
    scanf("%u", &plane->utility);
        
    printf("Percentage of ocupation in Firstclass for plane (real): >> ");
    scanf("%f", &plane->percentOccupationFirstclass);

    printf("Percentage of ocupation in Business for plane (real): >> ");
    scanf("%f", &plane->percentOccupationBusiness);

    printf("Percentage of ocupation in Turist for plane (real): >> ");
    scanf("%f", &plane->percentOccupationTurist);
    
    printf("Is plane active? (enter a number being 0=FALSE, 1=TRUE): >> ");
    scanf("%u", &plane->isActive);
        
}

void planeWrite(tPlane plane){

    printf("Plane id: %d\n", plane.id);
    printf("Plane model: %s\n", plane.model);
	printf("Plane year: %d\n", plane.year);
	printf("Plane utility: %u\n", plane.utility);
	printf("Percentage of occupation in Firstclass: %.2f\n", plane.percentOccupationFirstclass);
    printf("Percentage of occupation in Business: %.2f\n", plane.percentOccupationBusiness);
    printf("Percentage of occupation in Turist: %.2f\n", plane.percentOccupationTurist);
    printf("Is the plane active? %u\n", plane.isActive);
    printf("\n");
}

void planeCopy(tPlane planeSrc, tPlane *planeDst){

    planeDst->id = planeSrc.id;
    strcpy(planeDst->model, planeSrc.model);
    planeDst->year = planeSrc.year;
    planeDst->utility = planeSrc.utility;
    planeDst->percentOccupationFirstclass = planeSrc.percentOccupationFirstclass;
    planeDst->percentOccupationBusiness = planeSrc.percentOccupationBusiness;
    planeDst->percentOccupationTurist = planeSrc.percentOccupationTurist;
    planeDst->isActive = planeSrc.isActive;
}

/*********************************************************************************************************
 * Write new functions here
 *
 ********************************************************************************************************/

void planesTableInitialize (tPlanesTable *planeTable){
    planeTable->numPlanes = 0;
}

double planesTableOccupation (tPlanesTable planeTable, int idClass){
	double aux;
	int i;
    
	aux = 0;
	
    for (i = 0;i<planeTable.numPlanes;i++){
        if (idClass == CODE_FIRSTCLASS){
            aux = aux + (double)planeTable.plane[i].percentOccupationFirstclass;
        }else{
            if (idClass == CODE_BUSINESS){
                aux = aux + (double)planeTable.plane[i].percentOccupationBusiness;
            }else{
                if (idClass == CODE_TURIST){
                    aux = aux + (double)planeTable.plane[i].percentOccupationTurist;
                }
            }
        }
    }

    aux = aux/(double)planeTable.numPlanes;    

    return aux;

}

void planesTableSelectByOccupation(tPlanesTable planesTable, double average, int idClass, tPlanesTable *selectTable){
	int i;
    
    planesTableInitialize(selectTable);
    
    for (i = 0;i<planesTable.numPlanes;i++){
        if (idClass == CODE_FIRSTCLASS){
            if (planesTable.plane[i].percentOccupationFirstclass < average){
                planeCopy(planesTable.plane[i], &selectTable->plane[selectTable->numPlanes]);
                selectTable->numPlanes = selectTable->numPlanes + 1;
            }
        }else{
            if (idClass == CODE_BUSINESS){
                if (planesTable.plane[i].percentOccupationBusiness < average){
                    planeCopy(planesTable.plane[i], &selectTable->plane[selectTable->numPlanes]);
                    selectTable->numPlanes = selectTable->numPlanes + 1;
                }
            }else{
                if (idClass == CODE_TURIST){
                    if (planesTable.plane[i].percentOccupationTurist < average){
                        planeCopy(planesTable.plane[i], &selectTable->plane[selectTable->numPlanes]);
                        selectTable->numPlanes = selectTable->numPlanes + 1;
                    }
                }
            }
        }
    }
}
 