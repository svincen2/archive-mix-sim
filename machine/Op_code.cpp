#include "Op_code.h"

namespace mix
{
	/*
	* Returns whether or not the given op code is an arithmetic operation.
	* Parameters:
	*	code - Operation code.
	*/
	bool is_math_op(Op_code code)
	{
		return (Op_code::ADD <= code && code <= Op_code::DIV);
	}

	/*
	*
	* Returns whether or not the given op code is a load operation.
	* Parameters:
	*	code - Operation code.
	*/
	bool is_load_op(Op_code code)
	{
		return (Op_code::LDA <= code && code <= Op_code::LDX);
	}

	/*
	*
	* Returns whether or not the given op code is a load negative operation.
	* Parameters:
	*	code - Operation code.
	*/
	bool is_load_neg_op(Op_code code)
	{
		return (Op_code::LDAN <= code && code <= Op_code::LDXN);
	}

	/*
	* Returns whether or not the given op code is a store operation.
	* Parameters:
	*	code - Operation code.
	*/
	bool is_store_op(Op_code code)
	{
		return (Op_code::STA <= code && code <= Op_code::STZ);
	}
}

