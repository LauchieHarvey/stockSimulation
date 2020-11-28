// Stack implementation for double type. O(1) push, O(1) length, O(1) avg.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "stack.h"

// Initialise the stack variable
Stack* new_stack() {
    Stack* stack = malloc(sizeof(Stack));
    stack->length = 0;
    stack->averageValue = 0;
    stack->elements = malloc(sizeof(double));
    pthread_mutex_init(&stack->lock, NULL);
    return stack;
}

// O(1) push a new double onto the stack
void push(Stack* stack, double element) {
    // Lock the stack
    pthread_mutex_lock(&stack->lock);

    stack->length += 1;
    stack->elements = realloc(stack->elements, sizeof(double) * stack->length);
    stack->elements[stack->length - 1] = element;    

    // update the stack average
    stack->averageValue *= (stack->length - 1)/stack->length;
    stack->averageValue += element/stack->length;

    printf("newAvg: %f\n", stack->averageValue);
    fflush(stdout);

    // Release mutex
    pthread_mutex_unlock(&stack->lock);
}

// O(1) pop an element from the stack. returns -1 if there are no elements left.
double pop(Stack* stack) {
    // Lock the stack
    pthread_mutex_lock(&stack->lock);

    if (stack->length <= 0) {
	return -1;
    }
    double element = stack->elements[stack->length - 1];
    stack->length -= 1;
    stack = realloc(stack->elements, sizeof(double) * stack->length);

    // Update average stack value 
    stack->averageValue *= stack->length/(stack->length - 1);
    stack->averageValue -= element/(stack->length - 1);

    // Release the lock
    pthread_mutex_unlock(&stack->lock);
    
    return stack->elements[stack->length - 1];
}

// Releases memory formerly reserved for the stack back to the heap.
void free_stack(Stack* stack) {
    return;
}
