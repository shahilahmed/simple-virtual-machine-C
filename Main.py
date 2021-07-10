from Utils import *from sys import argv, exitfunctions = {}labels    = {}def tokenize(str_data):	str_data = sanitize(str_data)	tokens = []	for token in str_data.split():		try:			value = int(token)			tokens.append({"type" : "NUMBER", "value": value}) 		except Exception as e:			value = token.upper()			if token.count(":") >= 1:				value = value.strip(":")				value = ":" + value				tokens.append({"type" :  "LABEL", "value": value}) 			elif token.count("#") >= 1:				value = token.strip("#")				tokens.append({"type" : "SYMBOL", "value": value}) 			else:					tokens.append({"type" : "SYMBOL", "value": value}) 	return tokens	def	pass1(tokens = []):	result = []	loc = 0	while loc < len(tokens):		token = tokens[loc]		if token["type"] == "SYMBOL":			if token["value"] == "DEF":				func    = tokens[loc + 1]["value"]				nargs   = tokens[loc + 2]["value"]				functions[func] = {					"address" : None,					"nargs"   : nargs,				}				result.append({"type" : "DEF", "value" : func})				loc = loc + 3			else:				result.append(token)				loc = loc + 1		elif token["type"] == "LABEL":			labels[token["value"].strip(":")] = {				"address" : None			}			result.append(token)			loc = loc + 1		else:			result.append(token)			loc = loc + 1	if "MAIN" not in functions:		functions["MAIN"] = {			"address" : 0,			"nargs"   : 0,		}	return result	def pass2(tokens = []):	result = []	loc = 0	while loc < len(tokens):		token = tokens[loc]		arr = []		if token["type"] == "SYMBOL":			if token["value"] in ["CALL"]:				arr.append(tokens[loc]["value"])				arr.append(tokens[loc+1]["value"])				arr.append(functions[tokens[loc+1]["value"]]["nargs"])				loc = loc + 2			elif token["value"] in ["LOAD","STORE"]:				arr.append([tokens[loc]["value"],tokens[loc+1]["value"]])				arr.append(tokens[loc+2]["value"])				loc = loc + 3			elif token["value"] in ["RLOAD","RSTORE"]:				arr.append([tokens[loc]["value"],tokens[loc+1]["value"]])				arr.append(tokens[loc+2]["value"])				loc = loc + 3			elif token["value"] in ["INC","DEC"]:				arr.append([tokens[loc]["value"],tokens[loc+1]["value"]])				arr.append(tokens[loc+2]["value"])				loc = loc + 3			elif token["value"] in ["IF"]:				if tokens[loc+1]["value"] in ["EQ","NE","LT","LE","GT","GE"]:					arr.append([tokens[loc]["value"],tokens[loc+1]["value"]])					arr.append(tokens[loc+2]["value"])					loc = loc + 3			elif token["value"] in ["CONST","BR","BRT","BRF","ORG","ENT"]:				arr.append(tokens[loc]["value"])				arr.append(tokens[loc+1]["value"])				loc = loc + 2			elif token["value"] in ["SDATA"]:				temp_data = []				token = tokens[loc]				loc = loc + 1				while loc < len(tokens):					token = tokens[loc]					if token["value"] == "EDATA":						break					if isinstance(token["value"],str):						for value in token["value"]:							temp_data.append(ord(value))						temp_data.append(0)					else:								temp_data.append(token['value'])					loc = loc + 1									arr.append(["DATA",temp_data])				loc = loc + 1			else:				arr.append(token["value"])				loc = loc + 1		elif token["type"] == "DEF":				result.append("@" + token["value"])			loc = loc + 1		elif token["type"] == "LABEL":				result.append(token["value"])			loc = loc + 1		else:				loc = loc + 1		if len(arr) != 0:			result.append(arr)	return resultdef pass3(tokens = []):	result = []	loc = 0	while loc < len(tokens):		token = tokens[loc]		if isinstance(token[0],list):			opcode = token[0][0]			if opcode == "DATA":				result.append(token)			else:				type   = token[0][1]				value  = token[1]				if opcode in ["IF"]:					result.append([type])					result.append(["BRF",value])				elif opcode in ["INC","DEC"]:					opcode = "ADD" if opcode == "INC" else "SUB"					if type == "LOCAL":						result.append(["LOAD", 1 + value])												result.append(["CONST", 1])												result.append([opcode])												result.append(["STORE", 1 + value])											elif type == "DATA" or type == "GLOBAL":						result.append(["GLOAD",value])												result.append(["CONST", 1])												result.append([opcode])												result.append(["GSTORE",value])				elif opcode in ["LOAD","STORE"]:					if type == "ARGUMENT":						result.append([opcode,-3 - value])					elif type == "LOCAL":						result.append([opcode, 1 + value])					elif type == "DATA" or type == "GLOBAL":						if opcode == "LOAD":							opcode = "GLOAD"						elif opcode == "STORE":							opcode = "GSTORE"						result.append([opcode,value])					elif type == "CONSTANT":						result.append(["CONST",value])				elif opcode in ["RLOAD","RSTORE"]:					if type == "LOCAL":						if opcode == "RLOAD":							opcode = "SRLOAD"						elif opcode == "RSTORE":							opcode = "SRSTORE"						result.append([opcode,1 + value])					elif type == "DATA" or type == "GLOBAL":						if opcode == "RLOAD":							opcode = "RLOAD"						elif opcode == "RSTORE":							opcode = "RSTORE"						result.append([opcode,value])						else:			if token[0] == "PRINTLN":				result.append(["CONST",10])				result.append(["PRINTCHAR"])			elif token[0] == "PRINTSPACE":				result.append(["CONST",32])				result.append(["PRINTCHAR"])			else:				result.append(token)		loc = loc + 1	return resultdef pass4(tokens = []):	result = []	loc = 0	pc  = 0	while loc < len(tokens):		token = tokens[loc]		if token[0] == "ORG":			pc = token[1]			result.append(["ORG",pc])			loc = loc + 1		elif token[0][0] == "DATA":			counter = token[0][1].pop(0)			for data in token[0][1]:				result.append(["CONST",data])				result.append(["GSTORE",counter])				counter = counter + 1				pc = pc + 4			loc = loc + 1		else:			if isinstance(token,str):				if token[0] == "@":					value = token.strip("@")					if tokens[loc + 1][0] == "ORG":						pc = tokens[loc + 1][1]						result.append(["ORG",pc])						loc = loc + 1							functions[value]["address"] = pc				elif token[0] == ":":					value = token.strip(":")					labels[value]["address"] = pc			else:				##print(token)				##print("{} {}".format(pc,token))				pc = pc + len(token)				result.append(token)			loc = loc + 1	return resultdef pass5(tokens = []):	result = []	loc = 0	while loc < len(tokens):		token = tokens[loc]		arr = []		for value in token:			if value in functions:				arr.append(functions[value]["address"])			elif value in labels:				arr.append(labels[value]["address"])			else:				arr.append(value)		result.append(arr)		loc = loc + 1	return resultdef assemble(str_data = ""):	tokens = tokenize(str_data);	tokens = pass1(tokens)	tokens = pass2(tokens)	tokens = pass3(tokens)	tokens = pass4(tokens)	tokens = pass5(tokens)	program = []	for token in tokens:		program.append(token)	return program	def transpile(program = []):	str_data = ""	str_data = str_data + "void load_main(void) {\n"	str_data = str_data + "\taddress_main = {};\n".format(functions["MAIN"]["address"])	str_data = str_data + "\tint code[] = {\n"	for token in program:		str_data = str_data + "\t\t"		for value in token:			str_data = str_data + "{}, ".format(value)		str_data = str_data + "\n"	str_data = str_data + "\t};\n"	str_data = str_data + "\tvm_load(vm,code,((sizeof(code)) / sizeof(int)));\n"	str_data = str_data + "\tif(!can_vm_run) {\n"	str_data = str_data + "\t\tdisassemble(code,((sizeof(code)) / sizeof(int)));\n"	str_data = str_data + "\t}\n"	str_data = str_data + "}\n"	return str_data	str_header = """#include "core/defs.h"// Compile: gcc data.c vm.c testXX.c -o testXX.exe// Run: testXX.execonst int MAX_PAGE_STACK = TO_PAGE(TO_KB(MAX_KB_STACK));const int MAX_PAGE_CODE  = TO_PAGE(TO_KB(MAX_KB_CODE));const int MAX_PAGE_DATA  = TO_PAGE(TO_KB(MAX_KB_DATA));int can_vm_run = 1;type_vm *vm;int address_main = 0;void init_vm(void) {	vm = create_vm(MAX_PAGE_STACK,MAX_PAGE_CODE,MAX_PAGE_DATA);}void init_data(void) {}void init(void) {	init_vm();	init_data();}"""str_footer = """void load(void) {	load_main();	if(!can_vm_run) {		print_memory(vm->code,0,vm->max_memory_code);	}}void run(void) {	init();	load();	if(can_vm_run) {		printf("\\n");		printf("Output:\\n");		printf("\\n");		vm_run(vm,address_main);		//print_memory(vm->data,0,vm->max_memory_data);		printf("\\n");	} else {		print_vm(vm);	}}void vm_info() {	printf("\\n");	printf("%s %s by %s (Copyright 2021)\\n",NAME,VERSION,AUTHOR);	printf("\\n");}int main() {	vm_info();	run();		printf("\\n");	return 0;}"""def main():	argv.pop(0)	if len(argv) >= 1:		for path in argv:			path_array = path.split("\\")			filename = path_array[-1].split(".")[0]			if file_exists(path):				str_data = file_get_contents(path)				tokens   = tokenize(str_data);				program  = assemble(str_data)				str_data = transpile(program)				str_final = ""				str_final = str_final + str_header + "\n";				str_final = str_final + str_data + "\n";				str_final = str_final + str_footer + "\n";				file_put_contents(filename + ".c",str_final)								str_make = "";				str_make = str_make + "set src_file={}.c\n".format(filename);				str_make = str_make + "set exe_file={}.exe\n".format(filename);				str_make = str_make + "\n";				str_make = str_make + "cls\n";				str_make = str_make + "gcc core/data.c core/vm.c %src_file% -o %exe_file%\n";				str_make = str_make + "\n";				str_make = str_make + "%exe_file%\n";				str_make = str_make + "\n";				str_make = str_make + "rm %exe_file%\n";				str_make = str_make + "\n";				file_put_contents(filename + ".bat",str_make)				##file_put_contents("make_" + filename + ".bat",str_make)								print("{} has been transpiled sucessfully.".format(path))	else:		print()		print("usage: main.py file.ext")		print()	if __name__ == '__main__':	main()