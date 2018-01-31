#include <iostream>
#include "microvm.h"


int main(int argc, char** argv) {
	MicroVM* vm = &MicroVM();
#ifdef _DEBUG
	vm->load_program("A:\\Java\\Test\\prog.bin");
#else
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <binary>" << std::endl;
		return -1;
	}
	vm->load_program(argv[1]);
#endif
	vm->run();
#ifdef _DEBUG
	getchar();
#endif
	return 0;
}