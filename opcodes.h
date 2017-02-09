#ifndef OPCODES_H
#define OPCODES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum opcodes {
    HALT=-1,
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    LOAD,
    STORE,
    JMP,
    JMP_EQ,
};

int *program = NULL;
int max = 0;
int pc = 0;

inline int nextOp(int *op) {
    if (pc < 0 || pc > max) {
        return -1;
    }
    *op = program[pc++];
    return 0;
}

void loadProgram() {
    int len = 256;
    program = (int *)calloc(len, sizeof(int));

    int i = 0;
    int op;

    while (scanf("%d", &op) == 1) {
        program[i] = op;
        i++;
        if (i >= len) {
            program = (int *)realloc(program, len*2);
        }
    }
    program[i] = -1;
    max = i;
}

#endif /* OPCODES_H */
