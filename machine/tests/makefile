src_dir = ..
src_objs = $(src_dir)/Word.o
test_objs = test_machine_words.o
compile = g++ -std=c++11 -I/home/sean/Documents/cpp -c
link = g++ -std=c++11 -I/home/sean/Documents/cpp -o

tests : tests.o test_machine_words.o
	$(link) tests tests.o $(test_objs) $(src_objs)

tests.o : tests.cpp
	$(compile) tests.cpp

test_machine_words.o : test_machine_words.cpp
	$(compile) test_machine_words.cpp

clean:
	rm $(test_objs)
