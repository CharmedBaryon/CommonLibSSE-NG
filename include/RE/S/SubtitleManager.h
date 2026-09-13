#pragma once

#include "RE/B/BSAtomic.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"

namespace RE
{
	struct SubtitleInfo
	{
		// members
		ObjectRefHandle speaker;         // 00
		std::uint32_t   pad04;           // 04
		BSString        subtitle;        // 08
		float           targetDistance;  // 18
		bool            forceDisplay;    // 1C
		std::uint8_t    pad1D;           // 1D
		std::uint16_t   pad1E;           // 1E
	};
	static_assert(sizeof(SubtitleInfo) == 0x20);

	class SubtitleManager : public BSTSingletonSDM<SubtitleManager>
	{
	public:
		static SubtitleManager* GetSingleton()
		{
			static REL::Relocation<SubtitleManager**> singleton{ RELOCATION_ID(514283, 400443) };
			return *singleton;
		}

		void KillSubtitles()
		{
			using func_t = decltype(&SubtitleManager ::KillSubtitles);
			static REL::Relocation<func_t> func{ RELOCATION_ID(51755, 52628) };
			return func(this);
		}

		// members
		std::uint8_t           pad01;           // 01
		std::uint16_t          pad02;           // 02
		std::uint32_t          pad04;           // 04
		BSTArray<SubtitleInfo> subtitles;       // 18
		mutable BSSpinLock     lock;            // 20
		ObjectRefHandle        currentSpeaker;  // 28
	};
	static_assert(sizeof(SubtitleManager) == 0x30);
}
