#pragma once

#include "RE/B/BGSSaveGameBuffer.h"

namespace RE
{
	class BGSSaveFormBuffer : public BGSSaveGameBuffer
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSSaveFormBuffer;
		inline static constexpr auto VTABLE = VTABLE_BGSSaveFormBuffer;

		virtual ~BGSSaveFormBuffer();

		// override (BGSSaveGameBuffer)
		TESForm*       GetForm() override;       // 01 - { return form; }
		TESObjectREFR* GetReference() override;  // 02
		Actor*         GetActor() override;      // 03

		// members
		std::uint64_t unk18;  // 18
		std::uint64_t unk20;  // 20
		TESForm*      form;   // 28
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BGSSaveFormBuffer) == 0x30);
}
