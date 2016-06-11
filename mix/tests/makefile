src_dir = ..
test_objs = test_machine_words.o test_machine.o

src_objs = $(src_dir)/Machine.o $(src_dir)/Field.o $(src_dir)/Word.o \
           $(src_dir)/Half_word.o

compile = g++ -std=c++11 -I/home/sean/Documents/cpp -c
link = g++ -std=c++11 -I/home/sean/Documents/cpp -o

tests : tests.o test_machine_words.o test_machine.o
	$(link) tests tests.o $(test_objs) $(src_objs)

tests.o : tests.cpp
	$(compile) tests.cpp

test_machine_words.o : test_machine_words.cpp
	$(compile) test_machine_words.cpp

test_machine.o : test_machine.cpp
	$(compile) test_machine.cpp

clean:
	rm $(test_objs)
