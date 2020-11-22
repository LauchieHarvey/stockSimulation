// Stack implementation for double type. O(1) push, O(1) length, O(1) avg.
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Initialise the stack variable
Stack new_stack() {
    Stack stack; 
    stack.length = 0;
    stack.averageValue = 0;
    stack.elements = malloc(sizeof(double));
    return stack;
}

// O(1) push a new double onto the stack
void push(Stack* stack, double element) {
    stack->length += 1;
    stack = realloc(stack, sizeof(double) * stack->length);
    stack->elements[stack->length - 1] = element;    

    // update the stack average
    stack->averageValue *= (stack->length - 1)/stack->length;
    stack->averageValue += element/stack->length;
}

// O(1) pop an element from the stack. returns -1 if there are no elements left.
double pop(Stack* stack) {
    if (stack->length <= 0) {
	return -1;
    }
    double element = stack->elements[stack->length - 1];
    stack->length -= 1;
    stack = realloc(stack, sizeof(double) * stack->length);

    // Update average stack value 
    stack->averageValue *= stack->length/(stack->length - 1);
    stack->averageValue -= element/(stack->length - 1);
    
    return stack->elements[stack->length - 1];
}
