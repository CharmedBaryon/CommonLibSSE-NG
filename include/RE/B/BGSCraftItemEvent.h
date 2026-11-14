#pragma once

#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class BGSLocation;
	class TESForm;

	class BGSCraftItemEvent
	{
	public:
		[[nodiscard]] static std::int32_t& GetIndex()
		{
			static REL::Relocation<std::int32_t*> index{ RELOCATION_ID(508414, 380076) };
			return *index;
		}

		BGSCraftItemEvent(TESObjectREFR* a_workbench, BGSLocation* a_benchLocation, TESForm* a_createdObject) :
			workbench(BSPointerHandleManagerInterface<TESObjectREFR>::GetHandle(a_workbench)),
			benchLocation(a_benchLocation),
			createdObject(a_createdObject)
		{}

		// members
		ObjectRefHandle workbench;      // 00
		std::uint32_t   pad04;          // 04
		BGSLocation*    benchLocation;  // 08
		TESForm*        createdObject;  // 10
	};
	static_assert(sizeof(BGSCraftItemEvent) == 0x18);
}
