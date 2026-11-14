#include "RE/A/Argument.h"

#include <cstdint>

namespace
{
	std::int32_t ReadPackedInt(RE::BSScript::BSBitReader& a_reader)
	{
		/* Freaky bit math, Integers are variable packed in 3 different types
			 * 5-bit int (5 bits with 6th being `0`) -> 6 bits read (5 bit value)
			 * 13-bit int (5 bits, ignore 6th "flag" bit, 8 more bits, with final bit being `0`) -> 15 bits read (13 bit value)
			 * 32-bit int (5 bits, ignore 6th "flag" bit, 8 more bits, ignore 13th "flag" bit, 19 more bits) -> 34 bits read (32 bit value)
			 */

		auto acquiredPackedInt = [&a_reader] {
			auto encodedValue = static_cast<uint32_t>(a_reader.readRawBits(6));
			if (encodedValue & 0x20)  // 5-bit int
				return encodedValue & 0x1F;

			encodedValue |= static_cast<uint32_t>(a_reader.readRawBits(9)) << 5;
			if (encodedValue & 0x2000)  // 13-bit int
				return encodedValue & 0x1FFF;

			encodedValue |= static_cast<uint32_t>(a_reader.readRawBits(19)) << 13;  // 32-bit int
			return encodedValue;                                                    // full 32 bits, terminal stage
		};

		const auto encodedInt = acquiredPackedInt();

		// Zigzag to decode the unsigned int to signed int value - required due to variable-packed ints, as negative
		// ints can be small as well instead of the negative bit flag being at the very end of a full INT 32-bit type
		const std::int32_t decodedInt = (encodedInt & 1) ? ~static_cast<int32_t>(encodedInt >> 1) : static_cast<int32_t>(encodedInt >> 1);

		return decodedInt;
	}
}

namespace RE::BSScript::ByteCode
{
	Argument::Value::Value(void* a_val) :
		p(a_val)
	{}

	Argument::Value::~Value()
	{}

	Argument::Argument() :
		type(Type::kNone), value(nullptr)
	{}

	Argument::Argument(const Type& a_type) :
		type(a_type),
		value(nullptr)
	{}

	Argument::Argument(const Argument& a_rhs) :
		type(Type::kNone),
		value(nullptr)
	{
		Assign(a_rhs);
	}

	Argument::Argument(Argument&& a_rhs) noexcept :
		type(a_rhs.type), value(a_rhs.value.p)
	{
		a_rhs.value.p = nullptr;
		a_rhs.type = Type::kNone;
	}

	Argument::~Argument()
	{
		Reset();
	}

	Argument& Argument::operator=(const Argument& a_rhs)
	{
		if (this != std::addressof(a_rhs)) {
			Reset();
			Assign(a_rhs);
		}
		return *this;
	}

	Argument& Argument::operator=(Argument&& a_rhs) noexcept
	{
		if (this != std::addressof(a_rhs)) {
			Reset();

			type = a_rhs.type;
			value.p = a_rhs.value.p;
			a_rhs.type = Type::kNone;
			a_rhs.value.p = nullptr;
		}
		return *this;
	}

	bool Argument::IsNone() const
	{
		return type == Type::kNone;
	}

	bool Argument::IsIdentifier() const
	{
		return type == Type::kIdentifier;
	}

	bool Argument::IsString() const
	{
		return type == Type::kString;
	}

	bool Argument::IsInt() const
	{
		return type == Type::kInt;
	}

	bool Argument::IsFloat() const
	{
		return type == Type::kFloat;
	}

	bool Argument::IsBool() const
	{
		return type == Type::kBool;
	}

	bool Argument::IsLocalVar() const
	{
		return type == Type::kLocalVarIdx;
	}

	bool Argument::IsMemberVar() const
	{
		return type == Type::kMemberVarIdx;
	}

	Argument::Type Argument::GetType() const
	{
		return type;
	}

	BSFixedString Argument::GetIdentifier() const
	{
		assert(type == Type::kString || type == Type::kIdentifier);
		return value.string;
	}

	BSFixedString Argument::GetString() const
	{
		assert(type == Type::kString || type == Type::kIdentifier);
		return value.string;
	}

	std::int32_t Argument::GetInt() const
	{
		assert(type == Type::kInt);
		return value.i;
	}

	float Argument::GetFloat() const
	{
		assert(type == Type::kFloat);
		return value.f;
	}

	bool Argument::GetBool() const
	{
		assert(type == Type::kBool);
		return value.b;
	}

	std::uint32_t Argument::GetLocalVarIdx() const
	{
		assert(type == Type::kLocalVarIdx);
		return value.idx;
	}

	std::uint32_t Argument::GetMemberVarIdx() const
	{
		assert(type == Type::kMemberVarIdx);
		return value.idx;
	}

