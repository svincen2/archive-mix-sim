include_dir = /home/sean/Documents/cpp/
objs = Machine.o
compile = g++ -std=c++11 -I $(include_dir) -c
link = g++ -std=c++11 -I $(include_dir) -o
proj_name = mix-machine

Mix-machine.exe : main.cpp $(objs)
	$(link) $(proj_name) main.cpp $(objs)

Machine.o : Machine.h Machine.cpp
	$(compile) Machine.cpp

clean:
	rm $(objs) $(proj_name)

