# stack_vm_benchmarks
Simple benchmarks of different approaches to evaluating bytecode operations


Simple stack bytecode vm implementations for benchmarking purposes. 

## Switch.c
uses a classic switch statement to dispatch the instructions

## Computed-gotos.c
uses computed_gotos to dispatch the instructions

## Threaded.c
uses threads and function pointers to pre branch to the next operation
(not implemented)

#Results
### Tested on 2016 Macbook i3

Running on test.txt which calcuates the sum from 0 to 10000.

The eval() function is run 1000 times to get larger differences in runtime

| Switch (sec)  | ComputedGotos | Threaded |
| :-----------|-------------| ----------|
| ~ 8.3      |        ~8.0      |    N/A     |

On average the switch statement is about 0.3 seconds slower after 1000 runs. 
Not a significant difference, but enough to be noticable after alot of processed opcodes.
