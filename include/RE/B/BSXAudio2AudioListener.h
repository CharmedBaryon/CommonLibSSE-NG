#pragma once

#include "RE/B/BSAudioListener.h"

namespace RE
{
	class BSXAudio2AudioListener : public BSAudioListener
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSXAudio2AudioListener;

		~BSXAudio2AudioListener() override;  // 00

		// override (BSAudioListener)
		void Unk_01(void) override;  // 01
		void Unk_02(void) override;  // 02
		void Unk_04(void) override;  // 04

		// add
		virtual void Unk_06(void);  // 06

		// members
		std::uint64_t unk40;  // 40
		std::uint64_t unk48;  // 48
		std::uint64_t unk50;  // 50
		std::uint64_t unk58;  // 58
		std::uint64_t unk60;  // 60
		std::uint64_t unk68;  // 68
		std::uint64_t unk70;  // 70
	};
	static_assert(sizeof(BSXAudio2AudioListener) == 0x78);
}
