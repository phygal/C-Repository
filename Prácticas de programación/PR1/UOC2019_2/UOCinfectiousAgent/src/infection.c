#include "error.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "commons.h"
#include "infection.h"
#include <stdio.h>

// Initialize the Infection structure
tError infection_init(tInfection* object, tInfectiousAgent* infectiousAgent, const char* country,  tDate* date, int cases, int deaths){
	// PR1_EX4
	
	tInfectiousAgent *auxInfectiousAgent = NULL;
    // Verify pre conditions
    assert(object			!= NULL);
    assert(infectiousAgent	!= NULL);
    assert(country			!= NULL);
	assert(date				!= NULL);
	assert(cases			>= 0);
	assert(deaths			>= 0);
	
    // Allocate the memory for all the fields that are pointers. Note that we use plus 1 space for the "end of string" char '\0'.
	// To allocate memory we use the malloc command.
    object->infectiousAgent	= (tInfectiousAgent*)	malloc(	 							sizeof(tInfectiousAgent));
	auxInfectiousAgent		= (tInfectiousAgent*)		malloc(	 							sizeof(tInfectiousAgent));
	object->country			= (char*)				malloc((strlen(country) + 1)*		sizeof(char));
	object->date			= (tDate*)				malloc( 					  		sizeof(tDate));
	object->cases			= 0;
	object->deaths			= 0;
    	
    // Check that memory has been allocated for that fields. Pointers must be different from NULL.
    if(	object->infectiousAgent	== NULL
	 || object->country			== NULL
	 || object->date			== NULL
	) {
        // Some of the fields have a NULL value, what means that we found some problem allocating the memory
        printf("MEM error");
		return ERR_MEMORY_ERROR;
    }
	
    // Once the memory is allocated, copy the data. When the fields are strings, we need to use the string copy function strcpy. 
	object->infectiousAgent = infectiousAgent;
    strcpy(object->country, country);
    object->date->year = date->year;
	object->date->month = date->month;
	object->date->day = date->day;
	object->cases = cases;
	object->deaths = deaths;
	
    return OK;
}

// Remove the memory used by Infection structure
void infection_free(tInfection* object){
	// PR1_EX4
    // Verify pre conditions
    assert(object != NULL);
    
    // All memory allocated with malloc and realloc needs to be freed using the free command.
	// In this case, as we use malloc to allocate the fields, we have to free them
	if(object->infectiousAgent != NULL) {
		infectiousAgent_free(object->infectiousAgent);
	}
	if(object->country != NULL) {
		free(object->country);
		object->country = NULL;
	}
	if(object->date != NULL) {
		free(object->date);
		object->date = NULL;
	}
}

// Update cases and deaths of an Infection
void infection_update(tInfection* infection, int cases, int deaths){
	// PR1_EX4
	// Add the given number to the recorded number
	infection->cases = infection->cases + cases;
	infection->deaths = infection->deaths + deaths;
}

// Compare two infections
bool infection_equals(tInfection* infection1, tInfection* infection2) {    
	// PR1_EX4
    // Verify pre conditions
    assert(infection1 != NULL);
    assert(infection2 != NULL);
    
    // To see if two reservoirs are equals, we need to see ALL the values for their fields are equals.    
    // Strings are pointers to a table of chars, therefore, cannot be compared  as  " reservoir1->reservoirname == reservoir2->reservoirname ". We need to use a string comparison function    
    
	if(strcmp(infection1->infectiousAgent->name, infection2->infectiousAgent->name)) {
		// Names of the infectious agent are different
		return false;
	}
    
	if(strcmp(infection1->country, infection2->country)) {
		// Countries of the infections are different
		return false;
	}

    // Name and country have the same value
    return true;
}

// Get the size of the table
unsigned int infectionTable_size(tInfectionTable* table){
    // PR1_EX4
    // Verify pre conditions
    assert(table != NULL);
    
    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;
}

// Initialize the Table of infections
void infectionTable_init(tInfectionTable* table){
	// PR1_EX4
	// Verify pre conditions
    assert(table != NULL);    
    
    // The initialization of a table is to set it to the empty state. That is, with 0 elements. 
    table->size = 0;
    // Using dynamic memory, the pointer to the elements must be set to NULL (no memory allocated).
    table->elements = NULL;
}

