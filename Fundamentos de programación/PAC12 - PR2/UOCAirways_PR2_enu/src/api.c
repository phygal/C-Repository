#include <stdio.h>
#include <math.h>
#include <string.h>
#include <api.h>
#include "passenger.h"
#include "plane.h"
#include "flight.h"
#include "queue.h"
#include "list.h"

void appData_init(tAppData *object) {
	/* Set parent folder as the default path */
	strcpy(object->path, "../");
	
	/* Initialize the passenger table */
	passengerTable_init(&(object->passengers));
	
	/* Initialize the planes table */
	planesTable_init(&(object->planes));
    
	/* Initialize the flights table */
	flightsTable_init(&(object->flights));
}

void appData_load(tAppData *object, tError *retVal) {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Load the table of planes */
	sprintf(path,"%splanes.txt", object->path);
	planesTable_load(&(object->planes), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of planes\n");
	}

	/* Load the table of passengers */
	sprintf(path,"%spassengers.txt", object->path);
	passengerTable_load(&(object->passengers), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of passengers\n");
	}

	/* Load the table of flights */
	sprintf(path,"%sflights.txt", object->path);
	flightsTable_load(&(object->flights), path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error reading the file of flights\n");
	}
}

void appData_save(tAppData object, tError *retVal)  {
	char path[MAX_LINE];
	*retVal = OK;
	
	/* Save the table of planes */
	sprintf(path,"%splanes.txt", object.path);
	planesTable_save(object.planes, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of planes\n");
	}
	
	/* Save the table of passengers */
	sprintf(path,"%spassengers.txt", object.path);
	passengerTable_save(object.passengers, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of passengers\n");
	}

	/* Save the table of flights */
	sprintf(path,"%sflights.txt", object.path);
	flightsTable_save(object.flights, path, retVal);
	if(*retVal!=OK) {
		printf("ERROR: Error saving the file of flights\n");
	}
}

void appData_setPath(tAppData *object, const char *path)  {		
	strncpy(object->path, path, 255);	
}


/*********************** 
 *        API
 **********************/

void getPlanes(tAppData object, tPlaneTable *result) {
	*result = object.planes;	
}

