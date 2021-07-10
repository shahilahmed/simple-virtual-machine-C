
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
	address_main = 69;
	int code[] = {
		ENT, 3, 
		CONST, 0, 
		STORE, 1, 
		LOAD, -3, 
		STORE, 3, 
		LOAD, 1, 
		LOAD, 3, 
		LT, 
		BRF, 65, 
		CONST, 0, 
		STORE, 2, 
		LOAD, 2, 
		LOAD, 3, 
		LT, 
		BRF, 53, 
		LOAD, 1, 
		LOAD, 3, 
		MUL, 
		LOAD, 2, 
		ADD, 
		GSTORE, 512, 
		RLOAD, 512, 
		PRINTCHAR, 
		CONST, 32, 
		PRINTCHAR, 
		LOAD, 2, 
		CONST, 1, 
		ADD, 
		STORE, 2, 
		BR, 21, 
		CONST, 10, 
		PRINTCHAR, 
		LOAD, 1, 
		CONST, 1, 
		ADD, 
		STORE, 1, 
		BR, 10, 
		CONST, 10, 
		PRINTCHAR, 
		RET, 
		CONST, 114, 
		GSTORE, 0, 
		CONST, 110, 
		GSTORE, 1, 
		CONST, 98, 
		GSTORE, 2, 
		CONST, 113, 
		GSTORE, 3, 
		CONST, 107, 
		GSTORE, 4, 
		CONST, 98, 
		GSTORE, 5, 
		CONST, 110, 
		GSTORE, 6, 
		CONST, 114, 
		GSTORE, 7, 
		CONST, 112, 
		GSTORE, 8, 
		CONST, 112, 
		GSTORE, 9, 
		CONST, 112, 
		GSTORE, 10, 
		CONST, 112, 
		GSTORE, 11, 
		CONST, 112, 
		GSTORE, 12, 
		CONST, 112, 
		GSTORE, 13, 
		CONST, 112, 
		GSTORE, 14, 
		CONST, 112, 
		GSTORE, 15, 
		CONST, 46, 
		GSTORE, 16, 
		CONST, 46, 
		GSTORE, 17, 
		CONST, 46, 
		GSTORE, 18, 
		CONST, 46, 
		GSTORE, 19, 
		CONST, 46, 
		GSTORE, 20, 
		CONST, 46, 
		GSTORE, 21, 
		CONST, 46, 
		GSTORE, 22, 
		CONST, 46, 
		GSTORE, 23, 
		CONST, 46, 
		GSTORE, 24, 
		CONST, 46, 
		GSTORE, 25, 
		CONST, 46, 
		GSTORE, 26, 
		CONST, 46, 
		GSTORE, 27, 
		CONST, 46, 
		GSTORE, 28, 
		CONST, 46, 
		GSTORE, 29, 
		CONST, 46, 
		GSTORE, 30, 
		CONST, 46, 
		GSTORE, 31, 
		CONST, 46, 
		GSTORE, 32, 
		CONST, 46, 
		GSTORE, 33, 
		CONST, 46, 
		GSTORE, 34, 
		CONST, 46, 
		GSTORE, 35, 
		CONST, 46, 
		GSTORE, 36, 
		CONST, 46, 
		GSTORE, 37, 
		CONST, 46, 
		GSTORE, 38, 
		CONST, 46, 
		GSTORE, 39, 
		CONST, 46, 
		GSTORE, 40, 
		CONST, 46, 
		GSTORE, 41, 
		CONST, 46, 
		GSTORE, 42, 
		CONST, 46, 
		GSTORE, 43, 
		CONST, 46, 
		GSTORE, 44, 
		CONST, 46, 
		GSTORE, 45, 
		CONST, 46, 
		GSTORE, 46, 
		CONST, 46, 
		GSTORE, 47, 
		CONST, 80, 
		GSTORE, 48, 
		CONST, 80, 
		GSTORE, 49, 
		CONST, 80, 
		GSTORE, 50, 
		CONST, 80, 
		GSTORE, 51, 
		CONST, 80, 
		GSTORE, 52, 
		CONST, 80, 
		GSTORE, 53, 
		CONST, 80, 
		GSTORE, 54, 
		CONST, 80, 
		GSTORE, 55, 
		CONST, 82, 
		GSTORE, 56, 
		CONST, 78, 
		GSTORE, 57, 
		CONST, 66, 
		GSTORE, 58, 
		CONST, 81, 
		GSTORE, 59, 
		CONST, 75, 
		GSTORE, 60, 
		CONST, 66, 
		GSTORE, 61, 
		CONST, 78, 
		GSTORE, 62, 
		CONST, 82, 
		GSTORE, 63, 
		CONST, 0, 
		GSTORE, 64, 
		CONST, 8, 
		CALL, 0, 1, 
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


