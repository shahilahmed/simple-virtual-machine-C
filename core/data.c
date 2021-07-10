#include "defs.h"

type_instruction instructions[MAX_INSTRUCTION] = {
	{   EQ,      "EQ", 0}, // EQ = 0 
	{   NE,      "NE", 0},
	{   LT,      "LT", 0},
	{   LE,      "LE", 0},
	{   GT,      "GT", 0},
	{   GE,      "GE", 0},
	
	{  ADD,     "ADD", 0}, // ADD = 6
	{  SUB,     "SUB", 0},
	{  MUL,     "MUL", 0},
	{  DIV,     "DIV", 0},
	{  MOD,     "MOD", 0},
	
	{  AND,     "AND", 0}, // AND = 11
	{   OR,      "OR", 0},
	{  NOT,     "NOT", 0},
	
	{  BAND,     "BAND", 0}, // BAND = 14
	{   BOR,      "BOR", 0},
	{  BNOT,     "BNOT", 0},
	{  BSHL,     "BSHL", 0},
	{  BSHR,     "BSHR", 0},
	
	{STORE,    "STORE",  1}, // STORE = 19
	{  LOAD,    "LOAD",  1},
	{GSTORE,  "GSTORE",  1},
	{ GLOAD,   "GLOAD",  1},
	{RSTORE,  "RSTORE",  1},
	{ RLOAD,   "RLOAD",  1},
	{SRSTORE, "SRSTORE", 1},
	{ SRLOAD,  "SRLOAD", 1},
	
	{    BR,    " BR", 1}, // BR = 27
	{   BRT,    "BRT", 1},
	{   BRF,    "BRF", 1},
	
	{   ENT,    "ENT", 1}, // ENT = 30
	{   RET,    "RET", 0},
	{  CALL,   "CALL", 2},
	
	{ CONST,  "CONST", 1}, // CONST = 33
	{   POP,    "POP", 0},
	{ PRINT,  "PRINT", 0},
	{ PRINTCHAR,  "PRINTCHAR", 0},
	{ INPUT,  "INPUT", 0},
	{ INPUTCHAR,  "INPUTCHAR", 0},
	{   NOP,    "NOP", 0},
	{  HALT,   "HALT", 0}
};




