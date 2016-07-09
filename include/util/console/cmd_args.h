#ifndef UTIL_CONSOLE_CMD_ARGS_H
#define UTIL_CONSOLE_CMD_ARGS_H

#include <string>
#include <vector>

namespace console
{
	std::vector<std::string> get_args(int argc, char* argv[])
	{
		std::vector<std::string> args{};
		// argv[0] is program name, skip it.
		for (int i = 1; i < argc; ++i) {
			args.push_back(std::string{argv[i]});
		}
		return args;
	}
}
#endif

