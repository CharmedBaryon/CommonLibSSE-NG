#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSString.h"
#include "RE/E/ExtraMapMarker.h"
#include "RE/H/HUDMessageTypes.h"
#include "RE/I/IUIMessageData.h"

namespace RE
{
	class TESQuest;
	class TESWordOfPower;

	class HUDData : public IUIMessageData
	{
	public:
		inline static constexpr auto             RTTI = RTTI_HUDData;
		inline static constexpr auto             VTABLE = VTABLE_HUDData;
		inline static constexpr std::string_view CLASS_NAME = "HUDData";

		~HUDData() override;  // 00

		static void GenerateHUDMessage(const char* a_mode, bool a_enable)
		{
			using func_t = decltype(&HUDData::GenerateHUDMessage);
			static REL::Relocation<func_t> func{ RELOCATION_ID(50747, 51642) };
			return func(a_mode, a_enable);
		}

		// members
		REX::EnumSet<HUD_MESSAGE_TYPE, std::uint32_t> type;          // 10
		std::uint32_t                                 pad14;         // 14
		BSString                                      text;          // 18
		ObjectRefHandle                               crosshairRef;  // 28
		std::uint32_t                                 pad2C;         // 2C
		TESQuest*                                     quest;         // 30
		TESWordOfPower*                               wordOfPower;   // 38
		bool                                          show;          // 40
		std::uint8_t                                  pad41;         // 41
		std::uint16_t                                 pad42;         // 42
		REX::EnumSet<MARKER_TYPE, std::uint32_t>      discovery;     // 44
	};
	static_assert(sizeof(HUDData) == 0x48);
}
