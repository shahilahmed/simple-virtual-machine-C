
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
	address_main = 46;
	int code[] = {
		LOAD, -3, 
		CONST, 1, 
		LE, 
		BRF, 10, 
		CONST, 1, 
		RET, 
		LOAD, -3, 
		LOAD, -3, 
		CONST, 1, 
		SUB, 
		CALL, 0, 1, 
		MUL, 
		RET, 
		LOAD, -3, 
		CONST, 0, 
		LE, 
		BRF, 32, 
		CONST, 1, 
		RET, 
		LOAD, -4, 
		LOAD, -4, 
		LOAD, -3, 
		CONST, 1, 
		SUB, 
		CALL, 22, 2, 
		MUL, 
		RET, 
		ENT, 14, 
		CONST, 0, 
		STORE, 1, 
		CONST, 10, 
		STORE, 2, 
		CONST, 3, 
		STORE, 3, 
		LOAD, 1, 
		LOAD, 2, 
		LE, 
		BRF, 92, 
		LOAD, 1, 
		CONST, 5, 
		CALL, 22, 2, 
		SRSTORE, 3, 
		LOAD, 3, 
		CONST, 1, 
		ADD, 
		STORE, 3, 
		LOAD, 1, 
		CONST, 1, 
		ADD, 
		STORE, 1, 
		BR, 60, 
		CONST, 0, 
		STORE, 1, 
		CONST, 10, 
		STORE, 2, 
		CONST, 3, 
		STORE, 3, 
		LOAD, 1, 
		LOAD, 2, 
		LE, 
		BRF, 133, 
		SRLOAD, 3, 
		PRINT, 
		CONST, 10, 
		PRINTCHAR, 
		LOAD, 3, 
		CONST, 1, 
		ADD, 
		STORE, 3, 
		LOAD, 1, 
		CONST, 1, 
		ADD, 
		STORE, 1, 
		BR, 104, 
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


