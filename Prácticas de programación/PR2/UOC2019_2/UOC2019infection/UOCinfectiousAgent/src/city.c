#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "city.h"
#include <stdbool.h>
#include <limits.h>
#include "error.h"

// Initialize the City structure
tError city_init(tCity * city, char * name, tDate * date, long population, int cases, int critical_cases, int deaths, int recovered, int medical_beds) {
    // Verify pre conditions
    assert(city != NULL);
    assert(name != NULL);
    assert(date != NULL);
    assert(population > 0);
    assert(cases >= 0);
    assert(critical_cases >= 0);
    assert(deaths >= 0);
    assert(recovered >= 0);
    assert(medical_beds > 0);

    // Allocate the memory for the string fields, using the length of the provided text plus 1 space
    //for the "end of string" char '\0'. To allocate memory we use the malloc command.
    city->name = (char*)malloc((strlen(name) + 1) * sizeof(char));

    // Allocate the memory for the last_update field. We use the malloc command.
    city->last_update = (tDate*)malloc(sizeof(tDate));

    // Check that memory has been allocated for all fields. Pointer must be different from NULL.
    if (city->name == NULL || city->last_update == NULL) {
        // Some of the fields have a NULL value, what means that we found some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }

    // Copy params to City fields
    strcpy(city->name, name);

    city->last_update->day = date->day;
    city->last_update->month = date->month;
    city->last_update->year = date->year;

    city->population = population;
    city->cases = cases;
    city->critical_cases = critical_cases;
    city->deaths = deaths;
    city->recovered = recovered;
    city->medical_beds = medical_beds;

    return OK;
}

// Free a city
void city_free(tCity * city){
    assert(city != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc to allocate the fields, we have to free them
    if (city->name != NULL) {
        free(city->name);
        city->name = NULL;
    }

    if (city->last_update != NULL) {
        free(city->last_update);
        city->last_update = NULL;
    }

}

bool city_equal(tCity * city1, tCity * city2){
    // Verify pre conditions
    assert(city1 != NULL);
    assert(city2 != NULL);

    // To see if two cities are equals, we need to compare only their names   

    if (strcmp(city1->name, city2->name) != 0) {
        // cities are different
        return false;
    }

    return true;

}

// Create a list of cities
void cityList_create(tCityList * cities) {
    // PR2_EX1
	cities->first = NULL;
}

//Auxiliary function for cityList_insert in order to get the nth element given an index
tCityNode * cityList_getNth(tCityList * cities, int index){
	int i;
	tCityNode * prev;
	
	prev = cities->first;
	
	
	if (index != INT_MAX){
		i=1;
		if (prev != NULL) {
			// City node is move to the next one until index is reached.
			while (i < index) {
				// If next node is NULL, we prevent the loop going on by making i = index.
				if (prev->next == NULL){
					i = index;
				}
				else{
					i++;
				}
				prev = prev->next;
			}
		}
	}
	else{
		// When INT_MAX, the end of the list is looked for.
		if (prev != NULL) {
			while (prev->next != NULL){
				prev = prev->next;
			}
		}
	}
	return prev;
}
//Auxiliary function for cityList_insert in order to find a city node from a given name
tCityNode * city_find(tCityList * cities,tCity * city){
	tCityNode * auxCityNode;

	// Search algorithm
	bool found;

	// Initial treatment
    auxCityNode = cities->first;

    found = false;
	
    while ((auxCityNode != NULL) && (!found) ){

        if (city_equal(auxCityNode->city,city)) {
            found = true;
        } else {
            // Next node
			auxCityNode = auxCityNode->next;
        }
    }
	// Final treatment
	if (auxCityNode != NULL){
		return auxCityNode;
	} else {
		return NULL;
	}
}

// Insert a city at index position
tError cityList_insert(tCityList * cities, tCity * city, int index) {
    // PR2_EX1    
	tCityNode * auxCityNode;
	tCityNode * newCityNode;
	tCity * newCity;
	
	// Look if the name of the city is already in the list of cities
	auxCityNode = city_find(cities,city);

	if (auxCityNode != NULL){
		// Cursor have a NULL value, what means that we found the city already in the list
		return ERR_DUPLICATED;
	}
	else{
		newCityNode = (tCityNode*)malloc(sizeof(tCityNode));
		
		if(newCityNode == NULL) {
			// Cursor have a NULL value, what means that we found some problem allocating the memory
			
			return ERR_MEMORY_ERROR;
		}
		else {
			newCity = (tCity*)malloc(sizeof(tCity));
			
			if(newCity == NULL) {
				// Cursor have a NULL value, what means that we found some problem allocating the memory
				return ERR_MEMORY_ERROR;
			}
			else {
				
				if (index == 0){
					// No previous element
					newCityNode->next = cities->first;
					cities->first = newCityNode;
				}
				else{
					if (cities->first != NULL) {
						auxCityNode = cityList_getNth(cities,index);
						if (auxCityNode != NULL){
							// Standard case
							newCityNode->next = auxCityNode->next;
							auxCityNode->next = newCityNode;
						}
						else{
							// Index greater than number of elements
							return ERR_INVALID;
						}
					} else {
						cities->first = newCityNode;
						newCityNode->next = NULL;
					}
				}
				
				newCityNode->city = newCity;
				
				return city_init(newCity,city->name,city->last_update,city->population,city->cases,city->critical_cases,city->deaths,city->recovered,city->medical_beds);
			}
		}
	}
}

// Delete the city at index position
bool cityList_delete(tCityList * cities, int index) {
    // PR2_EX2
	int size,i;
	tCityNode * auxCityNode;
	tCityNode * prevCityNode;
	
	i=1;
	size = cityList_size(cities);
	auxCityNode = cities->first;
	
	
	//prevCityNode = auxCityNode;
	
	if ((index < size)&&(auxCityNode != NULL)){
		if (index == 0){
			// For index = 0, we move first node to the next one.
			cities->first = auxCityNode->next;
		} else {
			while(i<=index){
				// Previous city node is saved and auxiliary node is switched to the next one until index is reached.
				prevCityNode = auxCityNode;
				auxCityNode = auxCityNode->next;
				i++;
			}
			// Previous node is joined to the next node of the deleted node.
			prevCityNode->next = auxCityNode->next;
		}
		// City node is deleted freeing its memory.
		city_free(auxCityNode->city);
		free(auxCityNode);
		auxCityNode = NULL;
		return true;
	} else {
		// Index out of size of the city list or list is empty.
		return false;
	}
}

// Get the city at index position
tCity * cityList_get(tCityList * cities, int index) {
    // PR2_EX2
    int i;
	int size;
	tCityNode * auxCityNode;
	
	i=0;
	size = cityList_size(cities);
	auxCityNode = cities->first;
	
	// Check if index is lesser than size of the list and if the list is empty.
	if ((index < size)&&(auxCityNode != NULL)){
		// Loop for all nodes until index is reached.
		while(i<index){
			auxCityNode = auxCityNode->next;
			i++;
		}
		return auxCityNode->city;
	} else {
		// Index out of bounds of the list or list is empty.
		return NULL;
	}
	
	
}

// Returns true if the list is empty
bool cityList_empty(tCityList * cities) {
    // PR2_EX1
    return (cities->first == NULL);
}

// Find cities by name
tCity * cityList_find(tCityList * cities, char * cityName) {
    // PR2_EX2
	tCityNode * auxCityNode;
	
	// Search algorithm
	bool found;

	// Initial treatment
    auxCityNode = cities->first;

    found = false;
	
    while ((auxCityNode != NULL) && (!found) ){

        if (strcmp(auxCityNode->city->name,cityName) == 0) {
            found = true;
        } else {
            // Next node
			auxCityNode = auxCityNode->next;
        }
    }
	// Final treatment
	if (auxCityNode != NULL){
		return auxCityNode->city;
	} else {
		return NULL;
	}
}

// Update the city data
tCity * cityList_update(tCityList * cities, char * cityName, tDate * date, int cases, int critical_cases, int deaths, int recovered) {
    // PR2_EX2
	tCity * auxCity;
	
	// Look for the city in the list
	auxCity = cityList_find(cities,cityName);
	
	// If there is a city that matches the name, every field is updated.
	if (auxCity != NULL) {
		auxCity->last_update->year = date->year;
		auxCity->last_update->month = date->month;
		auxCity->last_update->day = date->day;
		
		// These fields must be added to the current value.
		auxCity->cases += cases;
		auxCity->critical_cases += critical_cases;
		auxCity->recovered += recovered;
		auxCity->deaths += deaths;
		
		// Deaths must be substracted from the current value of population.
		auxCity->population -= deaths;
	}
	
    return auxCity;
}

// Delete all cities
void cityList_free(tCityList * cities) {
    // PR2_EX2
	int size;
	
	size = cityList_size(cities);
	
	if (cities->first != NULL) {
		// Function cityList_delete with index = 0 (first node) is used for deleting every node until field size is reached.
		for(int i=0;i<size;i++) {
			cityList_delete(cities,0);
		}
	}

}

// Gets the number of elements in the list
int cityList_size(tCityList * cities) {
    // PR2_EX1    
	int size = 0;
	tCityNode * aux;
	
	aux = cities->first;
	
	// While there is a next node, size is risen.
	while (aux != NULL) {
		aux = aux->next;
		size++;
	}
	
	return size;
}

// Create a list of cities
void cityList_print(tCityList * cities) {
    // Verify pre conditions
    assert(cities != NULL);
    int num_elements = 0;
    tCityNode * ptr;
    ptr = cities->first;
    while (ptr != NULL) {
        printf("%d %s \n ", num_elements, ptr->city->name);
        printf("\tpopulation:%li medical_beds:%d updated:%d/%d/%d \n ",
            ptr->city->population,
            ptr->city->medical_beds,
            ptr->city->last_update->day,
            ptr->city->last_update->month,
            ptr->city->last_update->year);
        printf("\tcases:%d critical:%d deaths:%d recovered:%d \n ", ptr->city->cases, ptr->city->critical_cases, ptr->city->deaths, ptr->city->recovered);

        ptr = ptr->next;
        num_elements++;
    }
    printf("\n ");
}

long cityList_populationIterative(tCityNode * ptr){
    assert(ptr != NULL);
    long total_population = 0;
    while (ptr != NULL) {
        total_population += ptr->city->population;
        ptr = ptr->next;
    }
    return total_population;
}

long cityList_populationRecursive(tCityNode * ptr){
    if (ptr == NULL){
        return 0;
    }
    return cityList_populationRecursive(ptr->next) + ptr->city->population;

}

// Calculate recursively the total critical cases by going through all the items on the list.
int cityList_casesRecursive(tCityNode * cityNode){
    // PR2_EX3
	if (cityNode == NULL) {
		return 0;
	}
	return cityList_casesRecursive(cityNode->next) + cityNode->city->cases;
}

// Calculate recursively the total critical cases by going through all the items on the list.
int cityList_criticalCasesRecursive(tCityNode * cityNode){
    // PR2_EX3
    if (cityNode == NULL) {
		return 0;
	}
	return cityList_criticalCasesRecursive(cityNode->next) + cityNode->city->critical_cases;
}

// Calculate recursively the total deaths by going through all the items on the list.
int cityList_deathsRecursive(tCityNode * cityNode){
    // PR2_EX3
    if (cityNode == NULL) {
		return 0;
	}
	return cityList_deathsRecursive(cityNode->next) + cityNode->city->deaths;
}

// Calculate recursively the total Recovered by going through all the items on the list.
int cityList_recoveredRecursive(tCityNode * cityNode){
    // PR2_EX3
	if (cityNode == NULL) {
		return 0;
	}
	return cityList_recoveredRecursive(cityNode->next) + cityNode->city->recovered;
}

