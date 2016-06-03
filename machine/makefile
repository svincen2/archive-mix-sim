objs = Machine.o Word.o
compile = g++ -std=c++11 -c

Machine.o : Machine.h Machine.cpp Byte.h Word.o Half_word.h
	$(compile) Machine.cpp

Word.o : Word.h Word.cpp Basic_word.h
	$(compile) Word.cpp

clean:
	rm $(objs)

