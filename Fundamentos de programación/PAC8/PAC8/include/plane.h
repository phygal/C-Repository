/*
** File: plane.h
** Author: Daniel Galeano Sancho
** Date: 25-04-2019
** Description: PAC8
*/


// define constants
#define MAX_CHAR 20+1
#define MAX_PLANES 50


/*********************************************************************************************************
 * Write constants here */
#define NUM_CLASSES 3
#define CODE_FIRSTCLASS 1
#define CODE_BUSINESS 2
#define CODE_TURIST 3

//define enumerated boolean type
typedef enum {FALSE, TRUE} boolean;

//define enumerated utility type
typedef enum {COMMERCIAL,PRIVATE,GOVERNMENTAL,MILITAR,EXPERIMENTAL,OTHERS} tUtility;

//define tPlane type
typedef struct {
    int id; 
	char model[MAX_CHAR]; 
	int year;
	tUtility utility; 
	float percentOccupationFirstclass;
	float percentOccupationBusiness; 
	float percentOccupationTurist;       
	boolean isActive; 
} tPlane;

/*********************************************************************************************************
 * Define table type here 
 *********************************************************************************************************/
typedef struct { 
	tPlane plane[MAX_PLANES];
	int numPlanes;
} tPlanesTable;
 
/*********************************************************************************************************
 * Write new functions headers here
 *********************************************************************************************************/
/* Action for table initialization */ 
void planesTableInitialize (tPlanesTable *planeTable);

/* Function for calculating average occupation */
double planesTableOccupation (tPlanesTable planeTable, int idClass);

/* Action for selecting planes whose occupation is below average */ 
void planesTableSelectByOccupation(tPlanesTable planesTable, double average, int idClass, tPlanesTable *selectTable);
 