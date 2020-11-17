#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passenger.h"

void getPassengerStr(tPassenger passenger, int maxSize, char *str) {

/*************** PR1 EX3A *****************/
    int length;
	
    /* Build the string */	
	length = snprintf(str,maxSize-1,"%d %s %s %d %s %d %d %d %s %d %d %d", 
			(int)passenger.id, passenger.name, passenger.surname, (int)passenger.docType,
			passenger.docNumber, passenger.birthDate.year, passenger.birthDate.month,
			passenger.birthDate.day, (char*)passenger.countryISOCode,
			(int)passenger.customerCardHolder, passenger.cardNumber,passenger.fidelityPoints);
	if (length>0) 
		str[length]='\0';

/******************************************/
}


void getPassengerObject(const char *str, tPassenger *passenger) {
	
/*************** PR1 EX3B *****************/
	int aux_id, aux_docType, aux_customerCardHolder;
	char aux_countryISOCode[MAX_COUNTRY_CODE];
 			 
    /* read plane data */
    sscanf(str, "%d %s %s %d %s %d %d %d %s %d %d %d", 
			&aux_id, passenger->name, passenger->surname, &aux_docType,
			passenger->docNumber, &passenger->birthDate.year, &passenger->birthDate.month,
			&passenger->birthDate.day, aux_countryISOCode, &aux_customerCardHolder,
			&passenger->cardNumber, &passenger->fidelityPoints);

    passenger->id = (tPassengerId)aux_id;
    passenger->docType = (tDocumentType)aux_docType;
	passenger->customerCardHolder = (tBoolean)aux_customerCardHolder;
	strncpy(passenger->countryISOCode, aux_countryISOCode,MAX_COUNTRY_CODE);

/******************************************/
}

int date_cmp( tDate d1, tDate d2 ) {
    
    int result;
    
    result= 0;

    if (d1.year > d2.year)
        result= 1;
    else if (d1.year < d2.year)
        result= -1;
    else {
        if (d1.month > d2.month)
            result= 1;
        else if (d1.month < d2.month)
            result= -1;
        else {
            if (d1.day > d2.day)
                result= 1;
            else if (d1.day < d2.day)
                result= -1;
        }
    }
    
    return result;
}

void passengerTable_init(tPassengerTable *passengerTable) {
	
	passengerTable->nPassengers=0;
}
	
int passenger_cmp(tPassenger d1, tPassenger d2) {
	
	int result = 0;

/*************** PR1 EX4B *****************/
    result = strcmp(d1.name,d2.name);
    if (result==0) 
    {
        result = strcmp(d1.surname,d2.surname);
        if (result==0)
        {
			if (d1.docType > d2.docType) 
				result = 1;
			else if (d1.docType < d2.docType)
				result = -1;
			else{
				result = strcmp(d1.docNumber,d2.docNumber);
				if (result==0)
				{
					result = date_cmp(d1.birthDate,d2.birthDate);
					if (result==0)
					{
						result = strcmp(d1.countryISOCode,d2.countryISOCode);
						if (result==0)
						{
							if (d1.customerCardHolder > d2.customerCardHolder)
								result = 1;
							else if (d1.customerCardHolder < d2.customerCardHolder)
								result = -1;	
							else{
								if (d1.cardNumber > d2.cardNumber)
									result = 1;
								else if (d1.cardNumber < d2.cardNumber)
									result = -1;	
								else{
									if (d1.fidelityPoints > d2.fidelityPoints)
										result = 1;
									else if (d1.fidelityPoints < d2.fidelityPoints)
										result = -1;	
								}								
							}
						}
					}
				}
			}
		}
	}

/******************************************/

    return result;
}

void passenger_cpy(tPassenger *dst, tPassenger src) {

/*************** PR1 EX4A *****************/
    dst->id = src.id;
    strcpy(dst->name,src.name);
	strcpy(dst->surname,src.surname);
	dst->docType = src.docType;
	strcpy(dst->docNumber,src.docNumber);
	dst->birthDate.year = src.birthDate.year;
	dst->birthDate.month = src.birthDate.month;
	dst->birthDate.day = src.birthDate.day;
	strcpy(dst->countryISOCode,src.countryISOCode);
	dst->customerCardHolder = src.customerCardHolder;
	dst->cardNumber = src.cardNumber;
	dst->fidelityPoints = src.fidelityPoints;

/******************************************/
}

void passengerTable_add(tPassengerTable *tabPassenger, tPassenger passenger, tError *retVal) {

	*retVal = OK;

	/* Check if there enough space for the new passenger */
	if(tabPassenger->nPassengers>=MAX_PASSENGERS)
		*retVal = ERR_MEMORY;

	if (*retVal == OK) {
		/* Add the new passenger to the end of the table */
		passenger_cpy(&tabPassenger->table[tabPassenger->nPassengers],passenger);
		tabPassenger->nPassengers++;
	}

}

