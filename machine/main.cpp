#include "Machine.h"
#include "util/console/cmd_args.h"
#include <iostream>
#include <string>
#include <vector>

/*
* Print the given arguments to std::cout.
*/
void print_args(std::vector<std::string>& args) {
	for (auto p = args.begin(); p != args.end(); ++p) {
		std::cout << "arg: " << *p << '\n';
	}
}

/*
* Start mix machine and pass it the command line arguments.
* Parameters:
*	argc - Number of command line arguments.
*	argv - Command line arguments.
*/
int run(int argc, char* argv[])
{
	std::vector<std::string> args{console::get_args(argc, argv)};
	print_args(args);

	mix::Machine machine{};
	machine.start(args);
}

/*
* Main entry point.
* Calls run() and catches exceptions.
* Parameters:
*	argc - Number of command line arguments.
*	argv - Command line arguments.
*/
int main(int argc, char* argv[])
{
	try {
		run(argc, argv);
		return 0;
	}
	catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		return -1;
	}
}

