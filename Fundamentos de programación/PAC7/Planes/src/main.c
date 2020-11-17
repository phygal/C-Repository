/*
** File: main.c
** Author: Daniel Galeano Sancho
** Date: 10-04-2019
** Description: PAC7
*/

/* System header files */
#include <stdio.h>
#include "plane.h"

/* Main function */
int main(int argc, char **argv){
			
	/* Variables */
	tPlane plane1, plane2, priorPlane;
		
    /* Input information for plane 1 */
	printf("Plane 1:\n");
	planeRead(&plane1);
	printf("\n");
    
	/* Input information for plane 2 */
	printf("Plane 2:\n");
	planeRead(&plane2);	
	printf("\n");
	
	/* Analysing priority for planes */
	planePriorized(plane1, plane2, &priorPlane);
    
	/* Showing priority plane */
	printf("Priorized plane: \n");
	planeWrite(priorPlane);

	return 0;
}