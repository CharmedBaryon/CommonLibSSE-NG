#pragma once

#include "RE/B/BSResourceHandle.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESImageSpaceModifiableForm.h"
#include "RE/T/TESModel.h"

namespace RE
{
	class TESObjectREFR;

	class BGSCameraShot :
		public TESForm,                     // 00
		public TESModel,                    // 20
		public TESImageSpaceModifiableForm  // 48
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSCameraShot;
		inline static constexpr auto VTABLE = VTABLE_BGSCameraShot;
		inline static constexpr auto FORMTYPE = FormType::CameraShot;

		enum class CAM_ACTION
		{
			kShoot = 0,
			kFly = 1,
			kHit = 2,
			kZoom = 3
		};

		enum class CAM_OBJECT
		{
			kAttacker = 0,
			kProjectile = 1,
			kTarget = 2,
			kLeadActor = 3
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct CAMERA_SHOT_DATA  // DATA
		{
		public:
			enum class Flag
			{
				kNone = 0,
				kPositionFollowsLocation = 1 << 0,
				kRotationFollowsTarget = 1 << 1,
				kDontFollowBone = 1 << 2,
				kFirstPersonCamera = 1 << 3,
				kNoTracer = 1 << 4,
				kStartAtTimeZero = 1 << 5
			};

			// members
			REX::EnumSet<CAM_ACTION, std::uint32_t> cameraAction;                // 00
			REX::EnumSet<CAM_OBJECT, std::uint32_t> location;                    // 04
			REX::EnumSet<CAM_OBJECT, std::uint32_t> target;                      // 08
			REX::EnumSet<Flag, std::uint32_t>       flags;                       // 0C
			float                                   playerTimeMult;              // 10
			float                                   targetTimeMult;              // 14
			float                                   globalTimeMult;              // 18
			float                                   maxTime;                     // 1C
			float                                   minTime;                     // 20
			float                                   targetPercentBetweenActors;  // 24
			float                                   nearTargetDistance;          // 28
		};
		static_assert(sizeof(CAMERA_SHOT_DATA) == 0x2C);

		~BGSCameraShot() override;  // 00

		// override (TESForm)
		void InitializeData() override;      // 04
		bool Load(TESFile* a_mod) override;  // 06
		void InitItemImpl() override;        // 13

		// False for CAM_ACTION::kZoom shots; otherwise requires a loaded model and a non-null cameraNode.
		bool IsValid()
		{
			using func_t = decltype(&BGSCameraShot::IsValid);
			static REL::Relocation<func_t> func{ RELOCATION_ID(20263, 20706) };
			return func(this);
		}

		// Releases locationNode/targetNode/cameraNode; called on camera-shot teardown.
		void ReleaseNodes()
		{
			using func_t = decltype(&BGSCameraShot::ReleaseNodes);
			static REL::Relocation<func_t> func{ RELOCATION_ID(20264, 20707) };
			return func(this);
		}

		// nullptr clears targetNode/targetFadeNode; otherwise creates a positional-snapshot proxy (or
		// follows a_node directly, per an internal flag) and caches the nearest fade-node ancestor.
		void SetTargetNode(NiNode* a_node)
		{
			using func_t = decltype(&BGSCameraShot::SetTargetNode);
			static REL::Relocation<func_t> func{ RELOCATION_ID(20266, 20709) };
			return func(this, a_node);
		}

		// Mirrors SetTargetNode, but for locationNode.
		void SetLocationNode(NiAVObject* a_node)
		{
			using func_t = decltype(&BGSCameraShot::SetLocationNode);
			static REL::Relocation<func_t> func{ RELOCATION_ID(20265, 20708) };
			return func(this, a_node);
		}

		// Starts the shot: requests the camera model, validates its NiCamera/interpolator, sets up
		// VATS dolly-timing state, and plays the transition sound.
		void Play(TESObjectREFR* a_target, std::int32_t a_mode)
		{
			using func_t = decltype(&BGSCameraShot::Play);
			static REL::Relocation<func_t> func{ RELOCATION_ID(20262, 20705) };
			return func(this, a_target, a_mode);
		}

		// Per-frame position/frustum tick.
		void Update(float a_currentTime)
		{
			using func_t = decltype(&BGSCameraShot::Update);
			static REL::Relocation<func_t> func{ RELOCATION_ID(20267, 20710) };
			return func(this, a_currentTime);
		}

		// members
		CAMERA_SHOT_DATA      data;            // 58 - DATA
		std::uint32_t         pad84;           // 84
		NiAVObject*           locationNode;    // 88
		NiAVObject*           targetNode;      // 90
		RefHandle             unk98;           // 98
		std::uint32_t         unk9C;           // 9C
		NiPointer<NiNode>     cameraNode;      // A0 - smart ptr
		NiPointer<NiAVObject> targetFadeNode;  // A8 - smart ptr; nearest fade-capable ancestor node of targetNode
		std::uint8_t          unkB0;           // B0
		bool                  unkB1;           // B1
		std::uint16_t         padB2;           // B2
		std::uint32_t         padB4;           // B4
		ModelDBHandle         cameraHandle;    // B8
	};
	static_assert(sizeof(BGSCameraShot) == 0xC0);
}
