#pragma once

namespace RE
{
	class BGSChangeFlags
	{
	public:
		std::uint32_t flags;  // 0
	};
	static_assert(sizeof(BGSChangeFlags) == 0x4);

	class BGSUnloadedFormBuffer
	{
	public:
		void* unk0;  // 0
	};
	static_assert(sizeof(BGSUnloadedFormBuffer) == 0x8);

	class BGSFormChanges
	{
	public:
		BGSChangeFlags        changeFlags;         // 00
		std::uint32_t         pad04;               // 04
		BGSUnloadedFormBuffer unloadedFormBuffer;  // 08
	};
	static_assert(sizeof(BGSFormChanges) == 0x10);
}
