#pragma once

#include "RE/A/AITimeStamp.h"
#include "RE/B/BGSAnimationSequencer.h"
#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/B/BSTHashMap.h"
#include "RE/B/BSTList.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/B/BSTTuple.h"
#include "RE/M/Movement.h"
#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/P/PlayerCharacter.h"
#include "RE/T/TESShout.h"

namespace RE
{
	class ActorKnowledge;
	class BGSAttackData;
	class BGSProjectile;
	class DialogueItem;
	class IAnimationSetCallbackFunctor;
	class MagicItem;
	class NiBillboardNode;
	class NiAVObject;
	class NiPointLight;
	class NiRefObject;
	class TESObjectREFR;
	class TESObjectWEAP;
	class StandardDetectionListener;
	struct Crime;
	struct QueuedDialogueType;

	enum class VOICE_STATE
	{
		kNone = 0,
		kRequest = 1,
		kStart = 2,
		kContinue = 3,
		kPrecast = 4,
		kPostcast = 5,
		kFail = 6
	};

	struct DetectionEvent
	{
	public:
		// members
		std::uint32_t   actionValue;  // 00
		NiPoint3        location;     // 00
		AITimeStamp     timeStamp;    // 10
		ObjectRefHandle ref;          // 10
	};
	static_assert(sizeof(DetectionEvent) == 0x18);

	struct HighProcessData
	{
	public:
		enum class FADE_STATE
		{
			kNormal = 0,
			kIn = 1,
			kOut = 2,
			kTeleportIn = 3,
			kTeleportOut = 4,
			kOutDisable = 5,
			kOutDelete = 6
		};

		enum class BUMP_TYPE
		{
			kNone = static_cast<std::underlying_type_t<BUMP_TYPE>>(-1),
			kSmall = 0,
			kBig = 1
		};

		struct HEAD_TRACK_TYPES
		{
			enum HEAD_TRACK_TYPE : std::uint32_t
			{
				kDefault = 0,
				kAction,
				kScript,
				kCombat,
				kDialogue,
				kProcedure,

				kTotal = 6
			};
		};
		using HEAD_TRACK_TYPE = HEAD_TRACK_TYPES::HEAD_TRACK_TYPE;

		struct Data190 : public BSIntrusiveRefCounted
		{
		public:
			struct Data
			{
			public:
				struct UnkData
				{
					std::uint64_t unk00;  // 00
					std::uint64_t unk08;  // 08
					std::uint64_t unk10;  // 10
					std::uint64_t unk18;  // 18
					std::uint64_t unk20;  // 20
					std::uint64_t unk28;  // 28
					std::uint64_t unk30;  // 30
					std::uint64_t unk38;  // 38
					std::uint64_t unk40;  // 40
					std::uint64_t unk48;  // 48
					std::uint64_t unk50;  // 50
					std::uint64_t unk58;  // 58
					std::uint64_t unk60;  // 60
					std::uint64_t unk68;  // 68
					std::uint64_t unk70;  // 70
					std::uint64_t unk78;  // 78
				};
				static_assert(sizeof(UnkData) == 0x80);

				// members
				UnkData*      unk00;  // 00
				std::uint64_t unk08;  // 08
			};
			static_assert(sizeof(Data) == 0x10);

			// members
			std::uint32_t       unk04;  // 00
			BSTSmallArray<Data> unk08;  // 08
			std::uint64_t       unk28;  // 28
		};
		static_assert(sizeof(Data190) == 0x30);

		struct Data208
		{
		public:
			// members
			std::uint64_t unk00;  // 00
			std::uint64_t unk08;  // 08
			std::uint64_t unk10;  // 10
			std::uint64_t unk18;  // 18
			std::uint64_t unk20;  // 20
			std::uint64_t unk28;  // 28
			Data208*      next;   // 30
		};
		static_assert(sizeof(Data208) == 0x38);

