#ifndef MIX_MACHINE_FIELD_SPEC_H
#define MIX_MACHINE_FIELD_SPEC_H

namespace mix
{
	
	struct Field_spec
	{
	public:
		// Constants.
		static const int ENCODE_VALUE{8};

		// Constructor.
		Field_spec(int, int);

		// Operators.
		bool operator==(const Field_spec&) const;
		bool operator!=(const Field_spec&) const;

		// Properties.
		int left;
		int right;

		// Functions.
		int bytes() const;
		int size() const;
		int encode() const;
		bool contains_sign() const;

	private:
		// Check if field spec is valid.
		bool valid() const;
	};

	// Decode an encoded field spec.
	Field_spec decode_field_spec(int);
}
#endif

