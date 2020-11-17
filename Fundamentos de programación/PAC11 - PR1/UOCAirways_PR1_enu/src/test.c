#include <stdio.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "passenger.h"

#define PASSENGER1 "10 LUISA MARTINEZ 0 38908321Y 1980 7 15 ES 1 7814 1000"    
#define PASSENGER2 "20 JOHN DOE 1 44451217G 1976 3 14 UK 1 1234 100"
#define PASSENGER3 "30 PETER WILLIAMS 1 41072140T 1965 2 28 IR 0 0 0"
#define PASSENGER4 "40 JUSTINE LECLERC 1 23169220R 1960 8 20 FR 1 4361 200"
#define PASSENGER5 "50 JUSTINE LEBLANC 1 23169221R 1965 4 22 FR 1 4362 250"

void runTests() {	
	int passedTestPR1, passedTestPR2=0;
	int totalTestPR1, totalTestPR2=0;
	
	printf("=================================================\n");
	printf("====       PRACTICAL ACTIVITY 1 TESTS        ====\n");
	printf("=================================================\n");	
	runTestsPR1(&totalTestPR1, &passedTestPR1);

	printf("===================================\n");
	printf("====       TEST SUMMARY        ====\n");
	printf("===================================\n");		
	printf("\tPR1: Passed %d of %d [%0.2f%%]\n", passedTestPR1, totalTestPR1, (float)passedTestPR1/totalTestPR1*100.0);
	printf("\n\tTotal: Passed %d of %d [%0.2f%%]\n", passedTestPR1+passedTestPR2, totalTestPR1+totalTestPR2, (float)(passedTestPR1+passedTestPR2)/(totalTestPR1+totalTestPR2)*100.0);
	printf("===================================\n");		
}

void runTestsPR1(int *totalTest, int *passedTest) {
	*totalTest=0;
	*passedTest=0;
	
	test_serialization(totalTest, passedTest);
	test_cpycmp(totalTest, passedTest);
	test_persistence(totalTest, passedTest);
	test_search(totalTest, passedTest);
	test_count(totalTest, passedTest);
}

