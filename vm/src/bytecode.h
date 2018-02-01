#pragma once
#include <cstdint>
enum Instructions;
enum Registers;
enum Types;
class MicroVM;

typedef int8_t  byte_t;
typedef uint8_t ubyte_t;
typedef ubyte_t reg_t;

enum Instructions {
	NOP,	// 0x00  since: 1.0-beta
	MOV,	// 0x01  since: 1.0-beta
	ADD,	// 0x02  since: 1.0-beta
	SUB,	// 0x03  since: 1.0-beta
	MUL,	// 0x04  since: 1.0-beta
	DIV,	// 0x05  since: 1.0-beta
	MOD,	// 0x06  since: 1.0-beta
	AND,	// 0x07  since: 1.0-beta
	OR,		// 0x08  since: 1.0-beta
	XOR,	// 0x09  since: 1.0-beta
	NEG,	// 0x0A  since: 1.0-beta
	NOT,	// 0x0B  since: 1.0-beta
	PUSH,	// 0x0C  since: 1.0-beta
	POP,	// 0x0D  since: 1.0-beta
	PEEK,	// 0x0E  since: 1.0-beta
	RSHF,	// 0x0F  since: 1.0-beta
	LSHF,	// 0x10  since: 1.0-beta
	PRINT,	// 0x11  since: 1.0-beta
	READ,	// 0x12  since: 1.0-beta
	INC,	// 0x13  since: 1.0-beta
	DEC,	// 0x14  since: 1.0-beta
	JMP,	// 0x15  since: 1.0-beta
	HLT,	// 0x16  since: 1.0-beta
	EXIT,	// 0x17  since: 1.0-beta
	COPY,	// 0x18  since: 1.1-beta
	FILL,	// 0x19  since: 1.1-beta
	CALL,	// 0x1A  since: 1.1-beta
	RET,	// 0x1B  since: 1.1-beta
	XCHG,	// 0x1C  since: 1.1-beta
	CMP,	// 0x1D  since: 1.1-beta
	CMPS,	// 0x1E  since: 1.1-beta
	JE,		// 0x1F  since: 1.1-beta
	JNE,	// 0x20  since: 1.1-beta
	JG,		// 0x21  since: 1.1-beta
	JGE,	// 0x22  since: 1.1-beta
	JL,		// 0x23  since: 1.1-beta
	JLE,	// 0x24  since: 1.1-beta
	LOOP,	// 0x25  since: 1.1-beta
	IMUL,	// 0x26	 since: 1.1-beta
	IDIV,	// 0x27  since: 1.1-beta
	SLEEP,	// 0x28  since: 1.1-beta
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
enum Compares {
	NOT_SET,
	EQUAL,
	GREATER,
	LESS
};



Types get_type1(ubyte_t);
Types get_type2(ubyte_t);

#define check_reg(reg) if(reg > FLAGS) { \
	std::cerr << "Invalid Register: " << (unsigned)reg << " at " << (unsigned)regs[IP] << std::endl; \
	set_running(false);	\
	return; \
}
#define SWITCH_TYPE_DEFAULT default: \
	std::cerr << "Invalid Type! at " << (unsigned)regs[IP] << std::endl; \
	set_running(false); \
	return;