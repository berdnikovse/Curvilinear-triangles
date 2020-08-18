CC = gcc
ASM = nasm
CFLAGS = -std=c99 -Wall -m32
ASMFLAGS = -g -f elf32
MHEADER = headers/main.h

program: obj/functions.o obj/comp.o obj/samples.o obj/test.o obj/area.o obj/help.o obj/main.o 
	$(CC) obj/functions.o obj/comp.o obj/samples.o obj/test.o obj/area.o obj/help.o obj/main.o $(CFLAGS) -o program

obj/functions.o: source/functions.asm
	$(ASM) $(ASMFLAGS) source/functions.asm -o obj/functions.o -DUNIX

obj/comp.o: source/comp.c headers/comp.h headers/asmfunc.h
	$(CC) source/comp.c $(CFLAGS) -c -o obj/comp.o

obj/samples.o: source/samples.c headers/samples.h headers/sampfunc.h
	$(CC) source/samples.c $(CFLAGS) -c -o obj/samples.o

obj/test.o: source/test.c headers/test.h headers/comp.h headers/samples.h headers/asmfunc.h headers/basic_testfunc.h headers/constants.h
	$(CC) source/test.c $(CFLAGS) -c -o obj/test.o

obj/area.o: source/area.c headers/area.h headers/comp.h headers/samples.h headers/asmfunc.h headers/constants.h
	$(CC) source/area.c $(CFLAGS) -c -o obj/area.o

obj/help.o: source/help.c headers/help.h headers/asmfunc.h headers/constants.h
	$(CC) source/help.c $(CFLAGS) -c -o obj/help.o

obj/main.o: source/main.c $(MHEADER)
	$(CC) source/main.c $(CFLAGS) -c -o obj/main.o

$(MHEADER): headers/test.h headers/help.h headers/samples.h headers/area.h headers/constants.h
	rm -rf $(MHEADER)
	echo '#pragma once\n' >> $(MHEADER)
	echo '#include <stdio.h>' >> $(MHEADER)
	echo '#include <string.h>' >> $(MHEADER)
	echo '#include "../headers/test.h"' >> $(MHEADER)
	echo '#include "../headers/help.h"' >> $(MHEADER)
	echo '#include "../headers/samples.h"' >> $(MHEADER)
	echo '#include "../headers/area.h"' >> $(MHEADER)
	echo '#include "../headers/constants.h"' >> $(MHEADER)

all: clean program

clean:
	rm -rf program
	rm -rf obj/functions.o
	rm -rf obj/comp.o
	rm -rf obj/samples.o
	rm -rf obj/test.o
	rm -rf obj/area.o
	rm -rf obj/help.o
	rm -rf obj/main.o
	rm -rf $(MHEADER)



