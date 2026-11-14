#pragma once

#include "RE/M/MemoryManager.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class NiAVObject;

	enum class SOUND_MSG
	{
		None = 0,
		Init = 1,
		Shutdown = 2,
		Play = 4,
		Pause = 5,
		UnPause = 6,
		Stop = 7,
		PlayAfter = 8,
		FadeIn = 10,
		FadeOut = 11,
		SetVolume = 13,
		SetFrequency = 14,
		SetFrequencyVariance = 15,
		VolumeChanged = 16,
		FadeTo = 18,
		SetPosition = 19,
		SetBeamEnd = 20,
		SetStaticAttenuation = 21,
		LoadForPlayback = 25,
		KillAll = 27,
		ReleaseSound = 28,
		RegisterMovingSound = 29,
		UnRegisterMovingSound = 30,
		StopMovingSoundOnTarget = 31,
		AddToCache = 38,
		SuspendAudioThread = 39,
		SetListenerPosition = 40,
		SetListenerFrontOrientation = 41,
		SetListenerTopOrientation = 42,
		SetOutputModel = 50,
	};

	class BSSoundMessage
	{
	public:
		TES_HEAP_REDEFINE_NEW();

		// members
		SOUND_MSG             message;   // 00
		std::uint32_t         id;        // 04
		std::int32_t          iData;     // 08
		std::byte             pad0C[4];  // 0C
		void*                 pData;     // 10
		NiPointer<NiAVObject> spData;    // 18
		union                            // 20
		{
			NiPoint3      vector3;
			std::uint16_t curveValue[5];
		};
		std::byte       pad2C[4];  // 2C
		BSSoundMessage* next;      // 30
		BSSoundMessage* prev;      // 38
	};
	static_assert(sizeof(BSSoundMessage) == 0x40);
}
