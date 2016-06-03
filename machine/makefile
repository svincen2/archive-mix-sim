objs = Machine.o Field.o
compile = g++ -std=c++11 -c

Machine.o : Machine.h Machine.cpp Word.h Half_word.h Field.o
	$(compile) Machine.cpp

Field.o : Field.h Field.cpp
	$(compile) Field.cpp

clean:
	rm $(objs)

