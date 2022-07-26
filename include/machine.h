#ifndef _MACHINE_H_
#define _MACHINE_H_

typedef enum {
	 PSH, // pushes to stack:             PSH [arg]
	 POP, // pops from stack:             POP
	 REG, // sets register:               REG [reg] [arg]
	 RFM, // sets register from memory:   REG [reg] [arg]
	 SET, // writes to memory:            SET [mem] [arg]
	 GET, // reads from memory:           GET [mem] [reg]
	 ADD, // adds two reg and pushes:     ADD [reg] [reg]
	 JMP, // jumps to line:               JMP [arg]
	 JNZ, // jumps if CJ!=0:              JMP [arg]
	 SNZ, // sets CJ if reg != 0:         SNZ [reg]
	 HLT, // halts:                       HLT
} opcode_t;

typedef enum {
	 A, B, C, D, E, F, IP, SP, PC, CJ,
	 NUM_OF_REGISTERS,
} register_t;

typedef struct {
	 int running;
	 int stack[256];
	 int registers[NUM_OF_REGISTERS];
	 int *program;
} machine_t;

machine_t init();
int fetch(machine_t *machine);
void eval(machine_t *machine, int instr);
void run(machine_t *machine);
void log_machine(machine_t* machine);

#endif
