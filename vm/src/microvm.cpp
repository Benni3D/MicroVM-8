#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <Windows.h>
#include "microvm.h"

Types get_type1(ubyte_t i) {
	return static_cast<Types>(i & 0x0F);
}
Types get_type2(ubyte_t i) {
	return static_cast<Types>((i & 0xF0) >> 4);
}

MicroVM::MicroVM() {
	for (size_t i = 0; i < sizeof(memory); i++) {
		memory[i] = 0;
	}
}
void MicroVM::load_program(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (!in.is_open()) return;
	in.read((char*) memory, sizeof(memory));
	in.close();
}
void MicroVM::run() {
	regs[IP] = 0;
	regs[SP] = 0;
	set_running(true);
	while (regs[IP] < sizeof(memory)-1 && is_running()) {
		//std::cout << "Executing " << (unsigned)memory[regs[IP]] << " at " << (unsigned)regs[IP] << std::endl;
		exec(&memory[regs[IP]]);
	}
}
bool MicroVM::is_running() {
	return regs[FLAGS] & 0x1;
}
void MicroVM::stack_push(ubyte_t i) {
	if (regs[SP] >= sizeof(stack)) return;
	stack[regs[SP]++] = i;
}
ubyte_t MicroVM::stack_pop() {
	if (regs[SP] <= 0) return (ubyte_t) -1;
	return stack[--regs[SP]];
}
ubyte_t MicroVM::stack_peek() {
	if (regs[SP] <= 0) return (ubyte_t)-1;
	return stack[regs[SP] - 1];
}
void MicroVM::set_running(bool b) {
	if (b) regs[FLAGS] |= 0x1;
	else regs[FLAGS] &= 0xFE;
}
void MicroVM::exec(const ubyte_t* instr) {
	switch (*instr) {
	case NOP: {
		regs[IP]++;
		break;
	}
	case MOV: {
		Types type1 = get_type2(instr[1]),
			type2 = get_type1(instr[1]);
		switch (type1) {
		case TYPE_REG: {
			ubyte_t tar = instr[2];
			check_reg(tar);
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				regs[tar] = regs[src];
				break;
			}
			case TYPE_REF: {
				regs[tar] = memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				regs[tar] = instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		case TYPE_REF: {
			ubyte_t addr = instr[2];
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				memory[addr] = regs[src];
				break;
			}
			case TYPE_REF: {
				memory[addr] = memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				memory[addr] = instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 4;
		break;
	}
	case ADD: {
		Types type1 = get_type2(instr[1]),
			type2 = get_type1(instr[1]);
		switch (type1) {
		case TYPE_REG: {
			ubyte_t tar = instr[2];
			check_reg(tar);
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				regs[tar] += regs[src];
				break;
			}
			case TYPE_REF: {
				regs[tar] += memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				regs[tar] += instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		case TYPE_REF: {
			ubyte_t addr = instr[2];
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				memory[addr] += regs[src];
				break;
			}
			case TYPE_REF: {
				memory[addr] += memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				memory[addr] += instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 4;
		break;
	}
	case SUB: {
		Types type1 = get_type2(instr[1]),
			type2 = get_type1(instr[1]);
		switch (type1) {
		case TYPE_REG: {
			ubyte_t tar = instr[2];
			check_reg(tar);
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				regs[tar] -= regs[src];
				break;
			}
			case TYPE_REF: {
				regs[tar] -= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				regs[tar] -= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		case TYPE_REF: {
			ubyte_t addr = instr[2];
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				memory[addr] -= regs[src];
				break;
			}
			case TYPE_REF: {
				memory[addr] -= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				memory[addr] -= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 4;
		break;
	}
	case MUL: {
		Types type1 = get_type2(instr[1]),
			type2 = get_type1(instr[1]);
		switch (type1) {
		case TYPE_REG: {
			ubyte_t tar = instr[2];
			check_reg(tar);
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				regs[tar] *= regs[src];
				break;
			}
			case TYPE_REF: {
				regs[tar] *= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				regs[tar] *= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		case TYPE_REF: {
			ubyte_t addr = instr[2];
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				memory[addr] *= regs[src];
				break;
			}
			case TYPE_REF: {
				memory[addr] *= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				memory[addr] *= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 4;
		break;
	}
	case DIV: {
		Types type1 = get_type2(instr[1]),
			type2 = get_type1(instr[1]);
		switch (type1) {
		case TYPE_REG: {
			ubyte_t tar = instr[2];
			check_reg(tar);
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				if (regs[src] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				regs[tar] /= regs[src];
				break;
			}
			case TYPE_REF: {
				if (memory[instr[3]] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				regs[tar] /= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				if (instr[3] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				regs[tar] /= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		case TYPE_REF: {
			ubyte_t addr = instr[2];
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				if (regs[src] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				memory[addr] /= regs[src];
				break;
			}
			case TYPE_REF: {
				if (memory[instr[3]] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				memory[addr] /= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				if (instr[3] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				memory[addr] /= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 4;
		break;
	}
	case MOD: {
		Types type1 = get_type2(instr[1]),
			type2 = get_type1(instr[1]);
		switch (type1) {
		case TYPE_REG: {
			ubyte_t tar = instr[2];
			check_reg(tar);
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				if (regs[src] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				regs[tar] %= regs[src];
				break;
			}
			case TYPE_REF: {
				if (memory[instr[3]] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				regs[tar] %= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				if (instr[3] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				regs[tar] %= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		case TYPE_REF: {
			ubyte_t addr = instr[2];
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				if (regs[src] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				memory[addr] %= regs[src];
				break;
			}
			case TYPE_REF: {
				if (memory[instr[3]] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				memory[addr] %= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				if (instr[3] == 0) {
					std::cerr << "Division by zero at " << (unsigned)regs[IP] << "!" << std::endl;
					set_running(false);
					return;
				}
				memory[addr] %= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 4;
		break;
	}
	case AND: {
		Types type1 = get_type2(instr[1]),
			type2 = get_type1(instr[1]);
		switch (type1) {
		case TYPE_REG: {
			ubyte_t tar = instr[2];
			check_reg(tar);
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				regs[tar] &= regs[src];
				break;
			}
			case TYPE_REF: {
				regs[tar] &= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				regs[tar] &= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		case TYPE_REF: {
			ubyte_t addr = instr[2];
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				memory[addr] &= regs[src];
				break;
			}
			case TYPE_REF: {
				memory[addr] &= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				memory[addr] &= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 4;
		break;
	}
	case OR: {
		Types type1 = get_type2(instr[1]),
			type2 = get_type1(instr[1]);
		switch (type1) {
		case TYPE_REG: {
			ubyte_t tar = instr[2];
			check_reg(tar);
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				regs[tar] |= regs[src];
				break;
			}
			case TYPE_REF: {
				regs[tar] |= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				regs[tar] |= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		case TYPE_REF: {
			ubyte_t addr = instr[2];
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				memory[addr] |= regs[src];
				break;
			}
			case TYPE_REF: {
				memory[addr] |= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				memory[addr] |= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 4;
		break;
	}
	case XOR: {
		Types type1 = get_type2(instr[1]),
			type2 = get_type1(instr[1]);
		switch (type1) {
		case TYPE_REG: {
			ubyte_t tar = instr[2];
			check_reg(tar);
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				regs[tar] ^= regs[src];
				break;
			}
			case TYPE_REF: {
				regs[tar] ^= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				regs[tar] ^= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		case TYPE_REF: {
			ubyte_t addr = instr[2];
			switch (type2) {
			case TYPE_REG: {
				ubyte_t src = instr[3];
				check_reg(src);
				memory[addr] ^= regs[src];
				break;
			}
			case TYPE_REF: {
				memory[addr] ^= memory[instr[3]];
				break;
			}
			case TYPE_INT: {
				memory[addr] ^= instr[3];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 4;
		break;
	}
	case NEG: {
		ubyte_t type = instr[1];
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			regs[reg] ^= 0xFF;
			break;
		}
		case TYPE_REF: {
			memory[instr[2]] ^= 0xFF;
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 3;
		break;
	}
	case NOT: {
		ubyte_t type = instr[1];
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			if (regs[reg] == 0) regs[reg] = 1;
			else regs[reg] = 0;
			break;
		}
		case TYPE_REF: {
			if (memory[instr[2]] == 0) memory[instr[2]] = 1;
			else memory[instr[2]] = 0;
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 3;
		break;
	}
	case PUSH: {
		ubyte_t type = instr[1];
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			stack_push(regs[reg]);
			break;
		}
		case TYPE_INT: {
			stack_push(instr[2]);
			break;
		}
		case TYPE_REF: {
			stack_push(memory[instr[2]]);
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 3;
		break;
	}
	case POP: {
		ubyte_t type = instr[1];
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			regs[reg] = stack_pop();
			break;
		}
		case TYPE_REF: {
			memory[instr[2]] = stack_pop();
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 3;
		break;
	}
	case PEEK: {
		ubyte_t type = instr[1];
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			regs[reg] = stack_peek();
			break;
		}
		case TYPE_REF: {
			memory[instr[2]] = stack_peek();
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 3;
		break;
	}
	case RSHF: {
		ubyte_t type = instr[1];
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			regs[reg] >>= instr[3];
			break;
		}
		case TYPE_REF: {
			memory[instr[2]] >>= instr[3];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 4;
		break;
	}
	case LSHF: {
		ubyte_t type = instr[1];
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			regs[reg] <<= instr[3];
			break;
		}
		case TYPE_REF: {
			memory[instr[2]] <<= instr[3];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 4;
		break;
	}
	case PRINT: {
		ubyte_t type = get_type1(instr[1]);
		ubyte_t print_type = get_type2(instr[1]);
		ubyte_t i = NULL;
		if (print_type == PRINT_TYPE_STRING) {
			if (type != TYPE_REF) {
				std::cerr << "Invalid Type!" << std::endl;
				set_running(false);
				return;
			}
			const char* str = (const char*)&memory[instr[2]];
			for (int i = 0; str[i] != 0; i++) {
				if (str[i] == 13) std::cout << std::endl;
				std::cout << str[i];
			}
			regs[IP] += 3;
			break;
		}
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			i = regs[reg];
			break;
		}
		case TYPE_REF: {
			i = memory[instr[2]];
			break;
		}
		case TYPE_INT: {
			i = instr[2];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		switch (print_type) {
		case PRINT_TYPE_INT: {
			std::cout << (unsigned)i;
			break;
		}
		case PRINT_TYPE_CHAR: {
			if (i == 13) std::cout << std::endl;
			else std::cout << (char)i;
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 3;
		break;
	}
	case READ: {
		ubyte_t type = get_type1(instr[1]);
		ubyte_t read_type = get_type2(instr[1]);
		ubyte_t i = instr[2];
		if (read_type == READ_TYPE_STRING) {
			if (type != TYPE_REF) {
				std::cerr << "Invalid Type!" << std::endl;
				set_running(false);
				return;
			}
		}
		if (type == TYPE_REG) {
			check_reg(i);
		}
		switch (read_type) {
		case READ_TYPE_INT: {
			unsigned num;
			std::cin >> num;
			switch (type) {
			case TYPE_REG: {
				regs[i] = num & 0xFF;
				break;
			}
			case TYPE_REF: {
				memory[i] = num & 0xFF;
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		case READ_TYPE_CHAR: {
			std::string str;
			std::cin >> str;
			switch (type) {
			case TYPE_REG: {
				regs[i] = str[0];
				break;
			}
			case TYPE_REF: {
				memory[i] = str[0];
				break;
			}
			SWITCH_TYPE_DEFAULT
			}
			break;
		}
		case READ_TYPE_STRING: {
			std::string str;
			std::cin >> str;
			memcpy(&memory[i], str.c_str(), str.length());
			break;
		}
		}
		regs[IP] += 3;
		break;
	}
	case INC: {
		ubyte_t type = instr[1];
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			regs[reg]++;
			break;
		}
		case TYPE_REF: {
			memory[instr[2]]++;
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 3;
		break;
	}
	case DEC: {
		ubyte_t type = instr[1];
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			regs[reg]--;
			break;
		}
		case TYPE_REF: {
			memory[instr[2]]--;
			break;
		}
					   SWITCH_TYPE_DEFAULT
		}
		regs[IP] += 3;
		break;
	}
	case JMP: {
		ubyte_t type = instr[1];
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			regs[IP] = regs[reg];
			break;
		}
		case TYPE_REF: {
			regs[IP] = memory[instr[2]];
			break;
		}
		case TYPE_INT: {
			regs[IP] = instr[2];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		break;
	}
	case HLT: {
		break;
	}
	case EXIT: {
		set_running(false);
		regs[IP]++;
		break;
	}
	case COPY: {
		ubyte_t src = stack_pop();
		ubyte_t dest = stack_pop();
		ubyte_t size = instr[1];
		for (size_t i = 0; i < size; i++) {
			memory[dest + i] = memory[src + i];
		}
		regs[IP] += 2;
		break;
	}
	case FILL: {
		ubyte_t addr = stack_pop();
		ubyte_t fill = instr[1];
		ubyte_t size = instr[2];
		for (size_t i = 0; i < size; i++) {
			memory[addr + i] = fill;
		}
		regs[IP] += 3;
		break;
	}
	case CALL: {
		ubyte_t addr = instr[1];
		stack_push(regs[IP] + 2);
		regs[IP] = addr;
		break;
	}
	case RET: {
		regs[IP] = stack_pop();
		break;
	}
	case XCHG: {
		ubyte_t reg1 = instr[1], reg2 = instr[2];
		check_reg(reg1); check_reg(reg2);
		ubyte_t i = regs[reg1];
		regs[reg1] = regs[reg2];
		regs[reg2] = i;
		regs[IP] += 3;
		break;
	}
	case CMP: {
		ubyte_t type1 = get_type1(instr[1]);
		ubyte_t type2 = get_type2(instr[1]);
		ubyte_t i1, i2;
		switch (type1) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			i1 = regs[reg];
			break;
		}
		case TYPE_REF: {
			i1 = memory[instr[2]];
			break;
		}
		case TYPE_INT: {
			i1 = instr[2];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		switch (type2) {
		case TYPE_REG: {
			ubyte_t reg = instr[3];
			check_reg(reg);
			i2 = regs[reg];
			break;
		}
		case TYPE_REF: {
			i2 = memory[instr[3]];
			break;
		}
		case TYPE_INT: {
			i2 = instr[3];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}

		if (i1 == i2) last_cmp = EQUAL;
		else if (i1 > i2) last_cmp = GREATER;
		else if (i1 < i2) last_cmp = LESS;
		else last_cmp = NOT_SET;

		regs[IP] += 4;
		break;
	}
	case CMPS: {
		const char* str1 = reinterpret_cast<const char*>(&memory[instr[1]]);
		const char* str2 = reinterpret_cast<const char*>(&memory[instr[2]]);

		int i = strcmp(str1, str2);
		if (i == 0) last_cmp = EQUAL;
		else if (i < 0) last_cmp = LESS;
		else if (i > 0) last_cmp = GREATER;
		else last_cmp = NOT_SET;

		regs[IP] += 3;
		break;
	}
	case JE: {
		if (last_cmp == NOT_SET) {
			std::cerr << "There was no cmp!" << std::endl;
			set_running(false);
			return;
		}
		ubyte_t type = instr[1];
		ubyte_t addr;
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			addr = regs[reg];
			break;
		}
		case TYPE_REF: {
			addr = memory[instr[2]];
			break;
		}
		case TYPE_INT: {
			addr = instr[2];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		if (last_cmp == EQUAL)
			regs[IP] = addr;
		else regs[IP] += 3;
		break;
	}
	case JNE: {
		if (last_cmp == NOT_SET) {
			std::cerr << "There was no cmp!" << std::endl;
			set_running(false);
			return;
		}
		ubyte_t type = instr[1];
		ubyte_t addr;
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			addr = regs[reg];
			break;
		}
		case TYPE_REF: {
			addr = memory[instr[2]];
			break;
		}
		case TYPE_INT: {
			addr = instr[2];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		if (last_cmp != EQUAL)
			regs[IP] = addr;
		else regs[IP] += 3;
		break;
	}
	case JG: {
		if (last_cmp == NOT_SET) {
			std::cerr << "There was no cmp!" << std::endl;
			set_running(false);
			return;
		}
		ubyte_t type = instr[1];
		ubyte_t addr;
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			addr = regs[reg];
			break;
		}
		case TYPE_REF: {
			addr = memory[instr[2]];
			break;
		}
		case TYPE_INT: {
			addr = instr[2];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		if (last_cmp == GREATER)
			regs[IP] = addr;
		else regs[IP] += 3;
		break;
	}
	case JGE: {
		if (last_cmp == NOT_SET) {
			std::cerr << "There was no cmp!" << std::endl;
			set_running(false);
			return;
		}
		ubyte_t type = instr[1];
		ubyte_t addr;
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			addr = regs[reg];
			break;
		}
		case TYPE_REF: {
			addr = memory[instr[2]];
			break;
		}
		case TYPE_INT: {
			addr = instr[2];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		if (last_cmp == GREATER || last_cmp == EQUAL)
			regs[IP] = addr;
		else regs[IP] += 3;
		break;
	}
	case JL: {
		if (last_cmp == NOT_SET) {
			std::cerr << "There was no cmp!" << std::endl;
			set_running(false);
			return;
		}
		ubyte_t type = instr[1];
		ubyte_t addr;
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			addr = regs[reg];
			break;
		}
		case TYPE_REF: {
			addr = memory[instr[2]];
			break;
		}
		case TYPE_INT: {
			addr = instr[2];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		if (last_cmp == LESS)
			regs[IP] = addr;
		else regs[IP] += 3;
		break;
	}
	case JLE: {
		if (last_cmp == NOT_SET) {
			std::cerr << "There was no cmp!" << std::endl;
			set_running(false);
			return;
		}
		ubyte_t type = instr[1];
		ubyte_t addr;
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			addr = regs[reg];
			break;
		}
		case TYPE_REF: {
			addr = memory[instr[2]];
			break;
		}
		case TYPE_INT: {
			addr = instr[2];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		if (last_cmp == LESS || last_cmp == EQUAL)
			regs[IP] = addr;
		else regs[IP] += 3;
		break;
	}
	case LOOP: {
		ubyte_t type = instr[1];
		ubyte_t addr;
		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			addr = regs[reg];
			break;
		}
		case TYPE_REF: {
			addr = memory[instr[2]];
			break;
		}
		case TYPE_INT: {
			addr = instr[2];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		if (regs[C] > 1) {
			regs[C]--;
			regs[IP] = addr;
		}
		else regs[IP] += 3;
		break;
	}
	case IMUL: {
		ubyte_t type1 = get_type1(instr[1]);
		ubyte_t type2 = get_type2(instr[1]);
		byte_t i;
		switch (type2) {
		case TYPE_REG: {
			ubyte_t reg = instr[3];
			check_reg(reg);
			i = static_cast<byte_t>(regs[reg]);
			break;
		}
		case TYPE_REF: {
			i = static_cast<byte_t>(memory[instr[3]]);
			break;
		}
		case TYPE_INT: {
			i = static_cast<byte_t>(instr[3]);
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		switch (type1) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			regs[reg] = static_cast<ubyte_t>(static_cast<byte_t>(regs[reg]) * i);
			break;
		}
		case TYPE_REF: {
			memory[instr[2]] = static_cast<ubyte_t>(static_cast<byte_t>(memory[instr[2]]) * i);
			break;
		}
		SWITCH_TYPE_DEFAULT
		}

		regs[IP] += 4;
		break;
	}
	case IDIV: {
		ubyte_t type1 = get_type1(instr[1]);
		ubyte_t type2 = get_type2(instr[1]);
		byte_t i;
		switch (type2) {
		case TYPE_REG: {
			ubyte_t reg = instr[3];
			check_reg(reg);
			i = static_cast<byte_t>(regs[reg]);
			break;
		}
		case TYPE_REF: {
			i = static_cast<byte_t>(memory[instr[3]]);
			break;
		}
		case TYPE_INT: {
			i = static_cast<byte_t>(instr[3]);
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		switch (type1) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			regs[reg] = static_cast<ubyte_t>(static_cast<byte_t>(regs[reg]) / i);
			break;
		}
		case TYPE_REF: {
			memory[instr[2]] = static_cast<ubyte_t>(static_cast<byte_t>(memory[instr[2]]) / i);
			break;
		}
		SWITCH_TYPE_DEFAULT
		}

		regs[IP] += 4;
		break;
	}
	case SLEEP: {
		ubyte_t type = instr[1];
		ubyte_t seconds;

		switch (type) {
		case TYPE_REG: {
			ubyte_t reg = instr[2];
			check_reg(reg);
			seconds = regs[reg];
			break;
		}
		case TYPE_REF: {
			seconds = memory[instr[2]];
			break;
		}
		case TYPE_INT: {
			seconds = instr[2];
			break;
		}
		SWITCH_TYPE_DEFAULT
		}
		Sleep(seconds * 1000);
		regs[IP] += 3;
		break;
	}
	default:
		std::cerr << "Unknwon Instruction: " << (unsigned)*instr <<
			" at: " << (unsigned)regs[IP] << std::endl;
		set_running(false);
		break;
	}
}