		struct MuzzleFlash
		{
		public:
			// members
			bool                    unk00;                // 00
			bool                    unk01;                // 01
			bool                    unk02;                // 02
			bool                    unk03;                // 03
			float                   unk04;                // 04
			float                   muzzleFlashDuration;  // 08
			std::uint32_t           unk0C;                // 0C
			NiPointer<NiAVObject>   projectile3D;         // 10
			NiPointer<NiAVObject>   projectileNode;       // 18
			NiPointer<NiPointLight> attachedLight;        // 20
			BGSProjectile*          baseProjectile;       // 28
			TESObjectWEAP*          weaponSource;         // 30
			ActorHandle             shooterHandle;        // 38
			std::uint32_t           unk3C;                // 3C
		};
		static_assert(sizeof(MuzzleFlash) == 0x40);

		void ClearHeadtrackTarget(HEAD_TRACK_TYPE a_headtrackType, bool a_defaultHold)
		{
			using func_t = decltype(&HighProcessData::ClearHeadtrackTarget);
			REL::Relocation<func_t> func{ RELOCATION_ID(38726, 39756) };
			return func(this, a_headtrackType, a_defaultHold);
		}

		void SetHeadtrackTarget(HEAD_TRACK_TYPE a_headtrackType, TESObjectREFR* a_target)
		{
			using func_t = decltype(&HighProcessData::SetHeadtrackTarget);
			REL::Relocation<func_t> func{ RELOCATION_ID(38760, 39783) };
			return func(this, a_headtrackType, a_target);
		}

