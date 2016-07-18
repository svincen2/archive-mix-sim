include_dir = ../../include
test_suite = tests.o
tests = Sign_test.o Basic_word_test.o Machine_test.o Field_spec_test.o \
		Instruction_test.o
dependancies = ../Machine.o ../Sign.o ../Field_spec.o
compile = g++ -std=c++11 -I$(include_dir) -c
link = g++ -std=c++11 -I$(include_dir) -o
proj_name = tests

$(proj_name) : $(test_suite) $(tests)
	$(link) $(proj_name) $(test_suite) $(tests) $(dependancies)

$(test_suite) : tests.cpp
	$(compile) tests.cpp

Sign_test.o : Sign_test.cpp
	$(compile) Sign_test.cpp

Basic_word_test.o : Basic_word_test.cpp
	$(compile) Basic_word_test.cpp

Machine_test.o : Machine_test.cpp 
	$(compile) Machine_test.cpp

Field_spec_test.o : Field_spec_test.cpp
	$(compile) Field_spec_test.cpp

Instruction_test.o : Instruction_test.cpp
	$(compile) Instruction_test.cpp

clean:
	rm $(tests) $(proj_name)

relink:
	$(link) $(proj_name) $(test_suite) $(tests) $(dependancies)