	void Argument::SetIdentifier(const BSFixedString& a_val)
	{
		ChangeType(Type::kIdentifier);
		value.string = a_val;
	}

	void Argument::SetString(const BSFixedString& a_val)
	{
		ChangeType(Type::kString);
		value.string = a_val;
	}

	void Argument::SetInt(std::int32_t a_val)
	{
		ChangeType(Type::kInt);
		value.i = a_val;
	}

	void Argument::SetFloat(float a_val)
	{
		ChangeType(Type::kFloat);
		value.f = a_val;
	}

	void Argument::SetBool(bool a_val)
	{
		ChangeType(Type::kBool);
		value.b = a_val;
	}

	void Argument::SetLocalVarIdx(const std::uint32_t a_val)
	{
		ChangeType(Type::kLocalVarIdx);
		value.idx = a_val;
	}

	void Argument::SetMemberVarIdx(const std::uint32_t a_val)
	{
		ChangeType(Type::kMemberVarIdx);
		value.idx = a_val;
	}

	// Read the "Type" from the stream, then read variable amount of bits for the value
	bool Argument::ReadFromBitStream(BSBitReader& a_reader, const std::uint32_t a_localVarBitCount, const std::uint32_t a_memberVarBitCount)
	{
		const auto rawType = static_cast<Type>(a_reader.readRawBits(3));

		if (rawType > Type::kMemberVarIdx) {
			// Unexpected type value
			return false;
		}

		Reset();

		type = rawType;

		switch (type) {
		case Type::kNone:
			{
				// Nothing to do for None
				break;
			}
		case Type::kIdentifier:
		case Type::kString:
			{
				// Read 62 bits to establish the string ptr, then shift it to a full 64-bit pointer
				// Consequently, this means all strings have to be 4-byte aligned which is the case anyway
				const auto* stringPtr = reinterpret_cast<const char*>(a_reader.readRawBits(62) << 2);
				value.string = stringPtr;
				break;
			}
		case Type::kInt:
			{
				value.i = ReadPackedInt(a_reader);
				break;
			}
		case Type::kFloat:
			{
				value.f = std::bit_cast<float>(static_cast<uint32_t>(a_reader.readRawBits(32)));
				break;
			}
		case Type::kBool:
			{
				value.b = a_reader.readRawBits(1);
				break;
			}
		case Type::kLocalVarIdx:
			{
				value.idx = static_cast<uint32_t>(a_reader.readRawBits(a_localVarBitCount));
				break;
			}

		case Type::kMemberVarIdx:
			{
				value.idx = static_cast<uint32_t>(a_reader.readRawBits(a_memberVarBitCount));
				break;
			}
		}

		return true;
	}

	// Same as ReadFromBitStream, but skips instead
	void Argument::SkipFromBitStream(BSBitReader& a_reader, const std::uint32_t a_localVarBitCount, const std::uint32_t a_memberVarBitCount)
	{
		const auto rawType = static_cast<Type>(a_reader.readRawBits(3));

		if (rawType > Type::kMemberVarIdx) {
			// Unexpected type value
			return;
		}

		switch (rawType) {
		case Type::kNone:
			{
				// Nothing to do for None
				break;
			}
		case Type::kIdentifier:
		case Type::kString:
			{
				a_reader.readRawBits(62);
				break;
			}
		case Type::kInt:
			{
				ReadPackedInt(a_reader);
				break;
			}
		case Type::kFloat:
			{
				a_reader.readRawBits(32);
				break;
			}
		case Type::kBool:
			{
				a_reader.readRawBits(1);
				break;
			}
		case Type::kLocalVarIdx:
			{
				a_reader.readRawBits(a_localVarBitCount);
				break;
			}

		case Type::kMemberVarIdx:
			{
				a_reader.readRawBits(a_memberVarBitCount);
				break;
			}
		}
	}

	void Argument::ChangeType(const Type a_type)
	{
		Reset();
		type = a_type;
	}

	void Argument::Reset()
	{
		if (type == Type::kIdentifier || type == Type::kString) {
			value.string.~BSFixedString();
		}
		value.p = nullptr;
		type = Type::kNone;
	}

	void Argument::Assign(const Argument& a_rhs)
	{
		type = a_rhs.type;
		switch (a_rhs.type) {
		case Type::kNone:
		case Type::kInt:
		case Type::kFloat:
		case Type::kBool:
		case Type::kLocalVarIdx:
		case Type::kMemberVarIdx:
			{
				value.p = a_rhs.value.p;
				break;
			}
		case Type::kIdentifier:
		case Type::kString:
			{
				value.string = a_rhs.value.string;
				break;
			}
		}
	}
}