objs = Machine.o Half_word.o Field.o Instruction.o
compile = g++ -std=c++11 -c

Machine.o : Machine.h Machine.cpp Byte.h Comparison.h Half_word.o \
            Field.o Instruction.o Bit.h
	$(compile) Machine.cpp

Half_word.o : Half_word.h Half_word.cpp Basic_word.h
	$(compile) Half_word.cpp

Field.o : Field.h Field.cpp
	$(compile) Field.cpp

Instruction.o : Instruction.h Instruction.cpp
	$(compile) Instruction.cpp

clean:
	rm $(objs)