// Remove the memory used by InfectionTable structure
void infectionTable_free(tInfectionTable* object){
	// PR1_EX4
    // Verify pre conditions
    assert(object != NULL);
    
    // All memory allocated with malloc and realloc needs to be freed using the free command.
	// In this case, as we use malloc/realloc to allocate the elements, and need to free them.
    if(object->elements != NULL) {
        free(object->elements);
        object->elements = NULL;
    }
    // As the table is now empty, assign the size to 0.
    object->size = 0;
}

// Add a new Infection to the table
tError infectionTable_add(tInfectionTable* table, tInfection* infection){
	// PR1_EX4
    // Verify pre conditions
    assert(table != NULL);
    assert(infection != NULL);
    
    // Check if the infection already is on the table
    if (infectionTable_find(table, infection->infectiousAgent->name,infection->country))
        return ERR_DUPLICATED;
        
    // The first step is to allocate the required space. There are two methods to manage the memory (malloc and realloc).
	// Malloc allows to allocate a new memory block, while realloc allows to modify an existing memory block.    
    if(table->size == 0) {
        // Empty table
        
        // Increase the number of elements of the table
        table->size = 1;
        
        // Since the table is empty, and we do not have any previous memory block, we have to use malloc.
		// The amount of memory we need is the number of elements (will be 1) times the size of one element, which is computed by sizeof(type).
		// In this case the type is tInfection.
        table->elements = (tInfection*) malloc(table->size * sizeof(tInfection));        
    } else {
        // table with elements
        
        // Increase the number of elements of the table
        table->size = table->size + 1 ;
        
        // Since the table is not empty, we already have a memory block. We need to modify the size of this block, using the realloc command.
		// The amount of memory we need is the number of elements times the size of one element, which is computed by sizeof(type).
		// In this case the type is tInfection. We provide the previous block of memory.
        table->elements = (tInfection*) realloc(table->elements, table->size * sizeof(tInfection));         
    }
    
    // Check that the memory has been allocated
    if(table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }
    
    // Once we have the block of memory, which is an array of tInfection elements, we initialize the new element (which is the last one).
	// The last element is " table->elements[table->size - 1] " (we start counting at 0)
    infection_init(&(table->elements[table->size - 1]), infection->infectiousAgent, infection->country, infection->date,
							infection->cases, infection->deaths);
	
    return OK;
}

// Get Infection by Infection and country name
tInfection* infectionTable_find(tInfectionTable* table, const char* infectiousAgentName, const char* country){
	// PR1_EX4
    int i;
    
    // Verify pre conditions
    assert(table != NULL);
    assert(infectiousAgentName != NULL);
	assert(country != NULL);
    
	// Search over the table and return once we found the element.
    for(i=0; i<table->size; i++) {
        if((strcmp(table->elements[i].infectiousAgent->name, infectiousAgentName) == 0) &&
		   (strcmp(table->elements[i].country, country) == 0)) {
            // We return the ADDRESS (&) of the element, which is a pointer to the element
            return &(table->elements[i]);
        }
    }
    
    // The element has not been found. Return NULL (empty pointer).
    return NULL;
}

// Compare two Table of infections
bool infectionTable_equals(tInfectionTable* infectionTable1, tInfectionTable* infectionTable2){
	// PR1_EX4
    // Verify pre conditions
    assert(infectionTable1 != NULL);
    assert(infectionTable2 != NULL);

    int i;
    if(infectionTable1->size != infectionTable2->size){
      return false;
    }

    for(i=0; i< infectionTable1->size;i++)
    {
        // Uses "find" because the order of reservoirs could be different
        if(!infectionTable_find(infectionTable1, infectionTable2->elements[i].infectiousAgent->name,infectionTable2->elements[i].country)) {
            // names are different
            return false;
        }
    }
    
    return true;  
}

// Copy the data of a Infection to another Infection
tError infection_cpy(tInfection* dst, tInfection* src){
	// PR1_EX4
    // Verify pre conditions
    assert(dst != NULL);
    assert(src != NULL);
    
    // Free the space used by destination object. An initialized object is assumed.
	infection_free(dst);
    
    // Initialize the element with the new data
	infection_init(dst,src->infectiousAgent,src->country,src->date,src->cases,src->deaths);
    
    return OK;
}

