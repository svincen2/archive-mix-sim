include_dir = /home/sean/Documents/cpp/
test_suite = tests.o
tests = Basic_word_test.o Machine_test.o
dependancies = ../Machine.o ../Sign.o
compile = g++ -std=c++11 -I$(include_dir) -c
link = g++ -std=c++11 -I$(include_dir) -o
proj_name = tests

$(proj_name) : $(test_suite) $(tests)
	$(link) $(proj_name) $(test_suite) $(tests) $(dependancies)

$(test_suite) : tests.cpp
	$(compile) tests.cpp

Basic_word_test.o : Basic_word_test.cpp
	$(compile) Basic_word_test.cpp

Machine_test.o : Machine_test.cpp 
	$(compile) Machine_test.cpp

clean:
	rm $(tests) $(proj_name)

