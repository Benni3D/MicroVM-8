#pragma once
#include "bytecode.h"

class MicroVM {
private:
	ubyte_t memory[256];
	ubyte_t stack[64];
	reg_t regs[FLAGS + 1];
public:
	MicroVM();
	void load_program(const char* filename);
	void run();
	bool is_running();
private:
	void stack_push(ubyte_t);
	ubyte_t stack_pop();
	ubyte_t stack_peek();
	void set_running(bool);

	void exec(const ubyte_t*);
};