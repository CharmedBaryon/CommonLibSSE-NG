#pragma once

#include "RE/G/GFxLogBase.h"
#include "RE/G/GFxPlayerStats.h"
#include "RE/G/GNewOverrideBase.h"

namespace RE
{
	class GASGlobalContext;
	class GFxSprite;

	class GASStringContext
	{
	public:
		GASGlobalContext* globalContext;  // 00
		std::uint8_t      version;        // 08
		std::uint8_t      pad09[7];       // 09
		std::uint64_t     unk10;
		std::uint64_t     unk18;
		std::uint64_t     unk20;
		std::uint64_t     unk28;
	};
	static_assert(sizeof(GASStringContext) == 0x30);

	class GASEnvironment :
		public GFxLogBase<GASEnvironment>,                                       // 000
		public GNewOverrideBase<GFxStatMovieViews::kGFxStatMV_ActionScript_Mem>  // 008
	{
	public:
		~GASEnvironment() override;  // 00

		// override (GFxLogBase)
		bool IsVerboseActionErrors() const override;  // 01 - { return (sprite->GetMovieRoot()->flags & (1 << 6)) == 0; }

		// members
		void*             unk010;         // 010
		std::uint64_t     unk018;         // 018
		void*             unk020;         // 020
		void*             unk028;         // 028 - size is 0x408
		std::uint64_t     unk030;         // 030
		void*             unk038;         // 038
		void*             unk040;         // 040
		void*             unk048;         // 048
		std::uint64_t     unk050[19];     // 050
		GFxSprite*        sprite;         // 0E8
		GASGlobalContext* globalContext;  // 0F0 - struct
		std::uint8_t      version;        // 0F8
		std::uint8_t      pad0F9[7];      // 0F9
		std::uint64_t     pad100[20];     // 0A0
	private:
		KEEP_FOR_RE()
	};
#ifndef __INTELLISENSE__
	static_assert(sizeof(GASEnvironment) == 0x1A0);
#endif
}
