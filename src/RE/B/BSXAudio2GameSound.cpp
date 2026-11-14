#include "RE/B/BSXAudio2GameSound.h"

namespace RE
{
	BSXAudio2Audio* BSXAudio2GameSound::GetAudioImplementation()
	{
		static REL::Relocation<BSXAudio2Audio**> audioImplementation{ RELOCATION_ID(523613, 410149) };
		return *audioImplementation;
	}

	void BSXAudio2GameSound::SetAudioImplementation(BSXAudio2Audio* a_impl)
	{
		static REL::Relocation<BSXAudio2Audio**> audioImplementation{ RELOCATION_ID(523613, 410149) };
		*audioImplementation = a_impl;
	}

	void BSXAudio2GameSound::SeekInSamples(std::uint32_t a_samples)
	{
		using func_t = decltype(&BSXAudio2GameSound::SeekInSamples);
		static REL::Relocation<func_t> func{ RELOCATION_ID(66772, 68013) };
		return func(this, a_samples);
	}
}
