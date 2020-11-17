#include <stdio.h>
#include "data.h"
#include "stack.h"
#include "luggage.h"


void createStack(tStack *s) {
    s->nelem=0;
}

void push(tStack *s, tLuggage e) {

    if (s->nelem == MAX_PASSENGERS) {
        printf("\n Full stack \n");
    } else {
		s->A[s->nelem]=e;
        s->nelem++;
	}
}

void pop(tStack *s) {

    if (s->nelem == 0) {
        printf("\n Empty stack\n");
    } else {
        s->nelem--;
    }
}

void top(tStack s, tLuggage *e) {

    if (s.nelem == 0) {
        printf("\n Empty stack \n");
		e=NULL;
    } else {
		*e=s.A[s.nelem-1];
		//copyPassenger(e,s.A[s.nelem-1]);
    }
}

tBoolean emptyStack(tStack s) {

    return (s.nelem == 0);
}

tBoolean fullStack(tStack s) {

    return (s.nelem == MAX_PASSENGERS);
}

int heightStack(tStack s) {

    return (s.nelem);
}


// PAC10 Implementation of new functionalities

void invertStack(tStack *dst, tStack src) {
	
	tLuggage l;
	
	createStack(dst);
	while (emptyStack(src)==FALSE) {
		top(src, &l);		
		push(dst,l);
		pop(&src);
	}	
}