		// members
		stl::enumeration<VOICE_STATE, std::uint32_t>          voiceState;                                // 000
		std::uint32_t                                         pad004;                                    // 004
		TESShout*                                             currentShout;                              // 008
		TESShout::VariationID                                 currentShoutVariation;                     // 010
		float                                                 voiceTimeElapsed;                          // 014
		float                                                 voiceRecoveryTime;                         // 018
		float                                                 healthRegenDelay;                          // 01C
		float                                                 staminaRegenDelay;                         // 020
		float                                                 magickaRegenDelay;                         // 024
		float                                                 unk028;                                    // 028
		std::uint32_t                                         unk02C;                                    // 02C
		BSTArray<ActorHandle>                                 lastSpokenToArray;                         // 030
		std::uint64_t                                         unk048;                                    // 048
		BGSAnimationSequencer                                 animSequencer;                             // 050
		NiPoint3                                              pathingCurrentMovementSpeed;               // 088
		NiPoint3                                              pathingCurrentRotationSpeed;               // 094
		NiPoint3                                              pathingDesiredPosition;                    // 0A0
		NiPoint3                                              pathingDesiredOrientation;                 // 0AC
		NiPoint3                                              pathingDesiredMovementSpeed;               // 0B8
		NiPoint3                                              pathingDesiredRotationSpeed;               // 0C4
		std::uint32_t                                         unk0D0;                                    // 0D0
		float                                                 lastBumpDirection;                         // 0D4
		ObjectRefHandle                                       lastExtDoorActivated;                      // 0D8
		float                                                 activationHeight;                          // 0DC
		ActorHandle                                           reanimateCaster;                           // 0E0
		std::uint32_t                                         pad0E4;                                    // 0E4
		MagicItem*                                            reanimateSpell;                            // 0E8
		Movement::TypeData                                    currentMovementType;                       // 0F0
		stl::enumeration<FADE_STATE, std::uint32_t>           fadeState;                                 // 130
		float                                                 fadeAlpha;                                 // 134
		TESObjectREFR*                                        fadeTrigger;                               // 138
		ObjectRefHandle                                       headTrackTarget[HEAD_TRACK_TYPE::kTotal];  // 140
		bool                                                  headTracked[HEAD_TRACK_TYPE::kTotal];      // 158
		std::uint16_t                                         unk15E;                                    // 15E
		float                                                 headTrackTargetTimer;                      // 160
		NiPoint3                                              headTrackTargetOffset;                     // 164
		float                                                 headTrackHoldOffsetHoldTimer;              // 170
		float                                                 headTrackTargetOffsetTimer;                // 174
		ObjectRefHandle                                       lastTarget;                                // 178
		ObjectRefHandle                                       pathLookAtTarget;                          // 17C
		void*                                                 unk180;                                    // 180 - smart ptr
		void*                                                 unk188;                                    // 188 - smart ptr
		BSTSmartPointer<Data190>                              unk190;                                    // 190
		BSTSmartPointer<Data190>                              unk198;                                    // 198
		NiPoint3                                              unk1A0;                                    // 1A0
		std::uint32_t                                         unk1AC;                                    // 1AC
		std::uint64_t                                         unk1B0;                                    // 1B0
		std::uint64_t                                         unk1B8;                                    // 1B8
		std::uint64_t                                         unk1C0;                                    // 1C0
		std::uint64_t                                         unk1C8;                                    // 1C8
		std::uint64_t                                         unk1D0;                                    // 1D0
		std::uint64_t                                         unk1D8;                                    // 1D8
		float                                                 unk1E0;                                    // 1E0
		float                                                 cachedActorHeight;                         // 1E4
		NiPointer<NiRefObject>                                unk1E8;                                    // 1E8
		std::uint32_t                                         unk1F0;                                    // 1F0
		AITimeStamp                                           bumpTimer;                                 // 1F4
		AITimeStamp                                           unk1F8;                                    // 1F8
		BUMP_TYPE                                             bumpedState;                               // 1FC
		float                                                 takeBackTimer;                             // 200
		std::uint32_t                                         pad204;                                    // 204
		Data208*                                              unk208;                                    // 208
		std::uint32_t                                         unk210;                                    // 210
		PLAYER_ACTION                                         playerActionReaction;                      // 214
		BSFixedString                                         voiceSubtitle;                             // 218
		BSTArray<BSTTuple<FormID, NiPointer<ActorKnowledge>>> knowledgeArray;                            // 220
		mutable BSReadWriteLock                               knowledgeLock;                             // 238
		BSTArray<QueuedDialogueType*>                         queueofGreetings;                          // 240
		NiPointer<BGSAttackData>                              attackData;                                // 258
		NiPoint3                                              locationOffsetByWaterPoint;                // 260
		std::uint32_t                                         unk26C;                                    // 26C
		std::uint64_t                                         unk270;                                    // 270
		float                                                 unk278;                                    // 278
		NiPoint3                                              deathForceDirection;                       // 27C
		float                                                 deathForce;                                // 288
		float                                                 unk28C;                                    // 28C
		float                                                 unk290;                                    // 290
		float                                                 unk294;                                    // 294
		float                                                 unk298;                                    // 298
		float                                                 clearTalkToListTimer;                      // 29C
		float                                                 maxAlpha;                                  // 2A0
		float                                                 unk2A4;                                    // 2A4
		std::uint64_t                                         unk2A8;                                    // 2A8
		float                                                 checkToTalkTimer;                          // 2B0 - fAISocialTimerForConversationsMin
		std::uint32_t                                         unk2B4;                                    // 2B4
		std::uint64_t                                         unk2B8;                                    // 2B8
		std::uint64_t                                         unk2C0;                                    // 2C0
		std::uint64_t                                         unk2C8;                                    // 2C8
		std::uint64_t                                         unk2D0;                                    // 2D0
		std::uint32_t                                         animAction;                                // 2D8
		NiPoint3                                              leftWeaponLastPos;                         // 2DC
		NiPoint3                                              rightWeaponLastPos;                        // 2E8
		ObjectRefHandle                                       greetActor;                                // 2F4
		float                                                 soundDelay;                                // 2F8
		BSSoundHandle                                         soundHandles[2];                           // 2FC
		float                                                 greetingTimer;                             // 314
		float                                                 exclusiveTimer;                            // 318
		float                                                 idleTimer;                                 // 31C
		float                                                 detectGreetTimer;                          // 320
		float                                                 breathTimer;                               // 324
		float                                                 voiceTimer;                                // 328
		float                                                 dyingTimer;                                // 32C
		TESTopicInfo*                                         lastGreeting;                              // 330
		std::uint64_t                                         unk338;                                    // 338
		float                                                 awarePlayerTimer;                          // 340
		std::uint32_t                                         unk344;                                    // 344
		TESIdleForm*                                          currentProcessIdle;                        // 348
		RefHandle                                             unk350;                                    // 350
		std::uint32_t                                         unk354;                                    // 354
		std::uint64_t                                         unk358;                                    // 358
		BSTSmartPointer<DialogueItem>                         greetTopic;                                // 360
		std::uint32_t                                         unk368;                                    // 368
		RefHandle                                             unk36C;                                    // 36C
		void*                                                 unk370;                                    // 370
		std::uint64_t                                         unk378;                                    // 378
		NiPointer<NiBillboardNode>                            healthBarNode;                             // 380
		float                                                 unk388;                                    // 388
		std::uint32_t                                         unk38C;                                    // 38C
		std::uint32_t                                         numberGuardsPursuing;                      // 390
		float                                                 reEquipArmorTimer;                         // 394
		BSSimpleList<SpellItem*>*                             leveledSpellList;                          // 398
		float                                                 detectionModifier;                         // 3A0
		float                                                 detectionModifierTimer;                    // 3A4
		float                                                 lightLevel;                                // 3A8
		float                                                 sceneHeadTrackTimer;                       // 3AC
		float                                                 pCapVoiceFailsafeTimer;                    // 3B0
		std::uint32_t                                         pad3B4;                                    // 3B4
		void*                                                 unk3B8;                                    // 3B8
		std::uint64_t                                         unk3C0;                                    // 3C0
		MuzzleFlash*                                          muzzleFlash;                               // 3C8
		std::uint32_t                                         unk3D0;                                    // 3D0
		std::uint32_t                                         pad3D4;                                    // 3D4
		DetectionEvent*                                       actorsGeneratedDetectionEvent;             // 3D8
		NiPointer<StandardDetectionListener>                  detectionListener;                         // 3E0
		std::uint64_t                                         unk3E8;                                    // 3E8
		void*                                                 unk3F0;                                    // 3F0 - smart ptr
		std::uint64_t                                         unk3F8;                                    // 3F8
		BSTSmallArray<std::uint64_t>                          unk400;                                    // 400
		NiPoint3                                              animationDelta;                            // 418
		NiPoint3                                              animationAngleMod;                         // 424
		BSTSmartPointer<IAnimationSetCallbackFunctor>         unk430;                                    // 430
		float                                                 absorbTimer;                               // 438
		float                                                 unk43C;                                    // 43C
		Crime*                                                crimeToReactTo;                            // 440
		std::uint64_t                                         unk448;                                    // 448
		bool                                                  unk450;                                    // 450
		std::uint8_t                                          unk451;                                    // 451
		std::uint8_t                                          unk452;                                    // 452
		std::uint8_t                                          unk453;                                    // 453
		bool                                                  greetingPlayer;                            // 454
		std::uint8_t                                          unk455;                                    // 455
		std::uint8_t                                          unk456;                                    // 456
		bool                                                  detectAlert;                               // 457
		bool                                                  talkingToPC;                               // 458
		bool                                                  inCommandState;                            // 459
		std::uint8_t                                          unk45A;                                    // 45A
		std::uint8_t                                          unk45B;                                    // 45B
		std::uint8_t                                          unk45C;                                    // 45C
		std::uint8_t                                          unk45D;                                    // 45D
		std::uint8_t                                          unk45E;                                    // 45E
		bool                                                  isDualCasting;                             // 45F
		bool                                                  getPlantedExplosive;                       // 460
		bool                                                  approachingAutoTeleportDoor;               // 461
		bool                                                  arrested;                                  // 462
		bool                                                  unk463;                                    // 463
		bool                                                  unk464;                                    // 464
		bool                                                  unk465;                                    // 465
		bool                                                  unk466;                                    // 466
		bool                                                  unk467;                                    // 467
		bool                                                  farGeometry;                               // 468
		bool                                                  unk469;                                    // 469
		bool                                                  unk46A;                                    // 46A
		bool                                                  deathDialogue;                             // 46B
		bool                                                  fistsDrawn;                                // 46C
		bool                                                  unk46D;                                    // 46D
		bool                                                  unk46E;                                    // 46E
		bool                                                  unk46F;                                    // 46F
		bool                                                  doorActivated;                             // 470
		bool                                                  unk471;                                    // 471
		bool                                                  aggroRadiusStarted;                        // 472
		std::uint8_t                                          pad473;                                    // 473
		std::uint32_t                                         pad474;                                    // 474
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(HighProcessData) == 0x478);
}
