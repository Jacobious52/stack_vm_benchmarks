#include "opcodes.h"
#include "vm.h"

#include <sys/time.h>
#include <time.h>

void eval() {
    int op;
    while (nextOp(&op) != -1) {
        switch (op) {
            case PUSH: {
                //printf("push: ");
                int num;
                nextOp(&num);
                push(num);
                break;
            }
            case POP: {
                //printf("pop: ");
                pop();
                break;
            }
            case ADD: {
                //printf("add: ");
                int a = pop();
                int b = pop();
                push(a + b);
                break;
            }
            case SUB: {
                //printf("sub: ");
                int a = pop();
                int b = pop();
                push(a - b);
                break;
            }
            case MUL: {
                //printf("mul: ");
                int a = pop();
                int b = pop();
                push(a * b);
                break;
            }
            case DIV: {
                //printf("div: ");
                int a = pop();
                int b = pop();
                push(a / b);
                break;
            }
            case LOAD: {
                //printf("load: ");
                int p;
                nextOp(&p);
                push(vars[p]);
                break;
            }
            case STORE: {
                //printf("store: ");
                int p;
                nextOp(&p);
                vars[p] = pop();
                break;
            }
            case JMP: {
                //printf("jmp: ");
                nextOp(&pc);
                break;
            }
            case JMP_EQ: {
                //printf("jmp_eq: ");
                int num;
                nextOp(&num);
                if (pop() == num) {
                    nextOp(&pc);
                }
                nextOp(&num);
                break;
            }
            case HALT:
                //printf("halt: ");
                return;
            default:
                printf("unknown opcode: %d\n", op);
                return;
        }
        //printStack();
    }
}

int main() {
    loadProgram();

    struct timeval then, now;
    int i;
    gettimeofday(&then, NULL);
    for (i = 0; i < 1000; ++i) {
        eval();
        pc = 0;
    }
    gettimeofday(&now, NULL);

    printf("%d\n", top->value);
    printf("evaluated in %.5g seconds\n", now.tv_sec - then.tv_sec + 1e-6 * (now.tv_usec - then.tv_usec));

    return 0;
}
