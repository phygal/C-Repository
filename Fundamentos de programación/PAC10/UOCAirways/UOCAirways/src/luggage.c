#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "stack.h"
#include "luggage.h"

void str2LuggageObject(char *str, tLuggage *luggage) {
	
	char delim[] = " ";
	char *ptr;
	int id, airport, country, carrier;
	int numStops;
	
	ptr = strtok(str, delim);
	sscanf(ptr, "%d",&(id));
	luggage->idPassenger=id;
	//printf(" Passenger id = %d\n", id);
	ptr = strtok(NULL, delim);
	
	numStops=0;
	while(ptr != NULL)
	{	
	    sscanf(ptr, "%d",&(airport));
		ptr = strtok(NULL, delim);
	    sscanf(ptr, "%d",&(country));
		ptr = strtok(NULL, delim);
	    sscanf(ptr, "%d",&(carrier));
		luggage->airportCodes[numStops]=airport;
		luggage->countryCodes[numStops]=country;
		luggage->carrierCodes[numStops]=carrier;
		
		//printf(" ariport = %d, country = %d carrier=%d \n",airport, country, carrier);
		ptr = strtok(NULL, delim);
		numStops++;
	}
	luggage->numStopOvers=numStops-1;
	
}
void writeLuggageObject2str(tLuggage l, FILE *fout) {
	
	int k;
    
	fprintf(fout,"%d", l.idPassenger);
	for(k=0;k<l.numStopOvers+1;k++) 
		fprintf(fout," %d %d %d", l.airportCodes[k],l.countryCodes[k],l.carrierCodes[k]);
	fprintf(fout,"\n");
}


tBoolean readPassengerLuggage(tLuggage *l, FILE *fin) {
	
	char line[MAX_LINE];
	tBoolean success;
		
	if (!feof(fin)) {
		line[0] = '\0';
		/* Read one line (maximum 511 chars) and store it in "line" variable */
		fgets(line, MAX_LINE-1, fin);		
		/* Ensure that the string is ended by 0*/
		line[MAX_LINE-1]='\0';
		if(strlen(line)>0) {
			/* Obtain the object */
			str2LuggageObject(line, l);
			success=TRUE;
		} else {
			/* No content to be transferred to passenger */
			success=FALSE;
		}
	} else
	success=FALSE;
	return success;
}


void loadPassengersLuggage(tStack *s,const char *fname) {

	FILE *fin=0;
	tLuggage l;

	fin=fopen(fname, "r");	
	if (fin!=NULL) {
		// Read passengers file and fill stack
		while (!feof(fin) && !fullStack(*s)) {
			readPassengerLuggage(&l,fin);	
			push(s,l);
		}
		if (fullStack(*s) && !feof(fin)) {
			printf(" NOT ENOUGH STACK SPACE FOR ALL PASSENGERS\n");
		}
	} else {
		printf(" ERROR ACCESSING PASSENGERS FILE\n");
	}
	fclose(fin);
}	

void writePassengersLuggage(tStack s,const char *fname) {
	
	FILE *fout=0;
	tLuggage l;
	
	fout=fopen(fname, "w");
	while (!emptyStack(s)) {
		top(s,&l);
		pop(&s);
		writeLuggageObject2str(l,fout);
	}
        /* Close the file */
    fclose(fout);

}


void check(const char *File1,const char *File2, int testNum) {
	
	FILE *f1,*f2;	
	tLuggage l1,l2;
	tBoolean equals=TRUE;
	tBoolean read1, read2;

	f1=fopen(File1, "r");	
	f2=fopen(File2, "r");	
	
	while ((!feof(f1)) && (!feof(f2)) && (equals==TRUE)) {
		read1=readPassengerLuggage(&l1,f1);
		read2=readPassengerLuggage(&l2,f2);
		if (read1==read2) {
			if (read1==FALSE)
				equals=TRUE;
			else
				equals=cmpLuggages(l1,l2);
		} else
			equals=FALSE;
	}  
	if (equals==TRUE)
		printf("....TEST %d Passed OK \n",testNum);
		else
		printf("....TEST %d NOT Passed\n", testNum);

}

