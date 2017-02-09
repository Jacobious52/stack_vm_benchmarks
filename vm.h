#ifndef VM_H
#define VM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
    struct stack *next;
    int value;
} stack;

stack *top = NULL;
int vars[256];

inline void push(int v) {
    stack *next = NULL;
    if (top) {
        next = top;
    }
    top = (stack *)malloc(sizeof(stack));
    top->next = next;
    top->value = v;
}

inline int pop() {
    if (!top) {
        fprintf(stderr, "stack pop failed. head NULL\n");
        exit(1);
        return -1;
    }
    stack *next = top->next;
    int value = top->value;

    free(top);
    top = next;
    return value;
}

void printStack() {
    printf("[stack] ");
    stack *next = top;
    while (next) {
        printf("%d ", next->value);
        next = next->next;
    }
    printf("\n");
}

#endif /* VM_H */
