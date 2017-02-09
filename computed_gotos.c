#include "opcodes.h"
#include "vm.h"

#include <sys/time.h>
#include <time.h>

void eval() {
    static void *dispatchTable[] = {
       &&doPush,
       &&doPull,
       &&doAdd,
       &&doSub,
       &&doMul,
       &&doDiv,
       &&doLoad,
       &&doStore,
       &&doJmp,
       &&doJmpEq,
    };

    int op;

    #define dispatch() if (nextOp(&op) != -1 && op != -1) goto *dispatchTable[op]; else return;

    dispatch();
    doPush: {
        //printf("push: ");
        int num;
        nextOp(&num);
        push(num);
        dispatch();
    }
    doPull: {
        //printf("pop: ");
        pop();
        dispatch();
    }
    doAdd: {
        //printf("add: ");
        int a = pop();
        int b = pop();
        push(a + b);
        dispatch();
    }
    doSub: {
        //printf("sub: ");
        int a = pop();
        int b = pop();
        push(a - b);
        dispatch();
    }
    doMul: {
        //printf("mul: ");
        int a = pop();
        int b = pop();
        push(a * b);
        dispatch();
    }
    doDiv: {
        //printf("div: ");
        int a = pop();
        int b = pop();
        push(a / b);
        dispatch();
    }
    doLoad: {
        //printf("load: ");
        int p;
        nextOp(&p);
        push(vars[p]);
        dispatch();
    }
    doStore: {
        //printf("store: ");
        int p;
        nextOp(&p);
        vars[p] = pop();
        dispatch();
    }
    doJmp: {
        //printf("jmp: ");
        nextOp(&pc);
        dispatch();
    }
    doJmpEq: {
        //printf("jmp_eq: ");
        int num;
        nextOp(&num);
        if (pop() == num) {
            nextOp(&pc);
        }
        nextOp(&num);
        dispatch();
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
