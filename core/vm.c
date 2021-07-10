#include "defs.h"

void push(type_vm *vm,int value) {
	vm->stack[++vm->sp] = value;
}

int  pop(type_vm *vm) {
	int value = INVALID;
	value = vm->stack[vm->sp--];
	return value;
}

void vm_clear(type_vm *vm) {
	int index;
	for(index = 0; index < vm->max_memory_stack; index++) {
		vm->stack[index]  = INVALID;
	}
	for(index = 0; index < vm->max_memory_code; index++) {
		vm->code[index]  = INVALID;
	}
	for(index = 0; index < vm->max_memory_data; index++) {
		vm->data[index]  = INVALID;
	}
	vm->pc = -1;
	vm->sp = -1;
	vm->fp = -1;
	vm->is_running = FALSE;
}

type_vm *create_vm(int page_stack,int page_code,int page_data) {
	page_stack = (page_stack) ? page_stack : 1;
	page_code  = (page_code)  ? page_code  : 1;
	page_data  = (page_data)  ? page_data  : 1;
	type_vm *vm = (type_vm *)malloc(sizeof(type_vm));
	if(!vm) { 
		printf("Memory not available for vm.\n"); 
		exit(1); 
	}
	vm->max_memory_stack = TO_MEMORY(page_stack);
	vm->max_memory_code  = TO_MEMORY(page_code);
	vm->max_memory_data  = TO_MEMORY(page_data);
	vm->stack = (int *)malloc(vm->max_memory_stack * sizeof(int));
	if(!vm->stack) { 
		printf("Memory not available for stack.\n"); 
		exit(1); 
	}
	vm->code = (int *)malloc(vm->max_memory_code * sizeof(int));
	if(!vm->code) { 
		printf("Memory not available for code.\n"); 
		exit(1); 
	}
	vm->data = (int *)malloc(vm->max_memory_data * sizeof(int));
	if(!vm->data) { 
		printf("Memory not available for data.\n"); 
		exit(1); 
	}
	vm_clear(vm);
	return vm;
}

void vm_load(type_vm *vm,int *code,int length) {
	int index, pc = 0; 
	for(index = 0; index < length; index++) {
		if(code[index] == ORG) {
			pc = code[index + 1];
			index = index + 2;
		}
		vm->code[pc]  = code[index];
		pc = pc + 1;
	}
}

void vm_load_string(type_vm *vm,int address,const char *string) {
	int index;
	for(index = 0; index < strlen(string); index++) {
		vm->data[(address + index)]  = string[index];
	}
	vm->data[(address + index)] = '\0';
}


void disassemble(int *code,int length) {
	int opcode, index = 0,old_index;
	int pc = 0;
	printf("\n");
	printf("code disassemble:\n");
	printf("\n");
	while(index < length) {
		opcode = code[index];
		if(opcode == ORG) {
			pc = code[index + 1];
			index = index + 2;
			printf("\n");
		} else {
			printf("    %4d %10s ",pc,instructions[opcode].str);
			switch(instructions[opcode].nargs) {
				case 1:
					printf("%6d ",code[index + 1]);
					index = index + 2;
					pc    = pc    + 2;
					break;
				case 2:
					printf("%6d %6d",code[index + 1],code[index + 2]);
					index = index + 3;
					pc    = pc    + 3;
					break;
				default:
					index = index + 1;
					pc    = pc    + 1;
					break;
			}
			printf("\n");
			
		}
	}
	printf("\n");
}


