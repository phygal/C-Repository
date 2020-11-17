#include <stdio.h>
#include "data.h"
#include "stack.h"
#include "passengers.h"

tBoolean checkFiles(const char *File1,const char *File2) {
	
	FILE *f1=0,*f2=0;	
	tPassenger p1,p2;
	tBoolean equals=TRUE;

	f1=fopen(File1, "r");	
	f2=fopen(File2, "r");	
	
	while ((!feof(f1)) && (!feof(f2)) && (equals==TRUE)) {
		readPassenger(&p1,f1);
		readPassenger(&p2,f2);
		equals=cmpPassengers(p1,p2);
	}
	return equals;
}