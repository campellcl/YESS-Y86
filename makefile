CC = g++
CFLAGS = -g -c -Wall -std=c++0x 
OBJ = lab5.o Tools.o RegisterFile.o Loader.o\
ConditionCodes.o Memory.o
.C.o:
	$(CC) $(CFLAGS) $< -o $@

lab5: $(OBJ)
	$(CC) $(OBJ) -o lab5
lab5.o: Memory.h RegisterFile.h ConditionCodes.h Loader.h

Loader.o: Loader.C Loader.h Memory.h

RegisterFile.o: RegisterFile.C RegisterFile.h Tools.h

Tools.o: Tools.C Tools.h

ConditionCodes.o: ConditionCodes.C ConditionCodes.h Tools.h

Memory.o: Memory.h Tools.h
#add the lines need to compile RegisterFile.C, Tools.C, ConditionCodes.C
#and Memory.C

clean:
	rm $(OBJ)

run:
	make clean
	make lab5
	./run.sh

submit:
	make clean
	submit can 3481-lab5 *.C *.h makefile 
