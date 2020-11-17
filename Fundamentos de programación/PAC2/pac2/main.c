/*
** File: main.c
** Author: Daniel Galeano Sancho
** Date: 06-03-2019
** Description: PAC2, Exercici 2
*/

/* System header file */
#include <stdio.h>

/* User defined types */
typedef enum {COMMERCIAL,PRIVATE,GOVERNMENTAL,MILITAR,EXPERIMENTAL,OTHERS} tUtility;
typedef enum {FALSE,TRUE} bool;

/* Main function */
int main(int argc, char **argv){

	/* Constants */
	const float WEIGHT_EMPTY1=41415.0;
	const float MAX_WEIGHT_WITHOUT_GAS1=61689.0;
	const unsigned int NUM_PASSENGERS_PER_FLIGHT_ATTENDANT=50;
	const float AVERAGE_WEIGHT=95.0;
	
	/* Variables */
	tUtility utility1, utility2, utility3;
	unsigned int year1, year2, year3; 
	unsigned int seats1, seats2, seats3; 
	unsigned int passengers1; 
	bool isActive1, isActive2, isActive3; 
	float b1;
	bool b2, b3, b4;

	utility1 = COMMERCIAL;
	seats1 = 200;

	printf("Enter the manufacturing year of the plane 1: >> ");
	scanf("%d",&year1);
	printf("Enter the manufacturing year of the plane 2: >> ");
	scanf("%d",&year2);
	printf("Enter the manufacturing year of the plane 3: >> ");
	scanf("%d",&year3);

	printf("Enter the utility of the plane 2 (0 for COMMERCIAL, 1 for PRIVATE, 2 for GOVERNMENTAL, 3 for MILITAR, 4 for EXPERIMENTAL, 5 for OTHERS): >> ");
	scanf("%u",&utility2);
	printf("Enter the utility of the plane 3 (0 for COMMERCIAL, 1 for PRIVATE, 2 for GOVERNMENTAL, 3 for MILITAR, 4 for EXPERIMENTAL, 5 for OTHERS): >> ");
	scanf("%u",&utility3);

	printf("Enter the number of seats of the plane 2: >> ");
	scanf("%d",&seats2);
	printf("Enter the number of seats of the plane 3: >> ");
	scanf("%d",&seats3);

	printf("Enter if the plane 1 is active (0 for FALSE, 1 for TRUE): >>  ");
	scanf("%u",&isActive1);
	printf("Enter if the plane 2 is active (0 for FALSE, 1 for TRUE) : >> ");
	scanf("%u",&isActive2);
	printf("Enter if the plane 3 is active (0 for FALSE, 1 for TRUE) : >> ");
	scanf("%u",&isActive3);

	printf("Enter the number of passengers of plane 1: >> ");
	scanf("%d",&passengers1);

	/* Apartat b1  */
	b1 = MAX_WEIGHT_WITHOUT_GAS1-WEIGHT_EMPTY1-AVERAGE_WEIGHT*((float)(passengers1 + 2 + ((passengers1-1)/NUM_PASSENGERS_PER_FLIGHT_ATTENDANT)+1));

	/* Apartat b2 */
	b2 = ((utility1==PRIVATE)&&(seats1>=15))||((utility2==PRIVATE)&&(seats2>=15))||((utility3==PRIVATE)&&(seats3>=15));	

	/* Apartat b3 */
	/* L’expressió year1 = year2 = year3 no la podem utilitzar perquè
	   no és sintàcticament correcta perquè la primera comparació (year1 = year2)
	   dona un resultat tipus booleà i s’està comparant amb year3 que és de tipus
	   enter. Per tant, l’hem d’utilitzar realitzant una modificació per tal que
	   sigui correcta. */
	b3 = (year1==year2)&&(year2==year3);

	/* Apartat b4 */
	/* L’expressió isActive1 = isActive2 = isActive3 la podríem
	   utilitzar perquè és sintàcticament correcta. El problema és
	   que no ens dona el que demana l’apartat. Aquesta expressió sí
	   que ens retorna cert si els tres avions estan actius, però també
	   dona cert quan l’avió 1 i l’avió 2 estan a diferent estat i l’avió
	   3 no està actiu, entre d’altres. Es resol utilitzant la mateixa
	   expressió que en l’apartat anterior. */
	b4 = (isActive1==isActive2)&&(isActive2==isActive3); 

	printf("Apartat b1: %.2f kg\n",b1);
	printf("Apartat b2 (0 for FALSE, 1 for TRUE): %u\n",b2);
	printf("Apartat b3 (0 for FALSE, 1 for TRUE): %u\n",b3);
	printf("Apartat b4 (0 for FALSE, 1 for TRUE): %u\n",b4);
	
	return 0;
}
