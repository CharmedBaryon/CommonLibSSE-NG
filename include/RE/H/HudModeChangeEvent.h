#pragma once

#ifdef ENABLE_SKYRIM_VR
namespace RE
{
	class HudModeChangeEvent
	{
	private:
		KEEP_FOR_RE()
	};

	// TODO: Name not fully accurate, needs REing to determine usage for this
	class HudMoveChangeEventSource : public BSTEventSource<HudModeChangeEvent>
	{
	public:
		HudMoveChangeEventSource* GetSingleton();  // TODO: Add singleton

		// members
		std::uint64_t unk58;      // 58
		std::uint64_t unk60;      // 60
		std::uint64_t unk68;      // 68
		std::uint32_t unk6C;      // 6C - set to 32
		std::uint32_t unk70;      // 70 - set to 32
		std::uint32_t unk74;      // 74 - set to 32
		void*         unk78;      // 78 - set to SkyrimVR.exe+0x1EAAB34
		std::uint64_t unk80;      // 80
		void*         unk88;      // 88 - points to allocated array of size 32, each member 0x18 size it seems
		std::uint64_t unk90[10];  // 90
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(HudMoveChangeEventSource) == 0xE8);  // Unconfirmed, highest seen so far
}
#endif
