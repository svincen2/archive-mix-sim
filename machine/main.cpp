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
	return machine.run(args);
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
	int exit_code{0};

	try {
		exit_code = run(argc, argv);
	}
	catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		exit_code = -1;
	}

	std::cout << "exit: " << exit_code << '\n';
	return exit_code;
}

