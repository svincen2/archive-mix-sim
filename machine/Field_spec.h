#ifndef MIX_MACHINE_FIELD_SPEC_H
#define MIX_MACHINE_FIELD_SPEC_H

namespace mix
{
	struct Field_spec
	{
	public:
		// Value used to encode/decode a field spec.
		static const int ENCODE_VALUE{8};

		// Constructor.
		Field_spec(int, int);

		// Properties.
		int left;
		int right;

		// Size of the field spec range.
		int size() const;

		// Encode field spec as integer.
		int encode() const;

	private:
		// Check if field spec is valid.
		bool valid() const;
	};

	// Decode an encoded field spec.
	Field_spec decode_field_spec(int);
}
#endif