// Remove a Infection from the table
tError infectionTable_remove(tInfectionTable* table, tInfection* infection){
	// PR1_EX4
    int i;
    bool found;
    
    // Verify pre conditions
    assert(table != NULL);
    assert(infection != NULL);
    
    // To remove an element of a table, we will move all elements after this element one position, to fill the space of the removed element.
    found = false;
    for(i=0; i<table->size; i++) {
        // If the element has been found. Displace this element to the previous element (will never happen for the first one).
		// We use the ADDRESS of the previous element &(table->elements[i-1]) as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if(found) {
            // Check the return code to detect memory allocation errors
            if(infectiousAgent_cpy(&(table->elements[i-1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }
        } else if((strcmp(table->elements[i].infectiousAgent->name, infection->infectiousAgent->name) == 0) &&
				  (strcmp(table->elements[i].country, infection->country) == 0)) {
            // The current element is the element we want to remove. Set found flag to true to start element movement.
            found = true;
        }
    }    
    
    // Once removed the element, we need to modify the memory used by the table.
    if(found) {
        // Modify the number of elements
        table->size = table->size - 1;
        
        // If we are removing the last element, we will assign the pointer to NULL, since we cannot allocate zero bytes
        if (table->size == 0) {
            table->elements = NULL;
        } else {                
            // Modify the used memory. As we are modifying a previously allocated block, we need to use the realloc command.
            table->elements = (tInfection*) realloc(table->elements, table->size * sizeof(tInfection));
            
            // Check that the memory has been allocated
            if(table->elements == NULL) {
                // Error allocating or reallocating the memory
                return ERR_MEMORY_ERROR;
            }        
        }
    } else {
        // If the element was not in the table, return an error.
        return ERR_NOT_FOUND;
    }         
    
    return OK;
}

// Given an infectious agent and a table of type tinfectionTable, 
// it performs a search of the country with the largest infected population, 
// offering us a pointer to it. In case of a tie, the country that is first on the list will be returned. 
// In case of not finding the infectious agent in the list, it will return NULL.
tInfection* infectionTable_getMaxInfection (tInfectionTable* table, const char* infectiousAgentName){
	// PR1_EX4
    int i;
	bool found=false;
	int maxCases = 0;
	int maxDeaths = 0;
	const char* wantedCountry;
    
    // Verify pre conditions
    assert(table != NULL);
    assert(infectiousAgentName != NULL);
    
	// Search over the table.
    for(i=0; i<table->size; i++) {
		// Only information that matchs the name of the infectious agent is checked.
        if((strcmp(table->elements[i].infectiousAgent->name, infectiousAgentName) == 0)) {
			// One time entering this clause means there is at least one element with that infection name.
			found=true;
			
			// If the number of cases of the new country are greater than last number of cases, name of the country and number of cases and deaths are updated.
			if(table->elements[i].cases > maxCases){
				wantedCountry = (char*) malloc((strlen(table->elements[i].country) + 1) * sizeof(char));
				strcpy(wantedCountry,table->elements[i].country);
				maxCases = table->elements[i].cases;
				maxDeaths = table->elements[i].deaths;
					
			}
			else {
				// The new info is also updated when the number of cases are equal but the number of deaths are greater. No need to update number of cases this time.
				if((table->elements[i].cases == maxCases)&&(table->elements[i].deaths > maxDeaths)){
					wantedCountry = (char*) malloc((strlen(table->elements[i].country) + 1) * sizeof(char));
					strcpy(wantedCountry,table->elements[i].country);
					maxDeaths = table->elements[i].deaths;
				}
			}
        }
    }

    
	if (found){
		// Return a cursor to the infection with the found country with that infectious agent.
		return infectionTable_find(table,infectiousAgentName,wantedCountry);
	}
	else{
		// The infection has not been found. Return NULL (empty pointer).	
		return NULL;
	}
}

// Given an infectious agent and a tinfectionTable type table, 
// calculate the mortality rate of an infectious agent worldwide, 
// adding all the deceased and dividing it by the number of affected.
float infectionTable_getMortalityRate (tInfectionTable* table, const char* infectiousAgentName){
	// PR1_EX4
    int i;
	tInfection *maxInfection = NULL;
	int cases = 0;
	int deaths = 0;
    // Verify pre conditions
    assert(table != NULL);
    assert(infectiousAgentName != NULL);
    
	// Search over the table.
    for(i=0; i<table->size; i++) {
        if((strcmp(table->elements[i].infectiousAgent->name, infectiousAgentName) == 0)) {
            // For every country with the same infection name, we sum all over the number of cases and the number of deaths.
			cases = cases + table->elements[i].cases;
			deaths = deaths	+ table->elements[i].deaths;
        }
    }
    
    // Mortality rate.
    return (float) deaths/cases;
}