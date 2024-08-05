#pragma once

namespace RE
{
	struct BGSNumericIDIndex
	{
	public:
		~BGSNumericIDIndex() noexcept {}  // intentional

		enum class Flags : std::uint8_t
		{
			kDefault = 1u << 6,  // idx 0x00
			kCreated = 1u << 7,  // idx 0xFF
		};

		[[nodiscard]] bool IsCreated() const noexcept { return flags.all(Flags::kCreated); }
		[[nodiscard]] bool IsDefault() const noexcept { return flags.all(Flags::kDefault); }

		[[nodiscard]] FormID GetNumericID() const
		{
			using func_t = decltype(&BGSNumericIDIndex::GetNumericID);
			static REL::Relocation<func_t> func{ RELOCATION_ID(35026, 35927) };
			return func(this);
		}
		void SetNumericID(FormID a_formID)
		{
			using func_t = decltype(&BGSNumericIDIndex::SetNumericID);
			static REL::Relocation<func_t> func{ RELOCATION_ID(35027, 35928) };
			return func(this, a_formID);
		}

		// members
		union
		{
			struct
			{
				union
				{
					std::uint8_t                          data1;
					stl::enumeration<Flags, std::uint8_t> flags;
				};                   // 0
				std::uint8_t data2;  // 1
				std::uint8_t data3;  // 2
			};
			std::uint8_t data[3]{ 0 };
		};  // 0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSNumericIDIndex) == 0x3);
}
