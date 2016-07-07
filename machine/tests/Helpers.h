#ifndef MIX_MACHINE_TESTS_HELPERS_H
#define MIX_MACHINE_TESTS_HELPERS_H

#include "../Basic_word.h"

using namespace mix;

/* Helper functions. */

// Asserts all bytes in the given word match the given bytes.
template<unsigned int N>
void require_bytes_are(Basic_word<N>& bw, std::vector<Byte> bytes)
{
	int i = 1;
	for (auto p = bytes.begin(); p != bytes.end(); ++p)
		REQUIRE(bw.byte(i++) == *p);
}

// Asserts that all bytes match between the two basic words.
template<unsigned int N>
void require_bytes_match(Basic_word<N>& a, Basic_word<N>& b)
{
	for (int i = 1; i <= N; ++i)
		REQUIRE(a.byte(i) == b.byte(i));
}
#endif

