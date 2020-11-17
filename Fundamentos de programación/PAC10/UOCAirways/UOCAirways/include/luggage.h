/* This code ensures that this file is included only once */
#ifndef __LUGGAGE_H
#define __LUGGAGE_H
/* If the constant LUGGAGE_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */

// provided base passenger / lugagge manipulation functionalities
void writeLuggageObject2str(tLuggage l, FILE *fout);
void str2luggageObject(const char *str, tLuggage *luggage);
void loadPassengersLuggage(tStack *s,const char *fname);
void writePassengersLuggage(tStack s,const char *fname);
tBoolean cmpLuggages(tLuggage l1,tLuggage l2);
void check(const char *File1,const char *File2, int testNum);

// Headers for the functions to be implemented
void printStack(tStack *s);
void splitLuggageOnArrival (tStack *s, tStack *exit, tStack *national, tStack *international);
void deletePassengerLuggage (tStack *s, int idPassenger, tBoolean *found);
void extractFlightLuggage (tStack *inStack, tStack *filteredStack, int airportCode);
void getWithInternationalConnection (tStack *s, tStack *getWithLuggage, int carrierCode);

#endif /*__LUGGAGE_H */