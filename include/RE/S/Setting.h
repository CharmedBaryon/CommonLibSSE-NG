#pragma once

#include "RE/C/Color.h"
#include "RE/M/MemoryManager.h"

namespace RE
{
	class Setting
	{
	public:
		inline static constexpr auto RTTI = RTTI_Setting;
		inline static constexpr auto VTABLE = VTABLE_Setting;

		TES_HEAP_REDEFINE_NEW();

		enum class Type
		{
			kUnknown = -1,
			kBool = 0,               // b
			kCharacter = 1,          // c
			kUnsignedCharacter = 2,  // h
			kInteger = 3,            // i
			kUnsignedInteger = 4,    // u
			kFloat = 5,              // f
			kString = 6,             // s: statically allocated, S: dynamically allocated
			kColorRGB = 7,           // r
			kColorRGBA = 8,          // a
		};

		union Data
		{
		public:
			// Member variables
			bool          b;
			std::int8_t   c;
			std::uint8_t  h;
			std::int32_t  i;
			std::uint32_t u;
			float         f;
			char*         s{ nullptr };
			std::uint32_t r;
			std::uint32_t a;
		};
		static_assert(sizeof(Data) == 0x8);

		// Add
		virtual ~Setting();                        // 0
		virtual bool IsPreferenceSetting() const;  // 1

		Setting() = delete;
		Setting(const Setting&) = delete;
		Setting(Setting&&) = delete;

		Setting& operator=(const Setting&) = delete;
		Setting& operator=(Setting&&) = delete;

		Setting(const std::string& name);
		Setting(const std::string& name, bool value);
		Setting(const std::string& name, const std::string& value);
		Setting(const std::string& name, float value);
		Setting(const std::string& name, std::int8_t value);
		Setting(const std::string& name, std::int32_t value);
		Setting(const std::string& name, std::uint8_t value);
		Setting(const std::string& name, std::uint32_t value);

		[[nodiscard]] bool        IsManaged() const;
		[[nodiscard]] Type        GetType() const;
		[[nodiscard]] const char* GetName() const;

		// Member functions
		[[nodiscard]] bool          GetBool() const;
		[[nodiscard]] std::int8_t   GetCharacter() const;
		[[nodiscard]] float         GetFloat() const;
		[[nodiscard]] std::int32_t  GetInteger() const;
		[[nodiscard]] const char*   GetString() const;
		[[nodiscard]] std::uint8_t  GetUnsignedCharacter() const;
		[[nodiscard]] std::uint32_t GetUnsignedInteger() const;
		[[nodiscard]] std::uint32_t GetColor() const;
		[[nodiscard]] std::uint32_t GetColorA() const;

		void SetBool(bool value);
		void SetCharacter(std::int8_t value);
		void SetFloat(float value);
		void SetInteger(std::int32_t value);
		void SetString(const std::string& value);
		void SetUnsignedCharacter(std::uint8_t value);
		void SetUnsignedInteger(std::uint32_t value);
		void SetColor(std::uint32_t value);
		void SetColorA(std::uint32_t value);

		// Member variables
		Data data;  // 08

	private:
		char* name{ nullptr };  // 10
	};
	STATIC_ASSERT_SIZE(Setting, 0x18);
}