void test_serialization(int *totalTest, int *passedTest) {	

	tPassenger d1, d2;
    char str[MAX_LINE];
		
	printf("=================================================\n");
	printf(" PASSENGERS SERIALIZATION (Exercise 3)\n");
	printf("=================================================\n");

	printf("\nTest 3.1: Serialitzation");
	(*totalTest)++;
/* Uncomment to test*/
  
    d1.id= 10;
    strcpy(d1.name,"LUISA");
    strcpy(d1.surname,"MARTINEZ");
    d1.docType= NIF;
    strcpy(d1.docNumber,"38908321Y");
    d1.birthDate.year= 1980;
    d1.birthDate.month= 07;
    d1.birthDate.day= 15;
    strcpy(d1.countryISOCode,"ES");
    d1.customerCardHolder= TRUE;
    d1.cardNumber= 7814;
    d1.fidelityPoints= 1000;
 
    getPassengerStr(d1,MAX_LINE,str);
	
    if (strcmp(PASSENGER1,str)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 3.2: Desserialitzation");
	(*totalTest)++;
    
/* Uncomment to test */
  
	getPassengerObject(PASSENGER1, &d2);
    if (d1.id==d2.id && strcmp(d1.name,d2.name)==0 && strcmp(d1.surname,d2.surname)==0 &&
		d1.docType==d2.docType && strcmp(d1.docNumber,d2.docNumber)==0 && 
        d1.birthDate.year==d2.birthDate.year && d1.birthDate.month==d2.birthDate.month && d1.birthDate.day==d2.birthDate.day && 
        strcmp(d1.countryISOCode,d2.countryISOCode)==0 && d1.customerCardHolder==d2.customerCardHolder && 
        d1.cardNumber==d2.cardNumber && d1.fidelityPoints==d2.fidelityPoints) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
  
	printf("\nTest 3.3: Equal serialization string after conversion to object");
	(*totalTest)++;
	getPassengerObject(PASSENGER1, &d1);
    getPassengerStr(d1,MAX_LINE,str);
    if (strcmp(PASSENGER1,str)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 3.4: Equal serialization object after conversion to string - Comparison");
	(*totalTest)++;
    getPassengerObject(str,&d2);
    if (passenger_cmp(d1, d2)==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;        
	} else {
		printf("\n\t-> FAIL\n");
	}
}	

void test_cpycmp(int *totalTest, int *passedTest) {	

	tPassenger d1, d2, d4, d5;
    char str[MAX_LINE];
		
	printf("=================================================\n");
	printf(" PASSENGERS COPY AND COMPARE (Exercise 4)\n");
	printf("=================================================\n");
	
	printf("\nTest 4.1: Copy (check by string comparison)");
	(*totalTest)++;
	getPassengerObject(PASSENGER1, &d1);
	passenger_cpy(&d2,d1);
    getPassengerStr(d2,MAX_LINE,str);
    if (strcmp(PASSENGER1,str)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 4.2: Compare equal passengers");
	(*totalTest)++;
    if (passenger_cmp(d1,d1)==0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
	
	printf("\nTest 4.3: Comparison, first passenger greater than first");
	(*totalTest)++;
	getPassengerObject(PASSENGER4, &d4);
	getPassengerObject(PASSENGER5, &d5);
    if (passenger_cmp(d4,d5)>0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}

	printf("\nTest 4.4: Comparison, second passenger lower than second");
	(*totalTest)++;
    if (passenger_cmp(d5,d4)<0){
       printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}
    
	printf("\nTest 4.5: Copy (check by structure comparison)");
	(*totalTest)++;
	passenger_cpy(&d2,d1);
    if (passenger_cmp(d1,d2)==0) {
        printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL\n");
	}    
}	

void test_persistence(int *totalTest, int *passedTest) {
	tPassengerTable passengers;
	tPassenger p1, p2, p3, p4;
	tError retVal;
	
	printf("=================================================\n");
	printf(" PERSISTENCE OF PASSENGERS (Exercise 5)\n");
	printf("=================================================\n");
	
	printf("\nTest 5.1: Save and load no data");
	(*totalTest)++;
	passengerTable_init(&passengers);	
	passengerTable_save(passengers, "./testPassengers.csv",&retVal);
	passengerTable_init(&passengers);		
	passengerTable_load(&passengers, "./testPassengers.csv",&retVal);
	
	if(retVal==OK){
		if(passengers.nPassengers==0) {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		} else {
			printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, passengers.nPassengers);
		}
	} else {
		printf("\n\t-> FAIL (problem in file reading/writing)\n");
	}
		
	printf("\nTest 5.2: Save and load passengers");
	(*totalTest)++;
	getPassengerObject(PASSENGER1, &p1);
	getPassengerObject(PASSENGER2, &p2);
	getPassengerObject(PASSENGER3, &p3);
	getPassengerObject(PASSENGER4, &p4);
    passengerTable_add(&passengers,p1,&retVal);
    passengerTable_add(&passengers,p2,&retVal);
    passengerTable_add(&passengers,p3,&retVal);
    passengerTable_add(&passengers,p4,&retVal);
	passengerTable_save(passengers, "./testPassengers.csv",&retVal);
	passengerTable_init(&passengers);		
	passengerTable_load(&passengers, "./testPassengers.csv",&retVal);
	
	if(retVal==OK){
		if(passengers.nPassengers==4) {
			if(passenger_cmp(passengers.table[0], p1) != 0 || 
			   passenger_cmp(passengers.table[1], p2) != 0 || 
			   passenger_cmp(passengers.table[2], p3) != 0 || 
			   passenger_cmp(passengers.table[3], p4) != 0 ) {
				printf("\n\t-> FAIL (Values are not correct)\n");
			} else {
				printf("\n\t-> OK\n");
				(*passedTest)++;
			}
		} else {
			printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 4, passengers.nPassengers);
		}
	} else {
		printf("\n\t-> FAIL (problem in file reading/writing)\n");
	}
}

void test_search(int *totalTest, int *passedTest) {	
	tPassengerTable passengers, result;
	tPassenger passenger1, passenger2, passenger3, passenger4, passenger5;	
    tDate date1, date2;
	tError retVal;
		
	printf("=================================================\n");
	printf(" PASSENGER TABLE FILTER (Exercise 6)\n");
	printf("=================================================\n");

	printf("\nTest 6.1: Passengers from a country in empty table");
	(*totalTest)++;
	passengerTable_init(&passengers);	
	passengerTable_init(&result);
    
	passengerTable_filterByCountry(passengers, "FR", &result);
	if(result.nPassengers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nPassengers);
	}

	getPassengerObject(PASSENGER1, &passenger1);
	getPassengerObject(PASSENGER2, &passenger2);
    getPassengerObject(PASSENGER3, &passenger3);
    getPassengerObject(PASSENGER4, &passenger4);
    getPassengerObject(PASSENGER5, &passenger5);
    passengerTable_add(&passengers,passenger1,&retVal);
    passengerTable_add(&passengers,passenger2,&retVal);
    passengerTable_add(&passengers,passenger3,&retVal);
    passengerTable_add(&passengers,passenger4,&retVal);
    passengerTable_add(&passengers,passenger5,&retVal);	
	
	printf("\nTest 6.2: Passengers from a non existent country in non empty table");
	(*totalTest)++;	
	passengerTable_filterByCountry(passengers, "IT", &result);
	if(result.nPassengers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nPassengers);
	}

	printf("\nTest 6.3: Passengers from an existent country in non empty table");
	(*totalTest)++;	
	passengerTable_filterByCountry(passengers, "FR", &result);
	if(result.nPassengers==2) {
		if((passenger_cmp(result.table[0], passenger4)!=0) ||
           (passenger_cmp(result.table[1], passenger5)!=0))  {
			printf("\n\t-> FAIL (Values are not correct)\n");
		} else {
			printf("\n\t-> OK\n");
			(*passedTest)++;
		}
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 2, result.nPassengers);
	}

	printf("\nTest 6.4: Passengers born within two dates in empty table");
	(*totalTest)++;
    date1.year= 1965; date1.month= 1; date1.day= 1;
    date2.year= 1980; date2.month= 1; date2.day= 1;
	passengerTable_init(&passengers);	
	passengerTable_filterByBirthDateInterval(passengers, date1, date2, &result);
	if(result.nPassengers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nPassengers);
	}
	
	printf("\nTest 6.5: Passengers born within two dates in non empty table: null interval");
	(*totalTest)++;
    passengerTable_add(&passengers,passenger1,&retVal);
    passengerTable_add(&passengers,passenger2,&retVal);
    passengerTable_add(&passengers,passenger3,&retVal);
    passengerTable_add(&passengers,passenger4,&retVal);
    passengerTable_add(&passengers,passenger5,&retVal);
	passengerTable_filterByBirthDateInterval(passengers, date2, date1, &result);
	if(result.nPassengers==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 0, result.nPassengers);
	}
	
	printf("\nTest 6.6: Passengers born within two dates in non empty table: interval includes some passengers");
	(*totalTest)++;
	passengerTable_filterByBirthDateInterval(passengers, date1, date2, &result);
	if(result.nPassengers==3) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 3, result.nPassengers);
	}
	
	printf("\nTest 6.7: Passengers born within two dates in non empty table: interval includes all passengers");
	(*totalTest)++;
    date1.year= 1960;
    date2.year= 1990;
	passengerTable_filterByBirthDateInterval(passengers, date1, date2, &result);
	if(result.nPassengers==5) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers in the table. Expected %d and returned %d)\n", 5, result.nPassengers);
	}
}
	
