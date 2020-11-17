#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include "research.h"
#include "infection.h"
#include "country.h"
#include "commons.h"
#include "error.h"
#include <memory.h>


// Creates a research element out of a country and a stats
tError research_init(tResearch* object, tCountry* country) {
    // PR3_EX1     
    // Verify pre conditions
    assert(object != NULL);
    assert(country != NULL);

    // Allocate the memory for the country field. We use the malloc command.
    object->country = (tCountry*)malloc(sizeof(tCountry));

    // Check that memory has been allocated for all fields. Pointer must be different from NULL.
    if (object->country == NULL){ 
        // Some of the fields have a NULL value, what means that we found some problem allocating the memory.
        return ERR_MEMORY_ERROR;
    }

    // Once the memory is allocated, copy the data.
	country_cpy(object->country, country);

    // As the field stats is a struct, we need to copy all fields.
    object->stats.Infectivity = country_totalCases(country);
    object->stats.Severity = country_totalCriticalCases(country);
    object->stats.Lethality = country_totalDeaths(country);

    return OK;
}

// Releases data pointed by research element
void research_free(tResearch* object) {
    // PR3_EX1   
    // Verify pre conditions
    assert(object != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command.
	// In this case, as we use malloc to allocate the fields, we have to free them.
    if (object->country != NULL) {
        country_free(object->country);
        free(object->country);
        object->country = NULL;
    }
}

// Compare stats of two countries, 1 if s1 wins, -1 if s2 wins, 0 if tie
int research_compare(tInfectionStats s1, tInfectionStats s2) {
    // PR3_EX1
	
	// Verify pre conditions
	assert(&s1 != NULL);
	assert(&s2 != NULL);
	
	if (s1.Infectivity == s2.Infectivity) {
		// Infectivity are equal.
		if (s1.Lethality == s2.Lethality) {
			// Lethality are equal.
			if (s1.Severity == s2.Severity) {
				// Severity are equal
			    // All three stats are equal, then return 0.
				return 0;
			} else {
				//Severity are different
				if (s1.Severity > s2.Severity){
					// Severity of first country is greater, then return 1.
					return 1;
				} else {
					// Severity of first country is lesser, then return -1.
					return -1;
				}
			}
		} else {
			// Lethality are different.
			if (s1.Lethality > s2.Lethality) {
				// Lethality of first country is greater, then return 1.
				return 1;
			} else {
				// Lethality of first country is lesser, then return -1.
				return -1;
			}
		}
	} else{
		// Infectivity are different
		if (s1.Infectivity > s2.Infectivity) {
			// Infectivity of first country is greater, then return 1.
			return 1;
		} else{
			// Infectivity of first country is lesser, then return -1.
			return -1;
		}
	}
}

// Create the research list
void researchList_create(tResearchList* list) {
    // PR3_EX2
	// Verify pre conditions
	assert(list != NULL);
	
	// Initialize all pointers and set size to 0.
	list->first = NULL;
	list->last = NULL;
	list->size = 0;
}

// Insert/adds a new research to the research list
tError researchList_insert(tResearchList* list, tResearch* research, int index) {
    // PR3_EX2
	int i=1;
	
	// Tmp node is the new node we create for the element to insert.
	tResearchListNode * resListNodeTmp;
	
	//Aux node is the node we use for reading already existing elements of the list.
	tResearchListNode * resListNodeAux;

	// Verify pre conditions
    assert(list != NULL);
	assert(research != NULL);
	assert(index > 0);
	
	// Assign memory for the new node.
	resListNodeTmp = (tResearchListNode*)malloc(sizeof(tResearchListNode));
	
	if (resListNodeTmp == NULL) {
		// There is a memory error if there is no memory assigned to node after a malloc.
		return ERR_MEMORY_ERROR;
    } else {
		// Assign memory to the new research
		resListNodeTmp->e = (tResearch*)malloc(sizeof(tResearch));
		
		// Assign the information of the country to the element
		research_init(resListNodeTmp->e,research->country);
		
		if (index > list->size + 1){
			// Index valid only if it is lesser than size of the list plus one.
			return ERR_INVALID_INDEX;
		}
		
		// Begin for the first node of the list
		resListNodeAux = list->first;
		
		// Index = 1 means to insert the element at the beginning of the list.
		if (index == 1) {
			if(resListNodeAux !=NULL) {
				// Insert the element before current node, only if there is a element (not empty list).
				resListNodeAux->prev = resListNodeTmp;
			}
			
			// New first node is the new one.
			list->first = resListNodeTmp;
			
			// Next node of the new one is the current node (old first one).
			resListNodeTmp->next = resListNodeAux;
			
			// As the new node is first one, the previous node is NULL.
			resListNodeTmp->prev = NULL;
			
			if (list->last == NULL) {
				// If there is no last element, means list is empty, so the new node is the last node too.
				list->last = resListNodeTmp;
			}
		
		// Index being equal to size+1, means to insert the new node at the end of the list
		} else if (index == list->size + 1) {
			// The next node of the current last node, is the new node.
			list->last->next = resListNodeTmp;
			
			// The previous node of the new one, is the old last node.
			resListNodeTmp->prev = list->last;
			
			// New last node is the new one.
			list->last = resListNodeTmp;
			
			// The next node of the new one is NULL (as it is the last node).
			resListNodeTmp->next = NULL;
		
		// Index between 1 and size+1.
		} else {
			// Look for the node at position set by index.
			while((resListNodeAux->next != NULL)&&(i<index)) {
				resListNodeAux = resListNodeAux->next;
				i++;
			}
			
			// Previous node of the new one is the node previous to the old one.
			resListNodeTmp->prev = resListNodeAux->prev;
			
			// Change the next node of the previous node of the old one, to be the new node.
			resListNodeAux->prev->next = resListNodeTmp;
			
			// Current node has previous one as the new node.
			resListNodeAux->prev = resListNodeTmp;
			
			// Next node of the new one is the current node.
			resListNodeTmp->next = resListNodeAux;
		}

		// When new node is set, add 1 to the size of the list.
		list->size++;

		return OK;
	}	
}

// Deletes a research from the research list
tError researchList_delete(tResearchList* list, int index) {
    // PR3_EX2
    int i;
    tResearchListNode * resListNode;

    // Verify pre conditions
    assert(list != NULL);
    assert(index >= 1);

    // Empty list.
    if (list->size == 0) return ERR_EMPTY_LIST;
	
	// Index out of bounds.
	if (index > list->size) return ERR_INVALID_INDEX;

    // Find element at index-1 position
    i = 1;
	resListNode = list->first;

	// Delete first element
	if (index == 1) {
		// After deletion, new first node is the next node of the current node.
		list->first = resListNode->next;
		
		if (resListNode->next != NULL) {
			// If there is a next node of the new first node, previous node of that one is NULL.
			resListNode->next->prev = NULL;
		} else {
			// If there is no node after first node, it means list is empty after deletion.
			list->last = NULL;
		}
	// Delete last element
	} else if (index == list->size) {
		// Node to be deleted is last one
		resListNode = list->last;
		
		// After new last element, there is no node.
		list->last->prev->next = NULL;
		
		// New last element is previous one of the old last node.
		list->last = list->last->prev;
	
	// Delete element in position set by index.
	} else {
		// Look for the node on the position set by index
		while((resListNode->next != NULL)&&(i<index)) {
			resListNode = resListNode->next;
			i++;
		}
		
		// Rearrange next node of the previous element, to be the next element.
		resListNode->prev->next = resListNode->next;
		
		// Rearrange previous node of the following element, to be the previous element.
		resListNode->next->prev = resListNode->prev;
	}
	
    // Free tResearch structure.
	research_free(resListNode->e);
	
	// Free pointer to the deleted node.
	resListNode = NULL;
	
	// As node is deleted, we substract 1 to the size of the list.
	list->size--;
	
	return OK;
}

// Gets research from given position, NULL if out of bounds
tResearchListNode* researchList_get(tResearchList* list, int index) {
    // PR3_EX2
    int i;
    tResearchListNode * resListNode;

    // Verify pre conditions
    assert(list != NULL);
    assert(index >= 1);

    // Index must be lesser or equal to the size of the list.
	if (index <= list->size) {
		i = 1;
		// Begin with first node.
		resListNode = list->first;
		
		// Look for the node at the position set by the index.
		while (i < index) {
			resListNode = resListNode->next;
			i++;
		}
		
		// Node found is what we are looking for
		return resListNode;
	
	//index is out of bounds
	} else {
		return NULL;
	}
}

// Gets true if list is empty
bool researchList_empty(tResearchList* list) {
    // PR3_EX2
	// Verify pre conditions
    assert(list != NULL);

	// First node equals NULL means an empty list. No need to check last node.
    if (list->first == NULL) {
		return true;
	} else {
		return false;
	}
}

// Remove all data for a research list
void researchList_free(tResearchList* list) {
    // PR3_EX2
	// Verify pre conditions
    assert(list != NULL);
	
	// While list is not empty, first node is deleted.
	while (list->size > 0) {
		researchList_delete(list,1);
	}
}

// given a list of country' research, returns the position of the country in the list
int researchList_getPosByCountryRecursive(tResearchListNode* first, tCountry *country, int pos) {
    // PR3_EX3
	if (first != NULL){
		// Check if name of the country of the node is the same as the one we are looking for.
		if (country_equal(first->e->country,country)) {
			// Get the position passed by parameters.
			return pos;
		} else {
			// Change the node to the next one, and add 1 to the position.
			return researchList_getPosByCountryRecursive(first->next,country,pos+1);
		}
	} else {
		// NULL node means an empty list or that none of the countries meet the name of the country.
		return -1;
	}
}

// given a list of country' research, returns the position of the country in the list
int researchList_getPosByCountry(tResearchList* list, tCountry *country) {
    // PR3_EX3
	// Verify pre conditions
    assert(list != NULL);
	assert(country != NULL);
	
	// Call recursive function starting with first node of the list and position 1.
    return researchList_getPosByCountryRecursive(list->first,country,1);
}

// Swap two elements in the list
tError researchList_swap(tResearchList* list, int index_dst, int index_src) {
    // PR3_EX3  
	int aux;
	tResearchListNode * resListNodeSrc;
	tResearchListNode * resListNodeDst; 
	
	// Verify pre conditions
    assert(list != NULL);
	
	// Both index must be less or equal the size of the list
	if ((index_src > list->size) || (index_dst > list->size)) {
		return ERR_INVALID_INDEX;
	}

	// In order to apply algorithm, index_src must be the least of the two.
	// If they are not, swap values. (As it is a swap function, there is no difference).
	if (index_src > index_dst) {
			aux = index_src;
			index_src = index_dst;
			index_dst = aux;
	}

	// Get the node related to each index.
	resListNodeSrc = researchList_get(list,index_src);
	resListNodeDst = researchList_get(list,index_dst);

	// Swap algorithm relies on inserting and deleting elements in a certain order.
	// 1. A copy of first node has to be inserted in the position of the second index.
	// 2. Delete first node at original position set by first index.
	// 3. A copy of second node has to be inserted in the position of the first index.
	// 4. Delete second node at position next to original set by second index plus 1.
	
	// Step 1.
	researchList_insert(list,resListNodeSrc->e,index_dst);
	
	// Step 2.
	researchList_delete(list,index_src);
	
	// Step 3.
	researchList_insert(list,resListNodeDst->e,index_src);
	
	// Step 4.
	researchList_delete(list,index_dst+1);
	
	return OK;
}

// Sorts input list using bubbleSort algorithm
tError researchList_bubbleSort(tResearchList *list) {
    // PR3_EX3
	tResearchListNode * resListNode;
	
	// Verify pre conditions
    assert(list != NULL);
	
	// If list is empty, sorting has finished.
	if (list->first != NULL){
		// Apply bubble sorting algorithm by looping every position in the list.
		for (int i = 1; i < list->size; i++) {
			// In every step in the algorithm, node starts at first node of the list.
			resListNode = list->first;
			
			// Loop for every position until last position sorted (size of the list minus i).
			for (int j = 1; j < list->size-i+1; j++) {
				// Decrease sort condition meets if second research stats are better (compare returns -1).
				if (research_compare(resListNode->e->stats,resListNode->next->e->stats) == -1) {
					// Sort means to swap between current element and the next one. 
					researchList_swap(list,j,j+1);
				}
				
				// In every loop, change the node to the nex one.
				resListNode = resListNode->next;
			}
		}
	}
	
	return OK;
}

// Helper function, print list contents
void researchList_print(tResearchList list) {
    tResearchListNode *pLNode;

    printf("===== List Contents:\n\n");

    for (int i = 0; i < list.size; i++) {
        pLNode = researchList_get(&list, i + 1);
        printf("\tElemPos: %d\t;\tInfectivity: %d\t;\tSeverity: %d\t;\tLethality: %d\t;\tCountry_Name: \"%s\"\n",
            i + 1,
            pLNode->e->stats.Infectivity,
            pLNode->e->stats.Severity,
            pLNode->e->stats.Lethality,
            pLNode->e->country->name
            );

    }

    printf("\n===== End Of List: %d elems\n", list.size);
}