int passengerTable_find(tPassengerTable tabPassenger, tPassengerId id) {

	int idx = NO_PASSENGER;
	
	int i=0;
	while(i< tabPassenger.nPassengers && idx==NO_PASSENGER) {
		/* Check if the id is the same */
		if(tabPassenger.table[i].id==id) {
			idx = i;
		}
		i++;
	}
	
	return idx;
}

void passengerTable_del(tPassengerTable *tabPassenger, tPassenger passenger) {
	
	int i;
    int pos;

	pos = passengerTable_find(*tabPassenger,passenger.id);
	if (pos!=NO_PASSENGER){
	/* If the passenger is found, all the rest of the elements are displaced one position */
		for(i=pos; i<tabPassenger->nPassengers-1; i++) {		
			passenger_cpy(&tabPassenger->table[i],tabPassenger->table[i+1]);
		}
		tabPassenger->nPassengers=tabPassenger->nPassengers-1;		
	}
}

void passengerTable_save(tPassengerTable tabPassenger, const char* filename, tError *retVal) {

	*retVal = OK;
	
/*************** PR1 EX5A *****************/
	FILE *fout=0;
	int i;
	char str[MAX_LINE];
	
	/* Open the output file */
	if((fout=fopen(filename, "w"))==0) {
		*retVal = ERR_CANNOT_WRITE;
	} else {
	
        /* Save all passengers to the file */
        for(i=0;i<tabPassenger.nPassengers;i++) {
            getPassengerStr(tabPassenger.table[i], MAX_LINE, str);
            fprintf(fout, "%s\n", str);
        }
            
        /* Close the file */
        fclose(fout);
	}

/******************************************/
}

void passengerTable_load(tPassengerTable *tabPassenger, const char* filename, tError *retVal) {
	
	*retVal = OK;
	
/*************** PR1 EX5B *****************/
	FILE *fin=0;
	char line[MAX_LINE];
	tPassenger newPassenger;
	
	/* Initialize the output table */
	passengerTable_init(tabPassenger);
	
	/* Open the input file */
	if((fin=fopen(filename, "r"))!=NULL) {

		/* Read all the planes */
		while(!feof(fin) && tabPassenger->nPassengers<MAX_PASSENGERS) {
			/* Remove any content from the line */
			line[0] = '\0';
			/* Read one line (maximum 511 chars) and store it in "line" variable */
			fgets(line, MAX_LINE-1, fin);
			/* Ensure that the string is ended by 0*/
			line[MAX_LINE-1]='\0';
			if(strlen(line)>0) {
				/* Obtain the object */
				getPassengerObject(line, &newPassenger);
				/* Add the new plane to the output table */
				passengerTable_add(tabPassenger, newPassenger, retVal);		
			}
		}
		/* Close the file */
		fclose(fin);
		
	}else {
		*retVal = ERR_CANNOT_READ;
	}

/******************************************/
}

void passengerTable_filterByCountry(tPassengerTable tabPassenger, tCountry country, tPassengerTable *result) {

/*************** PR1 EX6A *****************/
	tError retVal;
	int i;
	passengerTable_init(result);
	for(i=0;i<tabPassenger.nPassengers;i++) {
		if (strcmp(country, tabPassenger.table[i].countryISOCode)==0){
			passengerTable_add(result, tabPassenger.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabPlanes which cannot have more than MAX_PLANES*/
		}
	}

/******************************************/
}

void passengerTable_filterByBirthDateInterval(tPassengerTable tabPassenger, tDate minDate, tDate maxDate, tPassengerTable *result) {
    
/*************** PR1 EX6B *****************/
	tError retVal;
	int i;
	passengerTable_init(result);
	for(i=0;i<tabPassenger.nPassengers;i++) {
		if 	((date_cmp(tabPassenger.table[i].birthDate,minDate)!=-1)&&
			 (date_cmp(tabPassenger.table[i].birthDate,maxDate)!=1))
		{
			passengerTable_add(result, tabPassenger.table[i],&retVal);
		/* retVal will always be OK as the result table will be smaller than tabPlanes which cannot have more than MAX_PLANES*/
		}
	}

/******************************************/
}

int passengerTable_getNumberOfCardHolders(tPassengerTable tabPassenger) {

	int numPassengers = 0;

/*************** PR1 EX7A *****************/
	int i;
	
	for(i=0;i<tabPassenger.nPassengers;i++) {
		if (tabPassenger.table[i].customerCardHolder)
			numPassengers += 1;
	}

/******************************************/
	return numPassengers;
}

/* Gets the maximum amount of fidelity points of a passenger */
float passengerTable_getMaxFidelityPoints(tPassengerTable tabPassenger){

	int maxPoints = 0;

/*************** PR1 EX7B *****************/
	int i;
	
	for(i=0;i<tabPassenger.nPassengers;i++) {
		if (tabPassenger.table[i].customerCardHolder){
			if (tabPassenger.table[i].fidelityPoints > maxPoints){
				maxPoints = tabPassenger.table[i].fidelityPoints;
			}
		}
		
	}

/******************************************/
	return maxPoints;
}

