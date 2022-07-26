#include "machine.h"

// infinite loop program
int program[] = {
	 PSH, 3,
	 POP,
	 SNZ, F,
	 PSH, 4,
	 JNZ, 2,
	 HLT,
};

int main()
{
  machine_t m = init(program);
  run(&m);

  return 0;
}
