#pragma once

#include "RE/B/BSBitReader.h"
#include "RE/B/BSFixedString.h"

namespace RE::BSScript::ByteCode
{
#pragma pack(push, 4)
	struct Argument
	{
		enum class Type : std::uint32_t
		{
			kNone = 0,
			kIdentifier = 1,  // Identifier of object variables (Forms, Actors, etc.) as well as "self" and "::State"
			kString = 2,
			kInt = 3,
			kFloat = 4,
			kBool = 5,
			kLocalVarIdx = 6,   // index of local variable in function
			kMemberVarIdx = 7,  // index of member variable in script instance
		};

		static_assert(sizeof(Type) == 0x4);

		union Value
		{
			explicit Value(void* a_val = nullptr);
			~Value();

			int           i;
			float         f;
			bool          b;
			std::uint32_t idx;
			BSFixedString string;
			void*         p;  // Internal use only, not actual value type
		};

		static_assert(sizeof(Value) == 0x8);

		Argument();
		explicit Argument(const Type& a_type);
		Argument(const Argument& a_rhs);
		Argument(Argument&& a_rhs) noexcept;
		~Argument();

		Argument& operator=(const Argument& a_rhs);
		Argument& operator=(Argument&& a_rhs) noexcept;

		[[nodiscard]] bool IsNone() const;
		[[nodiscard]] bool IsIdentifier() const;
		[[nodiscard]] bool IsString() const;
		[[nodiscard]] bool IsInt() const;
		[[nodiscard]] bool IsFloat() const;
		[[nodiscard]] bool IsBool() const;
		[[nodiscard]] bool IsLocalVar() const;
		[[nodiscard]] bool IsMemberVar() const;
		[[nodiscard]] Type GetType() const;

		// Identical to GetString
		[[nodiscard]] BSFixedString GetIdentifier() const;
		[[nodiscard]] BSFixedString GetString() const;
		[[nodiscard]] std::int32_t  GetInt() const;
		[[nodiscard]] float         GetFloat() const;
		[[nodiscard]] bool          GetBool() const;
		[[nodiscard]] std::uint32_t GetLocalVarIdx() const;
		[[nodiscard]] std::uint32_t GetMemberVarIdx() const;

		void SetLocalVarIdx(std::uint32_t a_val);
		void SetMemberVarIdx(std::uint32_t a_val);
		void SetInt(std::int32_t a_val);
		void SetString(const BSFixedString& a_val);
		void SetFloat(float a_val);
		void SetBool(bool a_val);
		void SetIdentifier(const BSFixedString& a_val);

		bool        ReadFromBitStream(BSBitReader& a_reader, std::uint32_t a_localVarBitCount, std::uint32_t a_memberVarBitCount);
		static void SkipFromBitStream(BSBitReader& a_reader, std::uint32_t a_localVarBitCount, std::uint32_t a_memberVarBitCount);

	private:
		void ChangeType(Type a_type);
		void Reset();
		void Assign(const Argument& a_rhs);

		// members
		Type  type;   // 00
		Value value;  // 04
	};
	static_assert(sizeof(Argument) == 0xC);

#pragma pack(pop)
}