tBoolean cmpLuggages(tLuggage l1,tLuggage l2) {
	
	tBoolean equals=TRUE;
	int k,numStops;
	
	if ((l1.idPassenger!=l2.idPassenger) ||
		(l1.numStopOvers!=l2.numStopOvers)) 
			equals=FALSE;
	else {
		numStops=l1.numStopOvers+1;
		k=0;
		while ((k<numStops) && (equals==TRUE)) {
			equals=(l1.airportCodes[k] == l2.airportCodes[k]);
			k++;
		}
		k=0;
		while ((k<numStops) && (equals==TRUE)) {
			equals=(l1.countryCodes[k] == l2.countryCodes[k]);
			k++;
		}
		k=0;
		while ((k<numStops) && (equals==TRUE)) {
			equals=(l1.carrierCodes[k] == l2.carrierCodes[k]);
			k++;
		}
	}
	
	return equals;
}

void printStack(tStack *s){
	
	tStack aux;
	tLuggage l;
	int i;
	
	while (!emptyStack(*s)) {
		top(*s,&l);
		push(&aux, l);
		pop(s);
		printf(" Passenger id = %d\n", l.idPassenger);
		i=0;
		while (i<l.numStopOvers+1){
			printf(" airport = %d, country = %d carrier=%d \n",l.airportCodes[i], l.countryCodes[i], l.carrierCodes[i]);
			i++;
		}
	}
}

void splitLuggageOnArrival (tStack *s, tStack *exit, tStack *national, tStack *international){
    tLuggage l;
    int numStops;
    tDestination destination;

	while (!emptyStack(*s)){
        top(*s,&l);
        numStops = l.numStopOvers;
        if (numStops == 0){
            destination = EXIT;
		}else{
            if (l.countryCodes[0] != l.countryCodes[1]){
                destination = INTERNATIONAL;
            }else{
                destination = NATIONAL;
            }
        }
        if (destination == EXIT){
			push(exit,l);	
		}else{
			if (destination == NATIONAL){
				push(national,l);
			}else{
				push(international,l);
			}
		}
		
        pop(s);
    }

}

void deletePassengerLuggage (tStack *s, int idPassenger, tBoolean *found){
    tStack aux;
	tLuggage l;
    
    *found = FALSE;
    createStack(&aux);

    while ((!emptyStack(*s))||(!found)){
        top(*s,&l);

        if (l.idPassenger != idPassenger) {
            push(&aux, l);
        }else{
            *found = TRUE;
        }

        pop(s);
    }

    while (!emptyStack(aux)){
        top(aux,&l);
        push(s, l);
        pop(&aux);
    }
}

void extractFlightLuggage (tStack *s, tStack *filteredStack, int airportCode){
    tStack aux;
	tLuggage l;
	    
    createStack(&aux);    

    while (!emptyStack(*s)){
        top(*s,&l);
		if (l.airportCodes[0] == airportCode) {
            push(filteredStack, l);
        }else{
            push(&aux, l);
        }
        pop(s);
    }

    while (!emptyStack(aux)){
        top(aux,&l);
        push(s, l);
        pop(&aux);
    }
    
}

void getWithInternationalConnection (tStack *s, tStack *getWithLuggage, int carrierCode){
    tStack aux;
	tLuggage l;
    tBoolean isSelected;
	int i,numStops;

    createStack(&aux);

    while (!emptyStack(*s)){
        top(*s,&l);
        numStops = l.numStopOvers;
        isSelected = FALSE;

        if (numStops == 0){
            push(&aux, l);
        }else{
            for (i=1;i<l.numStopOvers+1;i++){
                if ((l.countryCodes[i] != l.countryCodes[i-1])&&
                    (l.carrierCodes[i-1] == carrierCode)&&
                    (l.carrierCodes[i] == carrierCode))
                        isSelected = TRUE;
            }
            if (isSelected){
                push(getWithLuggage, l);
            }else{
                push(&aux, l);
            }
        }
        pop(s);
    }

    while (!emptyStack(aux)){
        top(aux,&l);
        push(s, l);
        pop(&aux);
    }
}


