#pragma once
#include <cstdint>
enum Instructions;
enum Registers;
enum Types;
class MicroVM;

typedef uint8_t ubyte_t;
typedef ubyte_t reg_t;

enum Instructions {
	NOP,	// 0x00
	MOV,	// 0x01
	ADD,	// 0x02
	SUB,	// 0x03
	MUL,	// 0x04
	DIV,	// 0x05
	MOD,	// 0x06
	AND,	// 0x07
	OR,		// 0x08
	XOR,	// 0x09
	NEG,	// 0x0A
	NOT,	// 0x0B
	PUSH,	// 0x0C
	POP,	// 0x0D
	PEEK,	// 0x0E
	RSHF,	// 0x0F
	LSHF,	// 0x10
	PRINT,	// 0x11
	READ,	// 0x12
	INC,	// 0x13
	DEC,	// 0x14
	JMP,	// 0x15
	HLT,	// 0x16
	EXIT,	// 0x17
};
enum Registers {
	A,		// 0x00
	B,		// 0x01
	C,		// 0x02
	D,		// 0x03
	SI,		// 0x04
	DI,		// 0x05
	SP,		// 0x06
	IP,		// 0x07
	FLAGS	// 0x08
};
enum Types {
	TYPE_REG = 0,
	TYPE_REF = 1,
	TYPE_INT = 2,

	PRINT_TYPE_INT  = 0,
	PRINT_TYPE_CHAR = 1,
	PRINT_TYPE_STRING = 2,

	READ_TYPE_INT = 0,
	READ_TYPE_CHAR = 1,
	READ_TYPE_STRING = 2,
};

Types get_type1(ubyte_t);
Types get_type2(ubyte_t);

#define check_reg(reg) if(reg > FLAGS) { \
	std::cerr << "Invalid Register: " << (unsigned)reg << std::endl; \
	set_running(false);	\
	return; \
}
#define SWITCH_TYPE_DEFAULT default: \
	std::cerr << "Invalid Type!" << std::endl; \
	set_running(false); \
	return;