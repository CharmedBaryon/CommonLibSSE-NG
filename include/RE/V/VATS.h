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
	class PlayerCharacter;
	class Projectile;
	class TESBoundObject;

	// Opaque node in VATS::cameraShotQueue's singly-linked list; layout unknown.
	struct VATSCameraShotQueueNode;

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
	};
	static_assert(sizeof(VATSCommand) == 0xB8);

	class VATS : public BSTSingletonSDM<VATS>
	{
	public:
		// SetMode also handles values 2 and 3 identically; no caller reaches either, so they're
		// intentionally omitted rather than guessed.
		enum class VATS_MODE : std::uint32_t
		{
			kNone = 0,
			kKillCam = 4
		};

		[[nodiscard]] static VATS* GetSingleton()
		{
			static REL::Relocation<VATS**> singleton{ RELOCATION_ID(514725, 400883) };
			return *singleton;
		}

		void SetMagicTimeSlowdown(float a_magicTimeSlowdown, float a_playerMagicTimeSlowdown)
		{
			using func_t = decltype(&VATS::SetMagicTimeSlowdown);
			static REL::Relocation<func_t> func{ RELOCATION_ID(43103, 44300) };
			return func(this, a_magicTimeSlowdown, a_playerMagicTimeSlowdown);
		}

		// Mode-transition function: performs full enter/exit side effects (teardown on kNone,
		// kill-cam setup on kKillCam) before setting `mode`.
		void SetMode(VATS_MODE a_mode)
		{
			using func_t = decltype(&VATS::SetMode);
			static REL::Relocation<func_t> func{ RELOCATION_ID(43087, 44282) };
			return func(this, a_mode);
		}

		// Allocates a VATSCommand, appends it to commandList, and calls SetMode(kKillCam).
		void QueueCommand()
		{
			using func_t = decltype(&VATS::QueueCommand);
			static REL::Relocation<func_t> func{ RELOCATION_ID(43090, 44285) };
			return func(this);
		}

		// Pops the front of commandList once it finishes playing, or fully clears it and restores
		// the global time multiplier when a_hasMoreCommands is false.
		void AdvanceCommand(bool a_arg1, bool a_hasMoreCommands, bool a_arg3)
		{
			using func_t = decltype(&VATS::AdvanceCommand);
			static REL::Relocation<func_t> func{ RELOCATION_ID(43094, 44289) };
			return func(this, a_arg1, a_hasMoreCommands, a_arg3);
		}

		// Per-frame kill-cam update; no-ops unless mode == kKillCam.
		void UpdateKillCam(PlayerCharacter* a_player, void* a_arg2, std::uint32_t* a_arg3)
		{
			using func_t = decltype(&VATS::UpdateKillCam);
			static REL::Relocation<func_t> func{ RELOCATION_ID(43098, 44295) };
			return func(this, a_player, a_arg2, a_arg3);
		}

		// members
		std::uint32_t                          pad00;                    // 00
		BSTArray<BSTSmartPointer<VATSCommand>> commandList;              // 08
		VATS_MODE                              mode;                     // 20
		std::uint32_t                          pad24;                    // 24
		VATSCameraShotQueueNode*               cameraShotQueue;          // 28 - singly-linked list of pending BGSCameraShot nodes; advanced when cameraTime elapses
		BGSCameraShot*                         cameraShot;               // 30
		float                                  safetyTime;               // 38
		float                                  cameraTime;               // 3C
		float                                  castingAfterKillDelay;    // 40
		std::uint32_t                          pad44;                    // 44
		Projectile*                            killProjectile;           // 48 - camera location/target node fallback when cameraShot lacks one
		Projectile*                            killProjectile2;          // 50 - checked when killProjectile is null
		std::uint64_t                          unk58;                    // 58
		ImageSpaceModifierInstanceRB*          unk60;                    // 60
		ImageSpaceModifierInstanceRB*          unk68;                    // 68
		NiPointer<BSLight>                     VATSLight;                // 70
		bool                                   killCamActive;            // 78 - set true entering kKillCam; redundant with mode in what's decompiled so far
		bool                                   killCamInitialized;       // 79 - false entering kKillCam, latched true after UpdateKillCam's first-frame setup
		std::uint16_t                          pad7A;                    // 7A
		std::int32_t                           pendingCameraTransition;  // 7C - reset to 0 alongside camera-transition setup on kKillCam entry
		float                                  magicTimeSlowdown;        // 80
		float                                  playerMagicTimeSlowdown;  // 84
		TESBoundObject*                        item;                     // 88
		ExtraDataList*                         extraList;                // 90
		NiPointer<Actor>                       target;                   // 98
		std::int32_t                           unkA0;                    // A0
		std::uint32_t                          padA4;                    // A4
		NiPointer<Actor>                       attacker;                 // A8
		NiPointer<Actor>                       stranger;                 // B0
		mutable BSSpinLock                     lock;                     // B8
	};
	static_assert(sizeof(VATS) == 0xC0);
}
