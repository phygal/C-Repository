#include "data.h"

/* 
 * Methods for application data management 
 */

/* Initialize the application data */
void appData_init(tAppData *object);

/* Load the application data from file */
void appData_load(tAppData *object, tError *error);

/* Save the application data to a file */
void appData_save(tAppData object, tError *error);

/* Allow to assign a path to the application data */
void appData_setPath(tAppData *object, const char *path);

/* 
 * API
 */

/* Return a table with the passengers */
void getPassengers(tAppData object, tPassengerTable *result);

/* Get the passenger information */
void getPassenger(tAppData object, tPassengerId passengerId, tPassenger *passenger, tError *retVal);

/* Add a new passenger */
void addPassenger(tAppData *object, tPassenger passenger, tError *retVal);

/* Remove a certain passenger */
void removePassenger(tAppData *object, tPassenger passenger);

/* Return the table of planes */
void getPlanes(tAppData object, tPlaneTable *result);

/* Get the plane information */
void getPlane(tAppData object, tPlaneId planeId, tPlane *plane, tError *retVal);

/* Add a new plane */
void addPlane(tAppData *object, tPlane plane, tError *retVal);
