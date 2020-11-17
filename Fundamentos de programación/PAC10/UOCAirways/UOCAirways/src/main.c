#include <stdio.h>
#include "data.h"
#include "stack.h"
#include "luggage.h"

int main(int argc, char **argv)
{
	
	int testNum;
	
	tStack inputLuggage;
	tStack exit,national,international;
	tStack tmp;
	tBoolean found;
	
	
	// First test just to evaluate the correct functionality of
	// stack serializing
	// 1.- Load "../luggage1_in.txt" into inputLuggage
	// 2.- Invert the stack order by using invertStack
	// 3.- Write the stack in "../luggage1_out.txt"
	// 4.- Check the result of this action "../luggage1_result.txt"
	//      equals the generated file "../luggage1_out.txt"
	
	testNum=1;
	createStack(&inputLuggage);
	loadPassengersLuggage(&inputLuggage,"../luggage1_in.txt");
	
	invertStack(&tmp,inputLuggage);
	
	writePassengersLuggage(tmp,"../luggage1_out.txt");		
	check("../luggage1_result.txt","../luggage1_out.txt", testNum);  
	//printStack(&inputLuggage);
	
	// Second test to evaluate exercise 1.a implementation
	// 1.- Load "../luggage2_in.txt" into inputLuggage
	// 2.- Create stacks for the exit, international and international luggages
	// 3.- splitLuggageOnArrival
	// 4.- Write the three resulting stacks in three output files according to
	//			exit in "../luggage2_exit_out.txt"
	//			national in "../luggage2_national_out.txt"
	//			international in "../luggage2_international_out.txt"
	// 5.- Check the result of this action 

	testNum=2;
	createStack(&inputLuggage);
	loadPassengersLuggage(&inputLuggage,"../luggage2_in.txt");
	createStack(&exit);
	createStack(&national);
	createStack(&international);
	
	// Introduce here the call to your function
	splitLuggageOnArrival(&inputLuggage,&exit,&national,&international);
	
	writePassengersLuggage(exit,"../luggage2_exit_out.txt");	
	writePassengersLuggage(national,"../luggage2_national_out.txt");	
	writePassengersLuggage(international,"../luggage2_international_out.txt");
	check("../luggage2_exit_result.txt","../luggage2_exit_out.txt", testNum);  
	check("../luggage2_national_result.txt","../luggage2_national_out.txt", testNum);  
	check("../luggage2_international_result.txt","../luggage2_international_out.txt", testNum);  	
	

	// Third test to evaluate exercise 1.b implementation
	// 1.- Load "../luggage3_in.txt" into inputLuggage
	// 2.- Delete luggage for passenger 20
	// 3.- Write the resulting stacks in "../luggage3_out.txt"
	// 4.- Check the result of this action 

	testNum=3;
	createStack(&inputLuggage);
	loadPassengersLuggage(&inputLuggage,"../luggage3_in.txt");	

	// Introduce here the call to your function
	deletePassengerLuggage(&inputLuggage, 20, &found);
	
	writePassengersLuggage(inputLuggage,"../luggage3_out.txt");	
	check("../luggage3_result.txt","../luggage3_out.txt", testNum);  



	// Fourth test to evaluate exercise 1.c implementation
	// 1.- Load "../luggage4_in.txt" into inputLuggage
	// 2.- Extract luggage for flight with destination airport code 33
	// 3.- Write the resulting stacks in "../luggage4_out.txt"
	// 4.- Check the result of this action 
	testNum=4;
	createStack(&inputLuggage);
	createStack(&tmp);
	loadPassengersLuggage(&inputLuggage,"../luggage4_in.txt");
	
	// Introduce here the call to your function
	extractFlightLuggage (&inputLuggage, &tmp, 33);
	
	writePassengersLuggage(tmp,"../luggage4_out.txt");	
	check("../luggage4_result.txt","../luggage4_out.txt", testNum); 


	// Fifth test to evaluate exercise 1.d implementation
	// 1.- Load "../luggage5_in.txt" into inputLuggage
	// 2.- Extract luggage for international connections with flights
	//		for carrier with code 22
	// 3.- Write the resulting stacks in "../luggage45_out.txt"
	// 4.- Check the result of this action 
	testNum=5;
	createStack(&inputLuggage);
	createStack(&tmp);
	loadPassengersLuggage(&inputLuggage,"../luggage5_in.txt");
	
	// Introduce here the call to your function
	getWithInternationalConnection (&inputLuggage, &tmp, 22);
	
	writePassengersLuggage(tmp,"../luggage5_out.txt");	
	check("../luggage5_result.txt","../luggage5_out.txt", testNum); 
		
	return 0;
}
