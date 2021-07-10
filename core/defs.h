#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/timeb.h>


/***************
DEFINATION PART
	- This part is used to define.

***************/
#define NAME    "Simple Virtual Machine"
#define VERSION "v3.5.5"
#define AUTHOR  "Md Shahil Ahmed"

#define FALSE   0
#define TRUE    1

#define TO_KB(value) (value * 1024) 
#define TO_MB(value) (value * 1024 * 1024) 


#define TO_MEMORY(page) (page * 256)
#define TO_PAGE(value)  (value / 256)

#define MAX_KB_STACK 8
#define MAX_KB_CODE  4
#define MAX_KB_DATA  1

enum {
	EQ  =   0,
	NE  =   1,
	LT  =   2,
	LE  =   3,
	GT  =   4,
	GE  =   5,
	
	ADD =   6,
	SUB =   7,
	MUL =   8,
	DIV =   9,
	MOD =  10,
	
	AND =  11,
	OR  =  12,
	NOT =  13,
	
	BAND =  14,
	BOR  =  15,
	BNOT =  16,
	BSHL =  17,
	BSHR =  18,
	
	STORE  = 19,
	LOAD   = 20,
	GSTORE = 21,
	GLOAD  = 22,
	RSTORE = 23,
	RLOAD  = 24,
	SRSTORE = 25,
	SRLOAD  = 26,
	
	BR  = 27,
	BRT = 28,
	BRF = 29,
	
	ENT  = 30,
	RET  = 31,
	CALL = 32,
	
	CONST = 33,
	POP   = 34,
	PRINT = 35,
	PRINTCHAR = 36,
	INPUT     = 37,
	INPUTCHAR = 38,
	NOP   = 39,
	HALT  = 40,
	
	MAX_INSTRUCTION = HALT + 1,
	
	ORG = -4096,
	INVALID = -512
};

typedef struct {
	int  opcode;
	char str[30];
	int  nargs;
}type_instruction;

typedef struct {
	int max_memory_stack; 
	int max_memory_code; 
	int max_memory_data; 
	int *stack;
	int *code;
	int *data;
	int pc;
	int sp;
	int fp;
	int is_running;
}type_vm;

/***************
GLOBAL DATA PART
	- This part is used to declare global variables and static functions.
***************/
extern type_instruction instructions[MAX_INSTRUCTION];
/***************
MACRO PART
	- This part is used for macro.
***************/
/***************
PROTOTYPE PART
	- This part is used to define prototypes of function.
***************/

/* - vm.c - */
extern void push(type_vm *vm,int value);
extern int  pop(type_vm *vm);
extern void vm_clear(type_vm *vm);
extern type_vm *create_vm(int page_stack,int page_code,int page_data);
extern void vm_load(type_vm *vm,int *code,int length);
extern void disassemble(int *code,int length);
extern void vm_load_string(type_vm *vm,int address,const char *string);
extern void vm_execute(type_vm *vm);
extern void vm_run(type_vm *vm,int address);
extern void print_stack(const type_vm *vm);
extern void print_vm(const type_vm *vm);
extern void print_memory(const int *memory,int page,int max_memory);

/* - init.c - */
extern void init(void);

/* - test.c - */
extern void test(void);

#endif






























