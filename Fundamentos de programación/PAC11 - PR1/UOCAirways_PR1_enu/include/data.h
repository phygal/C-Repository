/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

#define MAX_PLANES 50
#define MAX_PLATE_NUMBER 20+1
#define MAX_PRODUCER_NAME 25+1
#define MAX_MODEL_NAME 15+1

#define MAX_NAME 15+1
#define MAX_SURNAME 25+1
#define MAX_DOC_NUMBER 20+1
#define MAX_COUNTRY_CODE 2+1

#define MAX_PASSENGERS 100
#define MAX_PATHNAME 500
#define MAX_LINE 514
#define NO_PLANE -1
#define NO_PASSENGER -1

/* Definition of a boolean type */
typedef enum {FALSE, TRUE} tBoolean;

/* Definition of the error type. */
typedef enum {OK=1, ERROR=0, ERR_CANNOT_READ=-1, ERR_CANNOT_WRITE=-2, 
			ERR_MEMORY=-3, ERR_DUPLICATED_ENTRY=-4, ERR_INVALID_DATA=-5, 
			ERR_ENTRY_NOT_FOUND=-6,
			ERR_NO_PASSENGER=-7,ERR_NO_PLANE=-8,ERR_NO_FREE_GAP=-9} tError;

typedef int tPassengerId;
typedef int tPlaneId;

typedef enum {
	COMMERCIAL, PRIVATE, GOVERNMENTAL, MILITAR, EXPERIMENTAL, OTHERS 
} tPlaneUtility;

typedef struct {
    tPlaneId id; 
	char plateNumber[MAX_PLATE_NUMBER]; 
	char producer[MAX_PRODUCER_NAME]; 
	char model[MAX_MODEL_NAME]; 
	int  year; 
	tPlaneUtility utility; 
	float weight; 
	float maxSpeed; 
	int maxHeight; 
	int motors; 
	int seats; 
	tBoolean isActive; 
} tPlane;

typedef struct {
	tPlane table[MAX_PLANES];
	int nPlanes;
} tPlaneTable;

/*************** PR1 EX1  *****************/
typedef enum {
	NIF, NIE, PASSPORT, DRIVING_LICENSE, OTHER_DOCUMENTS
} tDocumentType;
/******************************************/

typedef struct {
	int day, month, year;
} tDate;

typedef char tCountry[MAX_COUNTRY_CODE];

typedef struct {
	tPassengerId id;
/*************** PR1 EX1  *****************/
	char name[MAX_NAME];
	char surname[MAX_SURNAME];
	tDocumentType docType;
	char docNumber[MAX_DOC_NUMBER];
	tDate birthDate;
	tCountry countryISOCode;
	tBoolean customerCardHolder;
	unsigned int cardNumber;
	unsigned int fidelityPoints;

/******************************************/
} tPassenger;

typedef struct {
	tPassenger table[MAX_PASSENGERS];
	int nPassengers;
} tPassengerTable;

/* Definition of the application data structure */
typedef struct {
	/* Path where data will be stored */
	char path[MAX_PATHNAME];
	
	/* Planes table */
	tPlaneTable planes;
	
	/* Passengers table */
	tPassengerTable passengers;
	
} tAppData;

#endif /*__DATA_H*/