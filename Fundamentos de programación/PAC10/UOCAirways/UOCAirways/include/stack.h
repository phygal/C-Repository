/* This code ensures that this file is included only once */
#ifndef __STACK_H
#define __STACK_H
/* If the constant STACK_H is not defined (ifndef), the code is added, otherwise,
 * this code is excluded. When the code is added, the constant is defined, 
 * therefore next time this file will be included it will be defined and no 
 * inclusion will be done. */
typedef struct {
		tLuggage A[MAX_PASSENGERS];
		int nelem;
} tStack;

// provided base stack functionalities
void createStack(tStack *s);
void push(tStack *s, tLuggage e) ;
void pop(tStack *s);
void top(tStack s, tLuggage *e);
tBoolean emptyStack(tStack s);
tBoolean fullStack(tStack s);
int heightStack(tStack s);

// PAC10 Header definition for the functionalities to implement


void invertStack(tStack *s1, tStack s2);


#endif /*__STACK_H*/