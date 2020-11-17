#include <stdio.h>
#include <math.h>
#include <string.h>
#include <api.h>
#include "passenger.h"
#include "plane.h"

void appData_init(tAppData *object) {
	/* Set parent folder as the default path */
	strcpy(object->path, "../");
	
	/* Initialize the passenger table */
	passengerTable_init(&(object->passengers));
	
	/* Initialize the planes table */
	planesTable_init(&(object->planes));
}

void appData_load(tAppData *object, tError *retVal) {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Load the table of planes */
	sprintf(path,"%splanes.txt", object->path);
	planesTable_load(&(object->planes), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of planes\n");
	}

	/* Load the table of passengers */
	sprintf(path,"%spassengers.txt", object->path);
	passengerTable_load(&(object->passengers), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of passengers\n");
	}

}

void appData_save(tAppData object, tError *retVal)  {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Save the table of planes */
	sprintf(path,"%splanes.txt", object.path);
	planesTable_save(object.planes, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of planes\n");
	}
	
	/* Save the table of passengers */
	sprintf(path,"%spassengers.txt", object.path);
	passengerTable_save(object.passengers, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of passengers\n");
	}
	
}

void appData_setPath(tAppData *object, const char *path)  {		
	strncpy(object->path, path, 255);	
}


/*********************** 
 *        API
 **********************/

void getPlanes(tAppData object, tPlaneTable *result) {
	*result = object.planes;	
}

void getPlane(tAppData object, tPlaneId planeId, tPlane *plane, tError *retVal) {
	
	int i;
	*retVal = OK;

	/* Check if there is a plane with this id */
	i = planesTable_find(object.planes, planeId);
	if (i!=NO_PLANE) {
		plane_cpy(plane,object.planes.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}

}

void addPlane(tAppData *object, tPlane plane, tError *retVal) {
	*retVal = OK;
	tPlane tmp;

	/* Check if there is another plane with the same id */
	getPlane(*object, plane.id, &tmp, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new plane using the plane table method */
		planesTable_add(&(object->planes), plane, retVal);
	}

}

void getPassengers(tAppData object, tPassengerTable *result) {
	*result = object.passengers;	
}

void getPassenger(tAppData object, tPassengerId id, tPassenger *passenger, tError *retVal) {
	
	int i;
	*retVal = OK;
	
	/* Check if there is a passenger with this id */
	i = passengerTable_find(object.passengers, id);
	if (i!=NO_PASSENGER) {
		passenger_cpy(passenger,object.passengers.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}

}

void addPassenger(tAppData *object, tPassenger passenger, tError *retVal) {
	*retVal = OK;
	tPassenger tmpPassenger;
    
	/* Check if there is another passenger with the same id */
	getPassenger(*object, passenger.id, &tmpPassenger, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new passenger using the passenger table method */
		passengerTable_add(&(object->passengers), passenger, retVal);
	}

}

void removePassenger(tAppData *object, tPassenger passenger) {
	
	/* Call the method from the passengers table*/
	passengerTable_del(&(object->passengers), passenger);

}
