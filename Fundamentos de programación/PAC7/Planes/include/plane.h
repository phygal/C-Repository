/*
** File: plane.h
** Author: Daniel Galeano Sancho
** Date: 10-04-2019
** Description: PAC7
*/

/* Constants */
#define MAX_LENGTH 15
#define NUM_CLASSES 3

/* User defined types */
typedef enum {COMMERCIAL, PRIVATE, GOVERNMENTAL, MILITAR, EXPERIMENTAL, OTHERS} tUtility;
typedef enum {FALSE,TRUE} bool;
typedef struct{
	int id;
	char model[MAX_LENGTH];
	int year;
	tUtility utility;
	float percentOccupationFirstclass;
	float percentOccupationBusiness;
	float percentOccupationTurist;
	bool isActive;	
}tPlane; 

/* Read information of a plane */
void planeRead(tPlane *plane);

/* Write information of a plane */
void planeWrite(tPlane plane);

/* Copy information of a plane, planeIn, into another plane, planeOut */
void planeCopy(tPlane planeIn, tPlane *planeOut);

/* Analyse priority of plane1 and plane2. True: plane1>plane2, False: plane1<plane2 */
bool isFirstPlane(tPlane plane1, tPlane plane2);

/* Returns a priorized plane between plane1 and plane2 */
void planePriorized(tPlane plane1, tPlane plane2, tPlane *planePriority);