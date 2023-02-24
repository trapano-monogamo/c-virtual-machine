SRC = ./src
INCLUDE = ./include
CC_FLAGS = -Wall -Wextra -g -std=c11
CC = gcc

all:
	${CC} ${SRC}/*.c ${CC_FLAGS} -I${INCLUDE} -o mvm

run: all
	./mvm

.PHONY: clean

clean:
	-rm ./mvm
