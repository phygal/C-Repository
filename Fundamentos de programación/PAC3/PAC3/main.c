/*
** File: main.c
** Author: Daniel Galeano Sancho
** Date: 14-03-2019
** Description: PAC3
*/

/* System header file */
#include <stdio.h>

/* User defined types */
typedef enum {FALSE,TRUE} bool;

/* Main function */
int main(int argc, char **argv){

	/* Constants */
	const int NUM_SEATS_FIRST = 16;
    const int NUM_SEATS_BUSINESS = 20;
    const int NUM_SEATS_ECONOMY = 144;
    const int PITCH_FIRST = 135;
    const int PITCH_BUSINESS = 100;
    const int PITCH_ECONOMY = 74;
    const int LENGTH_FIRST = 600;
    const int LENGTH_BUSINESS = 550;

	
	/* Variables */
	int avgSold[3];
    
	printf("Enter last year sold tickets average for First Class: >> ");
	scanf("%d",&avgSold[0]);
	printf("Enter last year sold tickets average for Business Class: >> ");
	scanf("%d",&avgSold[1]);
	printf("Enter last year sold tickets average for Economy Class: >> ");
	scanf("%d",&avgSold[2]);

	if((avgSold[0]>0)&&(avgSold[0]<=NUM_SEATS_FIRST)){
		if((avgSold[1]>0)&&(avgSold[1]<=NUM_SEATS_BUSINESS)) {
			if((avgSold[2]>0)&&(avgSold[2]<=NUM_SEATS_ECONOMY)) {
				if((avgSold[0]<(0.25*NUM_SEATS_FIRST))&&(avgSold[1]<(0.5*NUM_SEATS_BUSINESS))) {
					printf("You should convert all the seats to economy class.\n");
					printf("Economy seats added: %d.\n",6*(LENGTH_FIRST + LENGTH_BUSINESS)/PITCH_ECONOMY);
				}else{
					if((avgSold[0]<(0.25*NUM_SEATS_FIRST))&&(avgSold[1]>=(0.5*NUM_SEATS_BUSINESS))) {
						printf("You should convert all the first class seats to business class seats.\n");
						printf("Business seats added: %d.\n",4*(LENGTH_FIRST)/PITCH_BUSINESS);
					}else{
						printf("You should do a more detailed study.\n");
					}
				}
			}else{
				printf("ERROR.\n");
			}
		}else{
			printf("ERROR.\n");
		}
	}else{
		printf("ERROR.\n");
	}



	
	return 0;
}