void test_count(int *totalTest, int *passedTest) {

    tAppData appData;
    tPassenger passenger1, passenger2, passenger3, passenger4, passenger5;
	int count;
	int max;
	tError retVal;
   
    appData_init(&appData);

	printf("=================================================\n");
	printf(" PASSENGERS STATISTICS (Exercise 7)\n");
	printf("=================================================\n");

	printf("\nTest 7.1: Number of card holders in empty table");
	(*totalTest)++;
	count= passengerTable_getNumberOfCardHolders(appData.passengers);
	if (count==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, count);
	}

	printf("\nTest 7.2: Number of card holders in non empty table (without hits)");
	(*totalTest)++;
	getPassengerObject(PASSENGER3, &passenger3);
	addPassenger(&appData,passenger3,&retVal);
	count= passengerTable_getNumberOfCardHolders(appData.passengers);
	if (count==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of registers found. Expected %d and returned %d)\n", 0, count);
	}
	
	printf("\nTest 7.3: Number of card holders in non empty table (with hits)");
	(*totalTest)++;
	getPassengerObject(PASSENGER1, &passenger1);
	getPassengerObject(PASSENGER2, &passenger2);
    getPassengerObject(PASSENGER4, &passenger4);
    getPassengerObject(PASSENGER5, &passenger5);
	addPassenger(&appData,passenger1,&retVal);
	addPassenger(&appData,passenger2,&retVal);
	addPassenger(&appData,passenger4,&retVal);
	addPassenger(&appData,passenger5,&retVal);
	count= passengerTable_getNumberOfCardHolders(appData.passengers);
	if (count==4) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of points. Expected %d and returned %d)\n", 2, count);
	}
		
	appData_init(&appData);

	printf("\nTest 7.4: Maximum number of fidelity points for a passenger in empty table:");
	(*totalTest)++;
	max = passengerTable_getMaxFidelityPoints(appData.passengers);
	if(max==0) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of points. Expected %d and returned %d)\n", 0, max);
	}

    addPassenger(&appData,passenger4,&retVal);
	
	printf("\nTest 7.5: Maximum number of fidelity points for a passenger - case 1 passenger:");
	(*totalTest)++;
	max = passengerTable_getMaxFidelityPoints(appData.passengers);
	if(max==200) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of points. Expected %d and returned %d)\n", 200, max);
	}

    addPassenger(&appData,passenger2,&retVal);
	
	printf("\nTest 7.6: Maximum number of fidelity points for a passenger - case 2 passengers in descending order:");
	(*totalTest)++;
	max = passengerTable_getMaxFidelityPoints(appData.passengers);
	if(max==200) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of points. Expected %d and returned %d)\n", 200, max);
	}   

	appData_init(&appData);
    addPassenger(&appData,passenger4,&retVal);
    addPassenger(&appData,passenger1,&retVal);
	
	printf("\nTest 7.7: Maximum number of fidelity points for a passenger - case 2 passengers in ascending order:");
	(*totalTest)++;
	max = passengerTable_getMaxFidelityPoints(appData.passengers);
	if(max==1000) {
		printf("\n\t-> OK\n");
		(*passedTest)++;
	} else {
		printf("\n\t-> FAIL (unexpected number of points. Expected %d and returned %d)\n", 1000, max);
	}  
}
	