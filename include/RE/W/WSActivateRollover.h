#pragma once

#ifdef ENABLE_SKYRIM_VR

#	include "RE/W/WorldSpaceMenu.h"

namespace RE
{
	class WSActivateRollover :
		public WorldSpaceMenu  // 40
	{
	public:
		inline static constexpr auto      RTTI = RTTI_WSActivateRollover;
		constexpr static std::string_view MENU_NAME = "WSActivateRollover";

		~WSActivateRollover() override;  // 00

		// override
		virtual UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 04
		virtual RE::NiNode*        GetMenuParentNode() override;                   // 0C
		virtual void               SetTransform() override;                        // 0D

		// members
		GFxValue*     unk58;  // 58
		std::uint32_t unk60;  // 60 - Flags of some kind?
		std::uint32_t unk64;  // 64 - padding?
		void*         unk68;  // 68
	private:
		KEEP_FOR_RE()
	};
#	if !defined(ENABLE_SKYRIM_VR)
	static_assert(sizeof(WSActivateRollover) == 0x68);
#	elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(WSActivateRollover) == 0x70);
#	else
	static_assert(sizeof(WSActivateRollover) == 0x58);
#	endif
}

#endif
