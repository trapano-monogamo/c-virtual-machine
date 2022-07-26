#include "machine.h"
#include "stdio.h"

machine_t init(int *program)
{
	 machine_t m = {0, {0}, {0, 0, 0, 0, 0, 0, 0, -1, 0, 0}, program};
	 return m;
}

int fetch(machine_t *machine)
{
	 return machine->program[machine->registers[IP]];
}

void eval(machine_t *machine, int instr)
{
#define ip (machine->registers[IP])
#define sp (machine->registers[SP])
#define stack (machine->stack)
#define program (machine->program)

	 switch (instr)
	 {
		  case PSH: {
				stack[++sp] = program[++ip];
				break;
		  }
		  case POP: {
				machine->registers[F] = stack[sp--];
				break;
		  }
		  case ADD: {
				int n1 = machine->registers[program[++ip]];
				int n2 = machine->registers[program[++ip]];
				int res = n1 + n2;
				stack[++sp] = res;
				break;
		  }
		  case REG: {
				int reg = program[++ip];
				int arg = program[++ip];
				machine->registers[reg] = arg;
				break;
		  }
		  case RFM: {
				int reg = program[++ip];
				int mem = program[++ip];
				machine->registers[reg] = stack[mem];
				break;
		  }
		  case SET: {
				int mem = program[++ip];
				int arg = program[++ip];
				stack[mem] = arg;
				break;
		  }
		  case GET: {
				int mem = program[++ip];
				int reg = program[++ip];
				machine->registers[reg] = stack[mem];
				break;
		  }
		  case JMP: {
				// ip-- to account for next iteration increment
				machine->registers[IP] = program[++ip];
				ip--;
				break;
		  }
		  case JNZ: {
				if (machine->registers[CJ] != 0) {
					 // ip-- to account for next iteration increment
					 machine->registers[IP] = program[++ip];
					 ip--;
				} else {
					 ip++;
				}
				machine->registers[CJ] = 0; // reset register
				break;
		  }
		  case SNZ: {
				if (machine->registers[program[++ip]] != 0)
					 machine->registers[CJ] = 1;
				else
					 machine->registers[CJ] = 0;
				break;
		  }
		  case HLT: {
				machine->running = 0;
				printf("halting...\n");
				break;
		  }

		  default: break;
	 }

#undef ip
#undef sp
#undef stack
#undef program
}

void run(machine_t *machine)
{
	 machine->running = 1;
	 printf("startig...\n");
	 while (machine->running != 0) {
		  eval(machine, fetch(machine));
		  machine->registers[IP]++;
		  if (machine->registers[SP] > 256) {
				printf("Stack overflow! Halting...\n");
				break;
		  }
	 }
	 log_machine(machine);
}

void log_machine(machine_t* machine)
{
	 int count;
	 count = 0;
	 for (int i=0; i<256; i++) {
		  printf("%d\t", machine->stack[i]);
		  if (++count % 20 == 0) printf("\n");
	 }
	 printf("\n---\n");
	 count = 0;
	 for (int i=0; i<NUM_OF_REGISTERS; i++) {
		  printf("%d\t", machine->registers[i]);
		  if (++count % 20 == 0) printf("\n");
	 }
	 printf("\n");
}
