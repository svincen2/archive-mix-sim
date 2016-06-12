src_dir = ..
test_objs = test_machine_words.o test_machine.o test_basic_word.o \
			test_field.o

src_objs = $(src_dir)/Machine.o $(src_dir)/Field.o \
           $(src_dir)/Half_word.o $(src_dir)/Instruction.o

compile = g++ -std=c++11 -I/home/sean/Documents/cpp -c
link = g++ -std=c++11 -I/home/sean/Documents/cpp -o

tests : $(test_objs)
	$(link) tests tests.o $(test_objs) $(src_objs)

tests.o : tests.cpp
	$(compile) tests.cpp

test_machine_words.o : test_machine_words.cpp
	$(compile) test_machine_words.cpp

test_machine.o : test_machine.cpp
	$(compile) test_machine.cpp

test_basic_word.o : test_basic_word.cpp
	$(compile) test_basic_word.cpp

test_field.o : test_field.cpp
	$(compile) test_field.cpp

clean:
	rm $(test_objs)
