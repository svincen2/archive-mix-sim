#ifndef MIX_MACHINE_MACHINE_H
#define MIX_MACHINE_MACHINE_H

#include <string>
#include <vector>

namespace mix
{
	class Machine
	{
	public:
		// Constructors and destructor.
		Machine();
		Machine(const Machine&) = delete;
		Machine(Machine&&) = delete;
		~Machine();

		// Public interface (API).
		int run(std::vector<std::string>&);
	};
}
#endif

