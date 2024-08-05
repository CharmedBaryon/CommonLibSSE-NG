#pragma once

namespace RE
{
	class TESForm;

	class BGSLoadFormData
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSLoadFormData;

		enum class Flags
		{
			kSkipForm = 1 << 0,
			kFormPending = 1 << 1,
			kRevertOnly = 1 << 2,
			kConstructedForm = 1 << 3,
			kCellChanged = 1 << 4,
			kLoadingPackageFromExtraData = 1 << 5
		};

		// members
		FormID                                 formID;            // 00
		std::uint32_t                          size;              // 04
		std::uint32_t                          uncompressedSize;  // 08
		std::uint32_t                          pad0C;             // 0C
		TESForm*                               form;              // 10
		std::uint32_t                          changeFlags;       // 18
		std::uint32_t                          oldChangeFlags;    // 1C
		stl::enumeration<Flags, std::uint32_t> flags;             // 20
		std::uint8_t                           pad22;             // 22
		std::uint8_t                           version;           // 23
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSLoadFormData) == 0x28);
}
