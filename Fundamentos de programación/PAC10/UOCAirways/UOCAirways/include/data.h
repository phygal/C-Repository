/* This code ensures that this file is included only once */
#ifndef __DATA_H
#define __DATA_H
/* If the constant DATA_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

#define MAX_PASSENGERS 400  
#define MAX_STOPOVERS 10
#define MAX_LINE 514


typedef enum {FALSE, TRUE} tBoolean;
typedef enum {EXIT, NATIONAL, INTERNATIONAL} tDestination;

typedef struct {
    int idPassenger;
    int airportCodes[MAX_STOPOVERS+1];
    int countryCodes[MAX_STOPOVERS+1];
    int carrierCodes[MAX_STOPOVERS+1];
	int numStopOvers;
} tLuggage;

#endif /*__DATA_H*/