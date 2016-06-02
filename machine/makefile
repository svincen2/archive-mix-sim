objs = Machine.o
compile = g++ -std=c++11 -c

Machine.o : Machine.h Machine.cpp Byte.h Word.h Half_word.h Word_template.h
	$(compile) Machine.cpp

clean:
	rm $(objs)

