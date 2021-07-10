
#include "core/defs.h"

// Compile: gcc data.c vm.c testXX.c -o testXX.exe
// Run: testXX.exe

const int MAX_PAGE_STACK = TO_PAGE(TO_KB(MAX_KB_STACK));
const int MAX_PAGE_CODE  = TO_PAGE(TO_KB(MAX_KB_CODE));
const int MAX_PAGE_DATA  = TO_PAGE(TO_KB(MAX_KB_DATA));

int can_vm_run = 1;
type_vm *vm;
int address_main = 0;

void init_vm(void) {
	vm = create_vm(MAX_PAGE_STACK,MAX_PAGE_CODE,MAX_PAGE_DATA);
}

void init_data(void) {
}

void init(void) {
	init_vm();
	init_data();
}

void load_main(void) {
	address_main = 67;
	int code[] = {
		CONST, 70, 
		GSTORE, 500, 
		CONST, 73, 
		GSTORE, 501, 
		CONST, 90, 
		GSTORE, 502, 
		CONST, 90, 
		GSTORE, 503, 
		CONST, 0, 
		GSTORE, 504, 
		CONST, 66, 
		GSTORE, 512, 
		CONST, 85, 
		GSTORE, 513, 
		CONST, 90, 
		GSTORE, 514, 
		CONST, 90, 
		GSTORE, 515, 
		CONST, 0, 
		GSTORE, 516, 
		RET, 
		ENT, 1, 
		LOAD, -3, 
		STORE, 1, 
		SRLOAD, 1, 
		CONST, 0, 
		NE, 
		BRF, 66, 
		SRLOAD, 1, 
		PRINTCHAR, 
		LOAD, 1, 
		CONST, 1, 
		ADD, 
		STORE, 1, 
		BR, 47, 
		RET, 
		CALL, 0, 0, 
		CONST, 512, 
		CALL, 41, 1, 
		CONST, 32, 
		PRINTCHAR, 
		CONST, 500, 
		CALL, 41, 1, 
		CONST, 10, 
		PRINTCHAR, 
		HALT, 
	};
	vm_load(vm,code,((sizeof(code)) / sizeof(int)));
	if(!can_vm_run) {
		disassemble(code,((sizeof(code)) / sizeof(int)));
	}
}


void load(void) {
	load_main();
	if(!can_vm_run) {
		print_memory(vm->code,0,vm->max_memory_code);
	}
}

void run(void) {
	init();
	load();
	if(can_vm_run) {
		printf("\n");
		printf("Output:\n");
		printf("\n");
		vm_run(vm,address_main);
		//print_memory(vm->data,0,vm->max_memory_data);
		printf("\n");
	} else {
		print_vm(vm);
	}
}

void vm_info() {
	printf("\n");
	printf("%s %s by %s (Copyright 2021)\n",NAME,VERSION,AUTHOR);
	printf("\n");
}

int main() {
	vm_info();
	run();	
	printf("\n");
	return 0;
}


