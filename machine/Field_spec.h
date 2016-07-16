#ifndef MIX_MACHINE_FIELD_SPEC_H
#define MIX_MACHINE_FIELD_SPEC_H

namespace mix
{
	struct Field_spec
	{
		int left;
		int right;
		void encode() const;
	};

	Field_spec decode_field_spec(int);
}
#endif

