#include "machine.h"

// infinite loop program
int testprogram[] = {
	 PSH, 3,
	 POP,
	 SNZ, F,
	 PSH, 4,
	 JNZ, 2,
	 HLT,
};

int program[] = {
	PSH, 3,
	PSH, 2,
	GET, 0, A,
	GET, 1, B,
	ADD, A, B,
	HLT,
};

int main()
{
  machine_t m = init(program);
  run(&m);

  return 0;
}
