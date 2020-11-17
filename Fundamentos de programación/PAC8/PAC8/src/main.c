/*
** File: main.c
** Author: Daniel Galeano Sancho
** Date: 25-04-2019
** Description: PAC8
*/

#include <stdio.h>
#include "plane.h"
/*********************************************************************************************************
 * Pac8/Pec8 code v.1
 ********************************************************************************************************/

//main algorithm
int main(int argc, char **argv){
    
/*********************************************************************************************************
 * Write main algorithm here 
 ********************************************************************************************************/

	int i, id;
	tPlanesTable planesTable, selectTable;
	double avg;
	boolean correct;
    
    correct = FALSE;
	
    planesTableInitialize(&planesTable);
    planesTableInitialize(&selectTable);

    printf("Number of planes to enter: >> ");
    scanf("%d",&(planesTable.numPlanes));
	
	for (i = 0;i<planesTable.numPlanes;i++){
        printf("\nPlane number: %d\n",i+1);
        planeRead(&(planesTable.plane[i]));
	}
    
    while (!correct){
        printf("\nEnter code of the class (1 for First Class, 2 for Business, 3 for Turist): >> ");
        scanf("%d",&id);

		if ((id == 1)||(id == 2)||(id == 3)){
            correct = TRUE;
        }else{
            printf("Incorrect code. Try again.\n");
		}
	}

    avg = planesTableOccupation(planesTable, id);

    planesTableSelectByOccupation(planesTable, avg, id, &selectTable);
	
	printf("\nThe number of planes below average is: %d\n\n",selectTable.numPlanes);

    if (selectTable.numPlanes != 0){
        for (i = 0;i<selectTable.numPlanes;i++){
            planeWrite(selectTable.plane[i]);
        }
    }
	
    return 0;
}