void vm_execute(type_vm *vm) {
	int opcode, a, b, address, nargs, value;
	opcode = vm->code[vm->pc++];
	switch(opcode) {
		case  NOP: break;
		case HALT: vm->is_running = FALSE; break;
		case CONST:   push(vm,vm->code[vm->pc++]); break;
		case   POP:   pop(vm); break;
		case  STORE:  vm->stack[(vm->fp + vm->code[vm->pc++])] = pop(vm);break;
		case  LOAD:   push(vm,vm->stack[(vm->fp + vm->code[vm->pc++])]); break;
		case GSTORE:  vm->data[vm->code[vm->pc++]] = pop(vm); break;
		case GLOAD:   push(vm,vm->data[vm->code[vm->pc++]]); break;
		case RSTORE:  vm->data[vm->data[vm->code[vm->pc++]]] = pop(vm); break;
		case RLOAD:   push(vm,vm->data[vm->data[vm->code[vm->pc++]]]); break;
		case SRSTORE: vm->data[vm->stack[(vm->fp + vm->code[vm->pc++])]] = pop(vm); break;
		case SRLOAD:  push(vm,vm->data[vm->stack[(vm->fp + vm->code[vm->pc++])]]); break;
		case PRINT:  printf("%d",pop(vm)); break;
		case PRINTCHAR:  printf("%c",pop(vm)); break;
		case INPUT: scanf("%d",&value); push(vm,value); break;
		case INPUTCHAR: value = getch(); push(vm,value); break;
		case ADD: b = pop(vm); a = pop(vm); push(vm,a + b); break;
		case SUB: b = pop(vm); a = pop(vm); push(vm,a - b); break;
		case MUL: b = pop(vm); a = pop(vm); push(vm,a * b); break;
		case DIV: b = pop(vm); a = pop(vm); push(vm,a / b); break;
		case MOD: b = pop(vm); a = pop(vm); push(vm,a % b); break;
		case AND: b = pop(vm); a = pop(vm); push(vm,a && b); break;
		case OR:  b = pop(vm); a = pop(vm); push(vm,a || b); break;
		case NOT: value = (!pop(vm)); push(vm,value); break;
		case BAND: b = pop(vm); a = pop(vm); push(vm,a & b); break;
		case BOR:  b = pop(vm); a = pop(vm); push(vm,a | b); break;
		case BNOT: value = (~pop(vm)); push(vm,value); break;
		case BSHL: b = pop(vm); a = pop(vm); push(vm,a << b); break;
		case BSHR: b = pop(vm); a = pop(vm); push(vm,a >> b); break;
		case EQ:  b = pop(vm); a = pop(vm); push(vm,((a == b) ? TRUE : FALSE)); break;
		case NE:  b = pop(vm); a = pop(vm); push(vm,((a != b) ? TRUE : FALSE)); break;
		case LT:  b = pop(vm); a = pop(vm); push(vm,((a <  b) ? TRUE : FALSE)); break;
		case LE:  b = pop(vm); a = pop(vm); push(vm,((a <= b) ? TRUE : FALSE)); break;
		case GT:  b = pop(vm); a = pop(vm);	push(vm,((a >  b) ? TRUE : FALSE)); break;
		case GE:  b = pop(vm); a = pop(vm); push(vm,((a >= b) ? TRUE : FALSE)); break;
		case BR:  address = vm->code[vm->pc++]; vm->pc = address; break;
		case BRT: address = vm->code[vm->pc++]; if(pop(vm) == TRUE)  vm->pc = address; break;
		case BRF: address = vm->code[vm->pc++]; if(pop(vm) == FALSE) vm->pc = address; break;
		case ENT: vm->sp = vm->sp + vm->code[vm->pc++]; break;
		case CALL:
			address = vm->code[vm->pc++];
			nargs   = vm->code[vm->pc++];
			push(vm,nargs);
			push(vm,vm->fp);
			push(vm,vm->pc);
			vm->fp = vm->sp;
			vm->pc = address;
			break;
		case RET:
			value = pop(vm);
			vm->sp = vm->fp;
			vm->pc = pop(vm);
			vm->fp = pop(vm);
			nargs  = pop(vm);
			vm->sp = vm->sp - nargs;
			push(vm,value);
			break;
		default:
			printf("Unkwown Opcode: %d at memory location %d.\n",opcode,(vm->pc - 1));
			exit(1);
			break;
	}	
}

void vm_run(type_vm *vm,int address) {
	if(!vm->is_running) {
		vm->is_running = TRUE;
		vm->pc = address;
		while(vm->is_running) {
			if(vm->pc >= vm->max_memory_code) vm->is_running = FALSE;
			vm_execute(vm);
			//if(vm->sp != -1) print_stack(vm);
		}
	}
}

void print_stack(const type_vm *vm) {
	int index;
	if(vm->sp == -1) {
		printf("Stack is Empty.\n");
	} else {
		printf("Stack: [");
		for(index = 0; index <= vm->sp; index++) {
			if(index == vm->fp) printf("{");
			printf("%d",vm->stack[index]);
			if(index == vm->fp) printf("}");
			printf(" ");
		}
		printf("]");
	}
	printf("\n");
}

void print_vm(const type_vm *vm) {
	int row, col, index;
	printf("\n");
	printf("vm->max_memory_stack : %5d Total page : %5d\n",
		vm->max_memory_stack,TO_PAGE(vm->max_memory_stack));
	printf("vm->max_memory_code  : %5d Total page : %5d\n",
		vm->max_memory_code,TO_PAGE(vm->max_memory_code));
	printf("vm->max_memory_data  : %5d Total page : %5d\n",
		vm->max_memory_data,TO_PAGE(vm->max_memory_data));
	printf("\n");
	printf("vm->pc: %5d\n",vm->pc);
	printf("vm->sp: %5d\n",vm->sp);
	printf("vm->fp: %5d\n",vm->fp);
	printf("\n");
}

void print_memory(const int *memory,int page,int max_memory) {
	int start = page * 256;
	int max_page = (max_memory / 256);
	int index;
	if(page >= 0 && page <= max_page - 1) {
		printf("\n");
		printf("memory: 0 to %d\n",(max_memory - 1));
		printf("page: %4d start: %4d end: %4d\n",page,start,((start + 256) - 1));
		printf("\n");
		for(index = 0; index < 256; index++) {
			if(!index) {
				printf("            0      1      2      3      4      5      6      7");
				printf("\n");
				printf("-----|--------------------------------------------------------");
			}
			if(!(index % 8)) {
				printf("\n");
				printf("%4d | ",(start + index));
			}
			if(memory[(start + index)] == INVALID) {
				printf("       ");
			} else {
				printf("%6d ",memory[(start + index)]);
			}
		}
		printf("\n");
	} else {
		printf("\n");
		printf("memory: 0 to %d\n",(max_memory - 1));
		printf("page must be between 0 and %d\n",(max_page - 1));
		printf("\n");
	}
	printf("\n");
}






