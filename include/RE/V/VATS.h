#pragma once

#include "RE/A/ActorValues.h"
#include "RE/B/BSAtomic.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/H/HitData.h"

namespace RE
{
	class Actor;
	class BGSCameraShot;
	class BSLight;
	class ExtraDataList;
	class ImageSpaceModifierInstanceRB;
	class TESBoundObject;

	class VATSCommand
	{
	public:
		std::uint32_t   actionPoints;  // 00 - 12
		std::uint8_t    unk04;         // 04
		std::uint8_t    unk05;         // 05
		std::uint8_t    unk06;         // 06
		std::uint8_t    unk07;         // 07
		std::uint8_t    unk08;         // 08
		std::uint8_t    unk09;         // 09
		std::uint16_t   unk0A;         // 0A
		ObjectRefHandle targetHandle;  // 0C
		ActorValue      bodyPartAV;    // 10
		std::uint32_t   pad14;         // 14
		HitData         hitData;       // 18
		std::uint64_t   unkA8;         // A8
		std::uint32_t   unkB0;         // B0
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(VATSCommand) == 0xB8);

	class VATS : public BSTSingletonSDM<VATS>
	{
	public:
		enum class VATS_MODE : std::uint32_t
		{
			kNone = 0,
			kKillCam = 4
		};

		[[nodiscard]] static VATS* GetSingleton()
		{
			REL::Relocation<VATS**> singleton{ RELOCATION_ID(514725, 400883) };
			return *singleton;
		}

		void SetMagicTimeSlowdown(float a_magicTimeSlowdown, float a_playerMagicTimeSlowdown)
		{
			using func_t = decltype(&VATS::SetMagicTimeSlowdown);
			static REL::Relocation<func_t> func{ RELOCATION_ID(43103, 44300) };
			return func(this, a_magicTimeSlowdown, a_playerMagicTimeSlowdown);
		}

		// members
		std::uint32_t                          pad00;                    // 00
		BSTArray<BSTSmartPointer<VATSCommand>> commandList;              // 08
		VATS_MODE                              VATSMode;                 // 20
		std::uint32_t                          pad24;                    // 24
		std::uint64_t                          unk28;                    // 28
		BGSCameraShot*                         cameraShot;               // 30
		float                                  safetyTime;               // 38
		float                                  cameraTime;               // 3C
		float                                  castingAfterKillDelay;    // 40
		std::uint32_t                          pad44;                    // 44
		std::uint64_t                          unk48;                    // 48
		std::uint64_t                          unk50;                    // 50
		std::uint64_t                          unk58;                    // 58
		ImageSpaceModifierInstanceRB*          unk60;                    // 60
		ImageSpaceModifierInstanceRB*          unk68;                    // 68
		NiPointer<BSLight>                     VATSLight;                // 70
		bool                                   unk78;                    // 78
		bool                                   unk79;                    // 79
		std::uint16_t                          pad7A;                    // 7A
		std::int32_t                           unk7C;                    // 7C
		float                                  magicTimeSlowdown;        // 80
		float                                  playerMagicTimeSlowdown;  // 84
		TESBoundObject*                        item;                     // 88
		ExtraDataList*                         extraList;                // 90
		NiPointer<Actor>                       target;                   // 98
		std::int32_t                           unkA0;                    // A0
		std::uint32_t                          padA4;                    // A4
		NiPointer<Actor>                       attacker;                 // A8
		NiPointer<Actor>                       unkB0;                    // B0 - stranger?
		mutable BSSpinLock                     lock;                     // B8
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(VATS) == 0xC0);
}
