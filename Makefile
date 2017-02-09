all: switch comp

switch: switch.c opcodes.h vm.h
	gcc switch.c -Wall -Wextra -pedantic -O3 -o switch

comp: computed_gotos.c opcodes.h vm.h
	gcc computed_gotos.c -Wall -Wextra -Wno-gnu-label-as-value -pedantic -O3 -o comp

clean:
	rm switch comp
