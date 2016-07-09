include_dir = ../include
objs = Machine.o Sign.o
compile = g++ -std=c++11 -I $(include_dir) -c
link = g++ -std=c++11 -I $(include_dir) -o
proj_name = mix-machine

Mix-machine.exe : main.cpp $(objs)
	$(link) $(proj_name) main.cpp $(objs)

Machine.o : Machine.h Machine.cpp
	$(compile) Machine.cpp

Sign.o : Sign.h Sign.cpp
	$(compile) Sign.cpp

clean:
	rm $(objs) $(proj_name)

