#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "infectiousAgent.h"

// Initialize the infectious agent structure
tError infectiousAgent_init(tInfectiousAgent* object, char* name, float r0, char* medium, tDate* date, char* city, tReservoirTable* reservoirList) {
    
    // PR1_EX2
	//tReservoirTable *auxReservoirTable = NULL;
	tReservoir *auxReservoir = NULL;
	
    // Verify pre conditions
    assert(object			!= NULL);
    assert(name				!= NULL);
    assert(r0				>= 0);    
	assert(medium			!= NULL);
	assert(date->year		> 0);
	assert(date->year		<= 9999);
	assert(date->month		> 0);
	assert(date->month		<= 12);
	assert(date->day		> 0);
	assert(date->day		<= 31);
	assert(city				!= NULL);
	assert(reservoirList	!= NULL);
	
    // Allocate the memory for all the fields that are pointers. Note that we use plus 1 space for the "end of string" char '\0'.
	// To allocate memory we use the malloc command.
	object->name	= (char*)	malloc((strlen(name) + 1)	* sizeof(char));
	object->r0 		= 0;
	object->medium	= (char*)	malloc((strlen(medium) + 1)	* sizeof(char));
	object->date	= (tDate*)	malloc( 					  sizeof(tDate));
    object->city	= (char*)	malloc((strlen(city) + 1)	* sizeof(char));
	//object->reservoirList = (tReservoirTable*) malloc(reservoirList->size *	sizeof(tReservoirTable));
	object->reservoirList = (tReservoirTable*) malloc(		sizeof(tReservoirTable));
	auxReservoir = (tReservoir*) malloc(sizeof(tReservoir));
	
    // Check that memory has been allocated for that fields. Pointers must be different from NULL.
    if(	object->name			== NULL
	 || object->medium			== NULL
	 || object->date			== NULL
	 || object->city			== NULL
	 || object->reservoirList	== NULL
	) {
        // Some of the fields have a NULL value, what means that we found some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }
	
    // Once the memory is allocated, copy the data. When the fields are strings, we need to use the string copy function strcpy. 
    strcpy(object->name, name);
	object->r0 = r0;
	strcpy(object->medium, medium);
    object->date->year = date->year;
	object->date->month = date->month;
	object->date->day = date->day;
	strcpy(object->city, city);

	reservoirTable_init(object->reservoirList);
	for (int i=0;i<reservoirList->size;i++){
		reservoir_init(auxReservoir,reservoirList->elements[i].name,reservoirList->elements[i].species);
		reservoirTable_add(object->reservoirList,auxReservoir);
		reservoir_free(auxReservoir);
		//reservoir_cpy(&(object->reservoirList->elements[i]),&(reservoirList->elements[i]));
		//reservoirTable_add(object->reservoirList,reservoirList);
	}
	
    return OK;
}

// Remove the memory used by infectious agent structure
void infectiousAgent_free(tInfectiousAgent* object) {
    
    // PR1_EX2
    // Verify pre conditions
    assert(object != NULL);
    
    // All memory allocated with malloc and realloc needs to be freed using the free command.
	// In this case, as we use malloc to allocate the fields, we have to free them
	if(object->name != NULL) {
		free(object->name);
		object->name = NULL;
	}
	if(object->r0 != 0.0){
		object->r0 = 0.0;
	}
	if(object->medium != NULL) {
		free(object->medium);
		object->medium = NULL;
	}
	if(object->date != NULL) {
		free(object->date);
		object->date = NULL;
	}
	if(object->city != NULL) {
		free(object->city);
		object->city = NULL;
	}
	if(object->reservoirList != NULL) {
		free(object->reservoirList);
		object->reservoirList = NULL;
	}
}

// Get the reservoirs list of an infectious agent
tReservoirTable* infectiousAgent_getReservoirs(tInfectiousAgent* object) {
    
	// PR1_EX2
    return object->reservoirList;
}

// Compare two infectious agent
bool infectiousAgent_equals(tInfectiousAgent* infectiousAgent1, tInfectiousAgent* infectiousAgent2) {
    
    // PR1_EX2
    // Verify pre conditions
    assert(infectiousAgent1 != NULL);
    assert(infectiousAgent2 != NULL);
    
    // To see if two reservoirs are equals, we need to see ALL the values for their fields are equals.    
    // Strings are pointers to a table of chars, therefore, cannot be compared  as  " reservoir1->reservoirname == reservoir2->reservoirname ". We need to use a string comparison function    
    
    if(strcmp(infectiousAgent1->name, infectiousAgent2->name) != 0) {
        // Names of the infectious agent are different
		return false;
    }
    
    if(infectiousAgent1->r0 != infectiousAgent2->r0) {
        // Basic reproductive ratios are different
		return false;
    }
	
	if(strcmp(infectiousAgent1->medium, infectiousAgent2->medium) != 0) {
        // Transmission medium is different
		return false;
    }
	
	if((infectiousAgent1->date->year != infectiousAgent2->date->year) ||
	   (infectiousAgent1->date->month != infectiousAgent2->date->month) ||
	   (infectiousAgent1->date->day != infectiousAgent2->date->day)) {
        // Dates of first infection are different
		return false;
    }
	
	if(strcmp(infectiousAgent1->city, infectiousAgent2->city) != 0) {
        // Cities of first infection are different
		return false;
    }
	
	if (!reservoirTable_equals(infectiousAgent1->reservoirList,infectiousAgent2->reservoirList)){
		return false;
	}

    // All fields have the same value
    return true;//return false;
}

// Copy the data of a infectious agent to another infectious agent
tError infectiousAgent_cpy(tInfectiousAgent* dest, tInfectiousAgent* src) {
    
    // PR1_EX2
    // Verify pre conditions
    assert(dest != NULL);
    assert(src != NULL);
    
    // Free the space used by destination object. An initialized object is assumed.
	infectiousAgent_free(dest);
    
    // Initialize the element with the new data
    //reservoir_init(dest, src->name, src->species);
	infectiousAgent_init(dest,src->name,src->r0,src->medium,src->date,src->city,src->reservoirList);
    
    return OK;// return ERR_NOT_IMPLEMENTED;
}

// Initialize the Table of infectious agents
void infectiousAgentTable_init(tInfectiousAgentTable* table) {
    // PR1_EX3
	// Verify pre conditions
    assert(table != NULL);    
    
    // The initialization of a table is to set it to the empty state. That is, with 0 elements. 
    table->size = 0;
    // Using dynamic memory, the pointer to the elements must be set to NULL (no memory allocated).
    table->elements = NULL;
}

// Remove the memory used by infectious agent table structure
void infectiousAgentTable_free(tInfectiousAgentTable* object) {
    // PR1_EX3
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

// Add a new infectious agent to the table
tError infectiousAgentTable_add(tInfectiousAgentTable* table, tInfectiousAgent* infectiousAgent) {
    // PR1_EX3
    // Verify pre conditions
    assert(table != NULL);
    assert(infectiousAgent != NULL);
    
    // Check if the infectious agent already is on the table
    if (infectiousAgentTable_find(table, infectiousAgent->name))
        return ERR_DUPLICATED;
        
    // The first step is to allocate the required space. There are two methods to manage the memory (malloc and realloc).
	// Malloc allows to allocate a new memory block, while realloc allows to modify an existing memory block.    
    if(table->size == 0) {
        // Empty table
        
        // Increase the number of elements of the table
        table->size = 1;
        
        // Since the table is empty, and we do not have any previous memory block, we have to use malloc.
		// The amount of memory we need is the number of elements (will be 1) times the size of one element, which is computed by sizeof(type).
		// In this case the type is tInfectiousAgent.
        table->elements = (tInfectiousAgent*) malloc(table->size * sizeof(tInfectiousAgent));        
    } else {
        // table with elements
        
        // Increase the number of elements of the table
        table->size = table->size + 1 ;
        
        // Since the table is not empty, we already have a memory block. We need to modify the size of this block, using the realloc command.
		// The amount of memory we need is the number of elements times the size of one element, which is computed by sizeof(type).
		// In this case the type is tInfectiousAgent. We provide the previous block of memory.
        table->elements = (tInfectiousAgent*) realloc(table->elements, table->size * sizeof(tInfectiousAgent));         
    }
    
    // Check that the memory has been allocated
    if(table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }
    
    // Once we have the block of memory, which is an array of tInfectiousAgent elements, we initialize the new element (which is the last one).
	// The last element is " table->elements[table->size - 1] " (we start counting at 0)
    infectiousAgent_init(&(table->elements[table->size - 1]), infectiousAgent->name, infectiousAgent->r0, infectiousAgent->medium,
							infectiousAgent->date, infectiousAgent->city, infectiousAgent->reservoirList);
	
    return OK;//return ERR_NOT_IMPLEMENTED;
}                      

// Remove a infectious agent from the table
tError infectiousAgentTable_remove(tInfectiousAgentTable* table, tInfectiousAgent* infectiousAgent) {
    // PR1_EX3
    int i;
    bool found;
    
    // Verify pre conditions
    assert(table != NULL);
    assert(infectiousAgent != NULL);
    
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
        } else if(strcmp(table->elements[i].name, infectiousAgent->name) == 0) {
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
            table->elements = (tInfectiousAgent*) realloc(table->elements, table->size * sizeof(tInfectiousAgent));
            
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
    
    return OK;//return ERR_NOT_IMPLEMENTED;
}

// Get infectious agent by infectious agent name
tInfectiousAgent* infectiousAgentTable_find(tInfectiousAgentTable* table, const char* infectiousAgentName) {
    // PR1_EX3
    int i;
    
    // Verify pre conditions
    assert(table != NULL);
    assert(infectiousAgentName != NULL);
    
    // Search over the table and return once we found the element.
    for(i=0; i<table->size; i++) {
        if(strcmp(table->elements[i].name, infectiousAgentName) == 0) {
            // We return the ADDRESS (&) of the element, which is a pointer to the element
            return &(table->elements[i]);
        }
    }
    
    // The element has not been found. Return NULL (empty pointer).
    return NULL;//return NULL;
}

// Get the size of the table
unsigned int infectiousAgentTable_size(tInfectiousAgentTable* table) {
	// PR1_EX3
    // Verify pre conditions
    assert(table != NULL);
    
    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;//return ERR_NOT_IMPLEMENTED;
}