void getPlane(tAppData object, tPlaneId planeId, tPlane *plane, tError *retVal) {
	
	int i;
	*retVal = OK;

	/* Check if there is a plane with this id */
	i = planesTable_find(object.planes, planeId);
	if (i!=NO_PLANE) {
		plane_cpy(plane,object.planes.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}
}

void addPlane(tAppData *object, tPlane plane, tError *retVal) {
	*retVal = OK;
	tPlane tmp;

	/* Check if there is another plane with the same id */
	getPlane(*object, plane.id, &tmp, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new plane using the plane table method */
		planesTable_add(&(object->planes), plane, retVal);
	}
}

void getPassengers(tAppData object, tPassengerTable *result) {
	*result = object.passengers;	
}

void getPassenger(tAppData object, tPassengerId id, tPassenger *passenger, tError *retVal) {
	
	int i;
	*retVal = OK;
	
	/* Check if there is a passenger with this id */
	i = passengerTable_find(object.passengers, id);
	if (i!=NO_PASSENGER) {
		passenger_cpy(passenger,object.passengers.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}
}

void addPassenger(tAppData *object, tPassenger passenger, tError *retVal) {
	*retVal = OK;
	tPassenger tmpPassenger;
    
	/* Check if there is another passenger with the same id */
	getPassenger(*object, passenger.id, &tmpPassenger, retVal);
	if(*retVal==OK) {
		*retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new passenger using the passenger table method */
		passengerTable_add(&(object->passengers), passenger, retVal);
	}
}

void removePassenger(tAppData *object, tPassenger passenger) {
	
	/* Call the method from the passengers table*/
	passengerTable_del(&(object->passengers), passenger);
}

void getFlights(tAppData object, tFlightTable *result) {
    
    *result = object.flights;
}

void getFlight(tAppData object, tFlightId id, tFlight *flight, tError *retVal) {
    
	int i;
	*retVal = OK;

	/* Check if there is a flight with this id */
	i = flightsTable_find(object.flights, id);
	if (i!=NO_FLIGHT) {
		flight_cpy(flight,object.flights.table[i]);
	} else {
		*retVal = ERR_ENTRY_NOT_FOUND;
	}    
}

void addFlight(tAppData *object, tFlight flight, tError *retVal) {
    
	*retVal = OK;
	tFlight tmpFlight;
    
	/* Check if there is another flight with the same id */
	getFlight(*object, flight.id, &tmpFlight, retVal);
	if(*retVal==OK) {
       *retVal = ERR_DUPLICATED_ENTRY;
	} else {
		/* Add the new flight using the flight table method */
		flightsTable_add(&(object->flights), flight, retVal);
	}    
}

void checkData(tFlight flight, tPassengerTable passengers, tPlaneTable planes, tError *retVal )
{
    /******************* PR2 - EX1 *****************/
	int i,j,k;
	int numberOfSeats;
	
	*retVal = OK;
	
	/* Check if there is a plane with this id */
	i = planesTable_find(planes, flight.plane);
	if (i == NO_PLANE) {
		*retVal = ERR_NO_PLANE;
	} else {	
		/* If the plane exists on the table, check if the number of seats are correct */
		numberOfSeats = planes.table[i].seats;

		if (numberOfSeats % 6 != 0) {
			*retVal = ERR_INVALID_DATA;
		} else {
			/* Check if every passenger on the booking list is on the passengers table */
			j=0;
			k=0;
			while ((j < flight.bookings.nElem) && (k != NO_PASSENGER)) {
				/* Check if the id is the same */
				k = passengerTable_find(passengers, flight.bookings.table[j].passenger);
				if (k == NO_PASSENGER) {
					*retVal = ERR_NO_PASSENGER;
				}
				j++;
			}
			if (*retVal != ERR_NO_PASSENGER) {
				/* Check if the flight has already started */
				if ((flight.status != BOOKING)               ||
				(flight.boardingGate != NO_BOARDING_GATE)||
				(!boardingQueue_empty(flight.priority))  ||
				(!boardingQueue_empty(flight.front))     ||
				(!boardingQueue_empty(flight.back))      ||
				(!boardingQueue_empty(flight.overbooking))) {
					*retVal = ERR_STARTED_FLIGHT;
				}
			}
		}
	}
    /***********************************************/
}

void getThresholdRows( int totalSeats,
                       int *max_priority_row, int *max_front_row, int *max_back_row)
{
    *max_priority_row= (int)((float)PRIORITY_ROW_PERCENT * (float)totalSeats / (float)MAX_SEATS_PER_ROW);
    *max_front_row= *max_priority_row + (int)((float)FRONT_ROW_PERCENT * (float)totalSeats / (float)MAX_SEATS_PER_ROW);
    *max_back_row= *max_front_row + (int)((float)BACK_ROW_PERCENT * (float)totalSeats / (float)MAX_SEATS_PER_ROW);   
}

void assignSeat( tBooking booking, tBoarding *card, int totalSeats,
                 int maxPriorityRow, int maxFrontRow, int maxBackRow,
                 int *seatsPriority, int *seatsFront, int *seatsBack )
{   
    /* initialize boarding card */
    card->passengerId= booking.passenger;
    card->row = NO_ROW;
    card->seat= NO_SEAT;

    /* calculate the proper seat to distribute weight along the plane */
    if (booking.priority) 
    {
        /* assign a priority seat if it's a priority booking and there's a free seat */
        if (*seatsPriority < maxPriorityRow*MAX_SEATS_PER_ROW) 
        {
            card->row = 1 + (*seatsPriority / MAX_SEATS_PER_ROW);
            card->seat= (char)((int)'A' + (*seatsPriority % MAX_SEATS_PER_ROW));          
            *seatsPriority = *seatsPriority + 1;
        }
    } 
    else 
    {
        /* assign a front seat if first half plane has less assigned seats than second half 
         * and there is a free front seat */
        if (*seatsPriority + *seatsFront < *seatsBack &&
            *seatsFront < (maxFrontRow-maxPriorityRow)*MAX_SEATS_PER_ROW) 
        {
            card->row = maxPriorityRow + 1 + (*seatsFront / MAX_SEATS_PER_ROW);
            card->seat= (char)((int)'A' + (*seatsFront % MAX_SEATS_PER_ROW));                      
            *seatsFront = *seatsFront + 1;
        } 
        else 
        {
            /* assign a back seat on other cases */
            if (*seatsBack < (maxBackRow-maxFrontRow)*MAX_SEATS_PER_ROW) 
            {
                card->row = maxFrontRow + 1 + (*seatsBack / MAX_SEATS_PER_ROW);
                card->seat= (char)((int)'A' + (*seatsBack % MAX_SEATS_PER_ROW));
                *seatsBack = *seatsBack + 1;
            }
        }
    }
}

void checkinFlight(tFlight *flight, tPlane plane, tError *retVal ) 
{
    /******************* PR2 - EX2 *****************/
	int maxPriorityRow, maxFrontRow, maxBackRow;
	int seatsPriority, seatsFront, seatsBack;
	int i,numBookings;
	
	tBoarding card;
	
	/* Change flight status to CHECKIN */
	flight->status = CHECKIN;
	
	/* Obtain maximum number of rows of each type */
	getThresholdRows(plane.seats,
					 &maxPriorityRow, &maxFrontRow, &maxBackRow);
	
	/* Assign a seat for each passenger on the booking list */
	i=0;
	numBookings = bookingList_length(flight->bookings);
	while (i < numBookings){
		assignSeat(flight->bookings.table[i], &card, plane.seats,
				   maxPriorityRow, maxFrontRow, maxBackRow,
				   &seatsPriority, &seatsFront, &seatsBack);
	/* Enqueue to its corresponding queue depending on the assigned seat */
		if(card.row != NO_ROW){
			if(card.row <= maxPriorityRow){
				boardingQueue_enqueue(&flight->priority,card);
			} else {
				if(card.row <= maxFrontRow){
					boardingQueue_enqueue(&flight->front,card);
				} else {
					if(card.row <= maxBackRow){
						boardingQueue_enqueue(&flight->back,card);
					}
				}
			}
		} else {
			/* If it is not possible to assign a seat, enqueue to overbooking queue */
			boardingQueue_enqueue(&flight->overbooking,card);
		}
		i++;
	}
    /***********************************************/
}

void accomodatePassenger( tPlane *plane, tBoarding boarding, tError *retVal )
{
    int row, seat, max_rows;
    tBoolean found;
    
    *retVal= OK;
    
    if (plane->occupiedSeats < plane->seats)
    {
        if (boarding.seat == NO_SEAT)
        {
            /* try to accomodate passenger with a non-assigned seat */
            max_rows= plane->seats / MAX_SEATS_PER_ROW;
            found= FALSE;
            row= 0;
            while (row < max_rows && !found)
            {
                seat= 0; 
                while (seat < MAX_SEATS_PER_ROW && !found)
                {
                    found= (plane->layout[row][seat]==NO_PASSENGER);
                    if (!found)
                         seat++;
                }
                if (!found)
                     row++;
            }
            
            if (found)
            {
                plane->layout[row][seat]= boarding.passengerId; 
                plane->occupiedSeats++;                
            }
            else
                *retVal= ERR_NO_FREE_GAP;
        }
        else
        {
            /* accomodate passenger with assigned seat */
            row = boarding.row-1;
            seat= (int)(boarding.seat)-(int)'A';
            plane->layout[row][seat]= boarding.passengerId; 
            plane->occupiedSeats++;
        }
    }
    else
        *retVal= ERR_NO_FREE_GAP;
}

void boardFlight(tFlight *flight, tPassengerTable *passengers, tPlane *plane, tError *retVal ) 
{
    /******************* PR2 - EX3 *****************/
	int index,fidelityPoints;
	tBoarding boarding,boarding2;
	tBoolean boardingComplete;

	/* Status changed to boarding */
	flight->status= BOARDING;
	
	*retVal = OK;
	boardingComplete = FALSE;
	
	/* Dequeue every queue in corresponding order until there is no more space 
	   or boarding is complete. */
	while ((*retVal != ERR_NO_FREE_GAP) && (!boardingComplete)){
		
		/* First of all, priority queue is emptied */
		if (!boardingQueue_empty(flight->priority)) {
			boarding = boardingQueue_head(flight->priority);
			accomodatePassenger(plane, boarding,retVal);
			index = passengerTable_find(*passengers, boarding.passengerId);
			if (*retVal == OK) {
				if (passengers->table[index].customerCardHolder) {
					fidelityPoints = 0;
					fidelityPoints = passengers->table[index].fidelityPoints;
					passengers->table[index].fidelityPoints = fidelityPoints + 100;
				}
				boardingQueue_dequeue(&flight->priority);
			}
			
		}else{
			/* When no priority passengers are left, front and back queues continue
			   boarding alternatively */
			if ((!boardingQueue_empty(flight->front)) ||
			   (!boardingQueue_empty(flight->back))) {
				if (!boardingQueue_empty(flight->front)) {
					boarding = boardingQueue_head(flight->front);
					accomodatePassenger(plane, boarding,retVal);				   
					index = passengerTable_find(*passengers, boarding.passengerId);
					if (*retVal == OK) {
						if (passengers->table[index].customerCardHolder) {
							fidelityPoints = 0;
							fidelityPoints = passengers->table[index].fidelityPoints;
							passengers->table[index].fidelityPoints = fidelityPoints + 100;
						}
						boardingQueue_dequeue(&flight->front);
					}
				}
				if (!boardingQueue_empty(flight->back)) {
					boarding2 = boardingQueue_head(flight->back);
					accomodatePassenger(plane, boarding2,retVal);				   
					index = passengerTable_find(*passengers, boarding2.passengerId);
					if (*retVal == OK) {
						if (passengers->table[index].customerCardHolder) {
							fidelityPoints = 0;
							fidelityPoints = passengers->table[index].fidelityPoints;
							passengers->table[index].fidelityPoints = fidelityPoints + 100;
						}
						boardingQueue_dequeue(&flight->back);
					}								
				}
			}else{
				/* When there is nobody in priority, front or back queues, overbooking
				   queue start to board */
				if (!boardingQueue_empty(flight->overbooking)) {
					boarding = boardingQueue_head(flight->overbooking);
					accomodatePassenger(plane, boarding,retVal);				   
					index = passengerTable_find(*passengers, boarding.passengerId);
					if (*retVal == OK) {
						if (passengers->table[index].customerCardHolder) {
							fidelityPoints = 0;
							fidelityPoints = passengers->table[index].fidelityPoints;
							passengers->table[index].fidelityPoints = fidelityPoints + 100;
						}
						boardingQueue_dequeue(&flight->overbooking);
					}								
				}else{
					/* If there is still space on the plane, but there is no more
					   passengers to board, the boarding is complete */
					boardingComplete = TRUE;
				}		
			}
		}
	}
    /***********************************************/
}

void closeFlight( tFlight *flight ) 
{
    flight->status= CLOSED;
}

void assignBoardingGate( tFlight *flight )
{
    int nPassengers;
    
    nPassengers= bookingList_length(flight->bookings);
    if (nPassengers < BOARDING_THRESHOLD_1)
        flight->boardingGate= BOARDING_GATE_1;
    else if (nPassengers < BOARDING_THRESHOLD_2)
        flight->boardingGate= BOARDING_GATE_2;
    else 
        flight->boardingGate= BOARDING_GATE_3;
}

void setUpPlane( tPlane *plane )
{
    /* frees all potential occupied seats for the given plane */
    init_occupied_seats(plane);
}

void processFlight(tFlight *flight, tPassengerTable *passengers, tPlaneTable *planes, tError *retVal ) 
{
    int index;
    tPlane plane;

    /* check the flight data is correct */
    checkData( *flight, *passengers, *planes, retVal );
    if (*retVal == OK)
    {
        index= planesTable_find(*planes, flight->plane);
        if (index != NO_PLANE) 
        {
            /* get the plane */
            plane_cpy(&plane, planes->table[index]);
            
            /* assign boarding gate */
            assignBoardingGate(flight);
            
            /* begin the checkin process */
            checkinFlight(flight, planes->table[index], retVal);

            /* prepare plane for the boarding */
            setUpPlane(&plane);
            
            /* begin boarding passenger into the plane */
            boardFlight(flight, passengers, &plane, retVal);
            
            /* close flight */
            closeFlight(flight);
        }
    }
}

int searchNextFlight( tFlightTable flights, tAirport origin, tAirport destination, int startIndex )
{
    int foundIndex= NO_FLIGHT;
    
    /******************* PR2 - EX4A *****************/
	int i;
	tBoolean found;
	
	found = FALSE;
	i = startIndex;
	
	/* We want to find flights with the same origin and destination, and among all of those,
	   the earliest one */
	while (i<flights.nFlights){
		/* First we check if origin and destination are the same */
		if ((strcmp(flights.table[i].originAirport,origin)==0) &&
			(strcmp(flights.table[i].destinationAirport,destination)==0)){
			/* If it is the first flight we have found, we keep its index */
			if (!found) {
				found = TRUE;
				foundIndex = i;
			}else{
				/* If we have found other flight, we compare which one is earlier, and 
				   we keep its index */
				if(time_cmp(flights.table[foundIndex].time,flights.table[i].time)==1){
					foundIndex = i;
				}
			}
		}
		i++;
	}
    /************************************************/
   
    return foundIndex;
}

void reallocatePassengers( tBoardingQueue *queue, tBookingList *list, 
                           tPassengerTable *passengers )
{
    /******************* PR2 - EX4B *****************/
	int id,index,position;
	tError retVal;
	tBooking reallocatedBooking;
	
	position = 1;
	
	/* Our aim is to empty overbooking queue */
	while(!boardingQueue_empty(*queue)){
		/* We obtain information about the first passenger in the overbooking queue */
		id = boardingQueue_head(*queue).passengerId;
		index = passengerTable_find(*passengers, id);
		
		/* We build a tBooking type with that information */
		reallocatedBooking.passenger = id;
		
		/* If the passenger has a fidelity card, its booking is set to priority type */
		if (passengers->table[index].customerCardHolder){
			reallocatedBooking.priority = 1;
		}else{
			reallocatedBooking.priority = 0;
		}
		
		/* Passengers are inserted at the beginning of the booking list with the
		   same order that have in the overbooking list */
		retVal = bookingList_insert(list, reallocatedBooking, position);
		
		/* If passengers have fidelity card, we reward them with 200 points */
		if ((retVal == OK)&&(passengers->table[index].customerCardHolder)) {
			passengers->table[index].fidelityPoints += 200;
		}
		boardingQueue_dequeue(queue);
		position++;
	}
    /************************************************/
}

void processAllFlights(tAppData *object, tError *retVal ) 
{    
    int i, next;
    
    for (i= 0; i < object->flights.nFlights; i++) 
    {
        /* process the current flight */
        processFlight( &object->flights.table[i], &object->passengers, &object->planes, retVal );
        
        /* reallocate overbooked passengers */
        if (boardingQueue_length(object->flights.table[i].overbooking)>0)
        {
            /* search next flight between the same origin and destination airport */
            next= searchNextFlight( object->flights,
                                    object->flights.table[i].originAirport, 
                                    object->flights.table[i].destinationAirport, i+1 );

            /* reallocate passengers from overbooking queue and bookings list */
            if (next != NO_FLIGHT)
                reallocatePassengers( &object->flights.table[i].overbooking, 
                                      &object->flights.table[next].bookings,
                                      &object->passengers );
        }
    }
}