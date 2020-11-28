#ifndef __STACK_H__
#define __STACK_H__

#include <pthread.h>

typedef struct Stack {
    double averageValue;
    int length;
    double* elements;
    pthread_mutex_t lock;
} Stack;

void push(Stack* stack, double element);

Stack* new_stack();

double pop(Stack* stack);

void free_stack(Stack* stack);

#endif
