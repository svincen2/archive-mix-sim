include_dir = ../include
objs = Machine.o Sign.o Field_spec.o Op_code.o Op_factory.o Load_operation.o \
	   Load_neg_operation.o Store_operation.o Math_operation.o
compile = g++ -std=c++11 -I $(include_dir) -c
link = g++ -std=c++11 -I $(include_dir) -o
proj_name = mix-machine

Mix-machine.exe : main.cpp $(objs)
	$(link) $(proj_name) main.cpp $(objs)

Field_spec.o : Field_spec.h Field_spec.cpp
	$(compile) Field_spec.cpp

Load_operation.o : Load_operation.h Load_operation.cpp
	$(compile) Load_operation.cpp

Load_neg_operation.o : Load_neg_operation.h Load_neg_operation.cpp
	$(compile) Load_neg_operation.cpp

Machine.o : Machine.h Machine.cpp
	$(compile) Machine.cpp

Math_operation.o : Math_operation.h Math_operation.cpp
	$(compile) Math_operation.cpp

Op_code.o : Op_code.h Op_code.cpp
	$(compile) Op_code.cpp

Op_factory.o : Op_factory.h Op_factory.cpp
	$(compile) Op_factory.cpp

Sign.o : Sign.h Sign.cpp
	$(compile) Sign.cpp

Store_operation.o : Store_operation.h Store_operation.cpp
	$(compile) Store_operation.cpp

clean:
	rm $(objs) $(proj_name)

