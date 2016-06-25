#include "Machine.h"
#include "util/console/cmd_args.h"
#include <iostream>
#include <string>
#include <vector>

/*
* Main entry point.
* Start mix machine and pass it the command line arguments.
* Parameters:
*	argc - Number of command line arguments.
*	argv - Command line arguments.
*/
int main(int argc, char* argv[])
{
	std::vector<std::string> args{console::get_args(argc, argv)};
	for (auto p = args.begin(); p != args.end(); ++p) {
		std::cout << "arg: " << *p << '\n';
	}
	std::cout << "exit: 0\n";
	return 0;
}
